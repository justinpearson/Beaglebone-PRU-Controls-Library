//#include <unistd.h> // for unsigned int sleep(unsigned int seconds);
#include "jpp-pru-lib.h"

#include <math.h> // M_PI
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


// To get usleep:
#define _POSIX_C_SOURCE199309L  // dammit, weird posix stuff. usleep specified in some versions of posix, not in others, and it's obsolete in favor of nanosleep, which takes shitty timespec arguments.
// warning: implicit declaration of function ‘usleep’ [-Wimplicit-function-declaration]
// see https://ubuntuforums.org/showthread.php?t=1146543
// note: changing to nanosleep not a great option
#include <time.h> // usleep, clock_gettime



#include <prussdrv.h>
#include <pruss_intc_mapping.h>

// jpp-pru-lib.c:419:4: error: implicit declaration of function ‘min’ [-Werror=implicit-function-declaration]
// http://stackoverflow.com/questions/20980815/implicit-declaration-of-function-min
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif



// Important memory locations
// These should be available to all functions here, but not to 
// functions outside of this file.
unsigned int* ctrladdr_CPU_wants_data;
unsigned int* ctrladdr_PRU_data_ready;
unsigned int* ctrladdr_CPU_new_sched ;
unsigned int* ctrladdr_PRU_ack_sched ;

unsigned int*  ctrladdr_CPU_new_period    ;
unsigned int*  ctrladdr_SAMPLE_PERIOD_CMD ;
unsigned int*  ctrladdr_SAMPLE_NUM_LOCK   ;
unsigned int*  ctrladdr_SAMPLE_NUM        ;


unsigned int* addr_cpu_data_buf;
unsigned int* addr_pru_data_buf;
unsigned int* addr_cpu_cmd_buf ;
unsigned int* addr_pru_cmd_buf ;



void start_pru( ) {

  // Disable buffering on stdout (why?)
  //http://stackoverflow.com/questions/1716296/why-does-printf-not-flush-after-the-call-unless-a-newline-is-in-the-format-strin
  // Edit: From Andy Ross's comment below, you can also disable buffering on stdout by using setbuf:
setbuf(stdout, NULL);


  printf("Welcome to the Beaglebone PRU library for real-time controls!\n");

   if(getuid()!=0){
      printf("You must run this program as root. Exiting.\n");
      exit(EXIT_FAILURE);
   }


  printf("NOTE: if you get a seg fault, make sure the jppprugpio device tree overlay has been loaded!!\n");
  printf("Here's the cmd: root@beaglebone# echo jppprugpio > /sys/devices/bone_capemgr.9/slots\n");
  printf("Assumes you have jppprugpio-00A0.dto in /lib/firmware\n");

  printf("Also do this:\n");
  printf("echo bone_eqep1 > $SLOTS\n");



  // Initialize structure used by prussdrv_pruintc_intc
  // PRUSS_INTC_INITDATA is found in pruss_intc_mapping.h
  tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

  // Allocate and initialize memory
  printf("prussdrv_init() (returned %d)\n",
	 prussdrv_init());
  
  printf("prussdrv_open (returned %d)\n",
	   prussdrv_open(PRU_EVTOUT_0));

  // Map PRU's interrupts
  printf("prussdrv_pruintc_init (returned %d)\n",
	 prussdrv_pruintc_init(&pruss_intc_initdata));

  // Get pointer to PRU0's data ram
  void *pru0DataMemory;
  unsigned int *pru0DataMemory_int;

  printf("pruss_map_prumem (returned %d)\n",
	 prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, &pru0DataMemory));

  pru0DataMemory_int = (unsigned int *) pru0DataMemory;
  printf("pru0 data memory addr: %p\n",(void*)pru0DataMemory_int);

  ////////////////////////////////////////////////////
  // set up various buffers

  ctrladdr_CPU_wants_data    =  pru0DataMemory_int+0;
  ctrladdr_PRU_data_ready    =  pru0DataMemory_int+1;
  ctrladdr_CPU_new_sched     =  pru0DataMemory_int+2;
  ctrladdr_PRU_ack_sched     =  pru0DataMemory_int+3;
  ctrladdr_CPU_new_period    =  pru0DataMemory_int+4;
  ctrladdr_SAMPLE_PERIOD_CMD =  pru0DataMemory_int+5;
  ctrladdr_SAMPLE_NUM_LOCK   =  pru0DataMemory_int+6;
  ctrladdr_SAMPLE_NUM        =  pru0DataMemory_int+7;

  addr_cpu_data_buf = pru0DataMemory_int + INTS_IN_CPU_PRU_CTRL_REG;
  addr_pru_data_buf = addr_cpu_data_buf  + INTS_PER_DATA_BUFFER;
  addr_cpu_cmd_buf  = addr_pru_data_buf  + INTS_PER_DATA_BUFFER;
  addr_pru_cmd_buf  = addr_cpu_cmd_buf   + INTS_PER_CMD_BUFFER; 

  printf(" ctrladdr_CPU_wants_data : %p\n",(void*)ctrladdr_CPU_wants_data);
  printf(" ctrladdr_PRU_data_ready : %p\n",(void*) ctrladdr_PRU_data_ready );
  printf(" ctrladdr_CPU_new_sched  : %p\n",(void*) ctrladdr_CPU_new_sched  );
  printf(" ctrladdr_PRU_ack_sched  : %p\n",(void*) ctrladdr_PRU_ack_sched  );

  printf(" ctrladdr_CPU_new_period    : %p\n",(void*) ctrladdr_CPU_new_period);
  printf(" ctrladdr_SAMPLE_PERIOD_CMD : %p\n",(void*) ctrladdr_SAMPLE_PERIOD_CMD );
  printf(" ctrladdr_SAMPLE_NUM_LOCK   : %p\n",(void*) ctrladdr_SAMPLE_NUM_LOCK  );
  printf(" ctrladdr_SAMPLE_NUM        : %p\n",(void*) ctrladdr_SAMPLE_NUM  );



  printf(" addr_cpu_data_buf : %p\n",(void*) addr_cpu_data_buf );
  printf(" addr_pru_data_buf : %p\n",(void*) addr_pru_data_buf );
  printf(" addr_cpu_cmd_buf  : %p\n",(void*) addr_cpu_cmd_buf  );
  printf(" addr_pru_cmd_buf  : %p\n",(void*) addr_pru_cmd_buf  );


  // set all the addrs in the pru data ram to something we'll recognize.
  unsigned int* addr = pru0DataMemory_int;

  // Wipe out cpu/pru ctrl regs
  for( int i=0; i<INTS_IN_CPU_PRU_CTRL_REG; i++ ) {
    *(addr++) = 0;
  }

  // CAREFUL:  we assume the buffers start right after the ctrl register.

  // Wipe out cpu data buf (cdb = "cpu data buffer")
  for( int i=0; i<INTS_PER_DATA_BUFFER; i++ ) {
    *(addr++) = 0xcdb0cdb0;
  }

  // Wipe out pru data buf (p=16th letter)
  for( int i=0; i<INTS_PER_DATA_BUFFER; i++ ) {
    *(addr++) = 0x16db16db;
  }

  // Wipe out cpu cmd buf 
  for( int i=0; i<INTS_PER_CMD_BUFFER; i++ ) {
    *(addr++) = 0xccb0ccb0;
  }
  // Wipe out pru cmd buf (p=16th letter)
  for( int i=0; i<INTS_PER_CMD_BUFFER; i++ ) {
    *(addr++) = 0x16cb16cb;
  }

  //  printf("About to start PRU, time=\n");
  //  toc();

  // Load and execute the PRU program on the PRU
  const char* binname =  "./jpp-pru-lib.bin";
  printf("executing bin file: %s\n",binname);
  printf("NOTE: a lot of stuff assumes PRU0 in this lib, sry.\n");
  int which_pru = 0;

#if 1
  printf("prussdrv_exec_program returned %d\n",
	 prussdrv_exec_program (which_pru, binname) );
#else
  printf("NOT STARTING PRU %d -- ARE YOU STARTING IT YOURSELF OR SOMETHING??\n",which_pru);
#endif
  printf("Waiting 1000ms to let PRU fill its internal buffer...");
  usleep(1000000); 
  printf("done.\n");

}


unsigned int get_sample_num() {
  *(ctrladdr_SAMPLE_NUM_LOCK) = 1;        // lock
  unsigned int sn = *ctrladdr_SAMPLE_NUM; // get
  *(ctrladdr_SAMPLE_NUM_LOCK) = 0;        // unlock
  return sn;
}

void set_PRU_sample_period(unsigned int period){ 
  *ctrladdr_SAMPLE_PERIOD_CMD = period;
  *ctrladdr_CPU_new_period = 1;
  while( !(*(ctrladdr_CPU_new_period) == 0) ) {  // Spin until PRU acks by setting to 0
    usleep(1);
  }
}

void check_initted() {
  if( ctrladdr_CPU_wants_data ==  NULL 
      || ctrladdr_PRU_data_ready == NULL 
      || ctrladdr_CPU_new_sched == NULL 
      || ctrladdr_PRU_ack_sched == NULL ) {
    printf("Hey idiot, ctrladdr_CPU_wants_data (or friends) is NULL so you probably didn't run start_pru(). Exiting.\n");
    exit(EXIT_FAILURE);
  }
}



void get_data_cmd_bufs( DataBuffer* pdb, CommandBuffer* pcb ) {
  check_initted();
  *(ctrladdr_CPU_wants_data) = 1;  // Set "CPU wants" bit
  while( !(*(ctrladdr_PRU_data_ready) == 1) ) {  // Spin until "data ready" bit
    usleep(1);
  }
  memcpy((void*)pdb, (void*)addr_cpu_data_buf, BYTES_PER_DATA_BUFFER );
  memcpy((void*)pcb, (void*)addr_cpu_cmd_buf, BYTES_PER_CMD_BUFFER );
  // Clear "CPU wants" bit and "Data ready" bits, just for good measure.
  *(ctrladdr_CPU_wants_data) =  0;
  *(ctrladdr_PRU_data_ready) =  0;
}

void get_data_buf( DataBuffer* pdb ) {

  //  printf("pru data ready: %x\n",*(ctrladdr_PRU_data_ready));

  check_initted();

  *(ctrladdr_CPU_wants_data) = 1;  // Set "CPU wants" bit

  //  printf("Waiting for \"Data ready\" bit...\n");
  while( !(*(ctrladdr_PRU_data_ready) == 1) ) {  // Spin until "data ready" bit
    usleep(1);
  }
  //  printf("Got it! Time:\n");
  //  printf("pru data ready: %x\n",*(ctrladdr_PRU_data_ready));
  //toc();

  /* unsigned int* addr = addr_cpu_data_buf;  // Copy buf into local array. */
  /* for( int i=0; i<PKTS_PER_DATA_BUFFER; i++ ) { */
  /*   for( int j=0; j<INTS_PER_DATA_PKT; j++ ) { */
  /*     pdb[i][j] = *(addr++); */
  /*   } */
  /* } */

  memcpy((void*)pdb, (void*)addr_cpu_data_buf, BYTES_PER_DATA_BUFFER );

  // Clear "CPU wants" bit and "Data ready" bits, just for good measure.
  *(ctrladdr_CPU_wants_data) =  0;
  *(ctrladdr_PRU_data_ready) =  0;
}


void set_cmd_buf( CommandBuffer cb ) {


  //     printf("Copying cmd to PRU data ram, time=\n");
  //     toc();

  // Copy actuation schedule into PRU data ram.
  /* unsigned int* addr = addr_cpu_cmd_buf; */
  /* for( int i=0; i<num_pkts*INTS_PER_CMD_PKT; i++ ) { */
  /* 	 *(addr++) = CMDS[i]; */
  /* } */
  /* printf("Done copying, time=\n"); */
  /* toc(); */

  check_initted();


  //  memcpy((void*)addr_cpu_cmd_buf, (void*)&cb, BYTES_PER_CMD_BUFFER);
  // dammit bug in here -- memcpy copies it somewhere weird. copy by hand:

  unsigned int* addr = addr_cpu_cmd_buf;
  for( int i=0; i<PKTS_PER_CMD_BUFFER; i++ ) {
    *(addr++) = cb[i].cycle_count;
    *(addr++) = cb[i].sample_num;
    *(addr++) = cb[i].gpio;
    *(addr++) = cb[i].duty;
  }


  // Tell the PRU we've got a new schedule.
  *ctrladdr_CPU_new_sched  = PKTS_PER_CMD_BUFFER;

  // Spin until the PRU says he copied it over
  //     printf("Waiting until pru says he copied over the new schedule...time=\n");
  //     toc();
  while( *ctrladdr_PRU_ack_sched  != 1 ) {
    usleep(1);
  }
  //     printf("He got it! time=\n");
  //   toc();

  // Clear "CPU new sch" bit and "PRU ack sch" bits, just for good measure.
  *ctrladdr_CPU_new_sched = 0;
  *ctrladdr_PRU_ack_sched = 0;
}



void fprintf_data_pkt( const DataPacket p, FILE* fp ) {
  fprintf(fp, "cycle: %u sample: %d adc: %d eqep: %d gpio: %x duty: %d last-data-req: %u last-cmd: %u",
	 p.cycle_count,
	 p.sample_num,
	 p.adc,
	 p.eqep,
	 p.gpio,
	 p.duty,
	 p.last_data_req,
	 p.last_cmd_sch
	 );
}

void fprintf_data_buf( const DataBuffer b, FILE* fp ) {
  for( int i=0; i<PKTS_PER_DATA_BUFFER; i++ ) {
    fprintf_data_pkt( b[i], fp );
  }
}


void print_data_pkt( const DataPacket p ) {
  printf("cycle: %10u sample: %6d adc: %5d eqep: %5d gpio: %4u duty: %5u last-data-req: %10u last-cmd: %10u\n",
	 p.cycle_count,
	 p.sample_num,
	 p.adc,
	 p.eqep,
	 p.gpio,
	 p.duty,
	 p.last_data_req,
	 p.last_cmd_sch
	 );
}

void print_data_buf( const DataBuffer b ) {
  for( int i=0; i<PKTS_PER_DATA_BUFFER; i++ ) {
    print_data_pkt( b[i] );
  }
}



void fprintf_cmd_pkt( const CommandPacket p, FILE* fp ) {
  fprintf(fp, "cycle: %u sample: %d gpio: %x duty: %d",
	 p.cycle_count,
	 p.sample_num,
	 p.gpio,
	 p.duty
	 );
}

void fprintf_cmd_buf( const CommandBuffer b, FILE* fp ) {
  for( int i=0; i<PKTS_PER_CMD_BUFFER; i++ ) {
    fprintf_cmd_pkt( b[i], fp );
  }
}





void print_cmd_pkt( const CommandPacket p ) {
  printf("cycle: %10u sample: %6d gpio: %4u duty: %5u\n",
	 p.cycle_count,
	 p.sample_num,
	 p.gpio,
	 p.duty
	 );
}

void print_cmd_buf( const CommandBuffer b ) {
  for( int i=0; i<PKTS_PER_CMD_BUFFER; i++ ) {
    print_cmd_pkt( b[i] );
  }
}







void make_cmd_buf_from_gpio( CommandBuffer* pb, unsigned int gpio ) {
  for( int i=0; i<PKTS_PER_CMD_BUFFER; i++ ) {
    (*pb)[i].cycle_count = 0x11111111;
    (*pb)[i].sample_num  = 0x22222222;
    (*pb)[i].gpio        = gpio;
    (*pb)[i].duty        = _100MHZ_TICKS_PER_PWM_PERIOD; // 100% duty
  }
}


void make_const_cmd_buf_from_raw( CommandBuffer* pb, 
		   unsigned int cycle_count, 
		   unsigned int sample_num,
		   unsigned int gpio,
		   unsigned int duty ) {
  for( int i=0; i<PKTS_PER_CMD_BUFFER; i++ ) {
    (*pb)[i].cycle_count = cycle_count;
    (*pb)[i].sample_num  = sample_num;
    (*pb)[i].gpio        = gpio;
    (*pb)[i].duty        = duty;
  }
}


void make_const_cmd_buf( CommandBuffer* pb, 
			 unsigned int cycle_count, 
			 unsigned int sample_num,
			 MotorState mstate,
			 double duty ) {

  unsigned int gpio = motor_state_to_gpio(mstate);
  unsigned int dutyticks = duty_to_dutyticks(duty);

  for( int i=0; i<PKTS_PER_CMD_BUFFER; i++ ) {
    (*pb)[i].cycle_count = cycle_count;
    (*pb)[i].sample_num  = sample_num;
    (*pb)[i].gpio        = gpio;
    (*pb)[i].duty        = dutyticks;
  }
}

unsigned int duty_to_dutyticks( double duty ) {
  return( round(duty / 100.0 * _100MHZ_TICKS_PER_PWM_PERIOD) );
}

double dutyticks_to_duty( unsigned int dutyticks ) {
  return( (double)dutyticks / _100MHZ_TICKS_PER_PWM_PERIOD * 100.0);
}

unsigned int motor_state_to_gpio( MotorState mstate ) {
  unsigned int gpio;
  switch( mstate ) {
  case MOTOR_STBY  : gpio = GPIO_STBY;  break;
  case MOTOR_BRAKE : gpio = GPIO_BRAKE; break;
  case MOTOR_CW    : gpio = GPIO_CW;    break;
  case MOTOR_CCW   : gpio = GPIO_CCW;   break;
  }
  return( gpio );
}

MotorState gpio_to_motor_state( unsigned int gpio ) {
  MotorState mstate;
  switch( gpio ) {
  case GPIO_STBY  : mstate = MOTOR_STBY;  break;
  case GPIO_BRAKE : mstate = MOTOR_BRAKE; break;
  case GPIO_CW    : mstate = MOTOR_CW;    break;
  case GPIO_CCW   : mstate = MOTOR_CCW;   break;
  }
  return( mstate );
}


double adc_to_amps( unsigned int raw_adc ) {
  // raw_adc is 0 to 4095.
  // From 'raw' adc counts to [0,1] (which is what I calibrated our current with, instead of volts, was 
  //easiest thing to do at the time):                                                                          
  //  double normalized_adc = raw_adc / 4096.0;

  // From 'noramlized adc' to current (amps)                                                             
  // See (MPC MHE DC motor project dropbox):/Dropbox/DC_motor/Notes/notes.md                             
  // plot                                                                                                
  // ![](Images/2016-07-06-14-40-17.png "Optional title")                                                
  // amps = 7.48 - 14.778 * adc_from_0_to_1                                                              
  //july 6: double amps = 7.48 - 14.778 * normalized_adc;                                                
  // july 22:                                                                                            
  //    double amps = 7.901 - 15.0682 * normalized_adc;                                                  
  // july 27:                                                                                            
  //  double volts = 1.8 * normalized_adc;
  //  double amps = 2.73454 - 3.03192 * volts; // hall-effect sensor 2 (w/ no filter capacitor)              

  // sep 7: see readme in /03-pru-ctrls-lib-tests/
  //  double amps = 2.602966952391388 + (-0.001338358981292) * raw_adc;
  // sep 8: why does the cal change so much??
  double amps = 3.141145598851507 + (-0.001818136024909) * raw_adc;

  return amps;
}



double eqep_to_angle( unsigned int eqep )  {

  // read eqep encoder of motor shaft                                                                    

  //    printf("Shaft: %d\n", eqep1.get_position());                                                       

  // returns "# of stripes observed on the encoder"                                                        
  // - There are 4096 stripes per revolution.                                                              
  // - we also need to wrap the angle to -pi to pi.                                                        

  //  return wrapMinMax( eqep / 4096.0, -M_PI, M_PI );
  // some weird wrapping problem around 0 eqep.
  // Note: if you uncomment this wrapMinMax, you'll need to #include util-jpp.h

  // eqep is an unsigned int, so when it goes negative, it wraps to 4 billion.
  // Converting it to an int uses 2's complement and correctly converts it to negative int.
  // Then you can cast it to a double. 
  // DO NOT cast to a double without first converting it to negative w/ 2's complement --
  // you'll get a double 4 billion insteadd of a negative number.
  int eqep_int = eqep;
  return -(double)eqep_int/4096.0*2.0*M_PI; // (eqep lines) * (1 rev / 4096 lines) * (2 pi rad / rev)

}


void gpio_duty_to_motor_voltage_cmd( unsigned int gpio,
				     unsigned int duty,
				     const double MAX_MOTOR_VOLTAGE,
				     double* pVm ) {
  double v = 0;
  double direction;
  if( gpio == GPIO_STBY || gpio == GPIO_BRAKE ) {
    v = 0;
    direction = 0;
  } else {
    v = (double)duty / _100MHZ_TICKS_PER_PWM_PERIOD * MAX_MOTOR_VOLTAGE;
    if( gpio == GPIO_CW ) {
      direction = 1.0;
    } else if( gpio == GPIO_CCW ) {
      direction = -1.0;
    } else {
      v = 9999;
      direction = 1;
      printf("%s %s (%d): Uh oh! GPIOs weren't what I expected! (%d didn't match stby %u brake %u cw %u ccw %u) \n",
	     __FILE__,__FUNCTION__,__LINE__, gpio, GPIO_STBY, GPIO_BRAKE, GPIO_CW, GPIO_CCW);
    }
  }
  *pVm = direction * v;
}

void motor_voltage_cmd_to_gpio_duty( const double MAX_MOTOR_VOLTAGE,
				     const double Vm,
				     unsigned int *pgpio,
				     unsigned int *pduty
				     ) {
  unsigned int duty, gpio;
  if( fabs(Vm) < 0.00001 ) {
    duty = 0;
    gpio = GPIO_BRAKE;
  } else {
    duty = round(  _100MHZ_TICKS_PER_PWM_PERIOD * fabs(Vm) / MAX_MOTOR_VOLTAGE );
    if( Vm > 0 ) {
      gpio = GPIO_CW;
    } else if( Vm < 0 ) {
      gpio = GPIO_CCW;
    } else {
      gpio = 0;
      duty =  round(_100MHZ_TICKS_PER_PWM_PERIOD * .13); // unlucky 13%
    }
  }
  duty = min(duty, _100MHZ_TICKS_PER_PWM_PERIOD); // don't max it out plz
  *pduty = duty;
  *pgpio = gpio;
}

    
void motor_voltage_schedule_to_cmd_buf( const double MAX_MOTOR_VOLTAGE,
					const double* voltages,
					const unsigned int NUM_VOLTAGES,
					const unsigned int sample_num,
					CommandBuffer* pcb ) {

   unsigned int MAX = min(NUM_VOLTAGES, PKTS_PER_CMD_BUFFER);
   for( int i=0; i<MAX; i++ ) {
     (*pcb)[i].cycle_count = 0x11111111;
     (*pcb)[i].sample_num  = sample_num+i;
     motor_voltage_cmd_to_gpio_duty( MAX_MOTOR_VOLTAGE,
				     voltages[i],
				     &((*pcb)[i].gpio),
				     &((*pcb)[i].duty)
				     );
   }
 }


void send_single_voltage( const double MAX_MOTOR_VOLTAGE, double voltage ) {
  if( voltage > MAX_MOTOR_VOLTAGE ) voltage = MAX_MOTOR_VOLTAGE;
  if( voltage < -MAX_MOTOR_VOLTAGE ) voltage = -MAX_MOTOR_VOLTAGE;
  CommandBuffer cb;
   for( int i=0; i<PKTS_PER_CMD_BUFFER; i++ ) {
     cb[i].cycle_count = 0;
     cb[i].sample_num  = MAGIC_SAMPLE_NUM_ALWAYS_EXECUTE;
     motor_voltage_cmd_to_gpio_duty( MAX_MOTOR_VOLTAGE,
				     voltage,
				     &(cb[i].gpio),
				     &(cb[i].duty)
				     );
   }

   set_cmd_buf(cb); 

}
