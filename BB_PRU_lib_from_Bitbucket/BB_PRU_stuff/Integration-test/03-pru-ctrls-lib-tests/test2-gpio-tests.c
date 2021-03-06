#include "jpp-pru-lib.h"
#include <stdio.h> // printf
#include <stdlib.h> // exit
#include <string.h> //  memcpy
#include <unistd.h> // usleep
int main() {

  start_pru();

  // Here, gpio bits 0,1,2,5 are osc, ghostbusters, terminator, mario theme songs.
#if 1
  unsigned int CMDS[] = { 

    0, 1, 37, 100,
    1000000, 2, 0, 100,
    2000000, 3, 7, 100,
    3000000, 4, 34, 100,
    4000000, 5, 3, 100,
    5000000, 6, 0, 100,
    6000000, 7, 39, 100,
    7000000, 8, 0, 100,
    8000000, 9, 3, 100,
    9000000, 10, 0, 100,
    10000000, 11, 39, 100,
    11000000, 12, 32, 100,
    12000000, 13, 5, 100,
    13000000, 14, 32, 100,
    14000000, 15, 33, 100,
    15000000, 16, 0, 100,
    16000000, 17, 33, 100,
    17000000, 18, 0, 100,
    18000000, 19, 33, 100,
    19000000, 20, 32, 100,
    20000000, 21, 35, 100,
    21000000, 22, 34, 100,
    22000000, 23, 3, 100,
    23000000, 24, 34, 100,
    24000000, 25, 3, 100,
    25000000, 26, 32, 100,
    26000000, 27, 3, 100,
    27000000, 28, 32, 100,
    28000000, 29, 33, 100,
    29000000, 30, 32, 100,
    30000000, 31, 1, 100,
    31000000, 32, 0, 100
  };
#else
  unsigned int CMDS[128];
  for( int i=0; i<128; i++ ) {
    CMDS[i] = 0x11111111;
    CMDS[i] += i;
  }
#endif

  CommandBuffer b;
  DataBuffer before, after;


  //  memcpy( &b, CMDS, sizeof(CMDS) ); // no work for some reason? 
#if 0
  for( int i=0; i<PKTS_PER_CMD_BUFFER; i++ ) {
    b[i].cycle_count = 0x11111111;
    b[i].sample_num = i;
    b[i].gpio = (i%2==0) ? 0x00000000 : 0xffffffff;
    b[i].duty = 0xabcdef;
  }
#else
  for( int i=0; i<PKTS_PER_CMD_BUFFER; i++ ) {
    b[i].cycle_count = CMDS[4*i+0];
    b[i].sample_num  = CMDS[4*i+1];
    b[i].gpio        = CMDS[4*i+2];
    b[i].duty        = CMDS[4*i+3];
  }
#endif

  printf("Before:\n");
  get_data_buf( &before );
  print_data_buf( before );

  printf("Sending cmd...\n");
  set_cmd_buf( b );

  usleep(1000000);

  printf("After 100ms:\n");

  get_data_buf( &after );
  print_data_buf( after );

  exit(0);
}
