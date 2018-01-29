//#include <unistd.h> // for unsigned int sleep(unsigned int seconds);
#include "jpp-pru-lib.h"


#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// To get usleep:
#define _POSIX_C_SOURCE199309L  // dammit, weird posix stuff. usleep specified in some versions of posix, not in others, and it's obsolete in favor of nanosleep, which takes shitty timespec arguments.
// warning: implicit declaration of function ‘usleep’ [-Wimplicit-function-declaration]
// see https://ubuntuforums.org/showthread.php?t=1146543
// note: changing to nanosleep not a great option
#include <time.h> // usleep, clock_gettime


#include <stdio.h>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>





// Important memory locations
// These should be available to all functions here, but not to 
// functions outside of this file.
unsigned int* ctrladdr_CPU_wants_data;
unsigned int* ctrladdr_PRU_data_ready;
unsigned int* ctrladdr_CPU_new_sched ;
unsigned int* ctrladdr_PRU_ack_sched ;

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
  printf("Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo jppprugpio > /sys/devices/bone_capemgr.9/slots\n");

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

  ctrladdr_CPU_wants_data =  pru0DataMemory_int;
  ctrladdr_PRU_data_ready =  pru0DataMemory_int+1;
  ctrladdr_CPU_new_sched  =  pru0DataMemory_int+2;
  ctrladdr_PRU_ack_sched  =  pru0DataMemory_int+3;

  addr_cpu_data_buf = pru0DataMemory_int + INTS_IN_CPU_PRU_CTRL_REG;
  addr_pru_data_buf = addr_cpu_data_buf  + INTS_PER_DATA_BUFFER;
  addr_cpu_cmd_buf  = addr_pru_data_buf  + INTS_PER_DATA_BUFFER;
  addr_pru_cmd_buf  = addr_cpu_cmd_buf   + INTS_PER_CMD_BUFFER; 

  printf(" ctrladdr_CPU_wants_data : %p\n",(void*)ctrladdr_CPU_wants_data);
  printf(" ctrladdr_PRU_data_ready : %p\n",(void*) ctrladdr_PRU_data_ready );
  printf(" ctrladdr_CPU_new_sched  : %p\n",(void*) ctrladdr_CPU_new_sched  );
  printf(" ctrladdr_PRU_ack_sched  : %p\n",(void*) ctrladdr_PRU_ack_sched  );

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
  printf("Waiting 200ms to let PRU fill its internal buffer...");
  usleep(200000); 
  printf("done.\n");

}





void get_data_buf( DataBuffer* pdb ) {

  //  printf("pru data ready: %x\n",*(ctrladdr_PRU_data_ready));

  if( ctrladdr_CPU_wants_data ==  NULL || ctrladdr_PRU_data_ready == NULL ) {
      printf("Hey idiot, ctrladdr_CPU_wants_data is NULL so you probably didn't run start_pru(). Exiting.\n");
      exit(EXIT_FAILURE);
   }


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

  if( ctrladdr_CPU_new_sched == NULL || ctrladdr_PRU_ack_sched == NULL ) {
      printf("Hey idiot, ctrladdr_CPU_new_sched == NULL || ctrladdr_PRU_ack_sched == NULL so you probably didn't run start_pru(). Exiting.\n");
      exit(EXIT_FAILURE);
   }



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




void print_data_pkt( const DataPacket p ) {
  printf("cycle: %u sample: %d adc: %d eqep: %d gpio: %x duty: %d last-data-req: %u last-cmd: %u\n",
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




void print_cmd_pkt( const CommandPacket p ) {
  printf("cycle: %u sample: %d gpio: %x duty: %d",
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







