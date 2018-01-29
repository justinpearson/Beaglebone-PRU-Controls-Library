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


   const int NUM_SAMPLES = 64;
   const int UINTS_PER_SAMPLE = 4;
   unsigned int samples[NUM_SAMPLES][UINTS_PER_SAMPLE];
   int i,j;

   // set all the addrs in the pru data ram to something we'll recognize.
     unsigned int* addr = pru0DataMemory_int;
     addr += 1; // base addr has ctrl register, move 1 int (1 word) (32 bits) past it
     // CAREFUL:  we assume the CPU's samples start right after the ctrl register.
     for( i=0; i<NUM_SAMPLES; i++ ) {
       for( j=0; j<UINTS_PER_SAMPLE; j++ ) {
	 *(addr++) = 0x33333333;
       }
     }

     // debugging trick: let's write the next buffer too.
     for( i=0; i<NUM_SAMPLES; i++ ) {
       for( j=0; j<UINTS_PER_SAMPLE; j++ ) {
	 *(addr++) = 0x77777777;
       }
     }


   // wipe out 0th int of pru data memory. trying to track down a bug.
   *pru0DataMemory_int = 0;


   // init our samples
   for( i=0; i<NUM_SAMPLES; i++ ) {
     for( j=0; j<UINTS_PER_SAMPLE; j++ ) {
       samples[i][j] = 12345678;
     }
   }

   // Load and execute the PRU program on the PRU
   const char* binname =  "./cpu-reads-adc-list.bin";

   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

         printf("executing bin file: %s\n",binname);
         prussdrv_exec_program (PRU_NUM, binname);


      // Sleep for a sec to let the PRU fill up its internal buffer with ADC samples.
      sleep(1);


   const int MAX_ITERS = 5;
   int num_iters = 0;
   while( num_iters++ < MAX_ITERS ) {

     // Set "CPU wants" bit
     //     *pru0DataMemory_int |= 0x00000001;
     *pru0DataMemory_int = 1; // WARNING!!!!!!!!!!!!!!!!!!!!!

     // Spin until "data ready" bit
     printf("Waiting for \"Data ready\" bit...\n");
     while( !((*pru0DataMemory_int) & 2) ) {
       usleep(1); 
     }
     printf("Got it!\n");

     // Copy buf into local array.
     unsigned int* addr = pru0DataMemory_int;
     addr += 1; // base addr has ctrl register
     // CAREFUL:  we assume the CPU's samples start right after the ctrl register.
     for( i=0; i<NUM_SAMPLES; i++ ) {
       for( j=0; j<UINTS_PER_SAMPLE; j++ ) {
     	 samples[i][j] = *(addr++);
       }
     }

     /* unsigned int* addr = pru0DataMemory_int; */
     /* unsigned int x; */
     /*   printf("ctrl register: %u\n",*(addr++)); */
     /*   printf("sample # (ctsly updated): %u\n",*(addr++)); */
     /*   x=*(addr++); */
     /*   printf("cycle #  (ctsly updated): %u (%lf ms)\n",x,5.0*x/1e6); */
     /*   printf("adc val  (ctsly updated): %u\n",*(addr++)); */
     /*   printf("sample # : %u\n",*(addr++)); */
     /*   x=*(addr++); */
     /*   printf("cycle #  : %u (%lf ms)\n",x,5.0*x/1e6); */
     /*   printf("adc val  : %u\n",*(addr++)); */







     /* memcpy((void*)samples,  */
     /* 	    (const void*)*(pru0DataMemory_int+1),  */
     /* 	    sizeof(unsigned int)*NUM_SAMPLES*UINTS_PER_SAMPLE); */

     // Clear "CPU wants" bit and "Data ready" bits.
     //     *pru0DataMemory_int &= ~(0x00000003);
     *pru0DataMemory_int = 0; // WHAM

     // Print out samples:
     for( i=0; i<NUM_SAMPLES; i++ ) {
              printf("i:%d\t#: %u\tcycles: %u\tms: %lf\tADC: %u\teyecatch: %x\n",
		     //	              printf("i:%d\t%u\t%u\t%u\t%u\n",
	      i,
	      samples[i][0],
	      samples[i][1],
			     	      samples[i][1]*5.0/1e6,
			     samples[i][2],
samples[i][3]);
     }
     
     // Run "control algorithm"
     //          usleep(20000);  // 20 ms
	  sleep(1);

   } 


   printf("Shutting down.\n");
   prussdrv_pru_disable(PRU_NUM);
   prussdrv_exit ();
   return EXIT_SUCCESS;
}


