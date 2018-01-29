



	
	
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

// We'll set up these variable names instead of using the raw register names: 

    // Scratch registers:
    #define tmp0        r1
    #define tmp1        r2
    #define tmp2        r3
    #define tmp3        r4
    #define tmp4        r5

    // Regs for memory addrs (eg, ADDR_OF_FIFO0DATA etc.)
    #define reg_ADDR_OF_ADC        r6
    #define reg_ADDR_OF_FIFO0DATA   r7
    #define out_buff    r8
    #define reg_PRU_DATA_RAM_BASE      r9   // Data RAM addr 0x00000000

    #define value       r10
    #define channel     r11
    #define ema         r12
    #define encoders    r13
    #define cap_delay   r14


// Start the code:

    .origin 0
    .entrypoint START

    START:


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

	

// Note:
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


// Q: If it's one-shot, does that mean we have to re-enable not the whole ADC but the STEPENABLE reg each time? Yes, I think so.

        // Write it back to the ADC register:
        SBBO tmp0, reg_ADDR_OF_ADC, OFFSET_STEPCONFIG1, 4

// Now we're ready to enable the ADC:
        LBBO tmp0, reg_ADDR_OF_ADC, OFFSET_CTRL, 4

        SET  tmp0.t2 // 1 = Step configuration registers are writable. Needed to trigger a sample.
        SET  tmp0.t1 // 1 = Store the Step ID number with the captured ADC data in the FIFO. (good to verify correct channel is being read)
        SET  tmp0.t0 // 1 = Turn on the ADC. 

        SBBO tmp0, reg_ADDR_OF_ADC, OFFSET_CTRL, 4

// Sample:
	MOV tmp0, 2   // don't want 0th bit: "enable TS charge step", want bit 1: enable step 1.
	SBBO tmp0, reg_ADDR_OF_ADC, OFFSET_STEPENABLE, 4   // triggers a capture / sample!
	

// Spin while there's nothing in the FIFO:

    WAIT_FOR_FIFO0:
        LBBO tmp0, reg_ADDR_OF_ADC, OFFSET_FIFO0COUNT, 4
        AND tmp0, tmp0, 127    // only bits 0 thru 6 are unreserved, so turn others off and keep only bits 0-6.
        QBEQ WAIT_FOR_FIFO0, tmp0, 0

    RETRIEVE_VALUE:
        LBBO tmp0, reg_ADDR_OF_FIFO0DATA, 0, 4
	// keep the 12 lowest bits
	MOV tmp1, 0xfff
        AND tmp0, tmp0, tmp1
        SBBO tmp0, reg_PRU_DATA_RAM_BASE, 0, 4 //  copy adc value to PRU data ram

	QBA QUIT




    QUIT:
        MOV R31.b0, PRU0_ARM_INTERRUPT+16   // Send notification to Host for program completion
        HALT
