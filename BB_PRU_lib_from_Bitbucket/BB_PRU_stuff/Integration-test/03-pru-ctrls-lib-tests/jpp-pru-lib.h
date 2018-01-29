#ifndef JPPPRULIB_H
#define JPPPRULIB_H

#include "jpp-pru-lib.hp"


struct DataPacket_s {
  unsigned int cycle_count;
  unsigned int sample_num;
  unsigned int adc;
  unsigned int eqep;
  unsigned int gpio;
  unsigned int duty;
  unsigned int last_data_req;
  unsigned int last_cmd_sch;
};


struct CommandPacket_s {
  unsigned int cycle_count;
  unsigned int sample_num;
  unsigned int gpio;
  unsigned int duty;
};


typedef struct DataPacket_s DataPacket;
typedef struct CommandPacket_s CommandPacket;

// http://stackoverflow.com/questions/31108968/const-and-typedef-of-arrays-in-c
typedef DataPacket      DataBuffer[PKTS_PER_DATA_BUFFER];
typedef CommandPacket   CommandBuffer[PKTS_PER_CMD_BUFFER];


void start_pru( );
void get_data_buf( DataBuffer* );
void set_cmd_buf(  CommandBuffer );

void print_data_pkt( const DataPacket );
void print_data_buf( const DataBuffer b );

void print_cmd_pkt( const CommandPacket );
void print_cmd_buf( const CommandBuffer b );



#endif  // header guard
