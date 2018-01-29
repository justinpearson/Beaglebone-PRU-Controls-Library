// WTF, we seem to not initialize reg_ADDR_OF_ADC!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Also we've been lazy and haven't changed the name from adc to eqep.


	// from
	// https://github.com/Teknoman117/beaglebot/tree/master/encoders
	// beaglebot/encoders/patches/sources/tieqep.c

// eQEP register offsets from its base IO address
#define QPOSCNT    0x0000
#define QPOSINIT 0x0004
	// ...


	
	
#define PRU0_ARM_INTERRUPT 19

// Next we `#define` the ADC offset registers.

#define ADDR_PRU0_CTRL 0x00022000
#define ADDR_CYCLE_COUNTER 0x0002200C	

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
#define rPRU0_DATA_RAM r15
#define rCYCLE_COUNTER r16
#define cycles r17
#define rPRU0_CTRL r18
#define MAX_U32 r19

// Start the code:

    .origin 0
    .entrypoint START

    START:

	mov MAX_U32, 0xffffffff

// Set up the PRU's ability to access memory outside its own private 8kB data ram
	// http://exploringbeaglebone.com/chapter13/#The_Programs
	LBCO r0, C4, 4, 4		// Load Bytes Constant Offset (?)
	CLR  r0, r0, 4			// Clear bit 4 in reg 0
	SBCO r0, C4, 4, 4		// Store Bytes Constant Offset

        MOV reg_PRU_DATA_RAM_BASE, 0                      // same. 



  MOV rPRU0_CTRL, ADDR_PRU0_CTRL // PRU0 CTRL register -- reg where 'cycle ctr enable' lives (only do this once)

  // "Cycle counter": TRM 4.5.1 (PRU_ICSS_PRU_CTRL regs: 0x00022000 for PRU0), offset 0xC: 32-bit CYCLE register	
  MOV rCYCLE_COUNTER, ADDR_CYCLE_COUNTER // PRU0 cycle counter	

	
// reset cycle counter -- eqep seems to not update after cycle counter maxes out.
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



	
    RETRIEVE_VALUE:
        LBBO tmp0, reg_ADDR_OF_ADC, QPOSCNT, 4 // read eqep0 position counter
	LBBO tmp2, rCYCLE_COUNTER, 0, 4
	SBBO tmp0, reg_PRU_DATA_RAM_BASE, 0, 4 //  copy eqep  value to PRU data ram
	SBBO tmp2, reg_PRU_DATA_RAM_BASE, 4, 4  // "start" time

	
	MOV tmp1, 10000  // this many iters, read encoder and write to data ram
WAIT:	
	SUB tmp1, tmp1, 1
	QBNE WAIT, tmp1, 0
	QBA RETRIEVE_VALUE

	// never quits



    QUIT:
        MOV R31.b0, PRU0_ARM_INTERRUPT+16   // Send notification to Host for program completion
        HALT
