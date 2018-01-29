#ifndef JPPPRULIB_H
#define JPPPRULIB_H

#include <stdlib.h>
#include <stdio.h>

#include "jpp-pru-lib.hp"

#define PRU_TICKS_PER_SEC (200000000LL)

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

// http://stackoverflow.com/questions/1102542/how-to-define-an-enumerated-type-enum-in-c
typedef enum {MOTOR_STBY, MOTOR_BRAKE, MOTOR_CW, MOTOR_CCW} MotorState;

void start_pru( );
void get_data_buf( DataBuffer* );
void set_cmd_buf(  CommandBuffer );

void print_data_pkt( const DataPacket );
void print_data_buf( const DataBuffer b );
void print_cmd_pkt( const CommandPacket );
void print_cmd_buf( const CommandBuffer b );

void fprintf_data_pkt( const DataPacket, FILE* fp );
void fprintf_data_buf( const DataBuffer b,  FILE* fp );
void fprintf_cmd_pkt( const CommandPacket,  FILE* fp );
void fprintf_cmd_buf( const CommandBuffer b,  FILE* fp );



void make_cmd_buf_from_gpio( CommandBuffer*, unsigned int );

void make_const_cmd_buf_from_raw( CommandBuffer* pb, 
			 unsigned int cycle_count, 
			 unsigned int sample_num,
			 unsigned int gpio,
			 unsigned int duty );



void make_const_cmd_buf( CommandBuffer* pb, 
			 unsigned int cycle_count, 
			 unsigned int sample_num,
			 MotorState mstate,
			 double duty );


unsigned int duty_to_dutyticks( double duty ); 
double dutyticks_to_duty( unsigned int dutyticks );
unsigned int motor_state_to_gpio( MotorState mstate );
MotorState gpio_to_motor_state( unsigned int gpio );


// hardware-specific functions
double adc_to_amps( unsigned int raw_adc );
double eqep_to_angle( unsigned int eqep );

void gpio_duty_to_motor_voltage_cmd( unsigned int gpio,
				     unsigned int duty,
				     const double MAX_MOTOR_VOLTAGE,
				     double* pVm );

void motor_voltage_cmd_to_gpio_duty( const double MAX_MOTOR_VOLTAGE,
				     const double Vm,
				     unsigned int *pgpio,
				     unsigned int *pduty
				     );

void motor_voltage_schedule_to_cmd_buf( const double MAX_MOTOR_VOLTAGE,
					const double* voltages,
					const unsigned int NUM_VOLTAGES,
					const unsigned int sample_num,
					CommandBuffer* pcb );

unsigned int get_sample_num();

void set_PRU_sample_period(unsigned int period);

void get_data_cmd_bufs( DataBuffer* pdb, CommandBuffer* pcb );

void send_single_voltage( const double MAX_MOTOR_VOLTAGE, const double voltage );

#endif  // header guard
