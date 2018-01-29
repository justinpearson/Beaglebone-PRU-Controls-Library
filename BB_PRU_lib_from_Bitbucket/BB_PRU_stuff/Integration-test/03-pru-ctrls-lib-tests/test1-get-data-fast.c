#include <unistd.h> // for unsigned int sleep(unsigned int seconds);
#include <stdio.h>
#include "jpp-pru-lib.h"

int main() {

  start_pru();

  const int NUM_BUFS = 10;
  DataBuffer data_bufs[NUM_BUFS];

  printf("Retrieving data bufs:\n");

  for( int i=0; i<NUM_BUFS; i++ ) {
    get_data_buf( &(data_bufs[i]) );
    usleep(100000); // If you leave this out, all buffers are identical -- must starve PRU or something.
  }

  printf("Done, printing data bufs:\n");

  for( int i=0; i<NUM_BUFS; i++ ) {
    printf("Buffer %d:\n",i);
    print_data_buf( data_bufs[i] );
  }

  return(0);
}
