This program demonstrates how the PRU delivers timestamped ADC samples to the CPU.

- Every 5ms, the PRU reads the ADC and writes the sample number (just
  an increasing int), the cycle counter when the ADC was sampled, and
  the ADC value itself into the PRU0 data ram in a "private" location.

- Every 20ms (roughly), the CPU sets the "CPU wants" bit in the PRU
  data ram, indicating to the PRU that the CPU wants the PRU to
  deliver an ADC sample from its internal running buffer of samples.

- The PRU copies a sample from its running buffer into an addr that
  the CPU knows to look for, and then sets the "data ready" bit in the
  1st int of the PRU data ram (the "control register" I call it).

- The CPU can now read its buffer, knowing that the PRU won't mess it up.

- The PRU continues to log ADC data to its private buffer, some other
  address in teh PRU data ram.

This program shows how the CPU can retrieve ADC sampled from the PRU
that have been sampled at very precise times. Even if the CPU runs a
slow controls algorithm, the ADC values it receives will have been
sampled at integer multiples of the 5ms timestep:




root@beaglebone:/home/debian/BB_PRU_stuff/ADC/05-CPU-gets-ADC-samples# ./run
I'm in: 
/home/debian/BB_PRU_stuff/ADC/05-CPU-gets-ADC-samples
Building .bin file cpu-reads-adc.p


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 120 word(s)

Building .c file cpu-reads-adc.c to make cpu-reads-adc
(Careful - does your .c load the correct .p / .bin?)
Running cpu-reads-adc
Hey, if you get a seg fault, make sure the EBB-PRU-Example device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo EBB-PRU-Example > /sys/devices/bone_capemgr.9/slots
executing bin file: ./cpu-reads-adc.bin
Waiting for "Data ready" bit...
Got it!
ctrl register: 2
sample # (ctsly updated): 2
cycle #  (ctsly updated): 1000019 (5.000095 ms)
adc val  (ctsly updated): 2044
sample # : 2
cycle #  : 1000019 (5.000095 ms)
adc val  : 2044
Waiting for "Data ready" bit...
Got it!
ctrl register: 2
sample # (ctsly updated): 7
cycle #  (ctsly updated): 6000063 (30.000315 ms)
adc val  (ctsly updated): 2048
sample # : 7
cycle #  : 6000063 (30.000315 ms)
adc val  : 2048
Waiting for "Data ready" bit...
Got it!
ctrl register: 2
sample # (ctsly updated): 12
cycle #  (ctsly updated): 11000107 (55.000535 ms)
adc val  (ctsly updated): 2043
sample # : 12
cycle #  : 11000107 (55.000535 ms)
adc val  : 2043
Waiting for "Data ready" bit...
Got it!
ctrl register: 2
sample # (ctsly updated): 17
cycle #  (ctsly updated): 16000151 (80.000755 ms)
adc val  (ctsly updated): 2046
sample # : 17
cycle #  : 16000151 (80.000755 ms)
adc val  : 2046
Waiting for "Data ready" bit...
Got it!
ctrl register: 2
sample # (ctsly updated): 22
cycle #  (ctsly updated): 21000195 (105.000975 ms)
adc val  (ctsly updated): 2044
sample # : 22
cycle #  : 21000195 (105.000975 ms)
adc val  : 2044
Shutting down.
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/05-CPU-gets-ADC-samples# 




The sampled labeled "(ctsly updated)" are the PRU's internal buffer of ADC samples (just 1 sample at the moment).




The 1st sample occurs at t=0, the 2nd sample at t=5ms, etc. Therefore the times (in ms) when you'd expect samples 7, 12, 17, and 22 are:

root@beaglebone:/home/debian/BB_PRU_stuff/ADC/05-CPU-gets-ADC-samples# python
Python 2.7.3 (default, Mar 14 2014, 17:55:54) 
[GCC 4.6.3] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> (2-1)*5
5
>>> (2-1.0)*5
5.0
>>> (7-1.0)*5
30.0
>>> (12-1.0)*5
55.0
>>> (17-1.0)*5
80.0
>>> (22-1.0)*5
105.0
>>> 




Now to make it work with a buffer of samples.


- The samples live in the PRU0 data ram. 
- There are 10 samples in a 'buffer'.
- There is a simple locking mechanism to prevent the CPU from reading samples mid-PRU-write.

- There are 2 buffers, so that the PRU can be populating one while the
  CPU is copying samples out of the other.

- When the CPU reads a buffer, it reads all the samples out of the buffer.
- Each sample is 2 32-bit uints: 
  - the PRU cycle counter right before the sample was taken
  - the ADC value (0-4095) representing 0-1.8V at ADC channel 0


PRU is always filling bakbuf, and when he sees that CPU wants info, he
copies it into buf and says it's ready.

- PRU code:
  - Spin until a sample-time. (Every 5ms)
  - Start an ADC sample.
  - Spin until ADC sample completes.
  - Copy into backbuf.
  - If "CPU wants" bit set and "Data delivered" bit not set,
    - Copy backbuf into buf.
    - Set "Data delivered" bit.

- CPU code:
  - Spin until a read-time. (Every 20ms)
  - Set "CPU wants" bit.
  - Spin until "Data ready" bit.
  - Copy buf into local array.
  - Clear "CPU wants" bit.
  - Print out samples.


Old idea: each dev has a "wants" and a "using" bit. Too complicated.

- CPU code:
  - 5 times, at 20ms apart:
    - Set "CPU wants" bit.
    - Read "PRU using" bit until it reads "not using". 
    - Now CPU has sole access to buf.
    - Copy all 10 samples out of the buf to a local array.
    - Clear "CPU wants" bit.

- PRU code:
  - Spin until a sample time.
  - Start an ADC sample.
  - Spin until ADC sample completes.
  - Copy into backbuf.
  - Set "PRU wants" bit.
  - Read "CPU using" bit until it 
  - If "CPU wants" bit is set, can't copy to buf. Set "dirty" bit on buf0. Return to "spin until sample time".
  - 
  

