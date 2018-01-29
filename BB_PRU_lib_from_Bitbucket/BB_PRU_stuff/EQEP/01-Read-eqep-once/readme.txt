PRU reads the eqep once, C code retrieves & pritns it

aug 23, 2016

note: should load the following dev tree overlays beforehand:

root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/01-Read-eqep-once# cat $SLOTS
 0: 54:PF--- 
 1: 55:PF--- 
 2: 56:PF--- 
 3: 57:PF--- 
 4: ff:P-O-L Bone-LT-eMMC-2G,00A0,Texas Instrument,BB-BONE-EMMC-2G
 5: ff:P-O-- Bone-Black-HDMI,00A0,Texas Instrument,BB-BONELT-HDMI
 6: ff:P-O-- Bone-Black-HDMIN,00A0,Texas Instrument,BB-BONELT-HDMIN
 8: ff:P-O-L Override Board Name,00A0,Override Manuf,BB-ADC
 9: ff:P-O-L Override Board Name,00A0,Override Manuf,bone_pwm_P8_34
10: ff:P-O-L Override Board Name,00A0,Override Manuf,am33xx_pwm
11: ff:P-O-L Override Board Name,00A0,Override Manuf,EBB-PRU-Example


Like this:

root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/01-Read-eqep-once# echo "bone_eqep1" > $SLOTS
root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/01-Read-eqep-once# dmesg |  tail
[  219.793292] bone-capemgr bone_capemgr.9: slot #11: Applied #3 overlays.
[ 1104.780704] bone-capemgr bone_capemgr.9: part_number 'bone_eqep1', version 'N/A'
[ 1104.780894] bone-capemgr bone_capemgr.9: slot #12: generic override
[ 1104.781099] bone-capemgr bone_capemgr.9: bone: Using override eeprom data at slot 12
[ 1104.781151] bone-capemgr bone_capemgr.9: slot #12: 'Override Board Name,00A0,Override Manuf,bone_eqep1'
[ 1104.781551] bone-capemgr bone_capemgr.9: slot #12: Requesting part number/version based 'bone_eqep1-00A0.dtbo
[ 1104.781602] bone-capemgr bone_capemgr.9: slot #12: Requesting firmware 'bone_eqep1-00A0.dtbo' for board-name 'Override Board Name', version '00A0'
[ 1104.781666] bone-capemgr bone_capemgr.9: slot #12: dtbo 'bone_eqep1-00A0.dtbo' loaded; converting to live tree
[ 1104.782190] bone-capemgr bone_capemgr.9: slot #12: #3 overlays
[ 1104.789243] bone-capemgr bone_capemgr.9: slot #12: Applied #3 overlays.
root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/01-Read-eqep-once# cat $SLOTS
 0: 54:PF--- 
 1: 55:PF--- 
 2: 56:PF--- 
 3: 57:PF--- 
 4: ff:P-O-L Bone-LT-eMMC-2G,00A0,Texas Instrument,BB-BONE-EMMC-2G
 5: ff:P-O-- Bone-Black-HDMI,00A0,Texas Instrument,BB-BONELT-HDMI
 6: ff:P-O-- Bone-Black-HDMIN,00A0,Texas Instrument,BB-BONELT-HDMIN
 8: ff:P-O-L Override Board Name,00A0,Override Manuf,BB-ADC
 9: ff:P-O-L Override Board Name,00A0,Override Manuf,bone_pwm_P8_34
10: ff:P-O-L Override Board Name,00A0,Override Manuf,am33xx_pwm
11: ff:P-O-L Override Board Name,00A0,Override Manuf,EBB-PRU-Example
12: ff:P-O-L Override Board Name,00A0,Override Manuf,bone_eqep1





Important: eqep1 doesnt' conflict with the PRU:

The PRU uses these pins:

root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/01-Read-eqep-once# grep -i 0x /home/debian/exploringBB/chp13/overlay/EBB-PRU-Example.dts 
               0x070 0x07  // P9_11 MODE7 | OUTPUT | GPIO pull-down
               0x074 0x27  // P9_13 MODE7 | INPUT | GPIO pull-down
               0x1a4 0x05  // P9_27 pr1_pru0_pru_r30_5, MODE5 | OUTPUT | PRU
               0x19c 0x26  // P9_28 pr1_pru0_pru_r31_3, MODE6 | INPUT | PRU

The EQEPs use these pins: EQEP1 seems safest:

root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/01-Read-eqep-once# grep -i 0x /home/debian/BB_PRU_stuff/EQEP/beaglebot/encoders/dts/bone_eqep1.dts 
                        0x0D8 0x22  /* P8_31 = GPIO0_10 = EQEP1_index, MODE2 */
                        0x0DC 0x22  /* P8_32 = GPIO0_11 = EQEP1_strobe, MODE2 */
                        0x0D4 0x32  /* P8_33 = GPIO0_9 = EQEP1B_in, MODE2 */
                        0x0D0 0x32  /* P8_35 = GPIO0_8 = EQEP1A_in, MODE2 */


The other eqeps do conflict with the PRU, I think, according to Derek's table. However, it doesnt'  look like they conflict here. Maybe there are certain PRU reg 30/31 pins that would conflict. Anyway, let's stick wtih 


root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/01-Read-eqep-once# grep -i 0x /home/debian/BB_PRU_stuff/EQEP/beaglebot/encoders/dts/bone_eqep0.dts 
                        0x1A8 0x21  /* P9_41 = GPIO3_20 = EQEP0_index, MODE1 */        
                        0x1AC 0x21  /* P9_25 = GPIO3_21 = EQEP0_strobe, MODE1 */   
                        0x1A0 0x31  /* P9_42 = GPIO3_18 = EQEP0A_in, MODE1 */       
                        0x1A4 0x31  /* P9_27 = GPIO3_19 = EQEP0B_in, MODE1 */       


root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/01-Read-eqep-once# grep -i 0x /home/debian/BB_PRU_stuff/EQEP/beaglebot/encoders/dts/bone_eqep2.dts 
                        0x0B8 0x23  /* P8_39 = GPIO2_12 = EQEP2_index, MODE3 */
                        0x0BC 0x23  /* P8_40 = GPIO2_13 = EQEP2_strobe, MODE3 */
                        0x0B0 0x33  /* P8_41 = GPIO2_10 = EQEP2A_in, MODE3 */
                        0x0B4 0x33  /* P8_42 = GPIO2_11 = EQEP2B_in, MODE3 */

root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/01-Read-eqep-once# grep -i 0x /home/debian/BB_PRU_stuff/EQEP/beaglebot/encoders/dts/bone_eqep2b.dts 
                               0x038 0x24  /* P8_16 = GPIO1_14 = EQEP2_index, MODE4 */
                               0x03C 0x24  /* P8_15 = GPIO1_15 = EQEP2_strobe, MODE4 */
                               0x030 0x34  /* P8_12 = GPIO1_12 = EQEP2A_in, MODE4 */
                               0x034 0x34  /* P8_11 = GPIO1_13 = EQEP2B_in, MODE4 */


so we'll use eqep1, so gotta  plug the sensor into these pins:

 P8_33 = GPIO0_9 = EQEP1B_in, MODE2 
 P8_35 = GPIO0_8 = EQEP1A_in, MODE2 



## Sanity check  - verify sysfs works


https://github.com/Teknoman117/beaglebot/tree/master/encoders


/sys/devices/ocp.*/{epwmss_addr}.epwmss/{eqep_addr}.eqep/

For eQEP0, the epwmss address is 48300000 and the eqep address is 48300180

--> For eQEP1, the epwmss address is 48302000 and the eqep address is 48302180

For eQEP2, the epwmss address is 48304000 and the eqep address is 48304180

It is important to note that only eQEP1 and eQEP2 are available on the Beaglebone, and that all three are available on the Beaglebo



root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/01-Read-eqep-once# cd /sys/devices/ocp.3/48302000.epwmss/48302180.eqep/
root@beaglebone:/sys/devices/ocp.3/48302000.epwmss/48302180.eqep# ls
driver	enabled  modalias  mode  period  position  power  subsystem  uevent
root@beaglebone:/sys/devices/ocp.3/48302000.epwmss/48302180.eqep# ls -l
total 0
lrwxrwxrwx 1 root root    0 Apr 23 20:48 driver -> ../../../../bus/platform/drivers/eqep
-rw-r--r-- 1 root root 4096 Apr 23 20:48 enabled
-r--r--r-- 1 root root 4096 Apr 23 20:48 modalias
-rw-r--r-- 1 root root 4096 Apr 23 20:48 mode
-rw-r--r-- 1 root root 4096 Apr 23 20:48 period
-rw-r--r-- 1 root root 4096 Apr 23 20:48 position
drwxr-xr-x 2 root root    0 Apr 23 20:48 power
lrwxrwxrwx 1 root root    0 Apr 23 20:38 subsystem -> ../../../../bus/platform
-rw-r--r-- 1 root root 4096 Apr 23 20:38 uevent
root@beaglebone:/sys/devices/ocp.3/48302000.epwmss/48302180.eqep# cat position
1632


( move the encode a little )

root@beaglebone:/sys/devices/ocp.3/48302000.epwmss/48302180.eqep# cat position
1686


Okay, the sysfs works. Now to figure out what's up wtih the PRU code.

Ah, gotta make sure you're addressing the correct eqep. 

    #define ADDR_OF_EQEP1         0x48302180 
