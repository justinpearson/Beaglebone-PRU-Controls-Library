// read adc ch 0 periodically.



	
	
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

#define SAMPLE_PERIOD (1000000-100) // in cycles (5ns / cycle)
#define MAX_SAMPLES 10
	
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
    #define num_samples     r11
    #define prev_time         r12
    #define current_time    r13
    #define adc_value   r14
	#define reg_MAX_SAMPLES r15
#define stop_time r16

// Start the code:

    .origin 0
    .entrypoint INIT

    INIT:



	MOV reg_SAMPLE_PERIOD, SAMPLE_PERIOD

	mov write_head, 4 // where in pru data ram we're gonna write to. (4, bc we reserve 0 for "num samples"

	mov num_samples, 0
	mov reg_MAX_SAMPLES, MAX_SAMPLES

	

// Set up the PRU's ability to access memory outside its own private 8kB
	
	// Source:
// http://www.embedded-things.com/bbb/understanding-bbb-pru-shared-memory-access/


	// Note: this guy:
	// http://nomel.org/post/30006622413/beaglebone-tutorial-accessing-main-memory-from
	// says you shouldn't poll the L3 / L4 memory bus from the PRU.
	// Does the ADC line count as L3 / L4?
	
// Put this in a header file
//	#define CONST_PRUCFG         C4
//	#define CONST_PRUSHAREDRAM   C28
//
//	#define PRU0_CTRL            0x22000
//	#define PRU1_CTRL            0x24000
//
//	#define CTPPR0               0x28
//
//	#define OWN_RAM              0x000
//	#define OTHER_RAM            0x020
//	#define SHARED_RAM           0x100
//
//	// Start your code with this
//	LBCO    r0, CONST_PRUCFG, 4, 4          // Enable OCP master port
//	CLR     r0, r0, 4
//	SBCO    r0, CONST_PRUCFG, 4, 4
//	MOV     r0, SHARED_RAM                  // Set C28 to point to shared RAM
//	MOV     r1, PRU1_CTRL + CTPPR0
//	SBBO    r0, r1, 0, 4

////////////	


	// original code from github
	// also derek, eg
	// http://exploringbeaglebone.com/chapter13/#The_Programs
	LBCO r0, C4, 4, 4					// Load Bytes Constant Offset (?)
	CLR  r0, r0, 4						// Clear bit 4 in reg 0
	SBCO r0, C4, 4, 4					// Store Bytes Constant Offset

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
        MOV reg_PRU_DATA_RAM_BASE, 0                      // same. 


	
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

	
ADC_SAMPLE:

	// Until it's time to sample, spin:
WAIT_FOR_SAMPLE_TIME:
	LBCO current_time, C28, 0xC, 4     // Load cycle count
	SUB delta_time, current_time, prev_time
	QBGT WAIT_FOR_SAMPLE_TIME, delta_time, reg_SAMPLE_PERIOD  // from doc:     qbgt    myLabel, r2.w0, 5  // Branch if 5 > r2.w0

// http://processors.wiki.ti.com/index.php/PRU_Assembly_Instructions#Quick_Branch_if_Less_Than_.28QBLT.29

	SBBO just_adc0_plz, reg_ADDR_OF_ADC, OFFSET_STEPENABLE, 4   // triggers a capture / sample!
	LBCO prev_time, C28, 0xC, 4     // save the time that we actually triggered the sample.

// Q: If it's one-shot, does that mean we have to re-enable not the whole ADC but the STEPENABLE reg each time? Yes, I think so.


// Spin while there's nothing in the FIFO:

    WAIT_FOR_FIFO0:
        LBBO tmp0, reg_ADDR_OF_ADC, OFFSET_FIFO0COUNT, 4
        AND tmp0, tmp0, 127    // only bits 0 thru 6 are unreserved, so turn others off and keep only bits 0-6.
        QBEQ WAIT_FOR_FIFO0, tmp0, 0

    RETRIEVE_VALUE:
	// There's a sample in the FIFO!

	// How long did it take?
	LBCO stop_time, C28, 0xC, 4     // Load "after" cycle count

	
        LBBO tmp0, reg_ADDR_OF_FIFO0DATA, 0, 4  // grab the sample from the ADC
	// keep the 12 lowest bits
	MOV tmp1, 0xfff
        AND adc_value, tmp0, tmp1


	SBBO prev_time, reg_PRU_DATA_RAM_BASE, write_head, 4 //  copy time of sample value to PRU data ram
	ADD write_head, write_head, 4
	SBBO adc_value, reg_PRU_DATA_RAM_BASE, write_head, 4 //  copy adc value to PRU data ram
	ADD write_head, write_head, 4
	SBBO stop_time, reg_PRU_DATA_RAM_BASE, write_head, 4 //  copy adc value to PRU data ram
	ADD write_head, write_head, 4


	ADD num_samples, num_samples, 1

	// If num_samples < max samples, do another.
	QBLT ADC_SAMPLE, reg_MAX_SAMPLES, num_samples  // from doc:    qblt    myLabel, r3, r4    // Branch if r4 < r3

	// All done. Before quitting, write how many adc samples we got:
	SBBO num_samples, reg_PRU_DATA_RAM_BASE, 0, 4
	
    QUIT:
        MOV R31.b0, PRU0_ARM_INTERRUPT+16   // Send notification to Host for program completion
        HALT
