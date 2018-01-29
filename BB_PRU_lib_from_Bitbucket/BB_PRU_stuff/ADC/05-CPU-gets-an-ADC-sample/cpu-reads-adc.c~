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

   void *pru0DataMemory;
   unsigned int *pru0DataMemory_int;
   prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, &pru0DataMemory);
   pru0DataMemory_int = (unsigned int *) pru0DataMemory;

   // Load and execute the PRU program on the PRU
   const char* binname =  "./cpu-reads-adc.bin";
   printf("executing bin file: %s\n",binname);
   prussdrv_exec_program (PRU_NUM, binname);

   const int NUM_SAMPLES = 10;
   const int UINTS_PER_SAMPLE = 3;
   unsigned int samples[NUM_SAMPLES][UINTS_PER_SAMPLE];
   int i,j;
   for( i=0; i<NUM_SAMPLES; i++ ) {
     for( j=0; j<UINTS_PER_SAMPLE; j++ ) {
       samples[i][j] = (i<<16) + j; // can view with %x
     }
   }

   const int MAX_ITERS = 5;
   int num_iters = 0;
   while( num_iters++ < MAX_ITERS ) {

     // Set "CPU wants" bit
     *pru0DataMemory_int |= 0x00000001;

     // Spin until "data ready" bit
     printf("Waiting for \"Data ready\" bit...\n");
     while( !(*pru0DataMemory_int & 2) ) {
       usleep(1); 
     }
     printf("Got it!\n");

     // Copy buf into local array.
     unsigned int* addr = pru0DataMemory_int;
     addr += 4; // CAREFUL, this needs to sync up with the .p code. 
     for( i=0; i<NUM_SAMPLES; i++ ) {
       for( j=0; j<UINTS_PER_SAMPLE; j++ ) {
	 samples[i][j] = *(addr++);
       }
     }


     /* memcpy((void*)samples,  */
     /* 	    (const void*)*(pru0DataMemory_int+1),  */
     /* 	    sizeof(unsigned int)*NUM_SAMPLES*UINTS_PER_SAMPLE); */

     // Clear "CPU wants" bit and "Data ready" bits.
     *pru0DataMemory_int &= ~(0x00000003);

     // Print out samples:
     for( i=0; i<NUM_SAMPLES; i++ ) {
       printf("#: %u\ttime: %u\tsample: %u\n",samples[i][0],samples[i][1],samples[i][2]);
     }
     
     // Run "control algorithm"
     usleep(20000);  // 20 ms

   } 


   printf("Shutting down.\n");
   prussdrv_pru_disable(PRU_NUM);
   prussdrv_exit ();
   return EXIT_SUCCESS;
}
