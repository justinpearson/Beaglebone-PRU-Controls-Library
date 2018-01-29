04-pwm-added-to-pru-lib

This tests that a C program can set not only the PWM direction, but also its duty cycle.

Currently the jpp-pru-lib sets the PRU's sample time to 0.8ms and the PWM duty cycle 33.33us per pwm period. So there are 24 PWM periods in a sample time.

If you look on the scope, you can see the PWM duty cycle staying constant at 10% for .8ms, then changing to 50% for the next 0.8ms timestep, then back to 10% for the next .8ms timestep, etc. 

See jpp's iphone pics fri sep 16.

Example output:



root@beaglebone:/home/debian/BB_PRU_stuff/PWM/04-PWM-added-to-PRU-lib# ./run
I'm in: 
/home/debian/BB_PRU_stuff/PWM/04-PWM-added-to-PRU-lib
Resetting eqep...
==========================
building PRU C library...
------------------------
Using pasm to assemble .p file  into .bin file ...


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 372 word(s)

~~~~~~~~~~~~~~~~~
Compiling .c file jpp-pru-lib.c into .o file jpp-pru-lib.o
~~~~~~~~~~~~~~~~~~~~~~~~~~
Building test .c file set-pwm-duty-schedule.c to make set-pwm-duty-schedule
Fri Sep 16 09:38:07 UTC 2016
Fri Sep 16 09:38:08 UTC 2016
Welcome to the Beaglebone PRU library for real-time controls!
NOTE: if you get a seg fault, make sure the jppprugpio device tree overlay has been loaded!!
Here's the cmd: root@beaglebone# echo jppprugpio > /sys/devices/bone_capemgr.9/slots
Assumes you have jppprugpio-00A0.dto in /lib/firmwareAlso do this:
echo bone_eqep1 > $SLOTS
prussdrv_init() (returned 0)
prussdrv_open (returned 0)
prussdrv_pruintc_init (returned 0)
pruss_map_prumem (returned 0)
pru0 data memory addr: 0xb6c4e000
 ctrladdr_CPU_wants_data : 0xb6c4e000
 ctrladdr_PRU_data_ready : 0xb6c4e004
 ctrladdr_CPU_new_sched  : 0xb6c4e008
 ctrladdr_PRU_ack_sched  : 0xb6c4e00c
 addr_cpu_data_buf : 0xb6c4e010
 addr_pru_data_buf : 0xb6c4e410
 addr_cpu_cmd_buf  : 0xb6c4e810
 addr_pru_cmd_buf  : 0xb6c4ea10
executing bin file: ./jpp-pru-lib.bin
NOTE: a lot of stuff assumes PRU0 in this lib, sry.
prussdrv_exec_program returned 0
Waiting 200ms to let PRU fill its internal buffer...done.
Data data_buf:
cycle: 35040028 sample: 218 adc: 1798 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 35200024 sample: 219 adc: 1797 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 35360020 sample: 220 adc: 1799 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 35520016 sample: 221 adc: 1801 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 35680028 sample: 222 adc: 1798 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 35840024 sample: 223 adc: 1800 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 36000023 sample: 224 adc: 1795 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 36160020 sample: 225 adc: 1787 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 36320016 sample: 226 adc: 1791 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 36480028 sample: 227 adc: 1798 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 36640024 sample: 228 adc: 1787 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 36800020 sample: 229 adc: 1783 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 36960016 sample: 230 adc: 1779 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 37120028 sample: 231 adc: 1800 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 37280024 sample: 232 adc: 1791 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 37440020 sample: 233 adc: 1796 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 37600016 sample: 234 adc: 1794 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 37760028 sample: 235 adc: 1784 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 37920024 sample: 236 adc: 1800 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 38080020 sample: 237 adc: 1784 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 38240016 sample: 238 adc: 1800 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 38400028 sample: 239 adc: 1783 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 38560024 sample: 240 adc: 1794 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 38720020 sample: 241 adc: 1792 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 38880016 sample: 242 adc: 1795 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 39040028 sample: 243 adc: 1791 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 39200024 sample: 244 adc: 1792 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 39360020 sample: 245 adc: 1806 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 39520016 sample: 246 adc: 1804 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 39680028 sample: 247 adc: 1801 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 39840024 sample: 248 adc: 1791 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 40000020 sample: 249 adc: 1791 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
Sending cmd...
Sleeping for 20ms...
Data after:
cycle: 39200024 sample: 244 adc: 1792 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 39360020 sample: 245 adc: 1806 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 39520016 sample: 246 adc: 1804 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 39680028 sample: 247 adc: 1801 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 39840024 sample: 248 adc: 1791 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 40000020 sample: 249 adc: 1791 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 0 last-cmd: 0
cycle: 40160016 sample: 250 adc: 1791 eqep: 0 gpio: 0 duty: 572662306 last-data-req: 40030013 last-cmd: 0
cycle: 40320016 sample: 251 adc: 1795 eqep: 0 gpio: 23 duty: 333 last-data-req: 40030013 last-cmd: 40166830
cycle: 40480020 sample: 252 adc: 1793 eqep: 0 gpio: 23 duty: 1667 last-data-req: 40030013 last-cmd: 40166830
cycle: 40640024 sample: 253 adc: 1795 eqep: 0 gpio: 23 duty: 333 last-data-req: 40030013 last-cmd: 40166830
cycle: 40800028 sample: 254 adc: 1782 eqep: 0 gpio: 23 duty: 1667 last-data-req: 40030013 last-cmd: 40166830
cycle: 40960016 sample: 255 adc: 1795 eqep: 0 gpio: 23 duty: 333 last-data-req: 40030013 last-cmd: 40166830
cycle: 41120023 sample: 256 adc: 1793 eqep: 0 gpio: 23 duty: 1667 last-data-req: 40030013 last-cmd: 40166830
cycle: 41280028 sample: 257 adc: 1783 eqep: 0 gpio: 23 duty: 333 last-data-req: 40030013 last-cmd: 40166830
cycle: 41440016 sample: 258 adc: 1784 eqep: 0 gpio: 23 duty: 1667 last-data-req: 40030013 last-cmd: 40166830
cycle: 41600020 sample: 259 adc: 1793 eqep: 0 gpio: 23 duty: 333 last-data-req: 40030013 last-cmd: 40166830
cycle: 41760024 sample: 260 adc: 1804 eqep: 0 gpio: 23 duty: 1667 last-data-req: 40030013 last-cmd: 40166830
cycle: 41920028 sample: 261 adc: 1783 eqep: 0 gpio: 23 duty: 333 last-data-req: 40030013 last-cmd: 40166830
cycle: 42080016 sample: 262 adc: 1794 eqep: 0 gpio: 23 duty: 1667 last-data-req: 40030013 last-cmd: 40166830
cycle: 42240020 sample: 263 adc: 1774 eqep: 0 gpio: 23 duty: 333 last-data-req: 40030013 last-cmd: 40166830
cycle: 42400024 sample: 264 adc: 1800 eqep: 0 gpio: 23 duty: 1667 last-data-req: 40030013 last-cmd: 40166830
cycle: 42560028 sample: 265 adc: 1783 eqep: 0 gpio: 23 duty: 333 last-data-req: 40030013 last-cmd: 40166830
cycle: 42720016 sample: 266 adc: 1785 eqep: 0 gpio: 23 duty: 1667 last-data-req: 40030013 last-cmd: 40166830
cycle: 42880020 sample: 267 adc: 1783 eqep: 0 gpio: 23 duty: 333 last-data-req: 40030013 last-cmd: 40166830
cycle: 43040024 sample: 268 adc: 1806 eqep: 0 gpio: 23 duty: 1667 last-data-req: 40030013 last-cmd: 40166830
cycle: 43200028 sample: 269 adc: 1791 eqep: 0 gpio: 23 duty: 333 last-data-req: 40030013 last-cmd: 40166830
cycle: 43360016 sample: 270 adc: 1787 eqep: 0 gpio: 23 duty: 1667 last-data-req: 40030013 last-cmd: 40166830
cycle: 43520020 sample: 271 adc: 1795 eqep: 0 gpio: 23 duty: 333 last-data-req: 40030013 last-cmd: 40166830
cycle: 43680024 sample: 272 adc: 1791 eqep: 0 gpio: 23 duty: 1667 last-data-req: 40030013 last-cmd: 40166830
cycle: 43840028 sample: 273 adc: 1790 eqep: 0 gpio: 23 duty: 333 last-data-req: 40030013 last-cmd: 40166830
cycle: 44000016 sample: 274 adc: 1808 eqep: 0 gpio: 23 duty: 1667 last-data-req: 40030013 last-cmd: 40166830
cycle: 44160020 sample: 275 adc: 1806 eqep: 0 gpio: 23 duty: 333 last-data-req: 40030013 last-cmd: 40166830
Sleeping for 2 sec...
Sending STBY cmd...
























// old:

Change the PWM duty cycle from the PRU.

This program sets up channel B (of A,B) of the PWM subsystem 1 (of 0,1,2) to be a 10% duty-cycle 3.3V 30kHz square wave on pin P8_34. 

Note that you must first do 

$ echo bone_pwm_P8_34 > $SLOTS

to enable this pin.

The PRU sets the PWM registers and then halts. However, the PWM peripheral still generates the sq wave.

I figured this out by following the example in the AM335X Technical Reference Manual, Page 2307 of SPRUH73N – October 2011 – Revised June 2016.


How to run:
1. compile .p to .bin
   $ pasm -b pru-set-pwm.p
2. run pru debugger
  $ root@beaglebone:/home/debian/BB_PRU_stuff/PWM/03-PRU-sets-PWM-peripheral# /home/debian/prudebug-0.25/prudbg
3. In debugger, load the .bin:

   l 0 pru-set-pwm.bin   // loads .p into PRU instr memory

4. In debugger, start the PRU with 'g'
   g 

You should see the square wave on pin P8_34.


Conceptual operation:

- there is a counter that's counting up at 100MHz (with sys clock ticks)
- once that counter hits some user-set threshold


How to change period:
- In the pru-set-pwm.p code:

  // TBPRD, TBPRD, 258h (period = 258h = 601 tbclk counts)
	mov tmp1, 3333 // or 2000: @ 100MHz sysclock, period will be 50kHz.
	sbbo tmp1, tmp0, TBPRD, 2

The '3333' is 3333 ticks of a 100MHz system clock. That's how fast the 

TBPRD: time-base period. A term from the TRM.

IMPORTANT: the TBPRD register is only 2 bytes, so you can only have values 0 - 65535 for TBPRD. DO NOT try to get a longer period

Since 0 <= TBPRD <= 65535, then the periods we can achieve are between

(0+1 tick / PWM period) * (1 sec / 1e8 ticks) = 1e-8 sec / period = 100 kHz
(65535+1 tick / PWM period) / (1e8 ticks / sec) .00065536 sec / period => 1.526 kHz. 

If we want something slower, that's what the clock divider is for, I bet.



How to change duty cycle:





PWM period = (TBPRD + 1) * T_TBCLK

TBPRD = 600 in our case
T_TBCLK is 100MHz? 

"TBCLK
Time-base clock.
This is a prescaled version of the system clock (SYSCLKOUT) and is used by all submodules within the
ePWM. This clock determines the rate at which time-base counter increments or decrements."

We've set it up so TBCLK is not prescaled wrt SYSCLKOUT. 

SYSCLKOUT is the normal CPU clock. 

Um, I think this clock runs at 100MHz according to 

#define SYSCLK 100000000

from 

// https://raw.githubusercontent.com/zedoul/rtdm-pwmss/master/rtdm-pwm/mf2044-pwm-drv.c

So that means 100M ticks per second? So the PWM period is then

601 ticks * ( 1 sec / 100M ticks ) = 6.01 us PWM period.

And we set up channel B to 200, and so we should have 200/601 = 33% duty cycle.

How to run:

pasm -b pru-set-pwm.p   // makes .bin

root@beaglebone:/home/debian/BB_PRU_stuff/PWM/03-PRU-sets-PWM-peripheral# /home/debian/prudebug-0.25/prudbg


l 0 pru-set-pwm.bin   // loads .p into PRU instr memory

g  // start code

I see a sq wave w/ period of 6us and low time of 2.52us! surprising it's not 2us. Maybe it'll be better if we make the period longer.

Hm, a 166kHz sq wave is a little cray. Let's shoot for 50kHz.

So we'd need the 100MHz clock to reset at 50kHz...

(100M cyc/sec) / (50 kResets / sec) = 2000 cyc / reset

So that is what TBPRD should be set to.

And let's shoot for a 20% duty cycle -- easy to see on the scope.

20% of 2000 is 400, so that's what we should set CMPB to.

We see 50kHz period as expected, but PWM signal is much smaller than 20% duty, and there are weird spikes.

Set CMPB to 1000 (TBPRD still at 2000). Still see 50khz good, but duty should be 50%, and we're seeing 6.6us low of a 20us period => 67% duty cycle.

CMPB   us high    duty
1000   13.4        67%
500    18.4        92%
0      3.4         17%

set TBPRD to 100000 and CMPB to 0, I see at 340us period (~3kHz) not 1kHz as expected, and 3.48us high-time (1% duty). What's going on here??

Arg. Both CMPA and CMPB seems to affect the output of P8_34, which is supposed to be impossible. There must be some weird-ass mixing going on. 

Also there are weird little 100ns blips in addition to the main sq wave when I do

TBPRD: 100000 (1 kHz in theory)
CMPA: 5000
CMPB: 10000

Causes:
- hi
- blip t=0
- to low 50us later
- to high 50us later
- period: 344us


Ah, typo, was having ch B change when CMPA did stuff. :(

Decision: disable A, since it doesn't seem to be working. 

Okay, now I've set up:

TBPRD 1000000
CMPA 0
CMPB 10000 



scope: 
- period 344us
- high for 50us


PWM period = (TBPRD + 1) * T_TBCLK

((1,000,000 + 1) ticks / period )* (1 sec / 100,000,000 ticks ) = 1/100 sec / period = 0.01 sec/period = 10ms/period

we're seeing .344 ms insetad: 30x faster. Maybe we have sysclk wrong? 


Q: Does period stay same, even if we change cmpb? 

cmpb 0

scope flat at 0 (good)

cmpb 1

period 344us

10ns blip (not a real pulse per se)

cmpb 10

period 344us

100ns blip

cmpb 100

period: 344us

1us hi, more like a square wave, 3.3V good

note: edges of sq wave wiggly, flat part at 3.3V, but up to 5V and -1.5V on up/down, for 250ns. 

cmpb 1000

period 344us

hi for 10us

cmpb 10000

period 344us still 

hi for 50us

cmpb 100000

period 344us

hi for 50us (no change from cmpb=10000)

redid 10000 cmpb to make sure. yup.

tbprd from 100000 to 200000, period should double

um, mostly at 3.3V with some crazy spikes.

oh shit -- tbprd is a 2-byte register, so its vals can only go up to 65535! 

We had it at 100000, which is 0x186A0, and only the lower 16 bits, 0x86A0, were used, which is 34464, which looks a lot like 344us, dammit!

So if TBPRD < 65535, then the periods we can achieve are

1 tick / period / (1e8 ticks / sec) = 1e-8 sec / period = 100kHz
(65535 ticks / period) / (1e8 ticks / sec) .00065535 sec / period => 1526Hz. 

If we want something slower, that's what the clock divider is for, I bet.

So if we want 30kHz pWM period to drive our motor, then we need...

TBPRD = 3333 

And if we want a 10% duty, then 

CMPB = 333

Let's see.

period: 33.2us (30kHz, YES)

high for 3.3us (YES, thsi is 10% of the period.














Derek's table shows pin names

ehrpwm0, 2a, 2b, 
ehrpwm1_tripzone_in
ehrpwm2_tripzone_in
ehrpmw2B
ehrpwm0_synco
ehrpwm2A

TRM: There are 3 PWM subsystems (PWMSS)

They must be labeled 0, 1, 2.

For some reason, each PWMSS can put a pwm signal on 2 pins, called A & B.

Since

# cat $SLOTS 

shows

 9: ff:P-O-L Override Board Name,00A0,Override Manuf,bone_pwm_P8_34

which Derek's table says is 

ehrpwm1B

that's the PWMSS we should be using.

We're using PWMSS 1, channel B.

TRM page 183 memory map: PWMSS1 starts at addr 0x48302000 to 0x483020FF. WIthin that, the ePWM1 registers run from 0x48302200 to 0x4830225F.

In pwm-registers.hp, that aligns with 

#define EPWM1_0_BASE 0x48302200

Note that there is also

#define EPWM1_1_BASE 0x48302260

The 0/1 difference is maybe the A/B, but the TRM says that 0x48302260 to 0x48303FFF is reserved. Moreover I think the A/B are somehow both controlled by regs belonging to a single PWMSS, see the pic Page 2307 of SPRUH73N – October 2011 – Revised June 2016. So I think that name is misleading.. we shouldn't use any addrs at EPWM1_1_BASE 0x48302260. 

Note: ehrpwm1A is 8_36, which we appear to not be using already (good).
We can monitor this one too.
