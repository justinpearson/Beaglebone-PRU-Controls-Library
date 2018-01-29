## How to use devmem2

addr of pru0 data ram:  0x4a300000

read 4 bytes from addr 0 of pru0 data ram:

root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300000
/dev/mem opened.
Memory mapped at address 0xb6feb000.
Value at address 0x4A300000 (0xb6feb000): 0x0

go 1 over, that's 1 byte over (not 4 bytes):

root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300001
/dev/mem opened.
Memory mapped at address 0xb6fe0000.
Value at address 0x4A300001 (0xb6fe0001): 0x11000000
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300002
/dev/mem opened.
Memory mapped at address 0xb6fad000.
Value at address 0x4A300002 (0xb6fad002): 0x11110000
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300003
/dev/mem opened.
Memory mapped at address 0xb6fa9000.
Value at address 0x4A300003 (0xb6fa9003): 0x11111100
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300004
/dev/mem opened.
Memory mapped at address 0xb6f59000.
Value at address 0x4A300004 (0xb6f59004): 0x11111111


Suppose addr 0x100 contains the byte 0x11. Suppose Going up from 0x100, the data contains this sequence of bytes:

addr: 0x  100 101 102 103 104 105
byte: 0x  11  10  00  00  00  0a
dec : 0d  17  16  00  00  00  10
Here's how that would look in devmem2:

root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300100
/dev/mem opened.
Memory mapped at address 0xb6fb0000.
Value at address 0x4A300100 (0xb6fb0100): 0x111
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300101
/dev/mem opened.
Memory mapped at address 0xb6f82000.
Value at address 0x4A300101 (0xb6f82101): 0x1
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300102
/dev/mem opened.
Memory mapped at address 0xb6f13000.
Value at address 0x4A300102 (0xb6f13102): 0xA000000
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300103
/dev/mem opened.
Memory mapped at address 0xb6f51000.
Value at address 0x4A300103 (0xb6f51103): 0xA0000
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300104
/dev/mem opened.
Memory mapped at address 0xb6f1d000.
Value at address 0x4A300104 (0xb6f1d104): 0xA00
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300105
/dev/mem opened.
Memory mapped at address 0xb6fee000.
Value at address 0x4A300105 (0xb6fee105): 0xA



write a 3 at addr 0 in teh pru0 data ram:



root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300000 w 0x00000003
/dev/mem opened.
Memory mapped at address 0xb6f73000.
Value at address 0x4A300000 (0xb6f73000): 0x0
Written 0x3; readback 0x3

write a 1 at addr 0 in teh pru0 data ram:

root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300000 w 0x00000001
/dev/mem opened.
Memory mapped at address 0xb6f05000.
Value at address 0x4A300000 (0xb6f05000): 0x3
Written 0x1; readback 0x1


## Misc other notes

### Set up date & time

    cp /usr/share/zoneinfo/America/Los_Angeles /etc/localtime

    $ date -s "4 OCT 2016 11:43:00"

### Access files from ubuntu "host"

Since you have ssh access to the BBB, can mount its filesystem via sftp without needing any special daemon running on BBB or ubuntu host machine.

Nautilus > "connect to server" > sftp://root@10.42.0.122/home/debian > now you have a graphical file-browser window that you can use to 