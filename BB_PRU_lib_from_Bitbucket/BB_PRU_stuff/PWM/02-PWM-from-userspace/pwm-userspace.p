// PRU program to provide a variable frequency clock on P9_27 (pru0_pru_r30_5) 
// that is controlled from Linux userspace by setting the PRU memory state. This
// program can be executed on either PRU0 or PRU1, but will have to be altered if
// you wish to change the clock to output on a different pin. Memory controlled:
// - The delay is set in memory address 0x00000000 (4 bytes)
// - The counter can be turned on and off by setting the LSB 0x00000004 (4 bytes) 
//   to 1 (on) or 0 (off)
// - The delay value can be updated by setting the second most LSB to 1 (it will 
//   immediately return to 0)
// This program was writen by Derek Molloy to align with the content of the book 
// Exploring BeagleBone

//  Justin Aug 17, 2016: Updating.
//  data ram will have 3 4-byte ints:
//  0th one is cmd:
	// byte 0: cmd pkt been serviced?
	   // bit 0: 1=cmd has not yet been serviced by PRU, 0=PRU has serviced
	// byte 1: cmd itself
	   // value 0: stop PRU program
	   // value 1: read run PRU program 

// 1st byte is "# PRU instrction cycles we'll stay LOW"
// 2nd byte is "# PRU instrction cycles we'll stay HIGH"


// Registers:
	// r0: temporary counter for counting down the low or high periods
	// r1: base data ram addr (0x00000000)
	// r2: number of PRU loop-iters to stay low
	// r3: num of PRU loop-iters to stay high
	// r4: used for editing the cmd int

// Note: the 'wait low' and 'wait high' loops each have 2 instrs in their bodies,
	// so if nlow = X, that will actually keep the output pin low for
	// X iters * (2 intrs / iter) * (5ns / instr) = 10*X ns.
	
.origin 0                        // start of program in PRU memory
.entrypoint START                // program entry point (for a debugger)

START:
	MOV	r1, 0x00000000	 // load the base data ram address into r1
	QBA	PARSECMDPKT	 // assume the C prog has loaded some values into our data RAM. parse them.
	MOV	r2, 100000 	// without a cmd pkt, stay low for this many loop iters
	MOV	r3, 10000	// and high for this many loop iters (~10ns per loop iter)

BEGINCYCLE:	
SETLOW:
	CLR	r30.t5           // set output pin to low	
	MOV	r0, r2  	 // r0 = # cycles to stay low.

WAITLOW:
	SUB	r0, r0, 1	 // decrement the counter by 1
	QBNE	WAITLOW, r0, 0   // repeat until the counter has expired (equals 0)

SETHIGH:
	SET	r30.t5		// set output pin to high
	MOV	r0, r3		// r0 = # cycles to stay high

WAITHIGH:
	SUB	r0, r0, 1	// r0 = r0 - 1
	QBNE	WAITHIGH, r0, 0 // repeat until r0==0

PARSECMDPKT:
	// bit 0: old=0/new=1 pkt
	// bit 1: run=1/stop=0
	LBBO	r4, r1, 0, 4		// r4 = load cmd packet, 4 bytes
	QBBC	BEGINCYCLE, r4.t0  // if bit 0 (new/old pkt) is 0, packet is old. Start another cycle.	
	QBBC	STOP, r4.t1		// if bit 1 (run/stop) is 0, stop.	
	CLR	r4, r4.t0	 // (else, pkt is new). set "new pkt" bit to 0. Otherwise we'll forget we serviced this pkt.
	// Service new pkt:  (write new loop durations into regs) and set the "new pkt" flag to 0 back in teh data ram.
	LBBO	r2, r1, 4, 4	 // r2 = number of PRU instrs to stay low, 4 bytes.
	LBBO	r3, r1, 8, 4	 // r3 = number of PRU instrs to stay high, 4 bytes.
	SBBO	r4, r1, 0, 4     // write cmd pkt back into memory. Otherwise we'll forget we serviced the pkt.
	QBA	BEGINCYCLE
	
STOP:
	CLR	r30.t5           // set output pin to low
	HALT
