// Every 5ms, log adc & cycle counter to "backup buffer"
// Watch the 0th int of data ram for msg from CPU.
// When CPU says so, copy from backup buffer to main buffer.
// Tell CPU we've done it.	



	
    #define PRU0_ARM_INTERRUPT 19


	
// Next we `#define` the ADC offset registers.
	
#define ADDR_OF_ADC         0x44e0d000
#define OFFSET_CTRL         0x0040
#define OFFSET_ADCSTAT      0x0044
#define OFFSET_ADC_CLKDIV   0x004c
#define OFFSET_STEPENABLE   0x0054
#define OFFSET_STEPCONFIG1  0x0064
#define OFFSET_STEPDELAY1   0x0068
#define OFFSET_FIFO0COUNT   0x00e4
#define ADDR_OF_FIFO0DATA   (ADDR_OF_ADC + 0x0100)

#define SAMPLE_PERIOD (1000000) // in cycles (5ns / cycle)
#define MAX_SAMPLES 10


#define ADDR_PRU_DATA_RAM_BASE 0x00000000
#define ADDR_BUFFER (ADDR_PRU_DATA_RAM_BASE + 4) // 4: skip the 4-byte ctrl-register at base addr.
#define SAMPLES_PER_BUFFER 64
#define BYTES_PER_SAMPLE 16
#define ADDR_BACKUP_BUFFER (ADDR_BUFFER + SAMPLES_PER_BUFFER*BYTES_PER_SAMPLE)


	
	
// We'll set up these variable names instead of using the raw register names: 

    // Scratch registers:
#define tmp0        r1
#define tmp1        r2
#define tmp2        r3
#define delta_time        r4
#define reg_SAMPLE_PERIOD        r5
#define reg_ADDR_OF_ADC        r6
#define reg_ADDR_OF_FIFO0DATA   r7
#define write_head    r8
#define reg_PRU_DATA_RAM_BASE      r9   // Data RAM addr 0x00000000
#define just_adc0_plz       r10
#define idx_in_backup_buffer     r11
#define prev_time         r12
#define current_time    r13
#define adc_value   r14
#define BOOGER r15
#define cycles_at_next_sample_time r16
#define reg_ADDR_BACKUP_BUFFER r17
#define reg_ADDR_BUFFER r18	
#define rPRU0_CTRL r19	
#define rCYCLE_COUNTER r20
#define num_total_samples r21
#define tmp3 r22
	
#define ADDR_PRU0_CTRL 0x00022000
#define ADDR_CYCLE_COUNTER 0x0002200C	
	
	
    .origin 0
    .entrypoint INIT

    INIT:
	mov num_total_samples, 0
	
	  MOV rCYCLE_COUNTER, ADDR_CYCLE_COUNTER // PRU0 cycle counter	
	MOV rPRU0_CTRL, ADDR_PRU0_CTRL // PRU0 CTRL register -- reg where 'cycle ctr enable' lives (only do this once)
	MOV reg_SAMPLE_PERIOD, SAMPLE_PERIOD
	mov write_head, 0 // (offset from ADDR_BUFFER) where in pru data ram we're gonna write to.

	mov idx_in_backup_buffer, 0
	mov reg_SAMPLE_PERIOD, SAMPLE_PERIOD
	mov cycles_at_next_sample_time, SAMPLE_PERIOD

	mov  reg_ADDR_BACKUP_BUFFER, ADDR_BACKUP_BUFFER
	mov  reg_ADDR_BUFFER, ADDR_BUFFER




// Set up the PRU's ability to access memory outside its own private 8kB
// http://exploringbeaglebone.com/chapter13/#The_Programs
LBCO r0, C4, 4, 4	// Load Bytes Constant Offset (?)
CLR  r0, r0, 4	 	// Clear bit 4 in reg 0
SBCO r0, C4, 4, 4	// Store Bytes Constant Offset

//////////////////////////////////////

// Enable cycle counter

	// First define some regs
	// source: http://www.embedded-things.com/bbb/understanding-bbb-pru-shared-memory-access/
	// Source: https://github.com/omcaree/bbb-prupwm/blob/master/include/pru.hp

	// Address for the Constant table Block Index Register (CTBIR)
	#define CTBIR          0x22020

	// Address for the Constant table Programmable Pointer Register 0(CTPPR_0)
	#define CTPPR_0         0x22028

	// Address for the Constant table Programmable Pointer Register 1(CTPPR_1)
	#define CTPPR_1         0x2202C
	

	// source:
	// http://theembeddedkitchen.net/beaglelogic-building-a-logic-analyzer-with-the-prus-part-1/449
	MOV    R1, CTPPR_0
	MOV    R2, 0x00000220      // C28 = 00_0220_00h = PRU0 CFG Registers
	SBBO   R2, R1, 0, 4

	LBCO   R1, C28, 0, 4      // Enable CYCLE counter
	SET    R1, 3
	SBCO   R1, C28, 0, 4


	

// Note: Can't use literal numbers in 
	// If you define
//	    #define ADDR_OF_FIFO0DATA   (ADDR_OF_ADC + 0x0100)
	// and do this:
//	        LBBO tmp0, ADDR_OF_FIFO0DATA, 0, 4
	// you get error:
//	firmware-j0.p(163) Error: Operand 2 '(0x44e0d000 + 0x0100)' invalid register or register mode
	// To fix:
//         LBBO tmp0, reg_ADDR_OF_FIFO0DATA, 0, 4

	// Therefore we do this:
	
        MOV reg_ADDR_OF_ADC, ADDR_OF_ADC                  // I guess it should be in a register, not just a #define
        MOV reg_ADDR_OF_FIFO0DATA, ADDR_OF_FIFO0DATA      // same.
        MOV reg_PRU_DATA_RAM_BASE, ADDR_PRU_DATA_RAM_BASE                      // same. 


	
// Next, before we configure the ADC, we should disable it. 
// Looks like we just set the lowest bit to "off":        

        // Disable ADC
        LBBO tmp0, reg_ADDR_OF_ADC, OFFSET_CTRL, 4
        CLR  tmp0.t0
        SBBO tmp0, reg_ADDR_OF_ADC, OFFSET_CTRL, 4


// To set at full speed, set the clock-divider to 0:

        // Put ADC capture to its full speed
        MOV tmp0, 0    // just write 0 to the whole reg?
        SBBO tmp0, reg_ADDR_OF_ADC, OFFSET_ADC_CLKDIV, 4

// Now we configure the first step of the ADC-conversion-state-machine. 

// Initially disable all steps of the state machine.
// We'll trigger a sample by enabling one later on.
// See "single-shot" vs "continuous" in TRM.

        LBBO tmp0, reg_ADDR_OF_ADC, OFFSET_STEPENABLE, 4
        CLR  tmp0, 16   // top 16 bits are reserved.
        SBBO tmp0, reg_ADDR_OF_ADC, OFFSET_STEPENABLE, 4


// Configure the 1st step: 
 

// Use `SET` and `CLR` here to set the bits correctly. (Note: everything's spelled out here for pedagogical purposes; could shorten the code a lot.)

        LBBO tmp0, reg_ADDR_OF_ADC, OFFSET_STEPCONFIG1, 4
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
        SBBO tmp0, reg_ADDR_OF_ADC, OFFSET_STEPCONFIG1, 4

// Now we're ready to enable the ADC. It won't do anything because we've disabled all the steps.
        LBBO tmp0, reg_ADDR_OF_ADC, OFFSET_CTRL, 4
        SET  tmp0.t2 // 1 = Step configuration registers are writable. Needed to trigger a sample.
        SET  tmp0.t1 // 1 = Store the Step ID number with the captured ADC data in the FIFO. (good to verify correct channel is being read)
        SET  tmp0.t0 // 1 = Turn on the ADC. 
        SBBO tmp0, reg_ADDR_OF_ADC, OFFSET_CTRL, 4 // now the ADC is on, so the state  machine is running, but there are no enabled steps, so it doesn't do anyhting.

// Sample:
	MOV just_adc0_plz, 2   // don't want 0th bit: "enable TS charge step", want bit 1: enable step 1. (only need to do this once.)


	
	

// Reset the cycle counter

	// Disable cycle counter
	// "Cycle counter enable": bit 3 of CTRL register (4.5.1.1):
	// 0h offset in PRU_ICSS_PRU_CTRL registers (4.5.1):
	// 0x00022000 in 4.3.1.2 Local Data Memory Map
	LBBO tmp0, rPRU0_CTRL, 0, 4   // read PRU_CTRL reg into register tmp0
	CLR  tmp0.t3  	              // clr 'cycle ctr enable' bit
	SBBO tmp0, rPRU0_CTRL, 0, 4         // push tmp0 back into the CTRL reg

	// Reset cycle counter to 0
	MOV tmp0, 0
	SBBO tmp0, rCYCLE_COUNTER, 0, 4

	// Enable cycle counter
	LBBO tmp0, rPRU0_CTRL, 0, 4   // read reg into register tmp0
	SET  tmp0.t3  	              // set 'cycle ctr enable' bit
	SBBO tmp0, rPRU0_CTRL, 0, 4         // push tmp0 back into the CTRL reg


	
//- PRU code:
//  - Spin until a sample-time. (Every 5ms)
//  - Start an ADC sample.
//  - Spin until ADC sample completes.
//  - Copy into backbuf.
//  - If "CPU wants" bit set and "Data delivered" bit not set,
//    - Copy backbuf into buf.
//    - Set "Data delivered" bit.
	
ADC_SAMPLE:

	// Until it's time to sample, spin:
WAIT_FOR_SAMPLE_TIME:
	LBCO current_time, C28, 0xC, 4     // Load cycle count
	qbgt WAIT_FOR_SAMPLE_TIME, current_time, cycles_at_next_sample_time
	// current cycle count >= cycles_at_next_sample_time. So time for a sample.
	// advance cycles_at_next in steps of SAMPLE_PERIOD until it's greater than cycle count.
ADVANCE_NEXT_SAMPLE_TIME:	
	add cycles_at_next_sample_time,  cycles_at_next_sample_time, reg_SAMPLE_PERIOD
	qble ADVANCE_NEXT_SAMPLE_TIME, current_time, cycles_at_next_sample_time

	// old but works:
//	SUB delta_time, current_time, prev_time
//	QBGT WAIT_FOR_SAMPLE_TIME, delta_time, reg_SAMPLE_PERIOD
	// from doc:     qbgt    myLabel, r2.w0, 5  // Branch if 5 > r2.w0
// end old

	
TRIGGER_SAMPLE:	
	SBBO just_adc0_plz, reg_ADDR_OF_ADC, OFFSET_STEPENABLE, 4   // triggers a capture / sample!
	LBCO prev_time, C28, 0xC, 4     // save the time that we actually triggered the sample.

// Spin while there's nothing in the FIFO:
WAIT_FOR_FIFO0:
        LBBO tmp0, reg_ADDR_OF_ADC, OFFSET_FIFO0COUNT, 4
        AND tmp0, tmp0, 127    // only bits 0 thru 6 are unreserved, so turn others off and keep only bits 0-6.
        QBEQ WAIT_FOR_FIFO0, tmp0, 0

RETRIEVE_VALUE:
	// There's a sample in the FIFO!
        LBBO tmp0, reg_ADDR_OF_FIFO0DATA, 0, 4  // grab the sample from the ADC
	MOV tmp1, 0xfff	// keep the 12 lowest bits (12-bit adc)
        AND adc_value, tmp0, tmp1
	ADD num_total_samples, num_total_samples, 1
	SBBO num_total_samples, reg_ADDR_BACKUP_BUFFER, write_head, 4 // copy sample # to backup buffer
	ADD write_head, write_head, 4
	SBBO prev_time, reg_ADDR_BACKUP_BUFFER, write_head, 4 // copy cycle cnt to backup buffer 
	ADD write_head, write_head, 4
	SBBO adc_value, reg_ADDR_BACKUP_BUFFER, write_head, 4 //  copy adc value to backup buffer
	ADD write_head, write_head, 4
	mov tmp1, 0xa4a4a4a4 // garbage eye-catching value
	SBBO tmp1, reg_ADDR_BACKUP_BUFFER, write_head, 4 //  copy garbage value to backup buffer
	ADD write_head, write_head, 4

	ADD idx_in_backup_buffer, idx_in_backup_buffer, 1


	// If "CPU Wants" bit is and "Data delivered" bit not set, copy backbuf into buf.
        LBBO tmp0, reg_PRU_DATA_RAM_BASE, 0, 4
	AND tmp0, tmp0, 3 // keep bottom 2 bits
	QBEQ DELIVER_TO_CPU, tmp0, 1 // cpu wants bit: bit 0. data ready bit: bit 1. So eq to 1 means cpu wants and data not delivered.
DONE_DELIVERING:	


	// If buf full, start overwriting old ones.
	// NOTE: This fn modifies idx_in_backup_buffer and write_head, so must come
	// after DELIVER_TO_CPU, since DELIVER_TO_CPU uses those to help it
	// write to the output buffer.
	QBEQ RESET_WRITE_HEAD, idx_in_backup_buffer, SAMPLES_PER_BUFFER
DONE_RESETTING_WRITE_HEAD:



	
	// Take another sample
	QBA ADC_SAMPLE

//////////////////////////////////////
// Functions not in main prog flow
//////////////////////////////////////
	
QUIT:
	
        MOV R31.b0, PRU0_ARM_INTERRUPT+16   // Send notification to Host for program completion
        HALT
	
DELIVER_TO_CPU:

	// # sample:
//	LBBO tmp0, reg_PRU_DATA_RAM_BASE, 4, 4
//	SBBO tmp0, reg_PRU_DATA_RAM_BASE, 16,4
	// cycle counter:
//	LBBO tmp0, reg_PRU_DATA_RAM_BASE, 8, 4
//	SBBO tmp0, reg_PRU_DATA_RAM_BASE, 20,4
	// adc value:
//	LBBO tmp0, reg_PRU_DATA_RAM_BASE, 12, 4
//	SBBO tmp0, reg_PRU_DATA_RAM_BASE, 24, 4
//	QBA DONE_COPYING	

	// copy bak buf into buf.
	MOV tmp1, write_head // addr offset in backup buffer
	mov tmp3, (SAMPLES_PER_BUFFER*BYTES_PER_SAMPLE) // addr offset in cpu's buffer
	MOV tmp2, 0 // num samples copied
COPY_ONE_SAMPLE:
	// 4 uints per sample:
	sub tmp1, tmp1, 4
	sub tmp3, tmp3, 4
	LBBO tmp0, reg_ADDR_BACKUP_BUFFER, tmp1, 4 
	SBBO tmp0, reg_ADDR_BUFFER, tmp3, 4
	sub tmp1, tmp1, 4
	sub tmp3, tmp3, 4	
	LBBO tmp0, reg_ADDR_BACKUP_BUFFER, tmp1, 4 
	SBBO tmp0, reg_ADDR_BUFFER, tmp3, 4
	sub tmp1, tmp1, 4
	sub tmp3, tmp3, 4	
	LBBO tmp0, reg_ADDR_BACKUP_BUFFER, tmp1, 4 
	SBBO tmp0, reg_ADDR_BUFFER, tmp3, 4
	sub tmp1, tmp1, 4
	sub tmp3, tmp3, 4	
	LBBO tmp0, reg_ADDR_BACKUP_BUFFER, tmp1, 4 
	SBBO tmp0, reg_ADDR_BUFFER, tmp3, 4

	ADD tmp2, tmp2, 1  // num_samples++
	QBEQ SET_DELIVERED_BIT, tmp2, SAMPLES_PER_BUFFER // if we've copied this many samples, we're done

	// if write head is 0 or less, reset it to end of backup buffer
	qbge RESET_COPY_HEAD, tmp1, 0 // qbge    myLabel, r3, r4    // Branch if r4 >= r3
DONE_RESETTING_COPY_HEAD:	
	
	QBA COPY_ONE_SAMPLE // copy another sample

///////////////////////////
// working code (but samples not nec in order)

		// copy bak buf into buf.
//	MOV tmp1, 0 // addr offset
//	MOV tmp2, 0 // num samples copied
//COPY_ONE_SAMPLE:
//	// 4 uints per sample:
//	LBBO tmp0, reg_ADDR_BACKUP_BUFFER, tmp1, 4 
//	SBBO tmp0, reg_ADDR_BUFFER, tmp1, 4
//	ADD tmp1, tmp1, 4
//	LBBO tmp0, reg_ADDR_BACKUP_BUFFER, tmp1, 4 
//	SBBO tmp0, reg_ADDR_BUFFER, tmp1, 4
//	ADD tmp1, tmp1, 4
//	LBBO tmp0, reg_ADDR_BACKUP_BUFFER, tmp1, 4 
//	SBBO tmp0, reg_ADDR_BUFFER, tmp1, 4
//	ADD tmp1, tmp1, 4
//	LBBO tmp0, reg_ADDR_BACKUP_BUFFER, tmp1, 4 
//	SBBO tmp0, reg_ADDR_BUFFER, tmp1, 4
//	ADD tmp1, tmp1, 4
//
//	ADD tmp2, tmp2, 1  // num_samples++
//	QBEQ SET_DELIVERED_BIT, tmp2, SAMPLES_PER_BUFFER // copy this many ints 
//	QBA COPY_ONE_SAMPLE
///////////////////

RESET_COPY_HEAD:
	mov tmp1, (SAMPLES_PER_BUFFER*BYTES_PER_SAMPLE)
	qba DONE_RESETTING_COPY_HEAD
	
SET_DELIVERED_BIT:	
	
	// Set "data delivered" bit
//        LBBO tmp0, reg_PRU_DATA_RAM_BASE, 0, 4
//	SET tmp0.t1 // 1st bit (0bit = "cpu wants" bit)
//	SBBO tmp0, reg_PRU_DATA_RAM_BASE, 0, 4
	mov tmp0, 2
	SBBO tmp0, reg_PRU_DATA_RAM_BASE, 0, 4

	qba DONE_DELIVERING
	
	
RESET_WRITE_HEAD:
	mov idx_in_backup_buffer, 0
	mov write_head, 0
	qba DONE_RESETTING_WRITE_HEAD

	