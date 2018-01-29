// If the CPU sets the bit for "I copied a new actuation schedule into the PRU0 data ram",
// the PRU copies it into another location, private to the PRU, so that the CPU can
// use their shared buffer. Then the PRU clears the "I copied..." bit.

// correction: cpu sets the int to "# of new cmd pkts for you to use in your actuation schedule."

// PRU sets their shared ctrl reg to 0 when it's done copying the new sch over.
	// That's how teh CPU tells if it's ok to copy a new sch in.
	
// Every 5ms, the PRU checks the cycle time. If the cycle time exceeds the next actuation time,
// set the GPIO pins accordingly. Advance the "play head" -- the addr of the
// actuation time. And copy over the next actuation time.


// CPU/PRU Sync Register: note: decide to use one 32-bit word for each bit of communication,
// hoping to avoid concurrency issues
// int 0: "cpu wants pru to copy over adc etc data"
// int 1: "pru done copying over data"
// int 2: "cpu has copied over new actuation schedule"
	

// size of cmd buffer
#define BYTES_PER_INT 		4
#define CMDS_PER_BUFFER 	64	
#define INTS_PER_CMD 		4
#define NUM_BYTES_IN_CMD_BUFFER (BYTES_PER_INT * INTS_PER_CMD * CMDS_PER_BUFFER)

	
// misc
#define INITIAL_REG_VALUE 0x22222222	
#define GPIO_MASK 	0b00100111  // bits 0,1,2,5 : DTO hooks these in r30 to pins like P9_27	
#define NOT_GPIO_MASK   0b11011000
	
// important addrs	
#define ADDR_PRU_DATA_RAM_BASE 	0x00000000
#define ADDR_PRU0_CTRL 		0x00022000
#define ADDR_CYCLE_COUNTER 	0x0002200C	
#define ADDR_CMD_BUFFER_FROM_CPU (ADDR_PRU_DATA_RAM_BASE + 4)
#define ADDR_CMD_BUFFER (ADDR_CMD_BUFFER_FROM_CPU + NUM_BYTES_IN_CMD_BUFFER)
#define ADDR_CMD_CPU_NEW_SCH (ADDR_PRU_DATA_RAM_BASE) // addr in pru data ram where cpu notifies pru of new cmd sch to copy in
	
// named registers
#define tmp0        			r1
#define tmp1        			r2
#define tmp2        			r3
#define num_cmd_pkts_in_buffer 		r4
#define rADDR_CMD_CPU_NEW_SCH 		r5
#define rCMD_BUFFER 			r6
#define rCMD_BUFFER_FROM_CPU 		r7
#define read_head 			r8
#define rPRU_DATA_RAM_BASE      	r9
#define current_time			r10
#define gpio_cmd			r11
#define cmd_time			r12


	
#define rPRU0_CTRL 			r19		
#define rCYCLE_COUNTER 			r20

	

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
	mov r29, INITIAL_REG_VALUE

	
	// init named registers
	mov tmp0, 			0
	mov tmp1, 			0
	mov tmp2, 			0
	mov num_cmd_pkts_in_buffer, 	0 		
	mov rADDR_CMD_CPU_NEW_SCH, 	ADDR_CMD_CPU_NEW_SCH
	mov rCMD_BUFFER, 		ADDR_CMD_BUFFER
	mov rCMD_BUFFER_FROM_CPU, 	ADDR_CMD_BUFFER_FROM_CPU
	mov read_head, 			0
	mov rPRU_DATA_RAM_BASE,      	ADDR_PRU_DATA_RAM_BASE
	mov rPRU0_CTRL, 		ADDR_PRU0_CTRL
	mov rCYCLE_COUNTER, 		ADDR_CYCLE_COUNTER
	mov current_time, 		0
	mov gpio_cmd,                   0




	
	// Set up the PRU's ability to access memory outside its own private 8kB
	// http://exploringbeaglebone.com/chapter13/#The_Programs
	LBCO r0, C4, 4, 4	// Load Bytes Constant Offset (?)
	CLR  r0, r0, 4	 	// Clear bit 4 in reg 0
	SBCO r0, C4, 4, 4	// Store Bytes Constant Offset




	

	MOV rCYCLE_COUNTER, ADDR_CYCLE_COUNTER // PRU0 cycle counter	
	MOV rPRU0_CTRL, ADDR_PRU0_CTRL // PRU0 CTRL register -- reg where 'cycle ctr enable' lives (only do this once)
       MOV rPRU_DATA_RAM_BASE, ADDR_PRU_DATA_RAM_BASE                      // same. 



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


// no cmd pkts yet. 
	mov num_cmd_pkts_in_buffer, 0
	
BEGIN_LOOP:	

	// Check ctrl register to see if CPU copied a new actuation schedule
	lbbo tmp0, rADDR_CMD_CPU_NEW_SCH, 0, 4
	qbne COPY_NEW_ACTUATION_SCHEDULE, tmp0, 0  // if nonzero, that's the number of new pkts!
DONE_COPYING_NEW_SCH:	

	// If we executed all our cmds, just gotta wait for a new set of cmds.
	qbeq BEGIN_LOOP, num_cmd_pkts_in_buffer, 0

	
	// If it's time to actuate,  do  it.
	LBBO current_time, rCYCLE_COUNTER, 0, 4      // Get current time
	lbbo cmd_time, rCMD_BUFFER, read_head, 4 // get time of next actuation (cmd time)
	qble ACTUATE, current_time, cmd_time // actuate if current time >= cmd time
DONE_ACTUATING:
	qba BEGIN_LOOP

ACTUATE:
	// pkt structure: (int) time, (int) gpio, (int) duty, (int) reserved
	// read gpio cmd int
	mov tmp0, read_head
	add tmp0, tmp0, 4
	lbbo gpio_cmd, rCMD_BUFFER, tmp0, 4 
	and gpio_cmd, gpio_cmd, GPIO_MASK // the DTO specifies that only bits 0,1,2,5 belong to the PRU
	// who knows what toggling the other bits of r30 will do. So
	// you're only allowed to modify r30 bits 0,1,2,5.
	// arg, I want to set bits 0,1,2,5 of r30 equal to bits 0,1,2,5 of gpio_cmd. How??
	// http://stackoverflow.com/questions/4439078/how-do-you-set-only-certain-bits-of-a-byte-in-c-without-affecting-the-rest
	mov tmp1, r30
	and tmp1, tmp1, NOT_GPIO_MASK  // zero out bits we may change
	or  tmp1, tmp1, gpio_cmd // add in the gpio cmd bits
	mov r30, tmp1         // write new gpio vals to regs. All should change at once.
	
	// cpy cmd pkt to our record of what was actually actuated
	// todo
	
	add read_head, read_head, (INTS_PER_CMD*BYTES_PER_INT)	// advance read head to next cmd.
	sub num_cmd_pkts_in_buffer, num_cmd_pkts_in_buffer, 1	// one less cmd pkt in our buffer.
	qba DONE_ACTUATING	// return 

	
COPY_NEW_ACTUATION_SCHEDULE:
	// assume format is:
	// uint32 cycle time
	// uint32 direction & stby gpios
	// uint32 duty cycle
	// uint32 reserved

	// For simplicity,
	// Totally overwrite our existing actuation schedule.
	// Later: figure out how to blend them.

	lbbo num_cmd_pkts_in_buffer, rADDR_CMD_CPU_NEW_SCH, 0, 4
	mov tmp2, 0 // num pkts copied
	mov tmp1, 0 // addr offset 
	
COPY_ONE_PKT:

	lbbo tmp0, rCMD_BUFFER_FROM_CPU, tmp1, 4
	sbbo tmp0, rCMD_BUFFER, tmp1, 4
	add tmp1, tmp1, 4
	lbbo tmp0, rCMD_BUFFER_FROM_CPU, tmp1, 4
	sbbo tmp0, rCMD_BUFFER, tmp1, 4
	add tmp1, tmp1, 4
	lbbo tmp0, rCMD_BUFFER_FROM_CPU, tmp1, 4
	sbbo tmp0, rCMD_BUFFER, tmp1, 4
	add tmp1, tmp1, 4
	lbbo tmp0, rCMD_BUFFER_FROM_CPU, tmp1, 4
	sbbo tmp0, rCMD_BUFFER, tmp1, 4
	add tmp1, tmp1, 4

	add tmp2, tmp2, 1 // # cmd pkts copied so far
	
	qbne COPY_ONE_PKT, tmp2, num_cmd_pkts_in_buffer

// done copying the new cmd schedule over. Tell CPU:

	mov tmp0, 0                  // clear the bit that the CPU set ("new schedule")
	sbbo tmp0, rADDR_CMD_CPU_NEW_SCH, 0, 4
	mov read_head, 0 // reset read head to start of new cmd buffer
	
// all done copying new :
	qba DONE_COPYING_NEW_SCH