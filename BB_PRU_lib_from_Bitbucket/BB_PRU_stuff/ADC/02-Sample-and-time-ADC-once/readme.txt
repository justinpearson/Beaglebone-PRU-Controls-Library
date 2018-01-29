this program samples the ADC once and times how long it takes.

justin pearson, 2016-08-22

It seems to take about 286 cycles (1430 ns) each time I run it, regardless of whether it's measuring 0V, .9V, or 1.8V. 

sample output:

root@beaglebone:/home/debian/BB_PRU_stuff/ADC/02-Sample-and-time-ADC-once# ls -lstr
total 60
 4 -rwxr-xr-x 1 debian debian   389 Aug 19 16:22 run~
 8 -rw-r--r-- 1 root   root    8052 Aug 19 16:45 sample-and-time.p~
 8 -rw-r--r-- 1 root   root    4355 Aug 22 10:36 sample-and-time.c~
12 -rw-r--r-- 1 root   root    8746 Aug 22 14:24 sample-and-time.p
 4 -rwxr-xr-x 1 debian debian   420 Aug 22 14:27 run
 8 -rw-r--r-- 1 root   root    4617 Aug 22 14:28 sample-and-time.c
 4 -rw-r--r-- 1 root   root     296 Aug 22 14:28 sample-and-time.bin
12 -rwxr-xr-x 1 root   root   11501 Aug 22 14:28 sample-and-time
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/02-Sample-and-time-ADC-once# ./run
I'm in: 
/home/debian/BB_PRU_stuff/ADC/02-Sample-and-time-ADC-once
Building .bin file sample-and-time.p


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 74 word(s)

Building .c file sample-and-time.c to make sample-and-time
(Careful - does your .c load the correct .p / .bin?)
Running sample-and-time
Hey, if you get a seg fault, make sure the EBB-PRU-Example device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo EBB-PRU-Example > /sys/devices/bone_capemgr.9/slots
executing bin file: ./sample-and-time.bin
Waiting...
ADC: 2048
start: 270
end: 556
# cycles that ADC took to sample: 286 (1430 ns)
Shutting down.
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/02-Sample-and-time-ADC-once# 
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/02-Sample-and-time-ADC-once# 
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/02-Sample-and-time-ADC-once# ./sample-and-time 
Hey, if you get a seg fault, make sure the EBB-PRU-Example device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo EBB-PRU-Example > /sys/devices/bone_capemgr.9/slots
executing bin file: ./sample-and-time.bin
Waiting...
ADC: 2046
start: 269
end: 555
# cycles that ADC took to sample: 286 (1430 ns)
Shutting down.
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/02-Sample-and-time-ADC-once# ./sample-and-time 
Hey, if you get a seg fault, make sure the EBB-PRU-Example device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo EBB-PRU-Example > /sys/devices/bone_capemgr.9/slots
executing bin file: ./sample-and-time.bin
Waiting...
ADC: 2045
start: 270
end: 556
# cycles that ADC took to sample: 286 (1430 ns)
Shutting down.
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/02-Sample-and-time-ADC-once# ./sample-and-time 
Hey, if you get a seg fault, make sure the EBB-PRU-Example device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo EBB-PRU-Example > /sys/devices/bone_capemgr.9/slots
executing bin file: ./sample-and-time.bin
Waiting...
ADC: 2045
start: 270
end: 556
# cycles that ADC took to sample: 286 (1430 ns)
Shutting down.
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/02-Sample-and-time-ADC-once# ./sample-and-time 
Hey, if you get a seg fault, make sure the EBB-PRU-Example device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo EBB-PRU-Example > /sys/devices/bone_capemgr.9/slots
executing bin file: ./sample-and-time.bin
Waiting...
ADC: 2045
start: 270
end: 556
# cycles that ADC took to sample: 286 (1430 ns)
Shutting down.
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/02-Sample-and-time-ADC-once# ./sample-and-time 
Hey, if you get a seg fault, make sure the EBB-PRU-Example device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo EBB-PRU-Example > /sys/devices/bone_capemgr.9/slots
executing bin file: ./sample-and-time.bin
Waiting...
ADC: 2045
start: 270
end: 556
# cycles that ADC took to sample: 286 (1430 ns)
Shutting down.
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/02-Sample-and-time-ADC-once# ./sample-and-time 
Hey, if you get a seg fault, make sure the EBB-PRU-Example device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo EBB-PRU-Example > /sys/devices/bone_capemgr.9/slots
executing bin file: ./sample-and-time.bin
Waiting...
ADC: 2044
start: 269
end: 555
# cycles that ADC took to sample: 286 (1430 ns)
Shutting down.
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/02-Sample-and-time-ADC-once# 
