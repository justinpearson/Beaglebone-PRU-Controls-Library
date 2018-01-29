// I'm pretty much following the instructions in pg 2308 of the SPRUH73N AM335x TRM to initialize the PWMSS for simple square wave.
// Justin Pearson
// Sep 12, 2016

#include "pwm-registers.hp"

#define PRU0_ARM_INTERRUPT 	19
	
#define tmp0 				r1
#define tmp1 				r2
#define tmp2 				r3
#define tmp3 				r4

	
//    .setcallreg  r29.w2  // Use R29.W2 in the CALL/RET pseudo ops, not the default of r30 (used for GPIOS)
    .origin 0
    .entrypoint INIT


INIT:

// Init the PWMSS1:
	
// Register Bit Value Comments
/////////////////////////////////////
	mov tmp0, EPWM1_0_BASE
	
// TBPRD, TBPRD, 258h (period = 258h = 601 tbclk counts)

	mov tmp1, 3333 // or 2000: @ 100MHz sysclock, period will be 50kHz.
	sbbo tmp1, tmp0, TBPRD, 2
	
// TBPHS TBPHS 0 Clear Phase Register to 0
	mov tmp1, 0
	sbbo tmp1, tmp0, TBPHS, 2
	
// TBCNT TBCNT 0 Clear TB counter
	mov tmp1, 0
	sbbo tmp1, tmp0, TBCNT, 2
	
// TBCTL
	mov tmp1, 0	
	clr tmp1.t0 // CTRMODE TB_UP
	clr tmp1.t1
	clr tmp1.t2 // PHSEN TB_DISABLE   // Phase loading disabled
	clr tmp1.t3 // PRDLD TB_SHADOW
	set tmp1.t4 // SYNCOSEL TB_SYNC_DISABLE
	set tmp1.t5
	clr tmp1.t6 // no software-forced synchronization pulse? TRM no mentions this.
	clr tmp1.t7 // HSPCLKDIV TB_DIV1  ( TBCLK = SYSCLK )
	clr tmp1.t8
	clr tmp1.t9
	clr tmp1.t10 // CLKDIV TB_DIV1
	clr tmp1.t11
	clr tmp1.t12

	clr tmp1.t13 // phase direction (not really used)
	set tmp1.t14 // "emulation mode bits" - free run during "emulation-suspend events" TRM no mentions.
	set tmp1.t15

	sbbo tmp1, tmp0, TBCTL, 2  // write this 16-bit reg

// CMPA CMPA 350 (15Eh) Compare A = 350 TBCLK counts
	mov tmp1, 0 // disable this damn thing, it's not showing up at P8_36
	sbbo tmp1, tmp0, CMPA, 2
	
// CMPB CMPB 200 (C8h) Compare B = 200 TBCLK counts
	mov tmp1, 333 // @ TBPRD 2000, having CMPB=400 should result in
	                // 20% duty cycle.
	sbbo tmp1, tmp0, CMPB, 2
	
// CMPCTL
	// This reg has 'reserved' bits; don't change those.
	mov tmp1, 0  // clear out the whole 32-bits before loading in anything
	lbbo tmp1, tmp0, CMPCTL, 2
	// compute new value
	clr tmp1.t4 // SHDWAMODE CC_SHADOW
	clr tmp1.t6 // SHDWBMODE CC_SHADOW

	set tmp1.t0 // jpp: disabling ch A. No loads possible.
	set tmp1.t1 // (old: LOADAMODE CC_CTR_ZERO  (Load on CTR = 0))

	clr tmp1.t2 // LOADBMODE CC_CTR_ZERO  (Load on CTR = 0)
	clr tmp1.t3

	sbbo tmp1, tmp0, CMPCTL, 2 // put it back
	

// AQCTLA
	// jpp: disabling ch A. Take no actions on ch a:
	lbbo tmp1, tmp0, AQCTLA, 2
	clr tmp1.t0
	clr tmp1.t1
	clr tmp1.t2
	clr tmp1.t3
	clr tmp1.t4
	clr tmp1.t5
	clr tmp1.t6
	clr tmp1.t7
	clr tmp1.t8
	clr tmp1.t9
	clr tmp1.t10
	clr tmp1.t11
// old:
	//	clr tmp1.t0	// ZRO AQ_SET
	//	set tmp1.t1
	//	set tmp1.t4	// CAU AQ_CLEAR
	//	clr tmp1.t5
	sbbo tmp1, tmp0, AQCTLA, 2

// AQCTLB
	lbbo tmp1, tmp0, AQCTLB, 2
	clr tmp1.t0	// ZRO AQ_SET
	set tmp1.t1
	set tmp1.t8	// CBU AQ_CLEAR
	clr tmp1.t9
	sbbo tmp1, tmp0, AQCTLB, 2

	
QUIT:
	
        MOV R31.b0, PRU0_ARM_INTERRUPT+16   // Send notification to Host for program completion
        HALT

	
// At this point, the PRU has configured the PWMSS1 with period TBPRD (
	
// Table 15-22. EPWMx Run Time Changes for Figure 15-28
// 2308
// Register Bit Value Comments
// CMPA CMPA Duty1A Adjust duty for output EPWM1A
//	mov tmp0, EPWM1_0_BASE
//	mov tmp1, 123 // some new value for the compare register
//	sbbo tmp1, tmp0, CMPA, 2
