#include "jpp-pru-lib.h"
#include <stdio.h> // printf
#include <stdlib.h> // exit
#include <string.h> //  memcpy
#include <unistd.h> // usleep
#include <math.h> // fmod
int main() {

  start_pru();

  CommandBuffer cb;
  CommandBuffer cb_stop;

  make_const_cmd_buf( &cb, 0, 0, MOTOR_CW, 50 );
  make_const_cmd_buf( &cb_stop, 0, 0, MOTOR_STBY, 0 );

  for( int i=0; i<PKTS_PER_CMD_BUFFER; i++ ) {
    cb[i].duty = i;
  }

  DataBuffer data_buf;
  unsigned int sample_num;

  get_data_buf( &data_buf );
  print_data_buf( data_buf );
  sample_num = data_buf[PKTS_PER_DATA_BUFFER-1].sample_num; 
  cb[0].sample_num = sample_num+1; 
  printf("It's now sample time %d. Sending ramp to start at sample num %d...\n",sample_num,cb[0].sample_num);
  set_cmd_buf( cb );

  printf("Sent. Sleeping for 15ms...\n");
  usleep(15000);
  printf("Awake.\n");

  printf("Data data_buf:\n");
  get_data_buf( &data_buf );
  print_data_buf( data_buf );

  sample_num = data_buf[PKTS_PER_DATA_BUFFER-1].sample_num; 
  printf("It's now sample time %d\n",sample_num);
  cb[0].sample_num = sample_num+1; 

  printf("Sleeping for 10ms to simulate preemption...\n");
  usleep(10000);
  printf("Awake.\n");
  printf("Sending ramp to start at sample_num %d...\n", cb[0].sample_num);
  set_cmd_buf( cb );

  printf("Sent. Sleeping for 10ms...\n");
  usleep(10000);
  printf("Awake.\n");

  printf("Data data_buf:\n");
  get_data_buf( &data_buf );
  print_data_buf( data_buf );
  sample_num = data_buf[PKTS_PER_DATA_BUFFER-1].sample_num; 
  cb_stop[0].sample_num = sample_num; 

  printf("Sending STBY cmd...\n");
  set_cmd_buf( cb_stop );

  return(0);

}
