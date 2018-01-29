#include <stdio.h>
#include <stdlib.h>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>


#define _POSIX_C_SOURCE199309L  // dammit, weird posix stuff. usleep specified in some versions of posix, not in others, and it's obsolete in favor of nanosleep, which takes shitty timespec arguments.
// warning: implicit declaration of function ‘usleep’ [-Wimplicit-function-declaration]
// see https://ubuntuforums.org/showthread.php?t=1146543
// note: changing to nanosleep not a great option

#include <time.h> // usleep, clock_gettime

#include <unistd.h> // for unsigned int sleep(unsigned int seconds);
#include "jadcpwmeqep.h"

#include "adc-eqep-gpio.h"

#define CHECK_ZERO(x)   if(!(x)){printf("PROBLEM: x");}


#define PRU_NUM	   0   // using PRU0 for these examples
//#define EQEP_SYSFS "/sys/devices/ocp.3/48302000.epwmss/48302180.eqep"
// eqep0: "/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep" // works
// eqep1: "/sys/devices/ocp.3/48302000.epwmss/48302180.eqep"




// https://gist.github.com/diabloneo/9619917
void timespec_diff(struct timespec *start, struct timespec *stop,
                   struct timespec *result)
{
  if ((stop->tv_nsec - start->tv_nsec) < 0) {
    result->tv_sec = stop->tv_sec - start->tv_sec - 1;
    result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000L;
  } else {
    result->tv_sec = stop->tv_sec - start->tv_sec;
    result->tv_nsec = stop->tv_nsec - start->tv_nsec;
  }
  return;
}

void toc() {
  static struct timespec t0;
  static struct timespec tprev;
  static bool firstTime = true;
  if( firstTime ) {
    firstTime = false;
    clock_gettime(CLOCK_REALTIME,&t0);
    clock_gettime(CLOCK_REALTIME,&tprev);
  }
  struct timespec tnow;
  clock_gettime(CLOCK_REALTIME,&tnow);
  struct timespec tdiff;
  struct timespec tdiff2;
  timespec_diff(&t0, &tnow, &tdiff);
  timespec_diff(&tprev, &tnow, &tdiff2);
  double d = tdiff.tv_sec + tdiff.tv_nsec/(double)1.0e9;
  double d2 = tdiff2.tv_sec + tdiff2.tv_nsec/(double)1.0e9;
  //  printf("Main CPU time: sec: %lu\tnsec: %lu\n",tdiff.tv_sec, tdiff.tv_nsec);
  printf("Main CPU time: %15.9lf (since last call: %15.9lf) \n",d,d2);
  tprev.tv_sec = tnow.tv_sec; // new becomes old for next time.
  tprev.tv_nsec = tnow.tv_nsec;

}

/* /\* // Indices into pkts *\/ */
/* /\* #define IDATA_CYCLE_COUNT      0 *\/ */
/* /\* #define IDATA_SAMPLE_NUM       1 *\/ */
/* /\* #define IDATA_ADC 2 *\/ */
/* /\* #define IDATA_EQEP 3 *\/ */
/* /\* #define IDATA_GPIO 4 *\/ */
/* /\* #define IDATA_DUTY 5 *\/ */
/* /\* #define IDATA_RESERVED1 6 *\/ */
/* /\* #define IDATA_RESERVED2 7 *\/ */

/* /\* #define ICMD_CYCLE_COUNT 0 *\/ */
/* /\* #define ICMD_SAMPLE_NUM 1 *\/ */
/* /\* #define ICMD_GPIO 2 *\/ */
/* /\* #define ICMD_DUTY 3 *\/ */


/* struct DataPacket { */
/*   unsigned int cycle_count; */
/*   unsigned int sample_num; */
/*   unsigned int adc; */
/*   unsigned int eqep; */
/*   unsigned int gpio; */
/*   unsigned int duty; */
/*   unsigned int last_data_req; */
/*   unsigned int last_cmd_sch; */
/* }; */


/* struct CommandPacket { */
/*   unsigned int cycle_count; */
/*   unsigned int sample_num; */
/*   unsigned int gpio; */
/*   unsigned int duty; */
/* }; */


/* // http://stackoverflow.com/questions/31108968/const-and-typedef-of-arrays-in-c */
/* typedef struct DataPacket      DataBuffer[PKTS_PER_DATA_BUFFER]; */
/* typedef struct CommandPacket   CommandBuffer[PKTS_PER_CMD_BUFFER]; */

/* const int NUM_BUFS = 10; */
/* DataBuffer data_bufs[NUM_BUFS]; */
/* CommandBuffer cmd_bufs[NUM_BUFS]; */


/* void print_data_pkt( DataPacket d ) { */
/*   printf("cycle: %u sample: %d adc: %d eqep: %d gpio: %x duty: %d last-data-req: %u last-cmd: %u\n", */
/* 	 d.cycle_count, */
/* 	 d.sample_num, */
/* 	 d.adc, */
/* 	 d.eqep, */
/* 	 d.gpio, */
/* 	 d.duty, */
/* 	 d.last_data_req, */
/* 	 d.last_cmd_sch */
/* 	 ); */
/* } */

/* void print_data_buf( DataBuffer b ) { */
/*   for( int i=0; i<PKTS_PER_DATA_BUFFER; i++ ) { */
/*     print_data_pkt( b[i] ); */
/*   } */
/* } */



/* void get_data_buf( DataBuffer* pdb ) { */

/*   *(ctrladdr_CPU_wants_data) = 1;  // Set "CPU wants" bit */

/*   //printf("Waiting for \"Data ready\" bit...\n"); */
/*   while( !(*(ctrladdr_PRU_data_ready) == 1) ) {  // Spin until "data ready" bit */
/*     usleep(1);  */
/*   } */
/*   //printf("Got it! Time:\n"); */
/*   //toc(); */

/*   unsigned int* addr = addr_cpu_data_buf;  // Copy buf into local array. */
/*   for( int i=0; i<PKTS_PER_DATA_BUFFER; i++ ) { */
/*     for( int j=0; j<INTS_PER_DATA_PKT; j++ ) { */
/*       pdb[i][j] = *(addr++); */
/*     } */
/*   } */
/*   // Clear "CPU wants" bit and "Data ready" bits, just for good measure. */
/*   *(ctrladdr_CPU_wants_data) =  0; */
/*   *(ctrladdr_PRU_data_ready) =  0; */
/* } */


//////////////////////////////////////////////////////////////////////////

int main (void)
{

  //http://stackoverflow.com/questions/1716296/why-does-printf-not-flush-after-the-call-unless-a-newline-is-in-the-format-strin
  // Edit: From Andy Ross's comment below, you can also disable buffering on stdout by using setbuf:
setbuf(stdout, NULL);

  printf("Hey, if you get a seg fault, make sure the jppprugpio device tree overlay has been loaded!!\n");
  printf("Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo jppprugpio > /sys/devices/bone_capemgr.9/slots\n");

  printf("Also do this:\n");
  printf("echo bone_eqep1 > $SLOTS");

   if(getuid()!=0){
      printf("You must run this program as root. Exiting.\n");
      exit(EXIT_FAILURE);
   }


  printf("Note: I'm using the qQEP sysfs entry:");
  printf("%s",EQEP_SYSFS);
  printf(", so make sure that exists!!\n");

  printf("Calling constructor...\n");
  //  eqep_init(); // maybe it'll work out of the box?

  printf("Setting period...\n");
  // Set the unit time period to some # of ns
  //  eqep_set_period(1000); // 5 ns per iter is the PRU // HANGS THE WHOLE PRU??


   // Initialize structure used by prussdrv_pruintc_intc
   // PRUSS_INTC_INITDATA is found in pruss_intc_mapping.h
   tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

   // Allocate and initialize memory
   if( !prussdrv_init() ) printf("PROBLEM: prussdrv_init()\n");
   if( !prussdrv_open(PRU_EVTOUT_0) ) printf("PROBLEM: prussdrv_open\n");

   // Map PRU's interrupts
   if( !prussdrv_pruintc_init(&pruss_intc_initdata) ) printf("PROBLEM: prussdrv_pruintc_init\n");

   // Get pointer to PRU0's data ram
   void *pru0DataMemory;
   unsigned int *pru0DataMemory_int;
   prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, &pru0DataMemory);
   pru0DataMemory_int = (unsigned int *) pru0DataMemory;
   printf("pru0 data memory: %x\n",pru0DataMemory_int);




   ////////////////////////////////////////////////////
   // set up various buffers

unsigned int* ctrladdr_CPU_wants_data =  pru0DataMemory_int;
unsigned int* ctrladdr_PRU_data_ready =  pru0DataMemory_int+1;
unsigned int* ctrladdr_CPU_new_sched  =  pru0DataMemory_int+2;
unsigned int* ctrladdr_PRU_ack_sched  =  pru0DataMemory_int+3;

 unsigned int* addr_cpu_data_buf = pru0DataMemory_int + INTS_IN_CPU_PRU_CTRL_REG;
 unsigned int* addr_pru_data_buf = addr_cpu_data_buf  + INTS_PER_DATA_BUFFER;
 unsigned int* addr_cpu_cmd_buf  = addr_pru_data_buf  + INTS_PER_DATA_BUFFER;
 unsigned int* addr_pru_cmd_buf  = addr_cpu_cmd_buf   + INTS_PER_CMD_BUFFER; 
   
   // set all the addrs in the pru data ram to something we'll recognize.
     unsigned int* addr = pru0DataMemory_int;

     // Wipe out cpu/pru ctrl regs
     for( int i=0; i<INTS_IN_CPU_PRU_CTRL_REG; i++ ) {
       *(addr++) = 0;
     }

     // CAREFUL:  we assume the buffers start right after the ctrl register.

     // Wipe out cpu data buf
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


     ////////////////////////////////////////////
     // set up our local data buffer


     unsigned int data_buf[PKTS_PER_DATA_BUFFER][INTS_PER_DATA_PKT];

   ////////////////////////////////////////////

   // set up gpio schedule


   // 200MHz PRU -> 2e8 cycles per second. 
   // Want GPIOs to all change once per second.
   // pkts: cycles, gpios, duty, reserved
#if 0
   unsigned int cmds[] = { 0,   0x00000000, 0, 0,
			   2e8, 0xffffffff, 0, 0,
			   4e8, 0x00000000, 0, 0,
			   6e8, 0xffffffff, 0, 0,
			   8e8, 0x00000000, 0, 0   };
   const int num_pkts = 5;
#endif

#if 1
   // This makes the beat from the Terminator 2 theme song.
   unsigned int CMDS[] = { 
     0, 0, 0, 0, 
     200000000, 1,  0xffffffff, 100, 
     201000000, 2,  0, 100, 
     218802452, 3,  0xffffffff, 100, 
     219802452, 4,  0, 100, 
     277204037, 5,  0xffffffff, 100, 
     278204037, 6,  0, 100, 
     329618073, 7,  0xffffffff, 100, 
     330618073, 8,  0, 100, 
     364440441, 9,  0xffffffff, 100, 
     365440441, 10, 0, 100, 
     542009258, 11, 0xffffffff, 100, 
     543009258, 12, 0, 100, 
     575196266, 13, 0xffffffff, 100, 
     576196266, 14, 0, 100, 
     635581207, 15, 0xffffffff, 100, 
     636581207, 16, 0, 100, 
     689212036, 17, 0xffffffff, 100, 
     690212036, 18, 0, 100, 
     724411201, 19, 0xffffffff, 100, 
     725411201, 20, 0, 100
};
   const int num_pkts = 21;
   unsigned int cmds[num_pkts*INTS_PER_CMD_PKT];
#endif
   ///////////////////////////////////////


   printf("About to start PRU, time=\n");
   toc();

   // Load and execute the PRU program on the PRU
   const char* binname =  "./adc-eqep-gpio.bin";
      printf("executing bin file: %s\n",binname);
   prussdrv_exec_program (PRU_NUM, binname);


   printf("Waiting...\n"); 
      // Sleep for a sec to let the PRU fill up its internal buffer with ADC samples.
      sleep(1);




/////////////////////////////////////////////
// main loop



      const int MAX_ITERS = 5;
      int num_iters = 0;
      //      while( num_iters++ < MAX_ITERS ) {



      ///////////////////////////////////////////////////
      // Read sensors from PRU
      ///////////////////////////////////////////////////

      printf("About to set \"CPU Want data\" bit, time=\n");
   toc();

     // Set "CPU wants" bit
      *(ctrladdr_CPU_wants_data) = 1;

     // Spin until "data ready" bit
     printf("Waiting for \"Data ready\" bit...\n");
     while( !(*(ctrladdr_PRU_data_ready) == 1) ) {
       usleep(1); 
     }
     printf("Got it! Time:\n");
   toc();

     // Clear "CPU wants" bit and "Data ready" bits, just for good measure.
     *(ctrladdr_CPU_wants_data) =  0;
     *(ctrladdr_PRU_data_ready) =  0;



#if 0
     // Copy buf into local array.
     addr = addr_cpu_data_buf;
     for( int i=0; i<PKTS_PER_DATA_BUFFER; i++ ) {
       for( int j=0; j<INTS_PER_DATA_PKT; j++ ) {
     	 data_buf[i][j] = *(addr++);
       }
     }

     // Print out local data buffer:
     /* for( int i=0; i<PKTS_PER_DATA_BUFFER; i++ ) { */
     /*   for( int j=0; j<INTS_PER_DATA_PKT; j++ ) { */
     /* 	 printf("(i=%d)(j=%d) val = %d (0x%x)\t",i,j,data_buf[i][j],data_buf[i][j]); */
     /*   } */
     /*   printf("\n"); */
     /* } */


     for( int i=0; i<PKTS_PER_DATA_BUFFER; i++ ) {
     	 printf("cycle: %u sample: %d adc: %d eqep: %d gpio: %x duty: %d last-data-req: %u last-cmd: %u\n",
		data_buf[i][IDATA_CYCLE_COUNT],
		data_buf[i][IDATA_SAMPLE_NUM],
		data_buf[i][IDATA_ADC],
		data_buf[i][IDATA_EQEP],
		data_buf[i][IDATA_GPIO],
		data_buf[i][IDATA_DUTY],
		data_buf[i][IDATA_RESERVED1],
		data_buf[i][IDATA_RESERVED2]
		);
     }
#endif


      ///////////////////////////////////////////////////
      // Run control alg
      ///////////////////////////////////////////////////

     //     usleep(1); 
#if 0
     // Now we've got a new actuation sequence.
     // To fake a new actuation sequence, let's take the last cycle count from our data buffer
     // and use that as the base time for a new sequence.
     unsigned int basetime = data_buf[PKTS_PER_DATA_BUFFER][IDATA_CYCLE_COUNT];
     for( int i=0; i<num_pkts*INTS_PER_CMD_PKT; i++ ) {
       cmds[i] = CMDS[i];
     }
     for( int i=ICMD_CYCLE_COUNT; i<num_pkts*INTS_PER_CMD_PKT; i+=INTS_PER_CMD_PKT ) {
       cmds[i] = CMDS[i] + basetime;
     }

	// - cycle count
	// - sample num
	// - gpio states
	// - duty cycle

     printf("Sending these cmds:\n");
     for( int i=0; i<num_pkts*INTS_PER_CMD_PKT; i+=INTS_PER_CMD_PKT ) {
       printf("cycle: %u\tsample num: %d\tgpio: %x\tduty: %d\n",
	      cmds[i],cmds[i+1],cmds[i+2],cmds[i+3] );
     }
#endif

      ///////////////////////////////////////////////////
      // Write actuation sequence to PRU
      ///////////////////////////////////////////////////

     //     if( num_iters == 2  ) {



     printf("Copying cmd to PRU data ram, time=\n");
     toc();
     // Copy actuation schedule into PRU data ram.
     addr = addr_cpu_cmd_buf;
     for( int i=0; i<num_pkts*INTS_PER_CMD_PKT; i++ ) {
	 *(addr++) = CMDS[i];
     }
     printf("Done copying, time=\n");
     toc();

     // Tell the PRU we've got a new schedule.
     *ctrladdr_CPU_new_sched  = num_pkts;

     // Spin until the PRU says he copied it over
     printf("Waiting until pru says he copied over the new schedule...time=\n");
     toc();
     while( *ctrladdr_PRU_ack_sched  != 1 ) {
       usleep(1); 
     }
     printf("He got it! time=\n");
   toc();

     // Clear "CPU new sch" bit and "PRU ack sch" bits, just for good measure.
     *ctrladdr_CPU_new_sched = 0;
     *ctrladdr_PRU_ack_sched = 0;



     // Now the PRU should be executing the plan.

     // Wait a sec to let the PRU start executing it...


     // In the meantime, copy over the CPU data buf.
     addr = addr_cpu_data_buf;
     for( int i=0; i<PKTS_PER_DATA_BUFFER; i++ ) {
       for( int j=0; j<INTS_PER_DATA_PKT; j++ ) {
     	 data_buf[i][j] = *(addr++);
       }
     }

     usleep(10000);


     // Done waiting for PRU to begin executing.

     // Grab another buffer. Hopefully we'll see when the PRU actually started executing.

     // Set "CPU wants" bit
      *(ctrladdr_CPU_wants_data) = 1;

     // Spin until "data ready" bit
     printf("Waiting for \"Data ready\" bit...\n");
     while( !(*(ctrladdr_PRU_data_ready) == 1) ) {
       usleep(1); 
     }
     printf("Got it!\n");

     // Clear "CPU wants" bit and "Data ready" bits, just for good measure.
     *(ctrladdr_CPU_wants_data) =  0;
     *(ctrladdr_PRU_data_ready) =  0;



     // Print old data buffer:
     printf("Old data buffer:\n");
     for( int i=0; i<PKTS_PER_DATA_BUFFER; i++ ) {
     	 printf("cycle: %u sample: %d adc: %d eqep: %d gpio: %x duty: %d last-data-req: %u last-cmd: %u\n",
		data_buf[i][IDATA_CYCLE_COUNT],
		data_buf[i][IDATA_SAMPLE_NUM],
		data_buf[i][IDATA_ADC],
		data_buf[i][IDATA_EQEP],
		data_buf[i][IDATA_GPIO],
		data_buf[i][IDATA_DUTY],
		data_buf[i][IDATA_RESERVED1],
		data_buf[i][IDATA_RESERVED2]
		);
     }

     // Copy over the new data buf and print it.
     addr = addr_cpu_data_buf;
     for( int i=0; i<PKTS_PER_DATA_BUFFER; i++ ) {
       for( int j=0; j<INTS_PER_DATA_PKT; j++ ) {
     	 data_buf[i][j] = *(addr++);
       }
     }

     printf("New data buffer:\n");
     for( int i=0; i<PKTS_PER_DATA_BUFFER; i++ ) {
     	 printf("cycle: %u sample: %d adc: %d eqep: %d gpio: %x duty: %d last-data-req: %u last-cmd: %u\n",
		data_buf[i][IDATA_CYCLE_COUNT],
		data_buf[i][IDATA_SAMPLE_NUM],
		data_buf[i][IDATA_ADC],
		data_buf[i][IDATA_EQEP],
		data_buf[i][IDATA_GPIO],
		data_buf[i][IDATA_DUTY],
		data_buf[i][IDATA_RESERVED1],
		data_buf[i][IDATA_RESERVED2]
		);
     }



     // Let's get the data buf a few more times just to verify that the whole cmd pkt is executed.
     printf("Here's the data buffer a few more times, just to show it's flushing:\n");
     for( int i=0; i<5; i++ ) {
       // Get data, print it, pause.

       printf("Setting \"CPU Wants\" bit, time=\n");
       toc();

       // Set "CPU wants" bit
       *(ctrladdr_CPU_wants_data) = 1;

       // Spin until "data ready" bit
       printf("Waiting for \"Data ready\" bit, time=\n");
       toc();

       while( !(*(ctrladdr_PRU_data_ready) == 1) ) {
	 usleep(1); 
       }
       printf("Got it! time=\n");
       toc();

       // Clear "CPU wants" bit and "Data ready" bits, just for good measure.
       *(ctrladdr_CPU_wants_data) =  0;
       *(ctrladdr_PRU_data_ready) =  0;



       printf("Copy over the new data buf, time=\n");
       toc();
       addr = addr_cpu_data_buf;
       for( int i=0; i<PKTS_PER_DATA_BUFFER; i++ ) {
	 for( int j=0; j<INTS_PER_DATA_PKT; j++ ) {
	   data_buf[i][j] = *(addr++);
	 }
       }

       printf("Done! time=\n");
       toc();

       printf("Printing Data buffer (iter %d) time=:\n",i);
       toc();
       for( int i=0; i<PKTS_PER_DATA_BUFFER; i++ ) {
     	 printf("cycle: %u sample: %d adc: %d eqep: %d gpio: %x duty: %d last-data-req: %u last-cmd: %u\n",
		data_buf[i][IDATA_CYCLE_COUNT],
		data_buf[i][IDATA_SAMPLE_NUM],
		data_buf[i][IDATA_ADC],
		data_buf[i][IDATA_EQEP],
		data_buf[i][IDATA_GPIO],
		data_buf[i][IDATA_DUTY],
		data_buf[i][IDATA_RESERVED1],
		data_buf[i][IDATA_RESERVED2]
		);
       }

       printf("Sleeping for 10ms, time=\n");
       toc();
       usleep(10000);
       printf("Awake! time=\n");
       toc();
     }






     // Get another data packet



     //     printf("Waiting a few sec to let pru finish executing the schedule...\n");
     //     sleep(2); // give pru time to execute plan before calling pru_disable.

     //      }  //  while




   /* printf("Sending HALT pkt\n."); */
   /* *pru0DataMemory_int = 1; // "new pkt"(1) and "stop"(0) */
   /* printf("It should've stopped by now!\n"); */

   /* sleep(2); */

   printf("Shutting down.\n");
   prussdrv_pru_disable(PRU_NUM);
   prussdrv_exit ();
   return EXIT_SUCCESS;
}
