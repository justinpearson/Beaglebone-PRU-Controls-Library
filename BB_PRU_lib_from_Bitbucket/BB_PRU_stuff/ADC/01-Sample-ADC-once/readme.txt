this file samples the ADC channel 0 (P9_39) once. You can measure it
with a voltage divider between the 1.8V adc rail (P9_32) and the adc
ground (P9_34):


Example output:

root@beaglebone:/home/debian/BB_PRU_stuff/ADC/Sample-ADC-once# ./run
Building .bin file sample-adc-once.p


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 63 word(s)

Building .c file sample-adc-once.c to make sample-adc-once
(Careful - does your .c load the correct .p / .bin?)
Running sample-adc-once
Hey, if you get a seg fault, make sure the EBB-PRU-Example device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo EBB-PRU-Example > /sys/devices/bone_capemgr.9/slots
executing bin file: ./sample-adc-once.bin
Waiting...
Value is: 2044
Shutting down.



Note that 2044 is almost 4096/2, which is because I was using 2 equal
resistors in my 1.8V voltage divider, so the measured voltage is
halfway between 0V (0 ADC counts) and 1.8V (4096 ADC counts) (4096
because it's a 12-bit adc and 2^12 = 4096).
