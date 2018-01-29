// PRU program to provide a fixed-frequency clock on P9_27 (pru0_pru_r30_5). This
// program can be executed on either PRU0 or PRU1, but will have to be altered if
// you wish to change the clock to output on a different pin. Memory controlled:
// This program was writen by Derek Molloy to align with the content of the book 
// Exploring BeagleBone

// jpp: updated to just count a bit
	
.origin 0                        // start of program in PRU memory
.entrypoint INIT                 // program entry point (for a debugger)

#define	TIME_UNTIL_SWITCH   500	 // choose this value to suit the frequency required
				 // 1 gives a 20MHz clock signal, increase from there
				 // 500 gives...
INIT:
	MOV	r1, TIME_UNTIL_SWITCH // load this const into r1

BEGIN_CYCLE:	
SETLOW:
	CLR	r30.t5		// set P9_27 low
	MOV	r0, r1		// put our waiting time r1 into temp register r0
WAITLOW:
	SUB	r0, r0, 1	// decrement counter by 1 
	QBNE	WAITLOW, r0, 0	// loop unless r0 == 0
SETHIGH:	
	SET	r30.t5		// set P9_27 high
	MOV	r0, r1		// re-load the waiting time r1 into temporary r0
WAITHIGH:	
	SUB	r0, r0, 1	// decrement counter by 1
	QBNE	WAITHIGH, r0, 0	// loop unless r0 == 0

	QBA	BEGIN_CYCLE	// start another cycle, so the program will not exit
END:
	HALT			// halt the pru program -- never reached
