// This program records the adc and eqep, and twiddles the gpios according to a certain schedule.
// When asked by the CPU, the PRU delivers the last several adc, eqep, and gpio values (see below
// for packet structure.)
// CPU can specify a GPIO actuation schedule for the PRU to obey.	
	

#include "adc-eqep-gpio.h"

	
//////////////////////////
// Named registers	
//////////////////////////

#define tmp0 				r1
#define tmp1 				r2
#define tmp2 				r3
#define tmp3 				r4
#define current_time 			r5
#define cycles_at_next_sample_time 	r6
#define time_of_last_cpu_data_req	r7
#define gpio_cmd			r8
#define gpio_actual			r9
#define pru_cmd_buf_read_head		r10
#define num_cmd_pkts_in_buffer		r11
#define adc_value			r12
#define pru_data_buf_write_head		r13
#define idx_in_pru_data_buf		r14
#define num_total_samples		r15
#define idx_in_pru_cmd_buf		r16
#define sample_time			r17
#define eqep				r18
#define time_of_last_cpu_cmd_sch	r19	
#define rADDR_CPU_PRU_CTRL_REG  	r20
#define rADDR_CPU_DATA_BUF      	r21
#define rADDR_PRU_DATA_BUF      	r22
#define rADDR_CPU_CMD_BUF       	r23
#define rADDR_PRU_CMD_BUF       	r24

	



	
	
    .setcallreg  r29.w2  // Use R29.W2 in the CALL/RET pseudo ops, not the default of r30 (used for GPIOS)
    .origin 0
    .entrypoint INIT


INIT:

	// init registers
	mov r0, INITIAL_REG_VALUE
	mov r1, INITIAL_REG_VALUE
	mov r2, INITIAL_REG_VALUE
	mov r3, INITIAL_REG_VALUE
	mov r4, INITIAL_REG_VALUE
	mov r5, INITIAL_REG_VALUE
	mov r6, INITIAL_REG_VALUE
	mov r7, INITIAL_REG_VALUE
	mov r8, INITIAL_REG_VALUE
	mov r9, INITIAL_REG_VALUE
	mov r10, INITIAL_REG_VALUE
	mov r11, INITIAL_REG_VALUE
	mov r12, INITIAL_REG_VALUE
	mov r13, INITIAL_REG_VALUE
	mov r14, INITIAL_REG_VALUE
	mov r15, INITIAL_REG_VALUE
	mov r16, INITIAL_REG_VALUE
	mov r17, INITIAL_REG_VALUE
	mov r18, INITIAL_REG_VALUE
	mov r19, INITIAL_REG_VALUE
	mov r20, INITIAL_REG_VALUE
	mov r21, INITIAL_REG_VALUE
	mov r22, INITIAL_REG_VALUE
	mov r23, INITIAL_REG_VALUE
	mov r24, INITIAL_REG_VALUE
	mov r25, INITIAL_REG_VALUE
	mov r26, INITIAL_REG_VALUE
	mov r27, INITIAL_REG_VALUE
	mov r28, INITIAL_REG_VALUE
	// r29 used for "RET" register

	// clear pru0 data ram
	// don't, debugging atm
	call CLEAR_PRU0_DATA_RAM
	

	// Set up the PRU's ability to access memory outside its own private 8kB
	// http://exploringbeaglebone.com/chapter13/#The_Programs
	LBCO tmp0, C4, 4, 4	// Load Bytes Constant Offset (?)
	CLR  tmp0, tmp0, 4	// Clear bit 4 
	SBCO tmp0, C4, 4, 4	// Store Bytes Constant Offset


	// Cycle counter setup
	// Use the CTPPR0 reg (Constant table Programmable Pointer Register 0) to 
	// confgure C28 to point to the family of 'PRU_ICSS_PRU_CTRL Registers' (0x0002_2000)
	// (The cycle counter lives in this family at offset 0xC)
	//http://theembeddedkitchen.net/beaglelogic-building-a-logic-analyzer-with-the-prus-part-1/449

	MOV    tmp1,  	0x22028  // Constant table Programmable Pointer Register 0
	MOV    tmp2, 	0x00000220  
	SBBO   tmp2, 	tmp1, 0, 4

// - init regs & addrs
	call INIT_REGISTERS
// - init adc
	call INIT_ADC
// - init cycle counter
	call RESET_CYCLE_COUNTER


	
BEGIN_LOOP:	
	
// If CPU has set 'cpu wants data' reg, copy over the PRU data buffer to the CPU data buffer.
	mov tmp1, ADDR_CPU_PRU_CTRL_REG
        LBBO tmp0, tmp1, OFST_CPU_WANTS_DATA, 4
	AND tmp0, tmp0, 1 // keep bottom bit
	QBEQ DELIVER_TO_CPU, tmp0, 1 
	DONE_DELIVERING:	

// If CPU has set 'cpu gives new actuation schedule' reg, copy new actuation schedule from cpu buf to pru buf.
	mov tmp1, ADDR_CPU_PRU_CTRL_REG
        LBBO tmp0, tmp1, OFST_CPU_NEW_SCHED, 4
	qbne COPY_NEW_ACTUATION_SCHEDULE, tmp0, 0  // if nonzero, that's the number of new pkts!
	DONE_COPYING_NEW_SCH:	

// Spin until next sample time.
WAIT_FOR_SAMPLE_TIME:
	LBCO current_time, C28, 0xC, 4     // What time is it?
//	qbgt WAIT_FOR_SAMPLE_TIME, current_time, cycles_at_next_sample_time // Spin until next sample time.
	// Note: for faster response to CPU, we warp back to BEGIN_LOOP intead of WAIT_FOR_SAMPLE_TIME.
	qbgt BEGIN_LOOP, current_time, cycles_at_next_sample_time // Spin until next sample time.
	
	// current cycle count >= cycles_at_next_sample_time. So time for a sample.
	// advance cycles_at_next in steps of SAMPLE_PERIOD until it's greater than cycle count.
	mov tmp0, SAMPLE_PERIOD
ADVANCE_NEXT_SAMPLE_TIME:
	add cycles_at_next_sample_time,  cycles_at_next_sample_time, tmp0
	qble ADVANCE_NEXT_SAMPLE_TIME, current_time, cycles_at_next_sample_time

// Now it's a sample time.
//         - initiate an adc sample
TRIGGER_ADC_SAMPLE:
	mov tmp0, 2  // bit 1: enable ADC state machine step 1 (adc channel 0)
	mov tmp1, ADDR_ADC
	SBBO tmp0, tmp1, OFFSET_STEPENABLE, 4   // triggers a capture / sample!
	LBCO sample_time, C28, 0xC, 4     // save the time that we actually triggered the sample.

// while we're waiting for the ADC,	
//         - read the eqep register
	mov tmp0, ADDR_EQEP1
	lbbo eqep, tmp0, QPOSCNT, 4
	
//         - write the next gpio cmd, if there are any left.
	// ie, while idx_in_pru_cmd_buf < num_cmd_pkts_in_buffer
	qbgt ACTUATE, idx_in_pru_cmd_buf, num_cmd_pkts_in_buffer
	DONE_ACTUATING:	


	

//         - wait until adc complete
WAIT_FOR_ADC_FIFO0:
	mov tmp1, ADDR_ADC
        LBBO tmp0, tmp1, OFFSET_FIFO0COUNT, 4
        AND tmp0, tmp0, 127    // only bits 0 thru 6 are unreserved, so turn others off and keep only bits 0-6.
        QBEQ WAIT_FOR_ADC_FIFO0, tmp0, 0 // spin until we have an adc sample.

//        - retrieve adc sample
RETRIEVE_VALUE:
	// There's a sample in the FIFO!
	mov tmp2, ADDR_FIFO0DATA
        LBBO tmp0, tmp2, 0, 4  // grab the sample from the ADC
	MOV tmp1, 0xfff	// keep the 12 lowest bits (12-bit adc)
        AND adc_value, tmp0, tmp1
	
	
//         - write sample #, cycle count, adc, eqep, and gpio to data pkt in pru-sensor-buf.

	//
	// data packet: 8 words = 32 byets = 0x20 bytes
	//
	// - cycle count
	// - sample num
	// - adc value
	// - eqep value
	// - gpios written @ this time
	// - duty written @ this time
	// - reserved
	// - reserved
	
	mov tmp0, ADDR_PRU_DATA_BUF	
	
	// cycle count
	SBBO sample_time, tmp0, pru_data_buf_write_head, 4
	ADD pru_data_buf_write_head, pru_data_buf_write_head, 4
	// sample num
	SBBO num_total_samples, tmp0, pru_data_buf_write_head, 4
	ADD pru_data_buf_write_head, pru_data_buf_write_head, 4
	// adc value
	SBBO adc_value, tmp0, pru_data_buf_write_head, 4
	ADD pru_data_buf_write_head, pru_data_buf_write_head, 4
	// eqep value
	SBBO eqep, tmp0, pru_data_buf_write_head, 4 
	ADD pru_data_buf_write_head, pru_data_buf_write_head, 4
	// gpios
	SBBO gpio_actual, tmp0, pru_data_buf_write_head, 4
	ADD pru_data_buf_write_head, pru_data_buf_write_head, 4
	// duty
	mov tmp1, 100  // for now, we're full-speed ahead (100% duty)
	SBBO tmp1, tmp0, pru_data_buf_write_head, 4
	ADD pru_data_buf_write_head, pru_data_buf_write_head, 4
	// reserved
	mov tmp1, time_of_last_cpu_data_req
	SBBO tmp1, tmp0, pru_data_buf_write_head, 4
	ADD pru_data_buf_write_head, pru_data_buf_write_head, 4
	// reserved
	mov tmp1, time_of_last_cpu_cmd_sch
	SBBO tmp1, tmp0, pru_data_buf_write_head, 4
	ADD pru_data_buf_write_head, pru_data_buf_write_head, 4
	
	ADD idx_in_pru_data_buf, idx_in_pru_data_buf, 1
	
	ADD num_total_samples, num_total_samples, 1

	// If buf full, start overwriting old ones.
	// NOTE: This fn modifies idx_in_pru_data_buf and write_head, so must come
	// after DELIVER_TO_CPU, since DELIVER_TO_CPU uses those to help it
	// write to the output buffer.
	QBEQ RESET_WRITE_HEAD, idx_in_pru_data_buf, PKTS_PER_DATA_BUFFER
	DONE_RESETTING_WRITE_HEAD:

	
// - repeat
	qba BEGIN_LOOP

QUIT: // never quit, I think.
	
        MOV R31.b0, PRU0_ARM_INTERRUPT+16   // Send notification to Host for program completion
        HALT

	






/////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////
	
DELIVER_TO_CPU:
//     - copy from PRU-sensor-buf to CPU-sensor-buf, then set 'data-ready' flag.

	// We write it backwards, since pru_data_buf_write_head already points to the most recent sample.

	// Remember the last time heard from CPU:
	LBCO time_of_last_cpu_data_req, C28, 0xC, 4
	

	// Clear "cpu wants" bit
	mov tmp0, 0
	mov tmp1, ADDR_CPU_PRU_CTRL_REG
	SBBO tmp0, tmp1, OFST_CPU_WANTS_DATA, 4
	

	MOV tmp1, pru_data_buf_write_head // addr offset in backup buffer
	mov tmp3, ( BYTES_PER_DATA_BUFFER) // addr offset of end of cpu's buffer
	MOV tmp2, 0 // num samples copied
  COPY_ONE_SAMPLE:
	// 8 uints per data packet (todo: should loop here)
	sub tmp1, tmp1, 4
	sub tmp3, tmp3, 4
	LBBO tmp0, rADDR_PRU_DATA_BUF, tmp1, 4 
	SBBO tmp0, rADDR_CPU_DATA_BUF, tmp3, 4
	sub tmp1, tmp1, 4
	sub tmp3, tmp3, 4	
	LBBO tmp0, rADDR_PRU_DATA_BUF, tmp1, 4 
	SBBO tmp0, rADDR_CPU_DATA_BUF, tmp3, 4
	sub tmp1, tmp1, 4
	sub tmp3, tmp3, 4	
	LBBO tmp0, rADDR_PRU_DATA_BUF, tmp1, 4 
	SBBO tmp0, rADDR_CPU_DATA_BUF, tmp3, 4
	sub tmp1, tmp1, 4
	sub tmp3, tmp3, 4	
	LBBO tmp0, rADDR_PRU_DATA_BUF, tmp1, 4 
	SBBO tmp0, rADDR_CPU_DATA_BUF, tmp3, 4
	sub tmp1, tmp1, 4
	sub tmp3, tmp3, 4
	LBBO tmp0, rADDR_PRU_DATA_BUF, tmp1, 4 
	SBBO tmp0, rADDR_CPU_DATA_BUF, tmp3, 4
	sub tmp1, tmp1, 4
	sub tmp3, tmp3, 4	
	LBBO tmp0, rADDR_PRU_DATA_BUF, tmp1, 4 
	SBBO tmp0, rADDR_CPU_DATA_BUF, tmp3, 4
	sub tmp1, tmp1, 4
	sub tmp3, tmp3, 4	
	LBBO tmp0, rADDR_PRU_DATA_BUF, tmp1, 4 
	SBBO tmp0, rADDR_CPU_DATA_BUF, tmp3, 4
	sub tmp1, tmp1, 4
	sub tmp3, tmp3, 4	
	LBBO tmp0, rADDR_PRU_DATA_BUF, tmp1, 4 
	SBBO tmp0, rADDR_CPU_DATA_BUF, tmp3, 4

	ADD tmp2, tmp2, 1  // num_samples++
	QBEQ SET_DELIVERED_BIT_AND_LEAVE, tmp2, PKTS_PER_DATA_BUFFER // if we've copied this many samples, we're done

	// if write head is 0 or less, reset it to end of backup buffer
	qbge RESET_COPY_HEAD, tmp1, 0 // qbge    myLabel, r3, r4    // Branch if r4 >= r3
	DONE_RESETTING_COPY_HEAD:	
	
	QBA COPY_ONE_SAMPLE // copy another sample

RESET_COPY_HEAD:
	mov tmp1, BYTES_PER_DATA_BUFFER
	qba DONE_RESETTING_COPY_HEAD
	
SET_DELIVERED_BIT_AND_LEAVE:	
	// Set "data delivered" bit
	mov tmp0, 1
	mov tmp1, ADDR_CPU_PRU_CTRL_REG
	SBBO tmp0, tmp1, OFST_PRU_DATA_READY, 4

	qba DONE_DELIVERING
	

RESET_WRITE_HEAD:
	mov idx_in_pru_data_buf, 0
	mov pru_data_buf_write_head, 0
	qba DONE_RESETTING_WRITE_HEAD


	

	
COPY_NEW_ACTUATION_SCHEDULE:
//     - copy from CPU-sch-buf to PRU-sch-buf, then set 'ack-new-sch' flag
	// assume format is:
	// uint32 cycle time
	// uint32 direction & stby gpios
	// uint32 duty cycle
	// uint32 reserved

	// For simplicity,
	// Totally overwrite our existing actuation schedule.
	// Later: figure out how to blend them.

	// Remember the last time heard from CPU:
	LBCO time_of_last_cpu_cmd_sch, C28, 0xC, 4
	
	// How many new pkts?
	lbbo num_cmd_pkts_in_buffer, rADDR_CPU_PRU_CTRL_REG, OFST_CPU_NEW_SCHED, 4

	// Clear "cpu new sched" bit
	mov tmp0, 0
	mov tmp1, ADDR_CPU_PRU_CTRL_REG
	SBBO tmp0, tmp1, OFST_CPU_NEW_SCHED, 4
	
	mov tmp2, 0 // num pkts copied
	mov tmp1, 0 // addr offset 
	
  COPY_ONE_PKT:
	// todo: loop for as many ints as are in a cmd pkt.
	lbbo tmp0, rADDR_CPU_CMD_BUF, tmp1, 4
	sbbo tmp0, rADDR_PRU_CMD_BUF, tmp1, 4
	add tmp1, tmp1, 4
	lbbo tmp0, rADDR_CPU_CMD_BUF, tmp1, 4
	sbbo tmp0, rADDR_PRU_CMD_BUF, tmp1, 4
	add tmp1, tmp1, 4
	lbbo tmp0, rADDR_CPU_CMD_BUF, tmp1, 4
	sbbo tmp0, rADDR_PRU_CMD_BUF, tmp1, 4
	add tmp1, tmp1, 4
	lbbo tmp0, rADDR_CPU_CMD_BUF, tmp1, 4
	sbbo tmp0, rADDR_PRU_CMD_BUF, tmp1, 4
	add tmp1, tmp1, 4

	add tmp2, tmp2, 1 // # cmd pkts copied so far
	
	qbne COPY_ONE_PKT, tmp2, num_cmd_pkts_in_buffer // copy another pkt unless we've got 'em all

// done copying the new cmd schedule over.
	
	// Set "pru ack sched" bit
	mov tmp0, 1
	mov tmp1, ADDR_CPU_PRU_CTRL_REG
	sbbo tmp0, tmp1, OFST_PRU_ACK_SCHED, 4
	mov pru_cmd_buf_read_head, 0 // reset read head to start of new cmd buffer
	
// all done copying new :
	qba DONE_COPYING_NEW_SCH





INIT_ADC:
	
	mov tmp1, ADDR_ADC
        LBBO tmp0, tmp1, OFFSET_CTRL, 4	// Disable ADC so we can config it.
        CLR  tmp0.t0
        SBBO tmp0, tmp1, OFFSET_CTRL, 4

        MOV tmp0, 0 // To capture 1 adc channel at full speed, set the clock-divider to 0 (whole reg?)
        SBBO tmp0, tmp1, OFFSET_ADC_CLKDIV, 4

	// Now we configure the first step of the ADC-conversion-state-machine. 

	// Initially disable all steps of the state machine.
	// We'll trigger a sample by enabling one later on.
	// See "single-shot" vs "continuous" in TRM.

        LBBO tmp0, tmp1, OFFSET_STEPENABLE, 4
        CLR  tmp0, 16   // top 16 bits are reserved.
        SBBO tmp0, tmp1, OFFSET_STEPENABLE, 4


	// Configure the 1st step of ADC stat machine

	// Use `SET` and `CLR` here to set the bits correctly. (Note:
	// everything's spelled out here for pedagogical purposes; could
	// shorten the code a lot.)

        LBBO tmp0, tmp1, OFFSET_STEPCONFIG1, 4
        CLR tmp0.t27   // disable range-check
        CLR tmp0.t26   // store in FIFO0
        CLR tmp0.t25   // differential ctrl pin (?)

        // SEL_RFM pins SW configuration. (?)
        CLR tmp0.t24
        CLR tmp0.t23   

        // SEL_INP pins SW configuration. (0000 = Channel 1, 0111 = Channel 8)
        CLR tmp0.t22
        CLR tmp0.t21
        CLR tmp0.t20
        CLR tmp0.t19

        // SEL_INM pins for negative differential. (?) (0000 = Channel 1, 0111 = Channel 8)
        CLR tmp0.t18
        CLR tmp0.t17
        CLR tmp0.t16
        CLR tmp0.t15

        // SEL_RFP pins SW configuration. (000 = VDDA_ADC)
        CLR tmp0.t14
        CLR tmp0.t13
        CLR tmp0.t12

        // WPNSW pin SW configuration (, YPNSW, XNPSW, ... ) (???)
        CLR tmp0.t11
        CLR tmp0.t10
        CLR tmp0.t9
        CLR tmp0.t8        
        CLR tmp0.t7        
        CLR tmp0.t6        
        CLR tmp0.t5        

        // Number of samplings to average: 
        // 000 = No average.
        // 001 = 2 samples average.
        // 010 = 4 samples average.
        // 011 = 8 samples average. 100 = 16 samples average.
        CLR tmp0.t4
        CLR tmp0.t3
        CLR tmp0.t2

        // Mode:
        // 00 = SW enabled, one-shot.
        // 01 = SW enabled, continuous.
        // 10 = HW synchronized, one-shot. 
        // 11 = HW synchronized, continuous.        
        CLR tmp0.t1
        CLR tmp0.t0

        // Write it back to the ADC register:
        SBBO tmp0, tmp1, OFFSET_STEPCONFIG1, 4

	// Now we're ready to enable the ADC.
	// It won't do anything because we've disabled all the steps.
        LBBO tmp0, tmp1, OFFSET_CTRL, 4
        SET  tmp0.t2 // 1 = Step configuration registers are writable. Needed to trigger a sample.
        SET  tmp0.t1 // 1 = Store the Step ID number with the captured ADC data in the FIFO.
	             // (good to verify correct channel is being read)
        SET  tmp0.t0 // 1 = Turn on the ADC. 
        SBBO tmp0, tmp1, OFFSET_CTRL, 4 // now the ADC is on, so the state  machine is running,
						   // but there are no enabled steps, so it doesn't do anyhting.
	RET


RESET_CYCLE_COUNTER:
// Reset the cycle counter when it maxes out: disable counter, set 0 to cycle counter reg, enable counter:
	LBCO   tmp0, C28, 0, 4      // Disable CYCLE counter
	CLR    tmp0, 3
	SBCO   tmp0, C28, 0, 4
	MOV    tmp0, 0              // Set cycle count to 0
	SBCO   tmp0, C28, 0xC, 4
	LBCO   tmp0, C28, 0, 4      // Enable CYCLE counter
	SET    tmp0, 3
	SBCO   tmp0, C28, 0, 4
	
	RET



INIT_REGISTERS:

	// init named registers
	// (Copy list of named regs above to here, then init them.)

	mov tmp0 			, 0
	mov tmp1 			, 0
	mov tmp2 			, 0
	mov tmp3 			, 0
	mov current_time 		, 0
	mov cycles_at_next_sample_time 	, SAMPLE_PERIOD
	mov time_of_last_cpu_data_req	, 0
	mov gpio_cmd			, 0
	mov gpio_actual			, 0
	mov pru_cmd_buf_read_head	, 0
	mov num_cmd_pkts_in_buffer	, 0
	mov adc_value			, 0
	mov pru_data_buf_write_head	, 0
	mov idx_in_pru_data_buf		, 0
	mov num_total_samples		, 0
	mov idx_in_pru_cmd_buf		, 0
	mov sample_time			, 0
	mov eqep			, 0
	mov time_of_last_cpu_cmd_sch	, 0
	mov rADDR_CPU_PRU_CTRL_REG  	, ADDR_CPU_PRU_CTRL_REG  		
	mov rADDR_CPU_DATA_BUF      	, ADDR_CPU_DATA_BUF      	
	mov rADDR_PRU_DATA_BUF      	, ADDR_PRU_DATA_BUF      	
	mov rADDR_CPU_CMD_BUF       	, ADDR_CPU_CMD_BUF       	
	mov rADDR_PRU_CMD_BUF       	, ADDR_PRU_CMD_BUF       	
	
	ret


ACTUATE:
	// cmd pkt: 4 words = 16 bytes = 0x10 bytes
	//
	// - cycle count
	// - sample num
	// - gpio states
	// - duty cycle

	// for simplicity, just actuate w/ the current sample in the buffer.
	// Don't try to be fancy by matching the commanded sample time.
	
	// pkt structure: (int) time, (int) gpio, (int) duty, (int) reserved
	// read gpio cmd int
	mov tmp0, pru_cmd_buf_read_head
	add tmp0, tmp0, 8 // gpio states is 3rd int
	mov tmp1, ADDR_PRU_CMD_BUF
	lbbo gpio_cmd, tmp1, tmp0, 4 

	// The DTO specifies that only bits 0,1,2,5 of r30 belong to the PRU.
	// Who knows what toggling the other bits of r30 will do. 
	// So you're only allowed to modify r30 bits 0,1,2,5.
	// I want to set bits 0,1,2,5 of r30 equal to bits 0,1,2,5 of gpio_cmd. How??
	// http://stackoverflow.com/questions/4439078/how-do-you-set-only-certain-bits-of-a-byte-in-c-without-affecting-the-rest
	// value = (value & ~mask) | (newvalue & mask);
	// Or:
	// value &= ~mask
	// newvalue &= mask
	// value |= newvalue
	mov tmp1, r30                      // tmp1 = value
	and tmp1, tmp1, NOT_GPIO_MASK      // value &= ~mask    (zero out bits we may change)
	and gpio_cmd, gpio_cmd, GPIO_MASK  // newvalue &= mask  (don't change any bits you're not allowed to)
	or  tmp1, tmp1, gpio_cmd           // value |= newvalue (add in the gpio cmd bits)
	mov r30, tmp1                      // write new gpio vals to regs. All should change at once.
	mov gpio_actual, tmp1
	
	add pru_cmd_buf_read_head, pru_cmd_buf_read_head, (INTS_PER_CMD_PKT*BYTES_PER_INT)	// advance read head to next cmd.
	add idx_in_pru_cmd_buf, idx_in_pru_cmd_buf, 1



	qba DONE_ACTUATING


CLEAR_PRU0_DATA_RAM:
	mov tmp0, 0
	mov tmp1, ADDR_PRU0_DATA_RAM
	mov tmp2, (ADDR_PRU0_DATA_RAM+BYTES_PER_DATA_RAM)
    CLEAR_ONE_INT:
	sbbo tmp0, tmp1, 0, 4
	add tmp1, tmp1, 4
	// if addr < max addr of the PRU0 data ram, repeat
	qbgt CLEAR_ONE_INT, tmp1, tmp2
	ret