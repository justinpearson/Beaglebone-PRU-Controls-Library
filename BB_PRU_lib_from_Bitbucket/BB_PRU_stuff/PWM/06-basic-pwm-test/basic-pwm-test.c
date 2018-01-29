#include "jpp-pru-lib.h"
#include <stdio.h> // printf
#include <stdlib.h> // exit
#include <string.h> //  memcpy
#include <unistd.h> // usleep
#include <math.h> // fmod


int main( int argc, char* argv[] ) {

  start_pru();
  const double MAX_MOTOR_VOLTAGE = 4;
  /* for( double v=0; v<=MAX_MOTOR_VOLTAGE; v+=.5 ) { */
  /*   send_single_voltage(MAX_MOTOR_VOLTAGE, v); */
  /*   sleep(1); */
  /* } */
  printf("0%% duty...\n");
  send_single_voltage(MAX_MOTOR_VOLTAGE, 0.0*MAX_MOTOR_VOLTAGE);
  sleep(1);
  printf("-100%% duty...\n");
  send_single_voltage(MAX_MOTOR_VOLTAGE, -1.0*MAX_MOTOR_VOLTAGE);
  sleep(1);
  printf("0%% duty...\n");
  send_single_voltage(MAX_MOTOR_VOLTAGE, 0.0*MAX_MOTOR_VOLTAGE);
  sleep(1);
  printf("+100%% duty...\n");
  send_single_voltage(MAX_MOTOR_VOLTAGE, 1.0*MAX_MOTOR_VOLTAGE);
  sleep(1);
  printf("0%% duty...\n");
  send_single_voltage(MAX_MOTOR_VOLTAGE, 0);

  /* const int NUM_BUFS = 10; */
  /* DataBuffer db[NUM_BUFS]; */
  /* CommandBuffer cb_rx[NUM_BUFS]; */
  /* CommandBuffer cb_tx; */


  /* for( int i=0; i<NUM_BUFS; i++ ) { */

  /*   get_data_cmd_bufs( &(db[i]), &(cb_rx[i]) ); */

  /*   unsigned int sn = get_sample_num(); */

  /*   for( int j=0; j<PKTS_PER_CMD_BUFFER; j++ ) { */
  /*     cb_tx[j].cycle_count = 13; // verify this doesn't appear -- we're having the PRU write the cyc count of the time when it rx'd the cmd buf, for debugging purposes. */
  /*     cb_tx[j].sample_num  = 0xfffffffe; // should always get executed. */
  /*     cb_tx[j].gpio        = GPIO_STBY; */
  /*     cb_tx[j].duty        = sn+j; */
  /*   } */

  /*   set_cmd_buf(cb_tx); */

  /*   usleep(30000); */
  /* } */


  /* for( int i=0; i<NUM_BUFS; i++ ) { */
  /*   printf("\ni=%d:\n",i); */
  /*   printf("Data:\n"); */
  /*   print_data_buf( db[i] ); */
  /*   printf("Cmd:\n"); */
  /*   print_cmd_buf( cb_rx[i] ); */
  /* } */



  return(0);
}
