#include "jpp-pru-lib.h"
#include <stdio.h> // printf
#include <stdlib.h> // exit
#include <string.h> //  memcpy
#include <unistd.h> // usleep

void make_cmd_buf_from_gpio( CommandBuffer*, unsigned int );
void make_cmd_buf_from_gpio( CommandBuffer* pb, unsigned int gpio ) {

  for( int i=0; i<PKTS_PER_CMD_BUFFER; i++ ) {
    (*pb)[i].cycle_count = 0x11111111;
    (*pb)[i].sample_num  = 0x22222222;
    (*pb)[i].gpio        = gpio;
    (*pb)[i].duty        = 0x33333333;
  }
  

}

int main() {

  start_pru();


  unsigned int stby = 0;
  unsigned int ain1 = 1;
  unsigned int ain2 = 2;
  unsigned int pwm  = 5;
  unsigned int lo = 0;
  unsigned int hi = 1;

  unsigned int STBY = (lo << stby) | (lo << ain1) | (lo << ain2) | (lo << pwm);
  unsigned int BRAKE= (hi << stby) | (lo << ain1) | (hi << ain2) | (lo << pwm);
  unsigned int CW   = (hi << stby) | (hi << ain1) | (lo << ain2) | (hi << pwm);
  unsigned int CCW  = (hi << stby) | (lo << ain1) | (hi << ain2) | (hi << pwm);

  printf("0x%x\t0x%x\t0x%x\t0x%x\n",STBY,BRAKE,CW,CCW);


  unsigned int cmds[] = {STBY, CW, BRAKE, CCW, BRAKE, CW, STBY};
  char* cmds_str[] = {"STBY","CW","BRAKE","CCW","BRAKE","CW","STBY"};
  int num_cmds = 7;


  CommandBuffer b;
  DataBuffer data_buf;

  for( int i=0; i<num_cmds; i++ ) {
    
    unsigned int cmd = cmds[i];
    printf("Cmd (%s): 0x%x\n",cmds_str[i],cmd);
    
  printf("Data data_buf:\n");
  get_data_buf( &data_buf );
  print_data_buf( data_buf );

  make_cmd_buf_from_gpio(&b, cmd);

  printf("Sending cmd...\n");
  set_cmd_buf( b );

  printf("Sleeping for 20ms...\n");
  usleep(20000);

  printf("Data after:\n");
  get_data_buf( &data_buf );
  print_data_buf( data_buf );

  printf("Sleeping for 2 sec...\n");
  sleep(2);


  }

  //  sleep(1);

  //////////////

  exit(0);
}
