See Derek Molloy's book 'exploring beaglebone' (:~/exploringBB/chp13/PRUClock) or chp14/fixedClock or something


This program has the PRU generate a 100kHz square wave by:
1. set pin P9_27 high
2. count from 500 to 0
3. set pin low
4. count from 500 to 0
5. repeat

The C code loads the PRU with these instructions and starts the PRU running.

You can verify this code w/ a oscilloscope, see pic taken Aug 22, 2016 on my iphone.

The PRU continues to generate the square wave even after the C code completes. It's not a problem to let the PRU contiune to run even while the main CPU is doing other stuff.


Sample output:

root@beaglebone:/home/debian/BB_PRU_stuff/PWM/01-Square-wave# ./run
Building .p


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 11 word(s)

Building .c
Running .c
EBB fixed-frequency clock PRU program now running
