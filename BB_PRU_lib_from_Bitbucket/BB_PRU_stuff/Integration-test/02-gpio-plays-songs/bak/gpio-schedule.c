#include <stdio.h>
#include <stdlib.h>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include <time.h> // clock_gettime
#include <unistd.h> // for unsigned int sleep(unsigned int seconds);

#define PRU_NUM	   0   // using PRU0 for these examples

int main (void)
{

  printf("Hey, if you get a seg fault, make sure the EBB-PRU-Example device tree overlay has been loaded!!\n");

  printf("Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo EBB-PRU-Example > /sys/devices/bone_capemgr.9/slots\n");

   if(getuid()!=0){
      printf("You must run this program as root. Exiting.\n");
      exit(EXIT_FAILURE);
   }
   // Initialize structure used by prussdrv_pruintc_intc
   // PRUSS_INTC_INITDATA is found in pruss_intc_mapping.h
   tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

   // Allocate and initialize memory
   prussdrv_init ();
   prussdrv_open (PRU_EVTOUT_0);

   // Map PRU's interrupts
   prussdrv_pruintc_init(&pruss_intc_initdata);

   // Get pointer to PRU0's data ram
   void *pru0DataMemory;
   unsigned int *pru0DataMemory_int;
   prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, &pru0DataMemory);
   pru0DataMemory_int = (unsigned int *) pru0DataMemory;

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
   unsigned int cmds[] = { 
     0, 0, 0, 0, 
     200000000, 0xffffffff, 0, 1,
     201000000, 0, 0, 2,
     218802452, 0xffffffff, 0, 3,
     219802452, 0, 0, 4,
     277204037, 0xffffffff, 0, 5,
     278204037, 0, 0, 6,
     329618073, 0xffffffff, 0, 7,
     330618073, 0, 0, 8,
     364440441, 0xffffffff, 0, 9,
     365440441, 0, 0, 10,
     542009258, 0xffffffff, 0, 11,
     543009258, 0, 0, 12,
     575196266, 0xffffffff, 0, 13,
     576196266, 0, 0, 14,
     635581207, 0xffffffff, 0, 15,
     636581207, 0, 0, 16,
     689212036, 0xffffffff, 0, 17,
     690212036, 0, 0, 18,
     724411201, 0xffffffff, 0, 19,
     725411201, 0, 0, 20
};
   const int num_pkts = 21;

#endif





   const int INTS_PER_PKT = 4;
   const int PKTS_PER_BUFFER = 64;

   int i,j;

   // set all the addrs in the pru data ram to something we'll recognize.
     unsigned int* addr = pru0DataMemory_int;
     addr += 1; // base addr has ctrl register, move 1 int (1 word) (32 bits) past it
     // CAREFUL:  we assume the CPU's samples start right after the ctrl register.
     for( i=0; i<INTS_PER_PKT*PKTS_PER_BUFFER; i++ ) {
	 *(addr++) = 0x33333333;
     }

     // debugging trick: let's write the next buffer too.
     for( i=0; i<INTS_PER_PKT*PKTS_PER_BUFFER; i++ ) {
	 *(addr++) = 0x77777777;
     }


   // wipe out 0th int of pru data memory. Otherwise PRU will think we've given it a new cmd pkt.
   *pru0DataMemory_int = 0;


   // Load and execute the PRU program on the PRU
   const char* binname =  "./gpio-schedule.bin";

   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   //         printf("executing bin file: %s\n",binname);
   //         prussdrv_exec_program (PRU_NUM, binname);


      // Sleep for a sec to let the PRU fill up its internal buffer with ADC samples.
      sleep(1);


   const int MAX_ITERS = 5;
   int num_iters = 0;
   //      while( num_iters++ < MAX_ITERS ) {

     // Write cmds to the buffer.
     addr = pru0DataMemory_int;
     addr += 1; // base addr has ctrl register, move 1 int (1 word) (32 bits) past it
     // CAREFUL:  we assume the CPU's samples start right after the ctrl register.
     for( i=0; i<num_pkts*INTS_PER_PKT; i++ ) {
	 *(addr++) = cmds[i];
     }


     // Tell the PRU we've got a new schedule.
     *pru0DataMemory_int = num_pkts;


     // Spin until "data ready" bit
     printf("Waiting until he got it \"cpu give new scheudle\" bit...\n");
     while( (*pru0DataMemory_int) != 0 ) {
       usleep(1); 
     }
     printf("He got it!\n");


     // Now the PRU should be executing the plan.

     printf("Waiting a few sec to let pru finish executing the schedule...\n");
     sleep(12); // give pru time to execute plan before calling pru_disable.

     //      } 


   printf("Shutting down.\n");
   prussdrv_pru_disable(PRU_NUM);
   prussdrv_exit ();
   return EXIT_SUCCESS;
}


