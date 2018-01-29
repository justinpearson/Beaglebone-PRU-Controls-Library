// 03-lib test

test0: get a data packet
test1: get several data packets in rapid succession
test2: like 02-gpio-song but cleaner code
test3: drive motor fwd and backward for a second each
test4: system identification on the motor
test5: calibrate ADC / current sensor





test0 example output:


root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ./run
I'm in: 
/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests
==========================
building PRU library...
Compiling .c file jpp-pru-lib.c into .o file jpp-pru-lib.o
Using pasm to assemble .p file jpp-pru-lib.p into .bin file jpp-pru-lib.bin...


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 306 word(s)

Building test .c file test0-get-data.c to make test0-get-data
NOT Running 
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ./test0-get-data
Welcome to the Beaglebone PRU library for real-time controls!
NOTE: if you get a seg fault, make sure the jppprugpio device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo jppprugpio > /sys/devices/bone_capemgr.9/slots
Also do this:
echo bone_eqep1 > $SLOTS
prussdrv_init() (returned 0)
prussdrv_open (returned 0)
prussdrv_pruintc_init (returned 0)
pruss_map_prumem (returned 0)
pru0 data memory addr: 0xb6d86000
 ctrladdr_CPU_wants_data : 0xb6d86000
 ctrladdr_PRU_data_ready : 0xb6d86004
 ctrladdr_CPU_new_sched  : 0xb6d86008
 ctrladdr_PRU_ack_sched  : 0xb6d8600c
 addr_cpu_data_buf : 0xb6d86010
 addr_pru_data_buf : 0xb6d86410
 addr_cpu_cmd_buf  : 0xb6d86810
 addr_pru_cmd_buf  : 0xb6d86a10
executing bin file: ./jpp-pru-lib.bin
NOTE: a lot of stuff assumes PRU0 in this lib, sry.
prussdrv_exec_program returned 0
Waiting 200ms to let PRU fill its internal buffer...done.
cycle: 9000028 sample: 8 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 10000028 sample: 9 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 11000028 sample: 10 adc: 2049 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 12000028 sample: 11 adc: 2051 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 13000028 sample: 12 adc: 2049 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 14000028 sample: 13 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 15000028 sample: 14 adc: 2048 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 16000028 sample: 15 adc: 2049 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 17000028 sample: 16 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 18000028 sample: 17 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 19000028 sample: 18 adc: 2049 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 20000028 sample: 19 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 21000028 sample: 20 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 22000028 sample: 21 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 23000028 sample: 22 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 24000028 sample: 23 adc: 2051 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 25000028 sample: 24 adc: 2048 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 26000028 sample: 25 adc: 2048 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 27000028 sample: 26 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 28000028 sample: 27 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 29000028 sample: 28 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 30000028 sample: 29 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 31000028 sample: 30 adc: 2049 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 32000028 sample: 31 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 33000015 sample: 32 adc: 2049 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 34000014 sample: 33 adc: 2052 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 35000014 sample: 34 adc: 2051 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 36000014 sample: 35 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 37000014 sample: 36 adc: 2051 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 38000014 sample: 37 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 39000014 sample: 38 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 40000014 sample: 39 adc: 2051 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0























test1 example output:

note that I was twirling the rotary encoder back and forth while this code was running. you can see the eqep sensor jiggling around.


root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ./run
I'm in: 
/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests
==========================
building PRU library...
Compiling .c file jpp-pru-lib.c into .o file jpp-pru-lib.o
Using pasm to assemble .p file jpp-pru-lib.p into .bin file jpp-pru-lib.bin...


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 306 word(s)

Building test .c file test1-get-data-fast.c to make test1-get-data-fast
NOT Running 
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ./test1-get-data-fast
Welcome to the Beaglebone PRU library for real-time controls!
NOTE: if you get a seg fault, make sure the jppprugpio device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo jppprugpio > /sys/devices/bone_capemgr.9/slots
Also do this:
echo bone_eqep1 > $SLOTS
prussdrv_init() (returned 0)
prussdrv_open (returned 0)
prussdrv_pruintc_init (returned 0)
pruss_map_prumem (returned 0)
pru0 data memory addr: 0xb6dc6000
 ctrladdr_CPU_wants_data : 0xb6dc6000
 ctrladdr_PRU_data_ready : 0xb6dc6004
 ctrladdr_CPU_new_sched  : 0xb6dc6008
 ctrladdr_PRU_ack_sched  : 0xb6dc600c
 addr_cpu_data_buf : 0xb6dc6010
 addr_pru_data_buf : 0xb6dc6410
 addr_cpu_cmd_buf  : 0xb6dc6810
 addr_pru_cmd_buf  : 0xb6dc6a10
executing bin file: ./jpp-pru-lib.bin
NOTE: a lot of stuff assumes PRU0 in this lib, sry.
prussdrv_exec_program returned 0
Waiting 200ms to let PRU fill its internal buffer...done.
Retrieving data bufs:
Done, printing data bufs:
Buffer 0:
cycle: 9000028 sample: 8 adc: 2049 eqep: 51 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 10000028 sample: 9 adc: 2049 eqep: 50 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 11000028 sample: 10 adc: 2050 eqep: 49 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 12000028 sample: 11 adc: 2049 eqep: 48 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 13000028 sample: 12 adc: 2050 eqep: 47 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 14000028 sample: 13 adc: 2050 eqep: 47 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 15000028 sample: 14 adc: 2049 eqep: 47 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 16000028 sample: 15 adc: 2050 eqep: 47 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 17000028 sample: 16 adc: 2050 eqep: 46 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 18000028 sample: 17 adc: 2049 eqep: 46 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 19000028 sample: 18 adc: 2050 eqep: 46 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 20000028 sample: 19 adc: 2050 eqep: 46 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 21000028 sample: 20 adc: 2049 eqep: 46 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 22000028 sample: 21 adc: 2050 eqep: 46 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 23000028 sample: 22 adc: 2050 eqep: 46 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 24000028 sample: 23 adc: 2050 eqep: 45 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 25000028 sample: 24 adc: 2050 eqep: 45 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 26000028 sample: 25 adc: 2048 eqep: 47 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 27000028 sample: 26 adc: 2049 eqep: 52 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 28000028 sample: 27 adc: 2050 eqep: 60 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 29000028 sample: 28 adc: 2050 eqep: 67 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 30000028 sample: 29 adc: 2050 eqep: 74 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 31000028 sample: 30 adc: 2050 eqep: 83 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 32000028 sample: 31 adc: 2051 eqep: 94 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 33000015 sample: 32 adc: 2050 eqep: 106 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 34000014 sample: 33 adc: 2050 eqep: 119 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 35000014 sample: 34 adc: 2049 eqep: 132 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 36000014 sample: 35 adc: 2050 eqep: 143 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 37000014 sample: 36 adc: 2049 eqep: 153 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 38000014 sample: 37 adc: 2050 eqep: 163 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 39000014 sample: 38 adc: 2050 eqep: 174 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 40000014 sample: 39 adc: 2050 eqep: 188 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
Buffer 1:
cycle: 29000028 sample: 28 adc: 2050 eqep: 67 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 30000028 sample: 29 adc: 2050 eqep: 74 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 31000028 sample: 30 adc: 2050 eqep: 83 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 32000028 sample: 31 adc: 2051 eqep: 94 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 33000015 sample: 32 adc: 2050 eqep: 106 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 34000014 sample: 33 adc: 2050 eqep: 119 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 35000014 sample: 34 adc: 2049 eqep: 132 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 36000014 sample: 35 adc: 2050 eqep: 143 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 37000014 sample: 36 adc: 2049 eqep: 153 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 38000014 sample: 37 adc: 2050 eqep: 163 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 39000014 sample: 38 adc: 2050 eqep: 174 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 40000014 sample: 39 adc: 2050 eqep: 188 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 41000014 sample: 40 adc: 2051 eqep: 207 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 42000014 sample: 41 adc: 2048 eqep: 234 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 43000014 sample: 42 adc: 2051 eqep: 269 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 44000014 sample: 43 adc: 2050 eqep: 308 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 45000014 sample: 44 adc: 2049 eqep: 348 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 46000014 sample: 45 adc: 2049 eqep: 379 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 47000014 sample: 46 adc: 2049 eqep: 405 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 48000014 sample: 47 adc: 2050 eqep: 424 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 49000014 sample: 48 adc: 2050 eqep: 441 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 50000014 sample: 49 adc: 2050 eqep: 454 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 51000014 sample: 50 adc: 2050 eqep: 467 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 52000014 sample: 51 adc: 2049 eqep: 480 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 53000014 sample: 52 adc: 2048 eqep: 495 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 54000014 sample: 53 adc: 2049 eqep: 510 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 55000014 sample: 54 adc: 2050 eqep: 525 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 56000014 sample: 55 adc: 2051 eqep: 540 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 57000014 sample: 56 adc: 2050 eqep: 554 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 58000014 sample: 57 adc: 2050 eqep: 571 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 59000014 sample: 58 adc: 2049 eqep: 584 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 60000014 sample: 59 adc: 2050 eqep: 597 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
Buffer 2:
cycle: 49000014 sample: 48 adc: 2050 eqep: 441 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 50000014 sample: 49 adc: 2050 eqep: 454 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 51000014 sample: 50 adc: 2050 eqep: 467 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 52000014 sample: 51 adc: 2049 eqep: 480 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 53000014 sample: 52 adc: 2048 eqep: 495 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 54000014 sample: 53 adc: 2049 eqep: 510 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 55000014 sample: 54 adc: 2050 eqep: 525 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 56000014 sample: 55 adc: 2051 eqep: 540 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 57000014 sample: 56 adc: 2050 eqep: 554 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 58000014 sample: 57 adc: 2050 eqep: 571 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 59000014 sample: 58 adc: 2049 eqep: 584 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 60000014 sample: 59 adc: 2050 eqep: 597 gpio: 0 duty: 100 last-data-req: 40554491 last-cmd: 0
cycle: 61000014 sample: 60 adc: 2049 eqep: 608 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 62000014 sample: 61 adc: 2049 eqep: 615 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 63000014 sample: 62 adc: 2049 eqep: 623 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 64000014 sample: 63 adc: 2049 eqep: 631 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 65000017 sample: 64 adc: 2050 eqep: 638 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 66000016 sample: 65 adc: 2051 eqep: 645 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 67000016 sample: 66 adc: 2049 eqep: 650 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 68000016 sample: 67 adc: 2050 eqep: 654 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 69000016 sample: 68 adc: 2050 eqep: 655 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 70000016 sample: 69 adc: 2051 eqep: 653 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 71000016 sample: 70 adc: 2049 eqep: 646 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 72000016 sample: 71 adc: 2050 eqep: 635 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 73000016 sample: 72 adc: 2050 eqep: 621 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 74000016 sample: 73 adc: 2050 eqep: 603 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 75000016 sample: 74 adc: 2051 eqep: 580 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 76000016 sample: 75 adc: 2049 eqep: 554 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 77000016 sample: 76 adc: 2049 eqep: 525 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 78000016 sample: 77 adc: 2049 eqep: 490 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 79000016 sample: 78 adc: 2051 eqep: 446 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 80000016 sample: 79 adc: 2051 eqep: 389 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
Buffer 3:
cycle: 69000016 sample: 68 adc: 2050 eqep: 655 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 70000016 sample: 69 adc: 2051 eqep: 653 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 71000016 sample: 70 adc: 2049 eqep: 646 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 72000016 sample: 71 adc: 2050 eqep: 635 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 73000016 sample: 72 adc: 2050 eqep: 621 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 74000016 sample: 73 adc: 2050 eqep: 603 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 75000016 sample: 74 adc: 2051 eqep: 580 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 76000016 sample: 75 adc: 2049 eqep: 554 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 77000016 sample: 76 adc: 2049 eqep: 525 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 78000016 sample: 77 adc: 2049 eqep: 490 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 79000016 sample: 78 adc: 2051 eqep: 446 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 80000016 sample: 79 adc: 2051 eqep: 389 gpio: 0 duty: 100 last-data-req: 60790923 last-cmd: 0
cycle: 81000016 sample: 80 adc: 2051 eqep: 322 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 82000016 sample: 81 adc: 2051 eqep: 249 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 83000016 sample: 82 adc: 2050 eqep: 174 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 84000016 sample: 83 adc: 2050 eqep: 92 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 85000016 sample: 84 adc: 2051 eqep: 5 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 86000016 sample: 85 adc: 2051 eqep: -72 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 87000016 sample: 86 adc: 2049 eqep: -137 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 88000016 sample: 87 adc: 2049 eqep: -183 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 89000016 sample: 88 adc: 2051 eqep: -218 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 90000016 sample: 89 adc: 2051 eqep: -250 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 91000016 sample: 90 adc: 2050 eqep: -265 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 92000016 sample: 91 adc: 2051 eqep: -266 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 93000016 sample: 92 adc: 2051 eqep: -265 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 94000016 sample: 93 adc: 2049 eqep: -265 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 95000016 sample: 94 adc: 2051 eqep: -264 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 96000016 sample: 95 adc: 2050 eqep: -264 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 97000019 sample: 96 adc: 2050 eqep: -263 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 98000018 sample: 97 adc: 2050 eqep: -262 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 99000018 sample: 98 adc: 2050 eqep: -261 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 100000018 sample: 99 adc: 2050 eqep: -260 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
Buffer 4:
cycle: 89000016 sample: 88 adc: 2051 eqep: -218 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 90000016 sample: 89 adc: 2051 eqep: -250 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 91000016 sample: 90 adc: 2050 eqep: -265 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 92000016 sample: 91 adc: 2051 eqep: -266 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 93000016 sample: 92 adc: 2051 eqep: -265 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 94000016 sample: 93 adc: 2049 eqep: -265 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 95000016 sample: 94 adc: 2051 eqep: -264 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 96000016 sample: 95 adc: 2050 eqep: -264 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 97000019 sample: 96 adc: 2050 eqep: -263 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 98000018 sample: 97 adc: 2050 eqep: -262 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 99000018 sample: 98 adc: 2050 eqep: -261 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 100000018 sample: 99 adc: 2050 eqep: -260 gpio: 0 duty: 100 last-data-req: 80830269 last-cmd: 0
cycle: 101000018 sample: 100 adc: 2051 eqep: -257 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 102000018 sample: 101 adc: 2050 eqep: -254 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 103000018 sample: 102 adc: 2050 eqep: -251 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 104000018 sample: 103 adc: 2051 eqep: -247 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 105000018 sample: 104 adc: 2050 eqep: -243 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 106000018 sample: 105 adc: 2048 eqep: -238 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 107000018 sample: 106 adc: 2049 eqep: -232 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 108000018 sample: 107 adc: 2050 eqep: -226 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 109000018 sample: 108 adc: 2051 eqep: -219 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 110000018 sample: 109 adc: 2051 eqep: -210 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 111000018 sample: 110 adc: 2051 eqep: -197 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 112000018 sample: 111 adc: 2050 eqep: -180 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 113000018 sample: 112 adc: 2050 eqep: -159 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 114000018 sample: 113 adc: 2051 eqep: -135 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 115000018 sample: 114 adc: 2049 eqep: -105 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 116000018 sample: 115 adc: 2050 eqep: -68 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 117000018 sample: 116 adc: 2051 eqep: -23 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 118000018 sample: 117 adc: 2049 eqep: 26 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 119000018 sample: 118 adc: 2050 eqep: 82 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 120000018 sample: 119 adc: 2050 eqep: 140 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
Buffer 5:
cycle: 109000018 sample: 108 adc: 2051 eqep: -219 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 110000018 sample: 109 adc: 2051 eqep: -210 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 111000018 sample: 110 adc: 2051 eqep: -197 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 112000018 sample: 111 adc: 2050 eqep: -180 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 113000018 sample: 112 adc: 2050 eqep: -159 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 114000018 sample: 113 adc: 2051 eqep: -135 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 115000018 sample: 114 adc: 2049 eqep: -105 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 116000018 sample: 115 adc: 2050 eqep: -68 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 117000018 sample: 116 adc: 2051 eqep: -23 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 118000018 sample: 117 adc: 2049 eqep: 26 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 119000018 sample: 118 adc: 2050 eqep: 82 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 120000018 sample: 119 adc: 2050 eqep: 140 gpio: 0 duty: 100 last-data-req: 100865983 last-cmd: 0
cycle: 121000018 sample: 120 adc: 2050 eqep: 194 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 122000018 sample: 121 adc: 2050 eqep: 250 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 123000018 sample: 122 adc: 2050 eqep: 309 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 124000018 sample: 123 adc: 2050 eqep: 365 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 125000018 sample: 124 adc: 2050 eqep: 415 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 126000018 sample: 125 adc: 2050 eqep: 451 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 127000018 sample: 126 adc: 2050 eqep: 482 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 128000018 sample: 127 adc: 2049 eqep: 507 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 129000021 sample: 128 adc: 2050 eqep: 528 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 130000020 sample: 129 adc: 2050 eqep: 553 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 131000020 sample: 130 adc: 2050 eqep: 572 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 132000020 sample: 131 adc: 2050 eqep: 587 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 133000020 sample: 132 adc: 2050 eqep: 599 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 134000020 sample: 133 adc: 2049 eqep: 609 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 135000020 sample: 134 adc: 2050 eqep: 617 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 136000020 sample: 135 adc: 2050 eqep: 623 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 137000020 sample: 136 adc: 2050 eqep: 627 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 138000020 sample: 137 adc: 2050 eqep: 629 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 139000020 sample: 138 adc: 2050 eqep: 629 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 140000020 sample: 139 adc: 2050 eqep: 629 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
Buffer 6:
cycle: 130000020 sample: 129 adc: 2050 eqep: 553 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 131000020 sample: 130 adc: 2050 eqep: 572 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 132000020 sample: 131 adc: 2050 eqep: 587 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 133000020 sample: 132 adc: 2050 eqep: 599 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 134000020 sample: 133 adc: 2049 eqep: 609 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 135000020 sample: 134 adc: 2050 eqep: 617 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 136000020 sample: 135 adc: 2050 eqep: 623 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 137000020 sample: 136 adc: 2050 eqep: 627 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 138000020 sample: 137 adc: 2050 eqep: 629 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 139000020 sample: 138 adc: 2050 eqep: 629 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 140000020 sample: 139 adc: 2050 eqep: 629 gpio: 0 duty: 100 last-data-req: 120914591 last-cmd: 0
cycle: 141000020 sample: 140 adc: 2050 eqep: 629 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 142000020 sample: 141 adc: 2049 eqep: 629 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 143000020 sample: 142 adc: 2049 eqep: 629 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 144000020 sample: 143 adc: 2050 eqep: 629 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 145000020 sample: 144 adc: 2050 eqep: 629 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 146000020 sample: 145 adc: 2050 eqep: 627 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 147000020 sample: 146 adc: 2049 eqep: 626 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 148000020 sample: 147 adc: 2050 eqep: 623 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 149000020 sample: 148 adc: 2050 eqep: 619 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 150000020 sample: 149 adc: 2050 eqep: 614 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 151000020 sample: 150 adc: 2050 eqep: 610 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 152000020 sample: 151 adc: 2050 eqep: 602 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 153000020 sample: 152 adc: 2050 eqep: 591 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 154000020 sample: 153 adc: 2050 eqep: 575 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 155000020 sample: 154 adc: 2050 eqep: 553 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 156000020 sample: 155 adc: 2050 eqep: 529 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 157000020 sample: 156 adc: 2050 eqep: 501 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 158000020 sample: 157 adc: 2050 eqep: 467 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 159000020 sample: 158 adc: 2050 eqep: 427 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 160000020 sample: 159 adc: 2050 eqep: 381 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 161000023 sample: 160 adc: 2050 eqep: 329 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
Buffer 7:
cycle: 150000020 sample: 149 adc: 2050 eqep: 614 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 151000020 sample: 150 adc: 2050 eqep: 610 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 152000020 sample: 151 adc: 2050 eqep: 602 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 153000020 sample: 152 adc: 2050 eqep: 591 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 154000020 sample: 153 adc: 2050 eqep: 575 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 155000020 sample: 154 adc: 2050 eqep: 553 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 156000020 sample: 155 adc: 2050 eqep: 529 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 157000020 sample: 156 adc: 2050 eqep: 501 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 158000020 sample: 157 adc: 2050 eqep: 467 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 159000020 sample: 158 adc: 2050 eqep: 427 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 160000020 sample: 159 adc: 2050 eqep: 381 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 161000023 sample: 160 adc: 2050 eqep: 329 gpio: 0 duty: 100 last-data-req: 140975345 last-cmd: 0
cycle: 162000022 sample: 161 adc: 2050 eqep: 278 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 163000022 sample: 162 adc: 2050 eqep: 231 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 164000022 sample: 163 adc: 2049 eqep: 185 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 165000022 sample: 164 adc: 2051 eqep: 137 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 166000022 sample: 165 adc: 2050 eqep: 85 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 167000022 sample: 166 adc: 2050 eqep: 35 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 168000022 sample: 167 adc: 2050 eqep: -11 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 169000022 sample: 168 adc: 2050 eqep: -51 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 170000022 sample: 169 adc: 2050 eqep: -77 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 171000022 sample: 170 adc: 2052 eqep: -95 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 172000022 sample: 171 adc: 2049 eqep: -105 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 173000022 sample: 172 adc: 2049 eqep: -109 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 174000022 sample: 173 adc: 2050 eqep: -109 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 175000022 sample: 174 adc: 2050 eqep: -108 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 176000022 sample: 175 adc: 2050 eqep: -104 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 177000022 sample: 176 adc: 2050 eqep: -97 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 178000022 sample: 177 adc: 2050 eqep: -86 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 179000022 sample: 178 adc: 2049 eqep: -69 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 180000022 sample: 179 adc: 2051 eqep: -45 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 181000022 sample: 180 adc: 2049 eqep: -12 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
Buffer 8:
cycle: 170000022 sample: 169 adc: 2050 eqep: -77 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 171000022 sample: 170 adc: 2052 eqep: -95 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 172000022 sample: 171 adc: 2049 eqep: -105 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 173000022 sample: 172 adc: 2049 eqep: -109 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 174000022 sample: 173 adc: 2050 eqep: -109 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 175000022 sample: 174 adc: 2050 eqep: -108 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 176000022 sample: 175 adc: 2050 eqep: -104 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 177000022 sample: 176 adc: 2050 eqep: -97 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 178000022 sample: 177 adc: 2050 eqep: -86 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 179000022 sample: 178 adc: 2049 eqep: -69 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 180000022 sample: 179 adc: 2051 eqep: -45 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 181000022 sample: 180 adc: 2049 eqep: -12 gpio: 0 duty: 100 last-data-req: 161034275 last-cmd: 0
cycle: 182000022 sample: 181 adc: 2050 eqep: 18 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 183000022 sample: 182 adc: 2049 eqep: 53 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 184000022 sample: 183 adc: 2050 eqep: 91 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 185000022 sample: 184 adc: 2050 eqep: 130 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 186000022 sample: 185 adc: 2050 eqep: 160 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 187000022 sample: 186 adc: 2049 eqep: 176 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 188000022 sample: 187 adc: 2050 eqep: 181 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 189000022 sample: 188 adc: 2050 eqep: 179 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 190000022 sample: 189 adc: 2050 eqep: 171 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 191000022 sample: 190 adc: 2050 eqep: 158 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 192000022 sample: 191 adc: 2049 eqep: 138 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 193000025 sample: 192 adc: 2051 eqep: 113 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 194000024 sample: 193 adc: 2050 eqep: 88 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 195000024 sample: 194 adc: 2050 eqep: 67 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 196000024 sample: 195 adc: 2050 eqep: 48 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 197000024 sample: 196 adc: 2052 eqep: 33 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 198000024 sample: 197 adc: 2051 eqep: 35 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 199000024 sample: 198 adc: 2050 eqep: 39 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 200000024 sample: 199 adc: 2050 eqep: 42 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 201000024 sample: 200 adc: 2051 eqep: 43 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
Buffer 9:
cycle: 190000022 sample: 189 adc: 2050 eqep: 171 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 191000022 sample: 190 adc: 2050 eqep: 158 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 192000022 sample: 191 adc: 2049 eqep: 138 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 193000025 sample: 192 adc: 2051 eqep: 113 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 194000024 sample: 193 adc: 2050 eqep: 88 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 195000024 sample: 194 adc: 2050 eqep: 67 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 196000024 sample: 195 adc: 2050 eqep: 48 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 197000024 sample: 196 adc: 2052 eqep: 33 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 198000024 sample: 197 adc: 2051 eqep: 35 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 199000024 sample: 198 adc: 2050 eqep: 39 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 200000024 sample: 199 adc: 2050 eqep: 42 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 201000024 sample: 200 adc: 2051 eqep: 43 gpio: 0 duty: 100 last-data-req: 181093635 last-cmd: 0
cycle: 202000024 sample: 201 adc: 2050 eqep: 42 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 203000024 sample: 202 adc: 2049 eqep: 40 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 204000024 sample: 203 adc: 2050 eqep: 37 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 205000024 sample: 204 adc: 2051 eqep: 35 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 206000024 sample: 205 adc: 2050 eqep: 34 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 207000024 sample: 206 adc: 2050 eqep: 33 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 208000024 sample: 207 adc: 2048 eqep: 33 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 209000024 sample: 208 adc: 2050 eqep: 33 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 210000024 sample: 209 adc: 2049 eqep: 33 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 211000024 sample: 210 adc: 2050 eqep: 33 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 212000024 sample: 211 adc: 2049 eqep: 33 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 213000024 sample: 212 adc: 2048 eqep: 33 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 214000024 sample: 213 adc: 2050 eqep: 32 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 215000024 sample: 214 adc: 2049 eqep: 29 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 216000024 sample: 215 adc: 2050 eqep: 23 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 217000024 sample: 216 adc: 2049 eqep: 14 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 218000024 sample: 217 adc: 2051 eqep: 1 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 219000024 sample: 218 adc: 2050 eqep: -16 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 220000024 sample: 219 adc: 2050 eqep: -37 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
cycle: 221000024 sample: 220 adc: 2050 eqep: -61 gpio: 0 duty: 100 last-data-req: 201153157 last-cmd: 0
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# 



///////////////////////////////////////

test2 example output:

for this one you should hook up an oscope to one of these pins and verify you see the beats of the various songs:


r30.t0 P9_31 switch btwn 0 & 1
r30.t1 P9_29 ghostbusters
r30.t2 P9_30 terminator
t30.t5 P9_27 mario



root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ./test2-gpio-tests
Welcome to the Beaglebone PRU library for real-time controls!
NOTE: if you get a seg fault, make sure the jppprugpio device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo jppprugpio > /sys/devices/bone_capemgr.9/slots
Also do this:
echo bone_eqep1 > $SLOTS
prussdrv_init() (returned 0)
prussdrv_open (returned 0)
prussdrv_pruintc_init (returned 0)
pruss_map_prumem (returned 0)
pru0 data memory addr: 0xb6e2a000
 ctrladdr_CPU_wants_data : 0xb6e2a000
 ctrladdr_PRU_data_ready : 0xb6e2a004
 ctrladdr_CPU_new_sched  : 0xb6e2a008
 ctrladdr_PRU_ack_sched  : 0xb6e2a00c
 addr_cpu_data_buf : 0xb6e2a010
 addr_pru_data_buf : 0xb6e2a410
 addr_cpu_cmd_buf  : 0xb6e2a810
 addr_pru_cmd_buf  : 0xb6e2aa10
executing bin file: ./jpp-pru-lib.bin
NOTE: a lot of stuff assumes PRU0 in this lib, sry.
prussdrv_exec_program returned 0
Waiting 200ms to let PRU fill its internal buffer...done.
Before:
cycle: 9000028 sample: 8 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 10000028 sample: 9 adc: 2048 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 11000028 sample: 10 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 12000028 sample: 11 adc: 2048 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 13000028 sample: 12 adc: 2049 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 14000028 sample: 13 adc: 2051 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 15000028 sample: 14 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 16000028 sample: 15 adc: 2049 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 17000028 sample: 16 adc: 2049 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 18000028 sample: 17 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 19000028 sample: 18 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 20000028 sample: 19 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 21000028 sample: 20 adc: 2049 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 22000028 sample: 21 adc: 2051 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 23000028 sample: 22 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 24000028 sample: 23 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 25000028 sample: 24 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 26000028 sample: 25 adc: 2049 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 27000028 sample: 26 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 28000028 sample: 27 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 29000028 sample: 28 adc: 2049 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 30000028 sample: 29 adc: 2051 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 31000028 sample: 30 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 32000028 sample: 31 adc: 2049 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 33000015 sample: 32 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 34000014 sample: 33 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 35000014 sample: 34 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 36000014 sample: 35 adc: 2051 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 37000014 sample: 36 adc: 2049 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 38000014 sample: 37 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 39000014 sample: 38 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 40000014 sample: 39 adc: 2050 eqep: 5 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
Sending cmd...
After 100ms:
cycle: 210000026 sample: 209 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 211000026 sample: 210 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 212000026 sample: 211 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 213000026 sample: 212 adc: 2049 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 214000026 sample: 213 adc: 2049 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 215000026 sample: 214 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 216000026 sample: 215 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 217000026 sample: 216 adc: 2049 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 218000026 sample: 217 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 219000026 sample: 218 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 220000026 sample: 219 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 221000026 sample: 220 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 222000026 sample: 221 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 223000026 sample: 222 adc: 2049 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 224000026 sample: 223 adc: 2049 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 225000029 sample: 224 adc: 2049 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 226000028 sample: 225 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 227000028 sample: 226 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 228000028 sample: 227 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 229000028 sample: 228 adc: 2052 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 230000028 sample: 229 adc: 2049 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 231000028 sample: 230 adc: 2049 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 232000028 sample: 231 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 233000028 sample: 232 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 234000028 sample: 233 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 235000028 sample: 234 adc: 2049 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 236000028 sample: 235 adc: 2049 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 237000028 sample: 236 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 238000028 sample: 237 adc: 2049 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 239000028 sample: 238 adc: 2050 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 240000028 sample: 239 adc: 2051 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
cycle: 241000028 sample: 240 adc: 2049 eqep: 5 gpio: 48 duty: 100 last-data-req: 40583307 last-cmd: 40993328
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# 






//////////////////////////////////////////
test3-drive-motor

This program drives the gpios so that the motor drives 

  char* cmds_str[] = {"STBY","CW","BRAKE","CCW","BRAKE","CW","STBY"};


note: since only 100% or -100% or 0%, I didn't use the 6v battery because 6V thrashes the little motor. Instead I used 2V from the agilent power supply.


example output:

root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ./run
I'm in: 
/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests
==========================
building PRU library...
Compiling .c file jpp-pru-lib.c into .o file jpp-pru-lib.o
Using pasm to assemble .p file jpp-pru-lib.p into .bin file jpp-pru-lib.bin...


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 307 word(s)

Building test .c file test3-drive-motor.c to make test3-drive-motor
NOT Running 
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ./test3-drive-motor
Welcome to the Beaglebone PRU library for real-time controls!
NOTE: if you get a seg fault, make sure the jppprugpio device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo jppprugpio > /sys/devices/bone_capemgr.9/slots
Also do this:
echo bone_eqep1 > $SLOTS
prussdrv_init() (returned 0)
prussdrv_open (returned 0)
prussdrv_pruintc_init (returned 0)
pruss_map_prumem (returned 0)
pru0 data memory addr: 0xb6da5000
 ctrladdr_CPU_wants_data : 0xb6da5000
 ctrladdr_PRU_data_ready : 0xb6da5004
 ctrladdr_CPU_new_sched  : 0xb6da5008
 ctrladdr_PRU_ack_sched  : 0xb6da500c
 addr_cpu_data_buf : 0xb6da5010
 addr_pru_data_buf : 0xb6da5410
 addr_cpu_cmd_buf  : 0xb6da5810
 addr_pru_cmd_buf  : 0xb6da5a10
executing bin file: ./jpp-pru-lib.bin
NOTE: a lot of stuff assumes PRU0 in this lib, sry.
prussdrv_exec_program returned 0
Waiting 200ms to let PRU fill its internal buffer...done.
0x0	0x5	0x23	0x25
Cmd (STBY): 0x0
Data data_buf:
cycle: 9000028 sample: 8 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 10000028 sample: 9 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 11000028 sample: 10 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 12000028 sample: 11 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 13000028 sample: 12 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 14000028 sample: 13 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 15000028 sample: 14 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 16000028 sample: 15 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 17000028 sample: 16 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 18000028 sample: 17 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 19000028 sample: 18 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 20000028 sample: 19 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 21000028 sample: 20 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 22000028 sample: 21 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 23000028 sample: 22 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 24000028 sample: 23 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 25000028 sample: 24 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 26000028 sample: 25 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 27000028 sample: 26 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 28000028 sample: 27 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 29000028 sample: 28 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 30000028 sample: 29 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 31000028 sample: 30 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 32000028 sample: 31 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 33000015 sample: 32 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 34000014 sample: 33 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 35000014 sample: 34 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 36000014 sample: 35 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 37000014 sample: 36 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 38000014 sample: 37 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 39000014 sample: 38 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 40000014 sample: 39 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
Sending cmd...
Sleeping for 20ms...
Data after:
cycle: 13000028 sample: 12 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 14000028 sample: 13 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 15000028 sample: 14 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 16000028 sample: 15 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 17000028 sample: 16 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 18000028 sample: 17 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 19000028 sample: 18 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 20000028 sample: 19 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 21000028 sample: 20 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 22000028 sample: 21 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 23000028 sample: 22 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 24000028 sample: 23 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 25000028 sample: 24 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 26000028 sample: 25 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 27000028 sample: 26 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 28000028 sample: 27 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 29000028 sample: 28 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 30000028 sample: 29 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 31000028 sample: 30 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 32000028 sample: 31 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 33000015 sample: 32 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 34000014 sample: 33 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 35000014 sample: 34 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 36000014 sample: 35 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 37000014 sample: 36 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 38000014 sample: 37 adc: 2049 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 39000014 sample: 38 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 40000014 sample: 39 adc: 2050 eqep: -49548193 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0
cycle: 41000018 sample: 40 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 40202555 last-cmd: 40612464
cycle: 42000016 sample: 41 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 40202555 last-cmd: 40612464
cycle: 43000014 sample: 42 adc: 2049 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 40202555 last-cmd: 40612464
cycle: 44000028 sample: 43 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 40202555 last-cmd: 40612464
Sleeping for 2 sec...
Cmd (CW): 0x23
Data data_buf:
cycle: 414000024 sample: 413 adc: 2049 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 415000024 sample: 414 adc: 2049 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 416000024 sample: 415 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 417000027 sample: 416 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 418000026 sample: 417 adc: 2049 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 419000026 sample: 418 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 420000026 sample: 419 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 421000026 sample: 420 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 422000026 sample: 421 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 423000026 sample: 422 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 424000026 sample: 423 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 425000026 sample: 424 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 426000026 sample: 425 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 427000026 sample: 426 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 428000026 sample: 427 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 429000026 sample: 428 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 430000026 sample: 429 adc: 2048 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 431000026 sample: 430 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 432000026 sample: 431 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 433000026 sample: 432 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 434000026 sample: 433 adc: 2049 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 435000026 sample: 434 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 436000026 sample: 435 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 437000026 sample: 436 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 438000026 sample: 437 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 439000026 sample: 438 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 440000026 sample: 439 adc: 2048 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 441000026 sample: 440 adc: 2049 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 442000026 sample: 441 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 443000026 sample: 442 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 444000026 sample: 443 adc: 2049 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 445000026 sample: 444 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
Sending cmd...
Sleeping for 20ms...
Data after:
cycle: 420000026 sample: 419 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 421000026 sample: 420 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 422000026 sample: 421 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 423000026 sample: 422 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 424000026 sample: 423 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 425000026 sample: 424 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 426000026 sample: 425 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 427000026 sample: 426 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 428000026 sample: 427 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 429000026 sample: 428 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 430000026 sample: 429 adc: 2048 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 431000026 sample: 430 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 432000026 sample: 431 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 433000026 sample: 432 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 434000026 sample: 433 adc: 2049 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 435000026 sample: 434 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 436000026 sample: 435 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 437000026 sample: 436 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 438000026 sample: 437 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 439000026 sample: 438 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 440000026 sample: 439 adc: 2048 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 441000026 sample: 440 adc: 2049 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 442000026 sample: 441 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 443000026 sample: 442 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 444000026 sample: 443 adc: 2049 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 445000026 sample: 444 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 44778855 last-cmd: 40612464
cycle: 446000026 sample: 445 adc: 2050 eqep: -49548193 gpio: 48 duty: 100 last-data-req: 445253783 last-cmd: 40612464
cycle: 447000014 sample: 446 adc: 2050 eqep: -49548193 gpio: 6b duty: 100 last-data-req: 445253783 last-cmd: 446224140
cycle: 448000028 sample: 447 adc: 2050 eqep: -49548203 gpio: 6b duty: 100 last-data-req: 445253783 last-cmd: 446224140
cycle: 449000029 sample: 448 adc: 2050 eqep: -49548274 gpio: 6b duty: 100 last-data-req: 445253783 last-cmd: 446224140
cycle: 450000026 sample: 449 adc: 2050 eqep: -49548382 gpio: 6b duty: 100 last-data-req: 445253783 last-cmd: 446224140
cycle: 451000024 sample: 450 adc: 2049 eqep: -49548529 gpio: 6b duty: 100 last-data-req: 445253783 last-cmd: 446224140
Sleeping for 2 sec...
Cmd (BRAKE): 0x5
Data data_buf:
cycle: 820000022 sample: 819 adc: 2049 eqep: -49729740 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 821000022 sample: 820 adc: 2050 eqep: -49730227 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 822000022 sample: 821 adc: 2050 eqep: -49730743 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 823000022 sample: 822 adc: 2050 eqep: -49731246 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 824000022 sample: 823 adc: 2050 eqep: -49731748 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 825000022 sample: 824 adc: 2049 eqep: -49732246 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 826000022 sample: 825 adc: 2050 eqep: -49732773 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 827000022 sample: 826 adc: 2049 eqep: -49733265 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 828000022 sample: 827 adc: 2050 eqep: -49733755 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 829000022 sample: 828 adc: 2049 eqep: -49734278 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 830000022 sample: 829 adc: 2050 eqep: -49734784 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 831000022 sample: 830 adc: 2050 eqep: -49735271 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 832000022 sample: 831 adc: 2050 eqep: -49735786 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 833000025 sample: 832 adc: 2049 eqep: -49736300 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 834000024 sample: 833 adc: 2050 eqep: -49736796 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 835000024 sample: 834 adc: 2050 eqep: -49737286 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 836000024 sample: 835 adc: 2049 eqep: -49737812 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 837000024 sample: 836 adc: 2050 eqep: -49738315 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 838000024 sample: 837 adc: 2050 eqep: -49738801 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 839000024 sample: 838 adc: 2049 eqep: -49739316 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 840000024 sample: 839 adc: 2050 eqep: -49739830 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 841000024 sample: 840 adc: 2050 eqep: -49740323 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 842000024 sample: 841 adc: 2050 eqep: -49740817 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 843000024 sample: 842 adc: 2049 eqep: -49741338 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 844000024 sample: 843 adc: 2050 eqep: -49741840 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 845000024 sample: 844 adc: 2050 eqep: -49742331 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 846000024 sample: 845 adc: 2049 eqep: -49742844 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 847000024 sample: 846 adc: 2050 eqep: -49743356 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 848000024 sample: 847 adc: 2050 eqep: -49743850 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 849000024 sample: 848 adc: 2050 eqep: -49744340 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 850000024 sample: 849 adc: 2049 eqep: -49744869 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 851000024 sample: 850 adc: 2049 eqep: -49745372 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
Sending cmd...
Sleeping for 20ms...
Data after:
cycle: 826000022 sample: 825 adc: 2050 eqep: -49732773 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 827000022 sample: 826 adc: 2049 eqep: -49733265 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 828000022 sample: 827 adc: 2050 eqep: -49733755 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 829000022 sample: 828 adc: 2049 eqep: -49734278 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 830000022 sample: 829 adc: 2050 eqep: -49734784 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 831000022 sample: 830 adc: 2050 eqep: -49735271 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 832000022 sample: 831 adc: 2050 eqep: -49735786 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 833000025 sample: 832 adc: 2049 eqep: -49736300 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 834000024 sample: 833 adc: 2050 eqep: -49736796 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 835000024 sample: 834 adc: 2050 eqep: -49737286 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 836000024 sample: 835 adc: 2049 eqep: -49737812 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 837000024 sample: 836 adc: 2050 eqep: -49738315 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 838000024 sample: 837 adc: 2050 eqep: -49738801 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 839000024 sample: 838 adc: 2049 eqep: -49739316 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 840000024 sample: 839 adc: 2050 eqep: -49739830 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 841000024 sample: 840 adc: 2050 eqep: -49740323 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 842000024 sample: 841 adc: 2050 eqep: -49740817 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 843000024 sample: 842 adc: 2049 eqep: -49741338 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 844000024 sample: 843 adc: 2050 eqep: -49741840 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 845000024 sample: 844 adc: 2050 eqep: -49742331 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 846000024 sample: 845 adc: 2049 eqep: -49742844 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 847000024 sample: 846 adc: 2050 eqep: -49743356 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 848000024 sample: 847 adc: 2050 eqep: -49743850 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 849000024 sample: 848 adc: 2050 eqep: -49744340 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 850000024 sample: 849 adc: 2049 eqep: -49744869 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 851000024 sample: 850 adc: 2049 eqep: -49745372 gpio: 6b duty: 100 last-data-req: 451024851 last-cmd: 446224140
cycle: 852000024 sample: 851 adc: 2050 eqep: -49745855 gpio: 6b duty: 100 last-data-req: 851521557 last-cmd: 446224140
cycle: 853000028 sample: 852 adc: 2052 eqep: -49746374 gpio: 4d duty: 100 last-data-req: 851521557 last-cmd: 852443642
cycle: 854000026 sample: 853 adc: 2049 eqep: -49746859 gpio: 4d duty: 100 last-data-req: 851521557 last-cmd: 852443642
cycle: 855000024 sample: 854 adc: 2051 eqep: -49747278 gpio: 4d duty: 100 last-data-req: 851521557 last-cmd: 852443642
cycle: 856000022 sample: 855 adc: 2049 eqep: -49747649 gpio: 4d duty: 100 last-data-req: 851521557 last-cmd: 852443642
cycle: 857000020 sample: 856 adc: 2049 eqep: -49747990 gpio: 4d duty: 100 last-data-req: 851521557 last-cmd: 852443642
Sleeping for 2 sec...
Cmd (CCW): 0x25
Data data_buf:
cycle: 1226000020 sample: 1225 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1227000020 sample: 1226 adc: 2051 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1228000020 sample: 1227 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1229000020 sample: 1228 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1230000020 sample: 1229 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1231000020 sample: 1230 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1232000020 sample: 1231 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1233000020 sample: 1232 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1234000020 sample: 1233 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1235000020 sample: 1234 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1236000020 sample: 1235 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1237000020 sample: 1236 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1238000020 sample: 1237 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1239000020 sample: 1238 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1240000020 sample: 1239 adc: 2051 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1241000020 sample: 1240 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1242000020 sample: 1241 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1243000020 sample: 1242 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1244000020 sample: 1243 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1245000020 sample: 1244 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1246000020 sample: 1245 adc: 2051 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1247000020 sample: 1246 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1248000020 sample: 1247 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1249000023 sample: 1248 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1250000022 sample: 1249 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1251000022 sample: 1250 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1252000022 sample: 1251 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1253000022 sample: 1252 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1254000022 sample: 1253 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1255000022 sample: 1254 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1256000022 sample: 1255 adc: 2051 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1257000022 sample: 1256 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
Sending cmd...
Sleeping for 20ms...
Data after:
cycle: 1232000020 sample: 1231 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1233000020 sample: 1232 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1234000020 sample: 1233 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1235000020 sample: 1234 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1236000020 sample: 1235 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1237000020 sample: 1236 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1238000020 sample: 1237 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1239000020 sample: 1238 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1240000020 sample: 1239 adc: 2051 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1241000020 sample: 1240 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1242000020 sample: 1241 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1243000020 sample: 1242 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1244000020 sample: 1243 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1245000020 sample: 1244 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1246000020 sample: 1245 adc: 2051 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1247000020 sample: 1246 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1248000020 sample: 1247 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1249000023 sample: 1248 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1250000022 sample: 1249 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1251000022 sample: 1250 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1252000022 sample: 1251 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1253000022 sample: 1252 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1254000022 sample: 1253 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1255000022 sample: 1254 adc: 2049 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1256000022 sample: 1255 adc: 2051 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1257000022 sample: 1256 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 857255455 last-cmd: 852443642
cycle: 1258000022 sample: 1257 adc: 2050 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 1257740979 last-cmd: 852443642
cycle: 1259000022 sample: 1258 adc: 2051 eqep: -49750051 gpio: 4d duty: 100 last-data-req: 1257740979 last-cmd: 852443642
cycle: 1260000026 sample: 1259 adc: 2050 eqep: -49750051 gpio: 6d duty: 100 last-data-req: 1257740979 last-cmd: 1259107208
cycle: 1261000024 sample: 1260 adc: 2051 eqep: -49750026 gpio: 6d duty: 100 last-data-req: 1257740979 last-cmd: 1259107208
cycle: 1262000022 sample: 1261 adc: 2051 eqep: -49749954 gpio: 6d duty: 100 last-data-req: 1257740979 last-cmd: 1259107208
cycle: 1263000020 sample: 1262 adc: 2049 eqep: -49749848 gpio: 6d duty: 100 last-data-req: 1257740979 last-cmd: 1259107208
Sleeping for 2 sec...
Cmd (BRAKE): 0x5
Data data_buf:
cycle: 1632000016 sample: 1631 adc: 2049 eqep: -49566341 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1633000019 sample: 1632 adc: 2051 eqep: -49565856 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1634000018 sample: 1633 adc: 2050 eqep: -49565331 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1635000018 sample: 1634 adc: 2050 eqep: -49564815 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1636000018 sample: 1635 adc: 2050 eqep: -49564316 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1637000018 sample: 1636 adc: 2050 eqep: -49563817 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1638000018 sample: 1637 adc: 2050 eqep: -49563286 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1639000018 sample: 1638 adc: 2051 eqep: -49562781 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1640000018 sample: 1639 adc: 2050 eqep: -49562292 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1641000018 sample: 1640 adc: 2050 eqep: -49561768 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1642000018 sample: 1641 adc: 2050 eqep: -49561252 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1643000018 sample: 1642 adc: 2049 eqep: -49560759 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1644000018 sample: 1643 adc: 2049 eqep: -49560251 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1645000018 sample: 1644 adc: 2049 eqep: -49559732 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1646000018 sample: 1645 adc: 2049 eqep: -49559229 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1647000018 sample: 1646 adc: 2050 eqep: -49558727 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1648000018 sample: 1647 adc: 2050 eqep: -49558205 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1649000018 sample: 1648 adc: 2050 eqep: -49557689 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1650000018 sample: 1649 adc: 2050 eqep: -49557196 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1651000018 sample: 1650 adc: 2050 eqep: -49556691 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1652000018 sample: 1651 adc: 2050 eqep: -49556160 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1653000018 sample: 1652 adc: 2049 eqep: -49555657 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1654000018 sample: 1653 adc: 2050 eqep: -49555168 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1655000018 sample: 1654 adc: 2050 eqep: -49554636 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1656000018 sample: 1655 adc: 2050 eqep: -49554126 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1657000018 sample: 1656 adc: 2050 eqep: -49553630 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1658000018 sample: 1657 adc: 2051 eqep: -49553123 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1659000018 sample: 1658 adc: 2050 eqep: -49552597 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1660000018 sample: 1659 adc: 2049 eqep: -49552096 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1661000018 sample: 1660 adc: 2051 eqep: -49551603 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1662000018 sample: 1661 adc: 2051 eqep: -49551071 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1663000018 sample: 1662 adc: 2051 eqep: -49550560 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
Sending cmd...
Sleeping for 20ms...
Data after:
cycle: 1638000018 sample: 1637 adc: 2050 eqep: -49563286 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1639000018 sample: 1638 adc: 2051 eqep: -49562781 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1640000018 sample: 1639 adc: 2050 eqep: -49562292 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1641000018 sample: 1640 adc: 2050 eqep: -49561768 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1642000018 sample: 1641 adc: 2050 eqep: -49561252 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1643000018 sample: 1642 adc: 2049 eqep: -49560759 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1644000018 sample: 1643 adc: 2049 eqep: -49560251 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1645000018 sample: 1644 adc: 2049 eqep: -49559732 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1646000018 sample: 1645 adc: 2049 eqep: -49559229 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1647000018 sample: 1646 adc: 2050 eqep: -49558727 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1648000018 sample: 1647 adc: 2050 eqep: -49558205 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1649000018 sample: 1648 adc: 2050 eqep: -49557689 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1650000018 sample: 1649 adc: 2050 eqep: -49557196 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1651000018 sample: 1650 adc: 2050 eqep: -49556691 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1652000018 sample: 1651 adc: 2050 eqep: -49556160 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1653000018 sample: 1652 adc: 2049 eqep: -49555657 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1654000018 sample: 1653 adc: 2050 eqep: -49555168 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1655000018 sample: 1654 adc: 2050 eqep: -49554636 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1656000018 sample: 1655 adc: 2050 eqep: -49554126 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1657000018 sample: 1656 adc: 2050 eqep: -49553630 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1658000018 sample: 1657 adc: 2051 eqep: -49553123 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1659000018 sample: 1658 adc: 2050 eqep: -49552597 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1660000018 sample: 1659 adc: 2049 eqep: -49552096 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1661000018 sample: 1660 adc: 2051 eqep: -49551603 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1662000018 sample: 1661 adc: 2051 eqep: -49551071 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1663000018 sample: 1662 adc: 2051 eqep: -49550560 gpio: 6d duty: 100 last-data-req: 1263200415 last-cmd: 1259107208
cycle: 1664000018 sample: 1663 adc: 2050 eqep: -49550070 gpio: 6d duty: 100 last-data-req: 1663690127 last-cmd: 1259107208
cycle: 1665000025 sample: 1664 adc: 2048 eqep: -49549550 gpio: 4d duty: 100 last-data-req: 1663690127 last-cmd: 1664925687
cycle: 1666000022 sample: 1665 adc: 2050 eqep: -49549055 gpio: 4d duty: 100 last-data-req: 1663690127 last-cmd: 1664925687
cycle: 1667000020 sample: 1666 adc: 2049 eqep: -49548630 gpio: 4d duty: 100 last-data-req: 1663690127 last-cmd: 1664925687
cycle: 1668000018 sample: 1667 adc: 2051 eqep: -49548256 gpio: 4d duty: 100 last-data-req: 1663690127 last-cmd: 1664925687
cycle: 1669000016 sample: 1668 adc: 2050 eqep: -49547915 gpio: 4d duty: 100 last-data-req: 1663690127 last-cmd: 1664925687
Sleeping for 2 sec...
Cmd (CW): 0x23
Data data_buf:
cycle: 2038000014 sample: 2037 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2039000014 sample: 2038 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2040000014 sample: 2039 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2041000014 sample: 2040 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2042000014 sample: 2041 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2043000014 sample: 2042 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2044000014 sample: 2043 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2045000014 sample: 2044 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2046000014 sample: 2045 adc: 2051 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2047000014 sample: 2046 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2048000014 sample: 2047 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2049000017 sample: 2048 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2050000016 sample: 2049 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2051000016 sample: 2050 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2052000016 sample: 2051 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2053000016 sample: 2052 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2054000016 sample: 2053 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2055000016 sample: 2054 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2056000016 sample: 2055 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2057000016 sample: 2056 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2058000016 sample: 2057 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2059000016 sample: 2058 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2060000016 sample: 2059 adc: 2051 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2061000016 sample: 2060 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2062000016 sample: 2061 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2063000016 sample: 2062 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2064000016 sample: 2063 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2065000016 sample: 2064 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2066000016 sample: 2065 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2067000016 sample: 2066 adc: 2051 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2068000016 sample: 2067 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2069000016 sample: 2068 adc: 2051 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
Sending cmd...
Sleeping for 20ms...
Data after:
cycle: 2044000014 sample: 2043 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2045000014 sample: 2044 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2046000014 sample: 2045 adc: 2051 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2047000014 sample: 2046 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2048000014 sample: 2047 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2049000017 sample: 2048 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2050000016 sample: 2049 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2051000016 sample: 2050 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2052000016 sample: 2051 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2053000016 sample: 2052 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2054000016 sample: 2053 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2055000016 sample: 2054 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2056000016 sample: 2055 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2057000016 sample: 2056 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2058000016 sample: 2057 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2059000016 sample: 2058 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2060000016 sample: 2059 adc: 2051 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2061000016 sample: 2060 adc: 2049 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2062000016 sample: 2061 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2063000016 sample: 2062 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2064000016 sample: 2063 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2065000016 sample: 2064 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2066000016 sample: 2065 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2067000016 sample: 2066 adc: 2051 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2068000016 sample: 2067 adc: 2050 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2069000016 sample: 2068 adc: 2051 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 1669048635 last-cmd: 1664925687
cycle: 2070000016 sample: 2069 adc: 2051 eqep: -49545846 gpio: 4d duty: 100 last-data-req: 2069527773 last-cmd: 1664925687
cycle: 2071000020 sample: 2070 adc: 2048 eqep: -49545846 gpio: 6b duty: 100 last-data-req: 2069527773 last-cmd: 2070420594
cycle: 2072000018 sample: 2071 adc: 2050 eqep: -49545868 gpio: 6b duty: 100 last-data-req: 2069527773 last-cmd: 2070420594
cycle: 2073000016 sample: 2072 adc: 2050 eqep: -49545941 gpio: 6b duty: 100 last-data-req: 2069527773 last-cmd: 2070420594
cycle: 2074000014 sample: 2073 adc: 2050 eqep: -49546051 gpio: 6b duty: 100 last-data-req: 2069527773 last-cmd: 2070420594
cycle: 2075000028 sample: 2074 adc: 2050 eqep: -49546198 gpio: 6b duty: 100 last-data-req: 2069527773 last-cmd: 2070420594
Sleeping for 2 sec...
Cmd (STBY): 0x0
Data data_buf:
cycle: 2444000028 sample: 2443 adc: 2050 eqep: -49727714 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2445000028 sample: 2444 adc: 2051 eqep: -49728200 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2446000028 sample: 2445 adc: 2050 eqep: -49728705 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2447000028 sample: 2446 adc: 2050 eqep: -49729219 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2448000028 sample: 2447 adc: 2050 eqep: -49729713 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2449000028 sample: 2448 adc: 2050 eqep: -49730197 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2450000028 sample: 2449 adc: 2050 eqep: -49730713 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2451000028 sample: 2450 adc: 2049 eqep: -49731213 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2452000028 sample: 2451 adc: 2050 eqep: -49731711 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2453000028 sample: 2452 adc: 2050 eqep: -49732212 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2454000028 sample: 2453 adc: 2051 eqep: -49732738 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2455000028 sample: 2454 adc: 2050 eqep: -49733231 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2456000028 sample: 2455 adc: 2050 eqep: -49733720 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2457000028 sample: 2456 adc: 2050 eqep: -49734239 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2458000028 sample: 2457 adc: 2049 eqep: -49734744 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2459000028 sample: 2458 adc: 2051 eqep: -49735232 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2460000028 sample: 2459 adc: 2050 eqep: -49735742 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2461000028 sample: 2460 adc: 2049 eqep: -49736257 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2462000028 sample: 2461 adc: 2050 eqep: -49736751 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2463000028 sample: 2462 adc: 2048 eqep: -49737238 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2464000028 sample: 2463 adc: 2050 eqep: -49737759 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2465000015 sample: 2464 adc: 2051 eqep: -49738258 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2466000014 sample: 2465 adc: 2049 eqep: -49738754 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2467000014 sample: 2466 adc: 2049 eqep: -49739255 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2468000014 sample: 2467 adc: 2051 eqep: -49739777 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2469000014 sample: 2468 adc: 2051 eqep: -49740270 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2470000014 sample: 2469 adc: 2051 eqep: -49740761 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2471000014 sample: 2470 adc: 2050 eqep: -49741282 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2472000014 sample: 2471 adc: 2050 eqep: -49741786 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2473000014 sample: 2472 adc: 2050 eqep: -49742272 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2474000014 sample: 2473 adc: 2049 eqep: -49742781 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2475000014 sample: 2474 adc: 2049 eqep: -49743283 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
Sending cmd...
Sleeping for 20ms...
Data after:
cycle: 2450000028 sample: 2449 adc: 2050 eqep: -49730713 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2451000028 sample: 2450 adc: 2049 eqep: -49731213 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2452000028 sample: 2451 adc: 2050 eqep: -49731711 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2453000028 sample: 2452 adc: 2050 eqep: -49732212 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2454000028 sample: 2453 adc: 2051 eqep: -49732738 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2455000028 sample: 2454 adc: 2050 eqep: -49733231 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2456000028 sample: 2455 adc: 2050 eqep: -49733720 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2457000028 sample: 2456 adc: 2050 eqep: -49734239 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2458000028 sample: 2457 adc: 2049 eqep: -49734744 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2459000028 sample: 2458 adc: 2051 eqep: -49735232 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2460000028 sample: 2459 adc: 2050 eqep: -49735742 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2461000028 sample: 2460 adc: 2049 eqep: -49736257 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2462000028 sample: 2461 adc: 2050 eqep: -49736751 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2463000028 sample: 2462 adc: 2048 eqep: -49737238 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2464000028 sample: 2463 adc: 2050 eqep: -49737759 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2465000015 sample: 2464 adc: 2051 eqep: -49738258 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2466000014 sample: 2465 adc: 2049 eqep: -49738754 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2467000014 sample: 2466 adc: 2049 eqep: -49739255 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2468000014 sample: 2467 adc: 2051 eqep: -49739777 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2469000014 sample: 2468 adc: 2051 eqep: -49740270 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2470000014 sample: 2469 adc: 2051 eqep: -49740761 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2471000014 sample: 2470 adc: 2050 eqep: -49741282 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2472000014 sample: 2471 adc: 2050 eqep: -49741786 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2473000014 sample: 2472 adc: 2050 eqep: -49742272 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2474000014 sample: 2473 adc: 2049 eqep: -49742781 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2475000014 sample: 2474 adc: 2049 eqep: -49743283 gpio: 6b duty: 100 last-data-req: 2075254231 last-cmd: 2070420594
cycle: 2476000014 sample: 2475 adc: 2049 eqep: -49743781 gpio: 6b duty: 100 last-data-req: 2475757883 last-cmd: 2070420594
cycle: 2477000014 sample: 2476 adc: 2049 eqep: -49744277 gpio: 6b duty: 100 last-data-req: 2475757883 last-cmd: 2070420594
cycle: 2478000018 sample: 2477 adc: 2047 eqep: -49744800 gpio: 48 duty: 100 last-data-req: 2475757883 last-cmd: 2477452432
cycle: 2479000016 sample: 2478 adc: 2048 eqep: -49745304 gpio: 48 duty: 100 last-data-req: 2475757883 last-cmd: 2477452432
cycle: 2480000014 sample: 2479 adc: 2050 eqep: -49745784 gpio: 48 duty: 100 last-data-req: 2475757883 last-cmd: 2477452432
cycle: 2481000028 sample: 2480 adc: 2050 eqep: -49746268 gpio: 48 duty: 100 last-data-req: 2475757883 last-cmd: 2477452432
Sleeping for 2 sec...
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# 

















/////////////////
test4-sysid

this program sends a particular trajectory of motor cmds to the motor for the purposes of doing system identification on the system.



example output:

root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ./run
I'm in: 
/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests
==========================
building PRU library...
Compiling .c file jpp-pru-lib.c into .o file jpp-pru-lib.o
Using pasm to assemble .p file jpp-pru-lib.p into .bin file jpp-pru-lib.bin...


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 307 word(s)

Building test .c file test4-sysid.c to make test4-sysid
NOT Running 
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ./test4-sysid
Welcome to the Beaglebone PRU library for real-time controls!
NOTE: if you get a seg fault, make sure the jppprugpio device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo jppprugpio > /sys/devices/bone_capemgr.9/slots
Also do this:
echo bone_eqep1 > $SLOTS
prussdrv_init() (returned 0)
prussdrv_open (returned 0)
prussdrv_pruintc_init (returned 0)
pruss_map_prumem (returned 0)
pru0 data memory addr: 0xb6cd6000
 ctrladdr_CPU_wants_data : 0xb6cd6000
 ctrladdr_PRU_data_ready : 0xb6cd6004
 ctrladdr_CPU_new_sched  : 0xb6cd6008
 ctrladdr_PRU_ack_sched  : 0xb6cd600c
 addr_cpu_data_buf : 0xb6cd6010
 addr_pru_data_buf : 0xb6cd6410
 addr_cpu_cmd_buf  : 0xb6cd6810
 addr_pru_cmd_buf  : 0xb6cd6a10
executing bin file: ./jpp-pru-lib.bin
NOTE: a lot of stuff assumes PRU0 in this lib, sry.
prussdrv_exec_program returned 0
Waiting 200ms to let PRU fill its internal buffer...done.
0x0	0x5	0x23	0x25
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ls
bak		 jpp-pru-lib.c	  jpp-pru-lib.p   sysid-data.txt	  test2-gpio-tests	test4-sysid.c
bak2		 jpp-pru-lib.c~   jpp-pru-lib.p~  test0-get-data	  test2-gpio-tests.c	test4-sysid.c~
jadcpwmeqep.c	 jpp-pru-lib.h	  #readme#	  test0-get-data.c	  test2-gpio-tests.c~
jadcpwmeqep.h	 jpp-pru-lib.h~   readme.txt	  test0-get-data.c~	  test3-drive-motor
jadcpwmeqep.h~	 jpp-pru-lib.hp   readme.txt~	  test1-get-data-fast	  test3-drive-motor.c
jadcpwmeqep.o	 jpp-pru-lib.hp~  run		  test1-get-data-fast.c   test3-drive-motor.c~
jpp-pru-lib.bin  jpp-pru-lib.o	  run~		  test1-get-data-fast.c~  test4-sysid
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# l
total 1.7M
 20K -rw-r--r-- 1 root root  18K Apr 23  2014 jpp-pru-lib.p
 12K -rw-r--r-- 1 root root 8.4K Apr 23  2014 jpp-pru-lib.c
4.0K drwxr-xr-x 5 root root 4.0K Apr 23  2014 ..
4.0K -rw-r--r-- 1 root root 3.9K Apr 23  2014 jpp-pru-lib.hp~
4.0K -rw-r--r-- 1 root root 1.8K Apr 23  2014 test3-drive-motor.c
 20K -rwxr-xr-x 1 root root  19K Apr 23  2014 test3-drive-motor
4.0K -rw-r--r-- 1 root root  125 Apr 23  2014 jpp-pru-lib.h~
4.0K -rw-r--r-- 1 root root 1.8K Apr 23  2014 test4-sysid.c~
144K -rw-r--r-- 1 root root 141K Apr 23  2014 readme.txt~
144K -rw-r--r-- 1 root root 142K Apr 23  2014 readme.txt
4.0K -rw-r--r-- 1 root root  190 Apr 23  2014 test0-get-data.c~
 48K -rw-r--r-- 1 root root  48K Apr 23  2014 jadcpwmeqep.o
4.0K -rw-r--r-- 1 root root  997 Apr 23  2014 jpp-pru-lib.h
4.0K -rwxr-xr-x 1 root root 1.3K Apr 23  2014 run~
4.0K -rw-r--r-- 1 root root 3.1K Apr 30  2014 jadcpwmeqep.h~
 40K -rw-r--r-- 1 root root  37K Apr 30  2014 jadcpwmeqep.c
4.0K drwxr-xr-x 2 root root 4.0K Apr 30  2014 bak
   0 lrwxrwxrwx 1 root root   32 Apr 30  2014 .#readme -> root@beaglebone.24998:1398791143
4.0K -rw-r--r-- 1 root root   13 Apr 30  2014 #readme#
4.0K -rw-r--r-- 1 root root 3.1K Aug 31 16:48 jadcpwmeqep.h
 20K -rw-r--r-- 1 root root  18K Sep  2 11:07 jpp-pru-lib.p~
4.0K -rw-r--r-- 1 root root  984 Sep  2 11:07 test2-gpio-tests.c~
8.0K -rw-r--r-- 1 root root 4.1K Sep  2 11:08 jpp-pru-lib.hp
4.0K -rw-r--r-- 1 root root  206 Sep  2 11:09 test1-get-data-fast.c~
4.0K drwxr-xr-x 2 root root 4.0K Sep  2 11:10 bak2
4.0K -rw-r--r-- 1 root root  203 Sep  2 11:24 test0-get-data.c
 12K -rw-r--r-- 1 root root 8.3K Sep  2 13:49 jpp-pru-lib.c~
 20K -rwxr-xr-x 1 root root  17K Sep  2 14:02 test0-get-data
4.0K -rw-r--r-- 1 root root  591 Sep  2 14:04 test1-get-data-fast.c
 20K -rwxr-xr-x 1 root root  18K Sep  2 14:05 test2-gpio-tests
 20K -rwxr-xr-x 1 root root  17K Sep  2 14:06 test1-get-data-fast
4.0K -rw-r--r-- 1 root root 2.0K Sep  2 14:09 test2-gpio-tests.c
4.0K -rw-r--r-- 1 root root 2.9K Sep  2 16:56 test3-drive-motor.c~
 12K -rw-r--r-- 1 root root 8.8K Sep  6 12:09 test4-sysid.c
4.0K -rwxr-xr-x 1 root root 1.5K Sep  6 12:11 run
 16K -rw-r--r-- 1 root root  14K Sep  6 12:11 jpp-pru-lib.o
4.0K -rw-r--r-- 1 root root 1.2K Sep  6 12:11 jpp-pru-lib.bin
 24K -rwxr-xr-x 1 root root  24K Sep  6 12:11 test4-sysid
4.0K drwxr-xr-x 4 root root 4.0K Sep  6 12:11 .
972K -rw-r--r-- 1 root root 970K Sep  6 12:11 sysid-data.txt
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# 

text file output:

cycle: 9000028 sample: 8 adc: 2100 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.063472 angle: 0.000000 volts: 0.000000
cycle: 10000028 sample: 9 adc: 2152 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.132756 angle: 0.000000 volts: 0.000000
cycle: 11000028 sample: 10 adc: 2158 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.140751 angle: 0.000000 volts: 0.000000
cycle: 12000028 sample: 11 adc: 2103 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.067469 angle: 0.000000 volts: 0.000000
cycle: 13000028 sample: 12 adc: 2115 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.083458 angle: 0.000000 volts: 0.000000
cycle: 14000028 sample: 13 adc: 2176 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.164734 angle: 0.000000 volts: 0.000000
cycle: 15000028 sample: 14 adc: 2173 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.160736 angle: 0.000000 volts: 0.000000
cycle: 16000028 sample: 15 adc: 2144 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.122097 angle: 0.000000 volts: 0.000000
cycle: 17000028 sample: 16 adc: 2156 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.138086 angle: 0.000000 volts: 0.000000
cycle: 18000028 sample: 17 adc: 2147 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.126094 angle: 0.000000 volts: 0.000000
cycle: 19000028 sample: 18 adc: 2144 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.122097 angle: 0.000000 volts: 0.000000
cycle: 20000028 sample: 19 adc: 2184 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.175393 angle: 0.000000 volts: 0.000000
cycle: 21000028 sample: 20 adc: 2123 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.094117 angle: 0.000000 volts: 0.000000
cycle: 22000028 sample: 21 adc: 2138 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.114103 angle: 0.000000 volts: 0.000000
cycle: 23000028 sample: 22 adc: 2180 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.170063 angle: 0.000000 volts: 0.000000
cycle: 24000028 sample: 23 adc: 2170 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.156739 angle: 0.000000 volts: 0.000000
cycle: 25000028 sample: 24 adc: 2191 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.184719 angle: 0.000000 volts: 0.000000
cycle: 26000028 sample: 25 adc: 2162 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.146080 angle: 0.000000 volts: 0.000000
cycle: 27000028 sample: 26 adc: 2144 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.122097 angle: 0.000000 volts: 0.000000
cycle: 28000028 sample: 27 adc: 2163 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.147412 angle: 0.000000 volts: 0.000000
cycle: 29000028 sample: 28 adc: 2129 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.102111 angle: 0.000000 volts: 0.000000
cycle: 30000028 sample: 29 adc: 2162 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.146080 angle: 0.000000 volts: 0.000000
cycle: 31000028 sample: 30 adc: 2169 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.155407 angle: 0.000000 volts: 0.000000
cycle: 32000028 sample: 31 adc: 2180 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.170063 angle: 0.000000 volts: 0.000000
cycle: 33000015 sample: 32 adc: 2150 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.130091 angle: 0.000000 volts: 0.000000
cycle: 34000014 sample: 33 adc: 2147 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.126094 angle: 0.000000 volts: 0.000000
cycle: 35000014 sample: 34 adc: 2167 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.152742 angle: 0.000000 volts: 0.000000
cycle: 36000014 sample: 35 adc: 2103 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.067469 angle: 0.000000 volts: 0.000000
cycle: 37000014 sample: 36 adc: 2144 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.122097 angle: 0.000000 volts: 0.000000
cycle: 38000014 sample: 37 adc: 2174 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.162069 angle: 0.000000 volts: 0.000000
cycle: 39000014 sample: 38 adc: 2201 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.198043 angle: 0.000000 volts: 0.000000
cycle: 40000014 sample: 39 adc: 2153 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.134089 angle: 0.000000 volts: 0.000000
cycle: 10000028 sample: 9 adc: 2152 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.132756 angle: 0.000000 volts: 4.000000
cycle: 11000028 sample: 10 adc: 2158 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.140751 angle: 0.000000 volts: 4.000000
cycle: 12000028 sample: 11 adc: 2103 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.067469 angle: 0.000000 volts: 4.000000
cycle: 13000028 sample: 12 adc: 2115 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.083458 angle: 0.000000 volts: 4.000000
cycle: 14000028 sample: 13 adc: 2176 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.164734 angle: 0.000000 volts: 4.000000
cycle: 15000028 sample: 14 adc: 2173 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.160736 angle: 0.000000 volts: 4.000000
cycle: 16000028 sample: 15 adc: 2144 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.122097 angle: 0.000000 volts: 4.000000
cycle: 17000028 sample: 16 adc: 2156 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.138086 angle: 0.000000 volts: 4.000000
cycle: 18000028 sample: 17 adc: 2147 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.126094 angle: 0.000000 volts: 4.000000
cycle: 19000028 sample: 18 adc: 2144 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.122097 angle: 0.000000 volts: 4.000000
cycle: 20000028 sample: 19 adc: 2184 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.175393 angle: 0.000000 volts: 4.000000
cycle: 21000028 sample: 20 adc: 2123 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.094117 angle: 0.000000 volts: 4.000000
cycle: 22000028 sample: 21 adc: 2138 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.114103 angle: 0.000000 volts: 4.000000
cycle: 23000028 sample: 22 adc: 2180 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.170063 angle: 0.000000 volts: 4.000000
cycle: 24000028 sample: 23 adc: 2170 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.156739 angle: 0.000000 volts: 4.000000
cycle: 25000028 sample: 24 adc: 2191 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.184719 angle: 0.000000 volts: 4.000000
cycle: 26000028 sample: 25 adc: 2162 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.146080 angle: 0.000000 volts: 4.000000
cycle: 27000028 sample: 26 adc: 2144 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.122097 angle: 0.000000 volts: 4.000000
cycle: 28000028 sample: 27 adc: 2163 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.147412 angle: 0.000000 volts: 4.000000
cycle: 29000028 sample: 28 adc: 2129 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.102111 angle: 0.000000 volts: 4.000000
cycle: 30000028 sample: 29 adc: 2162 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.146080 angle: 0.000000 volts: 4.000000
cycle: 31000028 sample: 30 adc: 2169 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.155407 angle: 0.000000 volts: 4.000000
cycle: 32000028 sample: 31 adc: 2180 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.170063 angle: 0.000000 volts: 4.000000
cycle: 33000015 sample: 32 adc: 2150 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.130091 angle: 0.000000 volts: 4.000000
cycle: 34000014 sample: 33 adc: 2147 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.126094 angle: 0.000000 volts: 4.000000
cycle: 35000014 sample: 34 adc: 2167 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.152742 angle: 0.000000 volts: 4.000000
cycle: 36000014 sample: 35 adc: 2103 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.067469 angle: 0.000000 volts: 4.000000
cycle: 37000014 sample: 36 adc: 2144 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.122097 angle: 0.000000 volts: 4.000000
cycle: 38000014 sample: 37 adc: 2174 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.162069 angle: 0.000000 volts: 4.000000
cycle: 39000014 sample: 38 adc: 2201 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.198043 angle: 0.000000 volts: 4.000000
cycle: 40000014 sample: 39 adc: 2153 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.134089 angle: 0.000000 volts: 4.000000
cycle: 41000018 sample: 40 adc: 2116 eqep: 0 gpio: 48 duty: 100 last-data-req: 40463227 last-cmd: 40535984 amps: -0.084790 angle: 0.000000 volts: 4.000000
cycle: 11000028 sample: 10 adc: 2158 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.140751 angle: 0.000000 volts: 4.000000
cycle: 12000028 sample: 11 adc: 2103 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.067469 angle: 0.000000 volts: 4.000000
cycle: 13000028 sample: 12 adc: 2115 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.083458 angle: 0.000000 volts: 4.000000
cycle: 14000028 sample: 13 adc: 2176 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.164734 angle: 0.000000 volts: 4.000000
cycle: 15000028 sample: 14 adc: 2173 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.160736 angle: 0.000000 volts: 4.000000
cycle: 16000028 sample: 15 adc: 2144 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.122097 angle: 0.000000 volts: 4.000000
cycle: 17000028 sample: 16 adc: 2156 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.138086 angle: 0.000000 volts: 4.000000
cycle: 18000028 sample: 17 adc: 2147 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.126094 angle: 0.000000 volts: 4.000000
cycle: 19000028 sample: 18 adc: 2144 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.122097 angle: 0.000000 volts: 4.000000
cycle: 20000028 sample: 19 adc: 2184 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.175393 angle: 0.000000 volts: 4.000000
cycle: 21000028 sample: 20 adc: 2123 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.094117 angle: 0.000000 volts: 4.000000
cycle: 22000028 sample: 21 adc: 2138 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.114103 angle: 0.000000 volts: 4.000000
cycle: 23000028 sample: 22 adc: 2180 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.170063 angle: 0.000000 volts: 4.000000
cycle: 24000028 sample: 23 adc: 2170 eqep: 0 gpio: 0 duty: 100 last-data-req: 0 last-cmd: 0 amps: -0.156739 angle: 0.000000 volts: 4.000000










//////////////////////////////

// test 5: calibrate current sensor



0 A:  Ave adc: 1944.653125
.2A: Ave adc: 1796.076562
.4A: Ave adc: 1645.387500
.6A: Ave adc: 1496.989062
.8A: Ave adc: 1346.962500
1A : Ave adc: 1197.746875

[
0   1944.653125
.2  1796.076562
.4  1645.387500
.6  1496.989062
.8  1346.962500
1    1197.746875
]



>> p = polyfit(d(:,2),d(:,1),1)

p =

   -0.0013    2.6030

>> p(1)

ans =

   -0.0013

>> p(2)

ans =

    2.6030

>> help polyval
 polyval Evaluate polynomial.
    Y = polyval(P,X) returns the value of a polynomial P evaluated at X. P
    is a vector of length N+1 whose elements are the coefficients of the
    polynomial in descending powers.
 
        Y = P(1)*X^N + P(2)*X^(N-1) + ... + P(N)*X + P(N+1)
 
    If X is a matrix or vector, the polynomial is evaluated at all
    points in X.  See POLYVALM for evaluation in a matrix sense.
 
    [Y,DELTA] = polyval(P,X,S) uses the optional output structure S created
    by POLYFIT to generate prediction error estimates DELTA.  DELTA is an
    estimate of the standard deviation of the error in predicting a future
    observation at X by P(X).
 
    If the coefficients in P are least squares estimates computed by
    POLYFIT, and the errors in the data input to POLYFIT are independent,
    normal, with constant variance, then Y +/- DELTA will contain at least
    50% of future observations at X.
 
    Y = polyval(P,X,[],MU) or [Y,DELTA] = polyval(P,X,S,MU) uses XHAT =
    (X-MU(1))/MU(2) in place of X. The centering and scaling parameters MU
    are optional output computed by POLYFIT.
 
    Example:
       Evaluate the polynomial p(x) = 3x^2+2x+1 at x = 5,7, and 9:
 
       p = [3 2 1];
       polyval(p,[5 7 9])%
 
    Class support for inputs P,X,S,MU:
       float: double, single
 
    See also polyfit, polyvalm.

    Reference page for polyval
    Other functions named polyval

>> polyval(p,1944)

ans =

    0.0012

>> polyval(p,1796)

ans =

    0.1993

>> polyval(p,1197)

ans =

    1.0010

>> p(1)

ans =

   -0.0013

>> p(2)

ans =

    2.6030

>> p(2) + p(1)*1944

ans =

    0.0012

>> p(2) + p(1)*1197

ans =

    1.0010



So the linear map from adc to amps is:

   2.602966952391388 + (-0.001338358981292) * adc_counts



root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# # here we go w/ .2 A:
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ./run
I'm in: 
/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests
Resetting eqep...
==========================
building PRU library...
Compiling .c file jpp-pru-lib.c into .o file jpp-pru-lib.o
Using pasm to assemble .p file jpp-pru-lib.p into .bin file jpp-pru-lib.bin...


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 307 word(s)

Building test .c file test5-calibrate-sensors.c to make test5-calibrate-sensors
test5-calibrate-sensors.c: In function ‘main’:
test5-calibrate-sensors.c:178:20: warning: unused variable ‘gpio_cmd’ [-Wunused-variable]
test5-calibrate-sensors.c:139:16: warning: unused variable ‘cmds’ [-Wunused-variable]
Running test5-calibrate-sensors
... at realtime priority:
Welcome to the Beaglebone PRU library for real-time controls!
NOTE: if you get a seg fault, make sure the jppprugpio device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo jppprugpio > /sys/devices/bone_capemgr.9/slots
Also do this:
echo bone_eqep1 > $SLOTS
prussdrv_init() (returned 0)
prussdrv_open (returned 0)
prussdrv_pruintc_init (returned 0)
pruss_map_prumem (returned 0)
pru0 data memory addr: 0xb6ce1000
 ctrladdr_CPU_wants_data : 0xb6ce1000
 ctrladdr_PRU_data_ready : 0xb6ce1004
 ctrladdr_CPU_new_sched  : 0xb6ce1008
 ctrladdr_PRU_ack_sched  : 0xb6ce100c
 addr_cpu_data_buf : 0xb6ce1010
 addr_pru_data_buf : 0xb6ce1410
 addr_cpu_cmd_buf  : 0xb6ce1810
 addr_pru_cmd_buf  : 0xb6ce1a10
executing bin file: ./jpp-pru-lib.bin
NOTE: a lot of stuff assumes PRU0 in this lib, sry.
prussdrv_exec_program returned 0
Waiting 200ms to let PRU fill its internal buffer...done.
0x0	0x5	0x23	0x25
1800 1804 1798 1808 1808 1783 1782 1804 1799 1787 1799 1795 1808 1795 1800 1796 1795 1793 1796 1775 1792 1806 1772 1795 1795 1791 1800 1814 1789 1808 1805 1774 
1788 1800 1789 1804 1792 1795 1792 1783 1775 1804 1783 1788 1799 1795 1804 1800 1800 1809 1774 1796 1795 1783 1777 1785 1811 1789 1805 1787 1804 1784 1802 1792 
1799 1790 1792 1799 1791 1816 1796 1792 1800 1800 1795 1806 1793 1801 1799 1803 1796 1807 1791 1795 1784 1807 1799 1795 1793 1793 1791 1796 1803 1799 1785 1808 
1779 1794 1801 1787 1800 1796 1776 1810 1804 1791 1799 1800 1791 1787 1800 1792 1794 1820 1803 1780 1792 1802 1793 1809 1789 1800 1796 1788 1791 1811 1785 1779 
1795 1786 1793 1791 1800 1806 1789 1792 1787 1803 1782 1793 1801 1813 1787 1787 1794 1796 1802 1799 1784 1793 1800 1796 1792 1776 1796 1791 1777 1778 1807 1804 
1796 1784 1798 1809 1791 1791 1792 1805 1804 1798 1800 1808 1796 1792 1802 1780 1803 1806 1791 1803 1803 1794 1808 1796 1799 1780 1792 1804 1785 1794 1810 1802 
1798 1785 1804 1785 1802 1803 1794 1791 1789 1796 1798 1782 1805 1791 1804 1799 1791 1787 1800 1795 1796 1777 1785 1798 1785 1792 1816 1777 1794 1816 1797 1805 
1792 1805 1795 1799 1800 1788 1811 1793 1811 1783 1796 1792 1803 1796 1824 1791 1832 1800 1799 1779 1807 1787 1793 1796 1794 1806 1783 1800 1776 1805 1791 1797 
1777 1799 1798 1791 1775 1779 1806 1795 1792 1790 1804 1807 1789 1805 1800 1802 1783 1784 1808 1792 1776 1772 1811 1783 1800 1796 1808 1793 1804 1795 1797 1792 
1796 1800 1790 1806 1799 1787 1807 1792 1800 1809 1799 1798 1804 1798 1801 1799 1796 1814 1820 1798 1775 1800 1799 1798 1795 1810 1788 1801 1783 1795 1808 1792 
1799 1794 1802 1781 1801 1807 1777 1808 1781 1787 1800 1792 1803 1802 1811 1792 1798 1816 1795 1805 1788 1792 1798 1792 1783 1800 1792 1794 1796 1797 1800 1792 
1796 1797 1776 1799 1807 1778 1795 1783 1794 1795 1795 1798 1776 1808 1805 1779 1796 1793 1785 1791 1807 1792 1792 1791 1796 1793 1815 1800 1808 1798 1808 1792 
1799 1800 1805 1796 1806 1795 1785 1807 1800 1792 1801 1799 1800 1791 1789 1803 1790 1806 1803 1794 1784 1798 1796 1779 1808 1796 1805 1816 1798 1802 1808 1811 
1787 1792 1798 1783 1789 1800 1796 1806 1773 1799 1799 1800 1792 1799 1804 1785 1782 1793 1780 1823 1795 1812 1799 1794 1802 1799 1796 1820 1783 1792 1804 1788 
1823 1783 1807 1796 1804 1796 1793 1793 1804 1779 1812 1793 1809 1799 1778 1802 1807 1793 1807 1795 1800 1794 1791 1792 1791 1792 1794 1795 1800 1805 1795 1803 
1798 1798 1796 1801 1788 1807 1800 1785 1791 1808 1792 1794 1799 1795 1813 1796 1795 1799 1789 1800 1808 1800 1798 1800 1791 1800 1801 1773 1817 1815 1808 1798 
1825 1802 1799 1786 1790 1791 1800 1761 1798 1811 1800 1787 1798 1812 1793 1794 1801 1792 1778 1798 1806 1793 1817 1803 1804 1791 1791 1792 1801 1793 1793 1820 
1790 1788 1800 1781 1792 1792 1792 1808 1793 1800 1783 1791 1804 1795 1795 1794 1777 1792 1792 1787 1792 1792 1804 1800 1797 1795 1808 1795 1784 1799 1788 1795 
1780 1800 1794 1806 1822 1790 1802 1808 1800 1783 1794 1800 1824 1800 1801 1800 1792 1791 1800 1808 1792 1799 1798 1794 1824 1803 1792 1792 1798 1791 1777 1800 
1792 1809 1796 1803 1792 1784 1778 1785 1791 1800 1792 1803 1793 1795 1795 1774 1785 1796 1795 1792 1809 1781 1795 1808 1807 1776 1779 1799 1795 1798 1779 1796 

Ave adc: 1796.076562
Making nicer data file...
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# # here we go, .4 A:
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ./run
I'm in: 
/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests
Resetting eqep...
==========================
building PRU library...
Compiling .c file jpp-pru-lib.c into .o file jpp-pru-lib.o
Using pasm to assemble .p file jpp-pru-lib.p into .bin file jpp-pru-lib.bin...


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 307 word(s)

Building test .c file test5-calibrate-sensors.c to make test5-calibrate-sensors
test5-calibrate-sensors.c: In function ‘main’:
test5-calibrate-sensors.c:178:20: warning: unused variable ‘gpio_cmd’ [-Wunused-variable]
test5-calibrate-sensors.c:139:16: warning: unused variable ‘cmds’ [-Wunused-variable]
Running test5-calibrate-sensors
... at realtime priority:
Welcome to the Beaglebone PRU library for real-time controls!
NOTE: if you get a seg fault, make sure the jppprugpio device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo jppprugpio > /sys/devices/bone_capemgr.9/slots
Also do this:
echo bone_eqep1 > $SLOTS
prussdrv_init() (returned 0)
prussdrv_open (returned 0)
prussdrv_pruintc_init (returned 0)
pruss_map_prumem (returned 0)
pru0 data memory addr: 0xb6d16000
 ctrladdr_CPU_wants_data : 0xb6d16000
 ctrladdr_PRU_data_ready : 0xb6d16004
 ctrladdr_CPU_new_sched  : 0xb6d16008
 ctrladdr_PRU_ack_sched  : 0xb6d1600c
 addr_cpu_data_buf : 0xb6d16010
 addr_pru_data_buf : 0xb6d16410
 addr_cpu_cmd_buf  : 0xb6d16810
 addr_pru_cmd_buf  : 0xb6d16a10
executing bin file: ./jpp-pru-lib.bin
NOTE: a lot of stuff assumes PRU0 in this lib, sry.
prussdrv_exec_program returned 0
Waiting 200ms to let PRU fill its internal buffer...done.
0x0	0x5	0x23	0x25
1639 1626 1656 1635 1664 1646 1623 1631 1668 1651 1639 1664 1639 1648 1644 1635 1641 1656 1645 1646 1640 1648 1646 1649 1655 1639 1645 1652 1646 1647 1636 1650 
1635 1639 1649 1648 1648 1648 1646 1639 1648 1648 1647 1650 1648 1644 1639 1664 1655 1662 1654 1656 1644 1625 1646 1652 1646 1628 1644 1651 1652 1635 1628 1648 
1647 1684 1635 1639 1640 1656 1651 1646 1644 1648 1655 1639 1644 1648 1639 1655 1643 1646 1637 1636 1656 1648 1646 1644 1649 1639 1634 1649 1626 1649 1646 1648 
1647 1648 1631 1639 1631 1644 1648 1660 1651 1640 1640 1651 1649 1657 1649 1641 1640 1656 1649 1659 1648 1639 1648 1639 1660 1647 1655 1664 1640 1643 1651 1646 
1659 1648 1646 1638 1637 1647 1648 1655 1663 1635 1648 1633 1648 1615 1636 1632 1649 1644 1631 1635 1660 1648 1641 1664 1661 1648 1647 1649 1645 1632 1639 1659 
1647 1631 1632 1639 1635 1661 1639 1640 1648 1655 1647 1660 1648 1639 1652 1640 1649 1645 1647 1643 1640 1647 1644 1633 1635 1639 1655 1660 1652 1643 1650 1639 
1633 1648 1656 1643 1649 1654 1653 1641 1645 1633 1655 1647 1635 1649 1636 1641 1636 1643 1641 1639 1664 1649 1655 1648 1647 1644 1646 1641 1640 1640 1639 1656 
1626 1643 1636 1644 1655 1649 1634 1641 1651 1657 1639 1660 1648 1643 1628 1631 1635 1647 1635 1660 1639 1648 1644 1650 1633 1643 1655 1648 1646 1647 1639 1640 
1632 1632 1644 1647 1647 1652 1636 1650 1638 1658 1660 1646 1646 1639 1632 1654 1644 1633 1652 1639 1649 1651 1649 1653 1639 1634 1644 1640 1640 1648 1649 1644 
1637 1633 1640 1644 1644 1647 1649 1654 1634 1654 1647 1656 1654 1635 1637 1643 1649 1628 1649 1647 1644 1647 1639 1647 1628 1646 1644 1660 1651 1641 1639 1654 
1643 1644 1641 1648 1652 1649 1655 1656 1647 1650 1644 1656 1647 1637 1644 1648 1650 1649 1655 1654 1655 1639 1646 1633 1655 1633 1649 1651 1640 1623 1644 1648 
1649 1647 1664 1651 1636 1651 1636 1647 1633 1645 1668 1647 1654 1651 1625 1639 1643 1664 1647 1650 1651 1647 1643 1657 1639 1630 1648 1647 1672 1625 1640 1644 
1652 1635 1641 1656 1655 1638 1657 1623 1656 1656 1654 1649 1631 1647 1639 1646 1649 1643 1643 1648 1650 1657 1648 1636 1639 1648 1635 1637 1640 1651 1634 1649 
1644 1633 1645 1664 1648 1632 1649 1643 1656 1632 1638 1649 1647 1644 1650 1655 1650 1652 1648 1635 1641 1654 1652 1639 1639 1660 1619 1632 1643 1648 1652 1639 
1645 1663 1656 1648 1647 1640 1641 1632 1649 1646 1649 1633 1633 1633 1648 1645 1651 1638 1640 1651 1647 1655 1648 1647 1647 1647 1636 1650 1656 1633 1652 1659 
1655 1644 1647 1628 1648 1655 1662 1624 1638 1659 1644 1615 1639 1648 1648 1632 1627 1655 1656 1645 1654 1651 1636 1648 1643 1641 1648 1656 1647 1640 1631 1656 
1639 1644 1659 1650 1625 1638 1632 1652 1633 1650 1628 1646 1639 1638 1649 1643 1639 1644 1641 1635 1656 1656 1668 1647 1663 1640 1639 1649 1647 1655 1624 1648 
1659 1656 1657 1655 1648 1639 1643 1656 1647 1652 1645 1649 1617 1650 1644 1659 1647 1646 1652 1666 1637 1643 1634 1647 1648 1632 1648 1651 1642 1659 1664 1648 
1638 1630 1643 1650 1651 1639 1646 1660 1657 1647 1637 1654 1633 1648 1647 1643 1640 1648 1656 1648 1640 1654 1635 1641 1650 1654 1630 1635 1629 1649 1633 1657 
1652 1644 1637 1648 1637 1631 1632 1651 1641 1647 1651 1649 1664 1672 1660 1657 1640 1632 1656 1640 1655 1646 1652 1646 1644 1631 1651 1652 1643 1639 1641 1648 

Ave adc: 1645.387500
Making nicer data file...
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# # .6 A:
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ./run
I'm in: 
/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests
Resetting eqep...
==========================
building PRU library...
Compiling .c file jpp-pru-lib.c into .o file jpp-pru-lib.o
Using pasm to assemble .p file jpp-pru-lib.p into .bin file jpp-pru-lib.bin...


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 307 word(s)

Building test .c file test5-calibrate-sensors.c to make test5-calibrate-sensors
test5-calibrate-sensors.c: In function ‘main’:
test5-calibrate-sensors.c:178:20: warning: unused variable ‘gpio_cmd’ [-Wunused-variable]
test5-calibrate-sensors.c:139:16: warning: unused variable ‘cmds’ [-Wunused-variable]
Running test5-calibrate-sensors
... at realtime priority:
Welcome to the Beaglebone PRU library for real-time controls!
NOTE: if you get a seg fault, make sure the jppprugpio device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo jppprugpio > /sys/devices/bone_capemgr.9/slots
Also do this:
echo bone_eqep1 > $SLOTS
prussdrv_init() (returned 0)
prussdrv_open (returned 0)
prussdrv_pruintc_init (returned 0)
pruss_map_prumem (returned 0)
pru0 data memory addr: 0xb6d1a000
 ctrladdr_CPU_wants_data : 0xb6d1a000
 ctrladdr_PRU_data_ready : 0xb6d1a004
 ctrladdr_CPU_new_sched  : 0xb6d1a008
 ctrladdr_PRU_ack_sched  : 0xb6d1a00c
 addr_cpu_data_buf : 0xb6d1a010
 addr_pru_data_buf : 0xb6d1a410
 addr_cpu_cmd_buf  : 0xb6d1a810
 addr_pru_cmd_buf  : 0xb6d1aa10
executing bin file: ./jpp-pru-lib.bin
NOTE: a lot of stuff assumes PRU0 in this lib, sry.
prussdrv_exec_program returned 0
Waiting 200ms to let PRU fill its internal buffer...done.
0x0	0x5	0x23	0x25
1510 1486 1489 1487 1504 1479 1487 1490 1500 1491 1504 1489 1503 1505 1478 1504 1486 1471 1491 1486 1498 1487 1488 1508 1488 1507 1483 1496 1499 1499 1500 1500 
1500 1491 1502 1507 1491 1489 1496 1499 1512 1500 1500 1488 1480 1504 1512 1508 1478 1487 1504 1504 1494 1486 1495 1500 1505 1484 1487 1520 1504 1486 1487 1484 
1498 1492 1487 1493 1504 1487 1508 1487 1491 1484 1488 1512 1490 1504 1520 1502 1511 1490 1506 1502 1504 1505 1496 1516 1506 1504 1486 1516 1504 1510 1495 1463 
1486 1503 1503 1504 1486 1491 1504 1475 1500 1494 1510 1505 1502 1508 1491 1496 1487 1501 1512 1504 1483 1504 1504 1494 1491 1487 1483 1504 1500 1487 1512 1508 
1507 1481 1499 1504 1482 1488 1508 1504 1495 1490 1499 1495 1504 1505 1508 1499 1517 1496 1500 1504 1486 1471 1496 1511 1491 1504 1536 1497 1496 1504 1495 1495 
1492 1512 1496 1496 1494 1488 1504 1503 1495 1503 1485 1487 1500 1487 1490 1504 1495 1482 1502 1497 1504 1496 1485 1503 1491 1501 1495 1511 1482 1502 1489 1502 
1499 1478 1495 1496 1504 1498 1507 1504 1491 1478 1497 1504 1496 1504 1504 1511 1500 1502 1493 1491 1495 1507 1492 1488 1491 1496 1487 1497 1505 1504 1485 1491 
1487 1512 1487 1489 1500 1500 1499 1494 1496 1506 1491 1491 1504 1495 1495 1498 1489 1479 1506 1488 1487 1484 1486 1499 1501 1498 1491 1499 1500 1512 1504 1498 
1492 1489 1489 1493 1497 1496 1502 1505 1501 1492 1491 1507 1498 1499 1494 1500 1504 1513 1505 1495 1488 1489 1496 1498 1483 1483 1484 1500 1508 1514 1503 1488 
1502 1512 1492 1455 1487 1510 1491 1487 1487 1519 1496 1479 1520 1520 1497 1503 1507 1493 1511 1497 1480 1480 1504 1494 1513 1485 1481 1500 1502 1495 1500 1481 
1478 1504 1522 1485 1514 1512 1501 1489 1486 1502 1500 1497 1505 1500 1481 1504 1497 1497 1487 1505 1511 1505 1494 1486 1507 1496 1500 1502 1502 1487 1471 1481 
1494 1507 1500 1504 1502 1504 1492 1482 1508 1485 1499 1501 1505 1508 1486 1471 1494 1518 1505 1498 1505 1485 1479 1504 1495 1503 1491 1488 1510 1491 1500 1501 
1500 1504 1499 1500 1487 1507 1490 1494 1495 1507 1489 1491 1500 1478 1496 1507 1485 1495 1508 1508 1488 1504 1491 1487 1495 1508 1500 1507 1487 1497 1495 1500 
1487 1491 1487 1488 1500 1507 1508 1487 1500 1496 1490 1479 1503 1499 1500 1489 1488 1501 1491 1491 1502 1501 1478 1495 1496 1496 1502 1504 1507 1502 1498 1486 
1500 1496 1504 1489 1508 1488 1496 1500 1496 1492 1505 1494 1496 1499 1511 1504 1496 1496 1499 1484 1498 1510 1495 1487 1483 1496 1505 1507 1502 1504 1498 1504 
1496 1504 1497 1484 1505 1504 1486 1490 1497 1505 1475 1496 1494 1486 1504 1501 1508 1520 1499 1532 1496 1512 1495 1496 1471 1497 1508 1487 1508 1504 1507 1488 
1502 1479 1488 1514 1481 1499 1489 1490 1505 1507 1488 1502 1504 1500 1506 1512 1503 1496 1505 1483 1489 1505 1504 1506 1512 1503 1504 1496 1499 1494 1510 1497 
1495 1490 1500 1504 1504 1516 1512 1488 1498 1480 1504 1507 1494 1500 1504 1487 1493 1495 1491 1504 1500 1509 1504 1512 1487 1487 1489 1492 1492 1499 1500 1504 
1487 1488 1496 1505 1492 1512 1504 1504 1497 1500 1508 1499 1483 1479 1497 1484 1489 1500 1491 1500 1507 1508 1510 1500 1499 1502 1495 1502 1499 1504 1499 1515 
1487 1479 1496 1503 1494 1493 1490 1487 1491 1488 1505 1520 1495 1492 1504 1497 1483 1485 1489 1500 1518 1490 1497 1487 1491 1486 1497 1496 1503 1475 1503 1491 

Ave adc: 1496.989062
Making nicer data file...
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# # .8 A:
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ./run
I'm in: 
/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests
Resetting eqep...
==========================
building PRU library...
Compiling .c file jpp-pru-lib.c into .o file jpp-pru-lib.o
Using pasm to assemble .p file jpp-pru-lib.p into .bin file jpp-pru-lib.bin...


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 307 word(s)

Building test .c file test5-calibrate-sensors.c to make test5-calibrate-sensors
test5-calibrate-sensors.c: In function ‘main’:
test5-calibrate-sensors.c:178:20: warning: unused variable ‘gpio_cmd’ [-Wunused-variable]
test5-calibrate-sensors.c:139:16: warning: unused variable ‘cmds’ [-Wunused-variable]
Running test5-calibrate-sensors
... at realtime priority:
Welcome to the Beaglebone PRU library for real-time controls!
NOTE: if you get a seg fault, make sure the jppprugpio device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo jppprugpio > /sys/devices/bone_capemgr.9/slots
Also do this:
echo bone_eqep1 > $SLOTS
prussdrv_init() (returned 0)
prussdrv_open (returned 0)
prussdrv_pruintc_init (returned 0)
pruss_map_prumem (returned 0)
pru0 data memory addr: 0xb6ced000
 ctrladdr_CPU_wants_data : 0xb6ced000
 ctrladdr_PRU_data_ready : 0xb6ced004
 ctrladdr_CPU_new_sched  : 0xb6ced008
 ctrladdr_PRU_ack_sched  : 0xb6ced00c
 addr_cpu_data_buf : 0xb6ced010
 addr_pru_data_buf : 0xb6ced410
 addr_cpu_cmd_buf  : 0xb6ced810
 addr_pru_cmd_buf  : 0xb6ceda10
executing bin file: ./jpp-pru-lib.bin
NOTE: a lot of stuff assumes PRU0 in this lib, sry.
prussdrv_exec_program returned 0
Waiting 200ms to let PRU fill its internal buffer...done.
0x0	0x5	0x23	0x25
1347 1341 1346 1338 1342 1340 1348 1340 1392 1351 1337 1342 1334 1343 1347 1344 1358 1332 1342 1347 1350 1337 1349 1339 1356 1347 1350 1324 1336 1342 1346 1346 
1344 1354 1352 1343 1337 1337 1353 1348 1329 1348 1343 1358 1358 1360 1352 1347 1358 1330 1348 1334 1356 1350 1348 1347 1346 1343 1356 1335 1347 1352 1331 1348 
1327 1352 1355 1361 1347 1344 1336 1356 1345 1334 1335 1337 1340 1376 1352 1346 1361 1355 1350 1344 1328 1345 1348 1340 1359 1376 1348 1341 1360 1345 1350 1347 
1307 1361 1347 1348 1334 1367 1328 1339 1343 1342 1335 1346 1347 1347 1339 1356 1359 1357 1349 1350 1350 1343 1352 1344 1347 1346 1352 1346 1352 1350 1344 1347 
1353 1344 1339 1349 1343 1336 1327 1348 1351 1347 1351 1356 1341 1354 1344 1355 1343 1360 1346 1342 1347 1358 1338 1352 1347 1348 1345 1358 1347 1359 1358 1335 
1330 1350 1327 1354 1351 1347 1346 1331 1342 1334 1350 1354 1338 1353 1354 1368 1350 1352 1359 1356 1328 1336 1344 1360 1350 1352 1342 1352 1353 1363 1356 1342 
1340 1348 1344 1347 1359 1350 1345 1359 1347 1350 1356 1347 1336 1340 1344 1342 1359 1346 1337 1357 1350 1359 1347 1350 1341 1344 1351 1352 1343 1353 1343 1351 
1335 1333 1344 1351 1344 1349 1348 1341 1354 1360 1348 1347 1354 1369 1350 1351 1343 1342 1327 1352 1350 1344 1359 1360 1347 1332 1348 1344 1340 1350 1341 1345 
1347 1341 1344 1342 1337 1335 1352 1331 1352 1355 1361 1347 1365 1349 1359 1350 1335 1345 1347 1329 1340 1347 1332 1340 1360 1347 1358 1351 1352 1356 1328 1345 
1342 1350 1351 1359 1344 1353 1358 1356 1333 1359 1360 1349 1337 1344 1342 1360 1347 1349 1347 1342 1355 1366 1356 1339 1351 1351 1339 1356 1353 1352 1374 1348 
1342 1352 1335 1347 1343 1331 1345 1355 1331 1355 1350 1344 1350 1346 1345 1337 1331 1339 1335 1342 1355 1351 1348 1351 1351 1339 1350 1345 1352 1351 1360 1356 
1339 1356 1336 1339 1333 1339 1343 1359 1348 1348 1331 1327 1374 1356 1348 1342 1344 1339 1368 1353 1339 1362 1348 1362 1351 1358 1335 1341 1344 1345 1345 1339 
1352 1348 1355 1348 1344 1340 1334 1351 1347 1354 1359 1349 1343 1326 1340 1343 1340 1351 1348 1336 1356 1352 1347 1353 1340 1343 1341 1339 1342 1360 1342 1350 
1361 1331 1343 1337 1342 1331 1351 1351 1348 1343 1343 1345 1372 1353 1347 1339 1337 1342 1346 1353 1351 1331 1351 1343 1336 1355 1340 1356 1344 1336 1350 1341 
1339 1343 1344 1343 1340 1336 1356 1345 1343 1345 1347 1359 1351 1351 1347 1352 1346 1343 1335 1343 1336 1345 1340 1331 1345 1329 1360 1347 1351 1356 1344 1351 
1351 1348 1345 1358 1350 1353 1359 1347 1351 1342 1334 1347 1347 1347 1351 1342 1339 1352 1357 1362 1343 1359 1338 1354 1343 1335 1343 1348 1346 1352 1344 1355 
1343 1356 1376 1343 1343 1335 1358 1343 1336 1340 1344 1350 1361 1348 1347 1343 1351 1355 1347 1353 1336 1360 1342 1355 1352 1343 1358 1353 1347 1348 1357 1342 
1343 1348 1340 1357 1341 1340 1345 1336 1335 1339 1346 1353 1347 1346 1336 1359 1358 1331 1341 1336 1350 1350 1341 1347 1347 1343 1334 1341 1336 1355 1348 1347 
1341 1342 1329 1352 1335 1348 1358 1376 1345 1352 1353 1341 1342 1351 1341 1341 1352 1336 1359 1339 1351 1359 1343 1352 1354 1331 1343 1343 1347 1350 1342 1348 
1348 1345 1360 1335 1356 1340 1351 1355 1357 1344 1331 1347 1360 1335 1347 1356 1347 1350 1351 1352 1356 1356 1358 1358 1363 1343 1341 1335 1356 1329 1359 1372 

Ave adc: 1346.962500
Making nicer data file...
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# # 1A:
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ./run
I'm in: 
/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests
Resetting eqep...
==========================
building PRU library...
Compiling .c file jpp-pru-lib.c into .o file jpp-pru-lib.o
Using pasm to assemble .p file jpp-pru-lib.p into .bin file jpp-pru-lib.bin...


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 307 word(s)

Building test .c file test5-calibrate-sensors.c to make test5-calibrate-sensors
test5-calibrate-sensors.c: In function ‘main’:
test5-calibrate-sensors.c:178:20: warning: unused variable ‘gpio_cmd’ [-Wunused-variable]
test5-calibrate-sensors.c:139:16: warning: unused variable ‘cmds’ [-Wunused-variable]
Running test5-calibrate-sensors
... at realtime priority:
Welcome to the Beaglebone PRU library for real-time controls!
NOTE: if you get a seg fault, make sure the jppprugpio device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo jppprugpio > /sys/devices/bone_capemgr.9/slots
Also do this:
echo bone_eqep1 > $SLOTS
prussdrv_init() (returned 0)
prussdrv_open (returned 0)
prussdrv_pruintc_init (returned 0)
pruss_map_prumem (returned 0)
pru0 data memory addr: 0xb6d9c000
 ctrladdr_CPU_wants_data : 0xb6d9c000
 ctrladdr_PRU_data_ready : 0xb6d9c004
 ctrladdr_CPU_new_sched  : 0xb6d9c008
 ctrladdr_PRU_ack_sched  : 0xb6d9c00c
 addr_cpu_data_buf : 0xb6d9c010
 addr_pru_data_buf : 0xb6d9c410
 addr_cpu_cmd_buf  : 0xb6d9c810
 addr_pru_cmd_buf  : 0xb6d9ca10
executing bin file: ./jpp-pru-lib.bin
NOTE: a lot of stuff assumes PRU0 in this lib, sry.
prussdrv_exec_program returned 0
Waiting 200ms to let PRU fill its internal buffer...done.
0x0	0x5	0x23	0x25
1182 1200 1192 1208 1196 1196 1216 1191 1201 1199 1197 1187 1179 1191 1200 1186 1201 1209 1207 1209 1189 1196 1201 1191 1190 1183 1190 1187 1191 1187 1201 1217 
1208 1196 1206 1208 1199 1208 1201 1190 1192 1189 1203 1193 1185 1203 1185 1201 1197 1191 1208 1198 1183 1195 1182 1192 1200 1200 1217 1190 1216 1198 1203 1198 
1181 1208 1187 1188 1192 1195 1193 1184 1200 1199 1196 1202 1232 1198 1206 1196 1199 1175 1202 1212 1206 1172 1199 1198 1208 1207 1218 1187 1191 1201 1208 1208 
1200 1195 1191 1216 1209 1209 1192 1199 1193 1203 1187 1201 1179 1198 1204 1198 1209 1189 1192 1190 1199 1211 1203 1216 1182 1201 1196 1195 1211 1202 1188 1200 
1216 1200 1199 1196 1204 1191 1183 1199 1208 1200 1206 1200 1179 1184 1208 1200 1208 1200 1198 1208 1200 1199 1199 1190 1198 1201 1204 1198 1191 1206 1196 1200 
1212 1204 1203 1203 1195 1181 1199 1199 1200 1204 1198 1175 1203 1203 1214 1198 1193 1191 1191 1208 1193 1192 1190 1208 1208 1201 1210 1196 1191 1207 1198 1192 
1206 1189 1208 1207 1200 1195 1192 1217 1200 1209 1193 1199 1195 1204 1203 1208 1186 1202 1182 1196 1207 1185 1191 1199 1210 1183 1224 1189 1202 1208 1222 1183 
1191 1199 1207 1191 1200 1190 1183 1197 1191 1195 1196 1196 1188 1207 1205 1200 1188 1203 1211 1193 1201 1204 1200 1198 1204 1199 1184 1185 1197 1207 1196 1193 
1191 1200 1212 1201 1192 1192 1186 1203 1199 1201 1210 1199 1185 1191 1195 1196 1167 1188 1212 1200 1203 1207 1216 1198 1182 1206 1200 1194 1191 1196 1200 1192 
1191 1208 1202 1198 1216 1210 1200 1196 1206 1196 1200 1203 1216 1189 1194 1199 1199 1201 1199 1203 1193 1216 1199 1186 1197 1187 1191 1196 1192 1183 1201 1196 
1194 1184 1187 1190 1204 1222 1208 1200 1188 1190 1195 1204 1218 1192 1183 1191 1195 1211 1205 1185 1183 1205 1186 1183 1199 1202 1204 1198 1193 1200 1192 1184 
1198 1191 1197 1224 1199 1191 1193 1203 1151 1185 1211 1183 1200 1183 1195 1182 1197 1206 1196 1197 1214 1196 1196 1202 1202 1191 1200 1200 1200 1192 1185 1200 
1202 1197 1203 1203 1183 1200 1200 1184 1191 1200 1207 1198 1189 1203 1201 1203 1207 1197 1199 1200 1209 1174 1199 1180 1191 1203 1193 1206 1218 1191 1216 1191 
1207 1173 1181 1199 1216 1207 1182 1188 1212 1198 1220 1192 1191 1208 1204 1208 1190 1201 1201 1200 1202 1198 1194 1207 1189 1198 1199 1190 1188 1200 1200 1204 
1199 1191 1209 1196 1205 1191 1208 1204 1216 1200 1208 1219 1212 1210 1206 1200 1206 1219 1201 1209 1201 1204 1188 1191 1200 1183 1196 1211 1182 1191 1191 1208 
1193 1200 1198 1200 1194 1224 1204 1192 1185 1203 1203 1192 1212 1191 1203 1199 1192 1183 1203 1204 1200 1192 1187 1203 1196 1199 1208 1192 1183 1206 1208 1192 
1201 1191 1207 1191 1196 1198 1194 1182 1209 1206 1201 1192 1188 1199 1200 1209 1206 1207 1199 1185 1201 1211 1191 1195 1199 1206 1196 1187 1216 1195 1201 1194 
1191 1193 1192 1203 1190 1172 1201 1212 1201 1207 1208 1217 1151 1196 1188 1206 1195 1191 1192 1182 1195 1191 1197 1191 1191 1211 1191 1192 1184 1187 1196 1191 
1200 1183 1183 1207 1185 1198 1179 1195 1183 1185 1203 1206 1200 1181 1199 1196 1203 1196 1203 1200 1208 1197 1158 1202 1209 1187 1191 1192 1211 1199 1198 1176 
1211 1199 1197 1196 1208 1201 1216 1191 1197 1196 1207 1192 1191 1198 1208 1203 1185 1199 1190 1207 1193 1199 1190 1216 1186 1204 1191 1200 1198 1191 1190 1220 

Ave adc: 1197.746875
Making nicer data file...
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# # -1A:
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# # Um, not safe. SKip.
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# # 0A:
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# ./run
I'm in: 
/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests
Resetting eqep...
==========================
building PRU library...
Compiling .c file jpp-pru-lib.c into .o file jpp-pru-lib.o
Using pasm to assemble .p file jpp-pru-lib.p into .bin file jpp-pru-lib.bin...


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 307 word(s)

Building test .c file test5-calibrate-sensors.c to make test5-calibrate-sensors
test5-calibrate-sensors.c: In function ‘main’:
test5-calibrate-sensors.c:178:20: warning: unused variable ‘gpio_cmd’ [-Wunused-variable]
test5-calibrate-sensors.c:139:16: warning: unused variable ‘cmds’ [-Wunused-variable]
Running test5-calibrate-sensors
... at realtime priority:
Welcome to the Beaglebone PRU library for real-time controls!
NOTE: if you get a seg fault, make sure the jppprugpio device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo jppprugpio > /sys/devices/bone_capemgr.9/slots
Also do this:
echo bone_eqep1 > $SLOTS
prussdrv_init() (returned 0)
prussdrv_open (returned 0)
prussdrv_pruintc_init (returned 0)
pruss_map_prumem (returned 0)
pru0 data memory addr: 0xb6d13000
 ctrladdr_CPU_wants_data : 0xb6d13000
 ctrladdr_PRU_data_ready : 0xb6d13004
 ctrladdr_CPU_new_sched  : 0xb6d13008
 ctrladdr_PRU_ack_sched  : 0xb6d1300c
 addr_cpu_data_buf : 0xb6d13010
 addr_pru_data_buf : 0xb6d13410
 addr_cpu_cmd_buf  : 0xb6d13810
 addr_pru_cmd_buf  : 0xb6d13a10
executing bin file: ./jpp-pru-lib.bin
NOTE: a lot of stuff assumes PRU0 in this lib, sry.
prussdrv_exec_program returned 0
Waiting 200ms to let PRU fill its internal buffer...done.
0x0	0x5	0x23	0x25
1951 1945 1927 1967 1939 1939 1935 1944 1959 1947 1950 1939 1968 1937 1942 1944 1943 1948 1948 1917 1950 1945 1942 1959 1950 1950 1923 1945 1936 1937 1953 1936 
1950 1950 1938 1955 1937 1947 1942 1955 1955 1959 1934 1949 1932 1936 1939 1953 1943 1922 1951 1943 1955 1945 1943 1955 1927 1951 1944 1934 1941 1951 1959 1944 
1955 1935 1968 1944 1954 1932 1936 1955 1945 1934 1945 1944 1945 1964 1968 1947 1945 1950 1948 1959 1935 1921 1948 1927 1932 1944 1944 1955 1954 1950 1942 1950 
1936 1950 1952 1944 1955 1934 1942 1935 1943 1939 1947 1931 1952 1942 1943 1960 1939 1948 1923 1940 1939 1944 1943 1944 1940 1968 1959 1932 1944 1937 1951 1939 
1951 1955 1948 1947 1940 1944 1952 1953 1936 1940 1945 1960 1944 1947 1960 1949 1951 1953 1948 1939 1954 1918 1945 1952 1950 1935 1939 1959 1950 1942 1947 1959 
1938 1919 1953 1937 1951 1948 1984 1927 1944 1937 1936 1958 1939 1947 1929 1944 1945 1940 1947 1947 1945 1945 1945 1951 1928 1939 1940 1948 1935 1952 1947 1944 
1932 1948 1940 1953 1946 1943 1939 1948 1953 1945 1952 1959 1959 1944 1944 1932 1964 1951 1966 1939 1948 1943 1940 1933 1959 1949 1952 1947 1935 1941 1951 1936 
1946 1946 1934 1935 1953 1949 1939 1936 1939 1947 1949 1950 1949 1953 1930 1949 1936 1948 1951 1963 1932 1943 1939 1949 1936 1949 1951 1936 1951 1937 1954 1945 
1943 1950 1946 1929 1948 1956 1953 1943 1945 1964 1934 1939 1961 1940 1950 1934 1955 1959 1935 1953 1944 1944 1951 1951 1943 1947 1944 1945 1960 1939 1953 1946 
1943 1939 1935 1944 1952 1944 1958 1932 1948 1951 1968 1945 1923 1953 1944 1948 1927 1971 1935 1949 1955 1943 1944 1950 1927 1950 1943 1942 1947 1952 1929 1944 
1953 1942 1947 1935 1939 1937 1952 1942 1952 1939 1948 1948 1940 1953 1942 1969 1947 1942 1943 1954 1944 1951 1931 1940 1964 1943 1943 1944 1944 1931 1947 1944 
1952 1939 1959 1936 1945 1984 1957 1951 1948 1951 1948 1942 1936 1943 1955 1950 1939 1939 1944 1951 1951 1934 1942 1950 1936 1943 1941 1935 1947 1936 1949 1945 
1968 1935 1929 1948 1943 1927 1959 1935 1936 1943 1944 1955 1931 1951 1939 1949 1943 1958 1948 1941 1959 1939 1942 1927 1937 1943 1926 1935 1955 1949 1930 1951 
1927 1942 1943 1952 1951 1950 1942 1939 1936 1950 1932 1953 1927 1950 1948 1928 1943 1949 1943 1951 1940 1948 1919 1957 1919 1926 1945 1955 1955 1939 1947 1950 
1956 1943 1934 1940 1932 1949 1948 1948 1927 1944 1951 1938 1937 1955 1950 1948 1948 1944 1948 1947 1931 1963 1947 1952 1958 1943 1949 1947 1943 1940 1934 1964 
1953 1935 1943 1942 1943 1943 1949 1968 1937 1936 1943 1945 1923 1947 1976 1939 1948 1939 1950 1919 1943 1936 1947 1945 1960 1969 1935 1933 1936 1939 1946 1923 
1936 1958 1941 1951 1921 1958 1935 1929 1931 1952 1955 1950 1946 1945 1950 1955 1946 1948 1948 1944 1943 1960 1950 1948 1939 1948 1938 1950 1937 1949 1950 1936 
1942 1935 1933 1944 1948 1964 1933 1953 1944 1935 1943 1929 1944 1947 1942 1951 1942 1951 1929 1947 1950 1956 1948 1950 1930 1947 1953 1951 1954 1937 1944 1939 
1958 1927 1956 1948 1947 1932 1944 1953 1937 1947 1950 1948 1945 1957 1949 1951 1944 1923 1955 1919 1927 1937 1950 1946 1931 1943 1950 1957 1937 1951 1932 1945 
1948 1937 1944 1945 1950 1932 1947 1928 1935 1943 1937 1968 1936 1943 1937 1943 1950 1944 1932 1948 1944 1942 1936 1946 1945 1943 1935 1949 1923 1942 1937 1945 

Ave adc: 1944.653125
Making nicer data file...
root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/03-pru-ctrls-lib-tests# 


















//////////
Also, if you set an int to a wrapped unsigned int, it seems to convert to negative correctly:

root@beaglebone:/home/debian/BB_PRU_stuff/Integration-test/02-gpio-plays-songs# ./test-unsigned-to-signed-int
ui_minusone: 4294967295 -1 ffffffff
i_minusone_equals: 4294967295 -1 ffffffff
i_minusone_pointer: 4294967295 -1 ffffffff
for loop
ui_minusone: 3 3 3
i_minusone_equals: 3 3 3
i_minusone_pointer: 3 3 3
ui_minusone: 2 2 2
i_minusone_equals: 2 2 2
i_minusone_pointer: 2 2 2
ui_minusone: 1 1 1
i_minusone_equals: 1 1 1
i_minusone_pointer: 1 1 1
ui_minusone: 0 0 0
i_minusone_equals: 0 0 0
i_minusone_pointer: 0 0 0
ui_minusone: 4294967295 -1 ffffffff
i_minusone_equals: 4294967295 -1 ffffffff
i_minusone_pointer: 4294967295 -1 ffffffff
ui_minusone: 4294967294 -2 fffffffe
i_minusone_equals: 4294967294 -2 fffffffe
i_minusone_pointer: 4294967294 -2 fffffffe
ui_minusone: 4294967293 -3 fffffffd
i_minusone_equals: 4294967293 -3 fffffffd
i_minusone_pointer: 4294967293 -3 fffffffd
ui_minusone: 4294967292 -4 fffffffc
i_minusone_equals: 4294967292 -4 fffffffc
i_minusone_pointer: 4294967292 -4 fffffffc
ui_minusone: 4294967291 -5 fffffffb
i_minusone_equals: 4294967291 -5 fffffffb
i_minusone_pointer: 4294967291 -5 fffffffb
ui_minusone: 4294967290 -6 fffffffa
i_minusone_equals: 4294967290 -6 fffffffa
i_minusone_pointer: 4294967290 -6 fffffffa

yay twos-complement.















