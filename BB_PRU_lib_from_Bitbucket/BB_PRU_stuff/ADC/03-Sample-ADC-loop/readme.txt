This program samples the ADC several times at a fixed interval. 

The interval is set in the PRU .p code, here:

#define SAMPLE_PERIOD (1000000-100) // in cycles (5ns / cycle)
#define MAX_SAMPLES 10 // max num of adc samples to collect.

The PRU writes these samples into the data ram in the following way:

# num samples retrieved
sample 1 caputure time
sample 1 adc value
sample 1 time capture completed
sample 2 capture time
sample 2 adc value (0-4096)
sample 2 time capture completed
...


all times are in PRU cycles. The PRU runs at 200MHz (5ns per cycle).





TODO: I'm doing the subtraction in a screwy way that will cause some drift over time.
Need to figure out a better way to tell if it's time to sample agin.

TODO: C should wait until P finishes, not just pause for 0.1s. Otherwise C could start pulling out vals before P is done populating!







sample output:

root@beaglebone:/home/debian/BB_PRU_stuff/ADC/03-Sample-ADC-loop# ./run
I'm in: 
/home/debian/BB_PRU_stuff/ADC/03-Sample-ADC-loop
Building .bin file sample-adcs.p


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 87 word(s)

Building .c file sample-adcs.c to make sample-adcs
(Careful - does your .c load the correct .p / .bin?)
Running sample-adcs
Hey, if you get a seg fault, make sure the EBB-PRU-Example device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo EBB-PRU-Example > /sys/devices/bone_capemgr.9/slots
executing bin file: ./sample-adcs.bin
Waiting...
awake!
# ADC samples to get: 10
start: 275		ADC: 2048		end: 555		delta (ns): 1400
start: 1000186		ADC: 2044		end: 1000419		delta (ns): 1165
start: 2000098		ADC: 2048		end: 2000331		delta (ns): 1165
start: 3000010		ADC: 2045		end: 3000243		delta (ns): 1165
start: 3999922		ADC: 2046		end: 4000155		delta (ns): 1165
start: 4999834		ADC: 2047		end: 5000067		delta (ns): 1165
start: 5999746		ADC: 2045		end: 5999979		delta (ns): 1165
start: 6999658		ADC: 2044		end: 6999891		delta (ns): 1165
start: 7999570		ADC: 2044		end: 7999803		delta (ns): 1165
start: 8999482		ADC: 2044		end: 8999715		delta (ns): 1165
Shutting down.
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/03-Sample-ADC-loop# 
