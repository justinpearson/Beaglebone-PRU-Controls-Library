# get the eqep driver running on the PRU

summary: we updated the kernel from "3.8.13-bone47 apr 11 2014" to
"3.8.13-bone80 june 2016" to get the built-in eqep driver and
device-tree overlay. Looking at Nathaniel Lewis's eqep kernel module
(root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/beaglebot/encoders/patches/sources#
ls tieqep.c), it seems like the eqep registers get called when you
load the DTO. So in order to read the eqep encoder, it may just be as easy as reading a single register.








2016-08-23

How to configure the EQEP registers from the PRU? Use Nathaniel Lewis's driver:

    https://github.com/Teknoman117/beaglebot.git



## Device tree overlay

I see from

  /home/debian/BB_PRU_stuff/EQEP/beaglebot/encoders/patches/0001-tieqep-driver.patch

he patches the device tree source file

   /arch/arm/boot/dts/am33xx.dtsi

So maybe we can make a device tree overlay that has these parts. 

Where to find a base DTO file that we can use, that will be somewhat related to EQEP? Like, pwm or ecap? 

Let's see, I think andrew set this up a long time ago. His email:

"I have simply patched the device tree in the 4.1.3 distro to ROSELINE to overlay the eqepX definitions, and put a slightly modified version of hte module into the core/modules directory."


Ah, I see these in the Roseline project:

https://bitbucket.org/rose-line/qot-stack.git

we have

2016-08-23 09:57:43 [roseline@roseline-controller-2 ~/qot-stack-2016-08-12/qot-stack/thirdparty/bb.org-overlays/src/arm] 
$ ls *qep*
bone_eqep0-00A0.dts  bone_eqep1-00A0.dts  bone_eqep2-00A0.dts  bone_eqep2b-00A0.dts

Oh, but easier: Nathaniel's project

    https://github.com/Teknoman117/beaglebot.git

has the eqep device trees:

  /home/debian/BB_PRU_stuff/EQEP/beaglebot/encoders/dts:
  total used in directory 36 available 1838408
  drwxr-xr-x 3 root root 4096 Aug 23 09:42 .
  drwxr-xr-x 5 root root 4096 Aug 23 09:42 ..
  -rw-r--r-- 1 root root 2049 Aug 23 09:42 bone_eqep0.dts
  -rw-r--r-- 1 root root 1989 Aug 23 09:42 bone_eqep1.dts
  -rw-r--r-- 1 root root 2192 Aug 23 09:42 bone_eqep2b.dts
  -rw-r--r-- 1 root root 1994 Aug 23 09:42 bone_eqep2.dts
  drwxr-xr-x 2 root root 4096 Aug 23 09:42 dtbo
  -rw-r--r-- 1 root root 4473 Aug 23 09:42 README.md


So let's try compiling, copying, and loading one:

   dtc -O dtb -o bone_eqep1-00A0.dtbo -b 0 -@ bone_eqep1.dts



root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/beaglebot/encoders/dts# dtc -O dtb -o bone_eqep1-00A0.dtbo -b 0 -@ bone_eqep1.dts
root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/beaglebot/encoders/dts# ls
bone_eqep0.dts	bone_eqep1-00A0.dtbo  bone_eqep1.dts  bone_eqep2b.dts  bone_eqep2.dts  dtbo  README.md


Seemed to compile ok. Let's load it:

root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/beaglebot/encoders/dts# echo bone_eqep1 > $SLOTS
bash: echo: write error: Invalid argument
root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/beaglebot/encoders/dts# echo $SLOTS
/sys/devices/bone_capemgr.9/slots
root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/beaglebot/encoders/dts# dmesg | tail
[60664.638941] bone-capemgr bone_capemgr.9: slot #11: Applied #3 overlays.
[401618.735232] bone-capemgr bone_capemgr.9: part_number 'bone_eqep1', version 'N/A'
[401618.735419] bone-capemgr bone_capemgr.9: slot #12: generic override
[401618.735470] bone-capemgr bone_capemgr.9: bone: Using override eeprom data at slot 12
[401618.735521] bone-capemgr bone_capemgr.9: slot #12: 'Override Board Name,00A0,Override Manuf,bone_eqep1'
[401618.735803] bone-capemgr bone_capemgr.9: slot #12: Requesting part number/version based 'bone_eqep1-00A0.dtbo
[401618.735854] bone-capemgr bone_capemgr.9: slot #12: Requesting firmware 'bone_eqep1-00A0.dtbo' for board-name 'Override Board Name', version '00A0'
[401618.738418] bone-capemgr bone_capemgr.9: slot #12: dtbo 'bone_eqep1-00A0.dtbo' loaded; converting to live tree
[401618.738853] of_resolve: Could not find symbol 'eqep1'
[401618.744505] bone-capemgr bone_capemgr.9: slot #12: Failed to resolve tree

Probably because the DTO included stuff 

Hm, can't figure out how to install. Seems like I have to 


### Update kernel on BB, hopefully it'll come with eqep drivers.

Instead of figuring out how to rebuild the kernel, 
Maybe I can update the BB's kernel. I think eqep support was added in a later version:

https://groups.google.com/forum/#!msg/beagleboard/Orp3tFcNgCc/bHpmOZTuHyIJ

Well it didn't make the time deadline for "2014-04-23"..

</cough>

But if you do:

cd /opt/scripts/tools
git pull
sudo ./update_kernel.sh

It'll pull something newer, as the (TIEQEP) was added in 3.8.13-bone48 release.

https://github.com/RobertCNelson/linux-dev/commit/b7bc988c048b69f03b71c72f7c544f2348f378d0

Although if you find a bug, i expect a patch. ;) 


root@beaglebone:/home/debian/BB_PRU_stuff/EQEP# cd /opt/scripts/tools/
root@beaglebone:/opt/scripts/tools# ls
beaglebone-black-eMMC-flasher.sh  developers  eMMC  graphics  grow_partition.sh  start_cloud9.sh  update_bootloader.sh	update_initrd.sh  update_kernel.sh  wm
root@beaglebone:/opt/scripts/tools# exit
debian@beaglebone:~/BB_PRU_stuff/Timing/01-Basic-timing-test$ cd /opt/scripts/tools/
debian@beaglebone:/opt/scripts/tools$ git pull
remote: Counting objects: 3348, done.
remote: Compressing objects: 100% (964/964), done.
remote: Total 3348 (delta 2346), reused 3295 (delta 2295), pack-reused 0
Receiving objects: 100% (3348/3348), 783.27 KiB | 820 KiB/s, done.
Resolving deltas: 100% (2346/2346), completed with 15 local objects.
From https://github.com/RobertCNelson/boot-scripts
   a4d0fe2..948d395  master     -> origin/master
Updating a4d0fe2..948d395
error: Your local changes to the following files would be overwritten by merge:
       tools/beaglebone-black-eMMC-flasher.sh
Please, commit your changes or stash them before you can merge.
Aborting
debian@beaglebone:/opt/scripts/tools$ ls
beaglebone-black-eMMC-flasher.sh  developers  eMMC  graphics  grow_partition.sh  start_cloud9.sh  update_bootloader.sh  update_initrd.sh  update_kernel.sh  wm
debian@beaglebone:/opt/scripts/tools$ git status
# On branch master
# Your branch is behind 'origin/master' by 700 commits, and can be fast-forwarded.
#
# Changes not staged for commit:
#   (use "git add <file>..." to update what will be committed)
#   (use "git checkout -- <file>..." to discard changes in working directory)
#
#	modified:   beaglebone-black-eMMC-flasher.sh
#
no changes added to commit (use "git add" and/or "git commit -a")
debian@beaglebone:/opt/scripts/tools$ git diff beaglebone-black-eMMC-flasher.sh 
diff --git a/tools/beaglebone-black-eMMC-flasher.sh b/tools/beaglebone-black-eMMC-flasher.sh
index ffac7e1..b380b8f 100755
--- a/tools/beaglebone-black-eMMC-flasher.sh
+++ b/tools/beaglebone-black-eMMC-flasher.sh
@@ -168,8 +168,8 @@ repartition_drive () {
 
 partition_drive () {
        flush_cache
-       umount_p1
-       umount_p2
+       umount ${destination}p1 || true
+       umount ${destination}p2 || true
 
        flush_cache
        repartition_drive
@@ -183,13 +183,13 @@ copy_boot () {
        mkdir -p /tmp/boot/ || true
        mount ${destination}p1 /tmp/boot/ -o sync
        #Make sure the BootLoader gets copied first:
-       cp -v /boot/uboot/MLO /tmp/boot/MLO || write_failure
+       cp -v /boot/uboot/Normal/MLO /tmp/boot/MLO || write_failure
        flush_cache_mounted
 
-       cp -v /boot/uboot/u-boot.img /tmp/boot/u-boot.img || write_failure
+       cp -v /boot/uboot/Normal/u-boot.img /tmp/boot/u-boot.img || write_failure
        flush_cache_mounted
 
-       rsync -aAXv /boot/uboot/ /tmp/boot/ --exclude={MLO,u-boot.img,*bak,flash-eMMC.txt,flash-eMMC.log} || write_failure
+       rsync -aAXv /boot/uboot/ /tmp/boot/ --exclude={MLO,u-boot.img,*bak,flash-eMMC.txt,flash-eMMC.log,Normal} || write_failure
        flush_cache_mounted
 
        unset root_uuid
@@ -223,6 +223,9 @@ copy_rootfs () {
        fi
        flush_cache_mounted
 
+       ln -s ../init.d/led_aging.sh /tmp/rootfs/etc/rc2.d/S18led_aging
+       flush_cache_mounted
+
        mkdir -p /tmp/rootfs/boot/uboot/ || true
        mkdir -p /tmp/rootfs/lib/modules/`uname -r` || true
        rsync -aAXv /lib/modules/`uname -r`/* /tmp/rootfs/lib/modules/`uname -r`/ || write_failure
debian@beaglebone:/opt/scripts/tools$ git stash
Saved working directory and index state WIP on master: a4d0fe2 bb.org: flasher, just the flash file
HEAD is now at a4d0fe2 bb.org: flasher, just the flash file
debian@beaglebone:/opt/scripts/tools$ git status
# On branch master
# Your branch is behind 'origin/master' by 700 commits, and can be fast-forwarded.
#
nothing to commit (working directory clean)
debian@beaglebone:/opt/scripts/tools$ git pull
Updating a4d0fe2..948d395
Fast-forward
 3rdparty/xinput_calibrator_pointercal.sh                          |   65 ++++--
 boot/am335x_evm.sh                                                |  476 +++++++++++++++++++++++++++++++++++-------
 boot/autoconfigure_usb0.sh                                        |  201 ++++++++++++++++++
 boot/beagle_x15.sh                                                |   58 ++++++
 boot/capemgr.sh                                                   |   26 +++
 boot/generic-startup.sh                                           |   76 +++++++
 boot/generic.sh                                                   |   39 ++++
 boot/omap3_beagle.sh                                              |   65 +++---
 boot/omap5_uevm.sh                                                |   44 ++++
 desktop-defaults/jessie/lxqt/lxqt/desktop.conf                    |    2 +
 desktop-defaults/jessie/lxqt/lxqt/globalkeyshortcuts.conf         |   92 +++++++++
 desktop-defaults/jessie/lxqt/lxqt/lxqt-runner.conf                |    2 +
 desktop-defaults/jessie/lxqt/lxqt/lxqt.conf                       |    2 +
 desktop-defaults/jessie/lxqt/lxqt/notifications.conf              |    2 +
 desktop-defaults/jessie/lxqt/lxqt/panel.conf                      |   56 +++++
 desktop-defaults/jessie/lxqt/lxqt/power.conf                      |    2 +
 desktop-defaults/jessie/lxqt/lxqt/session.conf                    |    9 +
 desktop-defaults/jessie/lxqt/openbox/rc.xml                       |  798 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 desktop-defaults/jessie/lxqt/pcmanfm-qt/lxqt/settings.conf        |   69 +++++++
 desktop-defaults/jessie/reset_lxqt.sh                             |    9 +
 device/bone/A335-eeprom.dump                                      |    1 +
 device/bone/bbbw-eeprom.dump                                      |    1 +
 device/bone/bbg-eeprom.dump                                       |    1 +
 device/bone/bbgw-eeprom.dump                                      |    1 +
 device/bone/bbgw/WL1835MOD_INI_C2PC.ini                           |  103 ++++++++++
 device/bone/bbgw/generate.sh                                      |    3 +
 device/bone/bbgw/wl18xx-conf.bin                                  |  Bin 0 -> 1229 bytes
 device/bone/capes/BB-BEAGLELOGIC/beaglelogic-pru0                 |  Bin 0 -> 11160 bytes
 device/bone/capes/BB-BEAGLELOGIC/beaglelogic-pru1                 |  Bin 0 -> 12648 bytes
 device/bone/capes/BBB_Audio_Cape_RevB/asound.state                | 1311 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 device/bone/capes/cape_eeprom_check.sh                            |   45 +++-
 device/bone/eeprom_database.txt                                   |   11 +
 device/bone/m10a-eeprom.dump                                      |    1 +
 device/bone/pru-rpmsg_client_sample/am335x-pru0-fw                |  Bin 0 -> 78652 bytes
 device/bone/pru-rpmsg_client_sample/am335x-pru1-fw                |  Bin 0 -> 78644 bytes
 device/bone/show-pins.pl                                          |  257 +++++++++++++++++++++++
 device/bone/tester/eeprom-blank.sh                                |   47 +++--
 tools/update_bootloader.sh => device/bone/tester/eeprom-u-boot.sh |   22 +-
 device/bone/tester/show-eeprom.sh                                 |   41 ++++
 device/x15/X15_B1-eeprom.dump                                     |    1 +
 device/x15/eeprom/eeprom-blank.sh                                 |   33 +++
 device/x15/pru-rpmsg_client_sample/am57xx-pru1_0-fw               |  Bin 0 -> 79240 bytes
 device/x15/pru-rpmsg_client_sample/am57xx-pru1_1-fw               |  Bin 0 -> 79252 bytes
 device/x15/pru-rpmsg_client_sample/am57xx-pru2_0-fw               |  Bin 0 -> 79240 bytes
 device/x15/pru-rpmsg_client_sample/am57xx-pru2_1-fw               |  Bin 0 -> 79252 bytes
 device/x15/show-eeprom.sh                                         |   25 +++
 device/x15/test_audio_jacks.sh                                    |   24 +++
 device/x15/test_dual_eth.sh                                       |   47 +++++
 fixes/debian-2014-03-04-to-2014-03-19.sh                          |   76 -------
 fixes/debian-2014-03-19-to-2014-03-27.sh                          |   32 ---
 fixes/debian-2014-03-27-to-2014-03-31.sh                          |   38 ----
 images/beaglebg.jpg                                               |  Bin 51221 -> 448772 bytes
 mods/jessie-systemd-poweroff.diff                                 |   12 ++
 mods/node-red/node-red-0.10.10.patch                              |   39 ++++
 mods/node-red/node-red-0.11.2.patch                               |   39 ++++
 mods/node-red/node-red-0.12.5.patch                               |   39 ++++
 mods/node-red/node-red-0.13.1.patch                               |   39 ++++
 mods/node-red/node-red-0.9.1-nocolors.patch                       |   47 +++++
 mods/wheezy-systemd-poweroff.diff                                 |   22 ++
 tools/beaglebone-black-eMMC-flasher.sh                            |  202 ++++++++++--------
 tools/developers/apt-proxy.sh                                     |    2 +-
 tools/developers/nfs-rsync.sh                                     |   31 +++
 tools/developers/rcnee-testing.sh                                 |   13 ++
 tools/developers/secondary_rootfs.sh                              |  168 +++++++++++++++
 tools/developers/update_bootloader.sh                             |  375 +++++++++++++++++++++++++++++++++
 tools/{ => developers}/update_initrd.sh                           |    0
 tools/eMMC/bbb-eMMC-flasher-eewiki-12mb.sh                        |  526 +++++++++++++++++++++++++++++++++++++++++++++++
 tools/eMMC/bbb-eMMC-flasher-eewiki-ext4.sh                        |  579 +++++++++++++++++++++++++++++++++++++++++++++++++++
 tools/eMMC/beaglebone-black-make-microSD-flasher-from-eMMC.sh     |  612 +++++++++++++++++++++++++++++++++++++++++-------------
 tools/eMMC/init-eMMC-flasher-a335.sh                              |  111 ++++++++++
 tools/eMMC/init-eMMC-flasher-from-usb-media-v1-bbgw.sh            |  913 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 tools/eMMC/init-eMMC-flasher-from-usb-media-v2-bbgw.sh            |  691 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 tools/eMMC/init-eMMC-flasher-from-usb-media.sh                    |  667 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 tools/eMMC/init-eMMC-flasher-v2.sh                                |  344 +++++++++++++++++++++++++++++++
 tools/eMMC/init-eMMC-flasher-v3-bbbw.sh                           |  597 +++++++++++++++++++++++++++++++++++++++++++++++++++++
 tools/eMMC/init-eMMC-flasher-v3-bbg.sh                            |  571 +++++++++++++++++++++++++++++++++++++++++++++++++++
 tools/eMMC/init-eMMC-flasher-v3-bbgw.sh                           |  597 +++++++++++++++++++++++++++++++++++++++++++++++++++++
 tools/eMMC/init-eMMC-flasher-v3-m10a.sh                           |  571 +++++++++++++++++++++++++++++++++++++++++++++++++++
 tools/eMMC/init-eMMC-flasher-v3-x15_b1.sh                         |  563 ++++++++++++++++++++++++++++++++++++++++++++++++++
 tools/eMMC/init-eMMC-flasher-v3.sh                                |  571 +++++++++++++++++++++++++++++++++++++++++++++++++++
 tools/eMMC/mmc_resize_usbflasher_example.md                       |  227 ++++++++++++++++++++
 tools/eMMC/mmc_usbflasher_example.md                              |  143 +++++++++++++
 tools/eMMC/readme.md                                              |   48 +++++
 tools/graphics/fsl-etnaviv.sh                                     |  134 ++++++++++++
 tools/graphics/ti-omapdrm.sh                                      |  122 +----------
 tools/graphics/ti-tilcdc.sh                                       |    5 +-
 tools/grow_partition.sh                                           |   94 ++++++---
 tools/init-eMMC-flasher.sh                                        |  391 +++++++++++++++++++++++++++++++++++
 tools/non-mmc-rootfs/mv_rootfs_dev_sda.sh                         |  168 +++++++++++++++
 tools/readme.txt                                                  |    6 +
 tools/software/add_nodesource_repo.sh                             |   53 +++++
 tools/start_cloud9.sh                                             |    3 -
 tools/update_kernel.sh                                            |  553 ++++++++++++++++++++++++++++++++++++++++++++-----
 tools/wm/efl.sh                                                   |  170 +++++++++++++++
 tools/wm/kwin.sh                                                  |    3 +
 tools/wm/lxqt.sh                                                  |  204 ++++++++++++++++++
 tools/wm/maynard.sh                                               |  114 +++++++++++
 tools/wm/weston-drm.sh                                            |   11 +
 tools/wm/weston-fbdev.sh                                          |   11 +
 tools/wm/weston.sh                                                |   17 ++
 100 files changed, 14882 insertions(+), 750 deletions(-)
 create mode 100755 boot/autoconfigure_usb0.sh
 create mode 100755 boot/beagle_x15.sh
 create mode 100755 boot/capemgr.sh
 create mode 100755 boot/generic-startup.sh
 create mode 100755 boot/generic.sh
 create mode 100755 boot/omap5_uevm.sh
 create mode 100644 desktop-defaults/jessie/lxqt/lxqt/desktop.conf
 create mode 100644 desktop-defaults/jessie/lxqt/lxqt/globalkeyshortcuts.conf
 create mode 100644 desktop-defaults/jessie/lxqt/lxqt/lxqt-runner.conf
 create mode 100644 desktop-defaults/jessie/lxqt/lxqt/lxqt.conf
 create mode 100644 desktop-defaults/jessie/lxqt/lxqt/notifications.conf
 create mode 100644 desktop-defaults/jessie/lxqt/lxqt/panel.conf
 create mode 100644 desktop-defaults/jessie/lxqt/lxqt/power.conf
 create mode 100644 desktop-defaults/jessie/lxqt/lxqt/session.conf
 create mode 100644 desktop-defaults/jessie/lxqt/openbox/rc.xml
 create mode 100644 desktop-defaults/jessie/lxqt/pcmanfm-qt/lxqt/settings.conf
 create mode 100755 desktop-defaults/jessie/reset_lxqt.sh
 create mode 100644 device/bone/A335-eeprom.dump
 create mode 100644 device/bone/bbbw-eeprom.dump
 create mode 100644 device/bone/bbg-eeprom.dump
 create mode 100644 device/bone/bbgw-eeprom.dump
 create mode 100644 device/bone/bbgw/WL1835MOD_INI_C2PC.ini
 create mode 100644 device/bone/bbgw/generate.sh
 create mode 100644 device/bone/bbgw/wl18xx-conf.bin
 create mode 100644 device/bone/capes/BB-BEAGLELOGIC/beaglelogic-pru0
 create mode 100644 device/bone/capes/BB-BEAGLELOGIC/beaglelogic-pru1
 create mode 100644 device/bone/capes/BBB_Audio_Cape_RevB/asound.state
 create mode 100644 device/bone/eeprom_database.txt
 create mode 100644 device/bone/m10a-eeprom.dump
 create mode 100644 device/bone/pru-rpmsg_client_sample/am335x-pru0-fw
 create mode 100644 device/bone/pru-rpmsg_client_sample/am335x-pru1-fw
 create mode 100644 device/bone/show-pins.pl
 rename tools/update_bootloader.sh => device/bone/tester/eeprom-u-boot.sh (94%)
 create mode 100755 device/bone/tester/show-eeprom.sh
 create mode 100644 device/x15/X15_B1-eeprom.dump
 create mode 100755 device/x15/eeprom/eeprom-blank.sh
 create mode 100644 device/x15/pru-rpmsg_client_sample/am57xx-pru1_0-fw
 create mode 100644 device/x15/pru-rpmsg_client_sample/am57xx-pru1_1-fw
 create mode 100644 device/x15/pru-rpmsg_client_sample/am57xx-pru2_0-fw
 create mode 100644 device/x15/pru-rpmsg_client_sample/am57xx-pru2_1-fw
 create mode 100755 device/x15/show-eeprom.sh
 create mode 100755 device/x15/test_audio_jacks.sh
 create mode 100755 device/x15/test_dual_eth.sh
 delete mode 100755 fixes/debian-2014-03-04-to-2014-03-19.sh
 delete mode 100755 fixes/debian-2014-03-19-to-2014-03-27.sh
 delete mode 100755 fixes/debian-2014-03-27-to-2014-03-31.sh
 create mode 100644 mods/jessie-systemd-poweroff.diff
 create mode 100644 mods/node-red/node-red-0.10.10.patch
 create mode 100644 mods/node-red/node-red-0.11.2.patch
 create mode 100644 mods/node-red/node-red-0.12.5.patch
 create mode 100644 mods/node-red/node-red-0.13.1.patch
 create mode 100644 mods/node-red/node-red-0.9.1-nocolors.patch
 create mode 100644 mods/wheezy-systemd-poweroff.diff
 create mode 100755 tools/developers/nfs-rsync.sh
 create mode 100755 tools/developers/rcnee-testing.sh
 create mode 100755 tools/developers/secondary_rootfs.sh
 create mode 100755 tools/developers/update_bootloader.sh
 rename tools/{ => developers}/update_initrd.sh (100%)
 create mode 100755 tools/eMMC/bbb-eMMC-flasher-eewiki-12mb.sh
 create mode 100755 tools/eMMC/bbb-eMMC-flasher-eewiki-ext4.sh
 create mode 100755 tools/eMMC/init-eMMC-flasher-a335.sh
 create mode 100755 tools/eMMC/init-eMMC-flasher-from-usb-media-v1-bbgw.sh
 create mode 100755 tools/eMMC/init-eMMC-flasher-from-usb-media-v2-bbgw.sh
 create mode 100755 tools/eMMC/init-eMMC-flasher-from-usb-media.sh
 create mode 100755 tools/eMMC/init-eMMC-flasher-v2.sh
 create mode 100755 tools/eMMC/init-eMMC-flasher-v3-bbbw.sh
 create mode 100755 tools/eMMC/init-eMMC-flasher-v3-bbg.sh
 create mode 100755 tools/eMMC/init-eMMC-flasher-v3-bbgw.sh
 create mode 100755 tools/eMMC/init-eMMC-flasher-v3-m10a.sh
 create mode 100755 tools/eMMC/init-eMMC-flasher-v3-x15_b1.sh
 create mode 100755 tools/eMMC/init-eMMC-flasher-v3.sh
 create mode 100644 tools/eMMC/mmc_resize_usbflasher_example.md
 create mode 100644 tools/eMMC/mmc_usbflasher_example.md
 create mode 100644 tools/eMMC/readme.md
 create mode 100755 tools/graphics/fsl-etnaviv.sh
 create mode 100755 tools/init-eMMC-flasher.sh
 create mode 100755 tools/non-mmc-rootfs/mv_rootfs_dev_sda.sh
 create mode 100644 tools/readme.txt
 create mode 100755 tools/software/add_nodesource_repo.sh
 delete mode 100755 tools/start_cloud9.sh
 create mode 100755 tools/wm/efl.sh
 create mode 100755 tools/wm/kwin.sh
 create mode 100755 tools/wm/lxqt.sh
 create mode 100755 tools/wm/maynard.sh
 create mode 100755 tools/wm/weston-drm.sh
 create mode 100755 tools/wm/weston-fbdev.sh
 create mode 100755 tools/wm/weston.sh
debian@beaglebone:/opt/scripts/tools$ uname -a
Linux beaglebone 3.8.13-bone47 #1 SMP Fri Apr 11 01:36:09 UTC 2014 armv7l GNU/Linux
debian@beaglebone:/opt/scripts/tools$ sudo ./update_kernel.sh 

here we go...

Linux beaglebone 3.8.13-bone47 #1 SMP Fri Apr 11 01:36:09 UTC 2014 armv7l GNU/Linux

reboot...

debian@beaglebone:~$ uname -a
Linux beaglebone 3.8.13-bone80 #1 SMP Wed Jun 15 17:03:55 UTC 2016 armv7l GNU/Linux

good so far.

Try to load the same DTO we tried before, it loads!:

root@beaglebone:/home/debian/BB_PRU_stuff/EQEP# dmesg --clear
root@beaglebone:/home/debian/BB_PRU_stuff/EQEP# echo bone_eqep1 > $SLOTS
root@beaglebone:/home/debian/BB_PRU_stuff/EQEP# dmesg | tail
[  970.173248] bone-capemgr bone_capemgr.9: part_number 'bone_eqep1', version 'N/A'
[  970.173572] bone-capemgr bone_capemgr.9: slot #11: generic override
[  970.173621] bone-capemgr bone_capemgr.9: bone: Using override eeprom data at slot 11
[  970.173670] bone-capemgr bone_capemgr.9: slot #11: 'Override Board Name,00A0,Override Manuf,bone_eqep1'
[  970.173930] bone-capemgr bone_capemgr.9: slot #11: Requesting part number/version based 'bone_eqep1-00A0.dtbo
[  970.173978] bone-capemgr bone_capemgr.9: slot #11: Requesting firmware 'bone_eqep1-00A0.dtbo' for board-name 'Override Board Name', version '00A0'
[  970.174055] bone-capemgr bone_capemgr.9: slot #11: dtbo 'bone_eqep1-00A0.dtbo' loaded; converting to live tree
[  970.174570] bone-capemgr bone_capemgr.9: slot #11: #3 overlays
[  970.187215] bone-capemgr bone_capemgr.9: slot #11: Applied #3 overlays.

root@beaglebone:/home/debian/BB_PRU_stuff/EQEP# cat $SLOTS
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
11: ff:P-O-L Override Board Name,00A0,Override Manuf,bone_eqep1

Great. So now we should be able to write a PRU program that writes the registers now.

FYI, it has a sysfs entry:

root@beaglebone:/home/debian/BB_PRU_stuff/EQEP# find /sys/devices/ocp.3/ -iname "*qep*"
/sys/devices/ocp.3/48302000.epwmss/48302180.eqep

root@beaglebone:/home/debian/BB_PRU_stuff/EQEP# cd /sys/devices/ocp.3/48302000.epwmss/48302180.eqep
root@beaglebone:/sys/devices/ocp.3/48302000.epwmss/48302180.eqep# ls -lstr
total 0
0 -rw-r--r-- 1 root root 4096 Apr 28 13:03 uevent
0 lrwxrwxrwx 1 root root    0 Apr 28 13:03 subsystem -> ../../../../bus/platform
0 drwxr-xr-x 2 root root    0 Apr 28 13:11 power
0 -rw-r--r-- 1 root root 4096 Apr 28 13:12 mode
0 -rw-r--r-- 1 root root 4096 Apr 28 13:12 position
0 -rw-r--r-- 1 root root 4096 Apr 28 13:12 period
0 -r--r--r-- 1 root root 4096 Apr 28 13:12 modalias
0 -rw-r--r-- 1 root root 4096 Apr 28 13:12 enabled
0 lrwxrwxrwx 1 root root    0 Apr 28 13:12 driver -> ../../../../bus/platform/drivers/eqep
root@beaglebone:/sys/devices/ocp.3/48302000.epwmss/48302180.eqep# cat position
0

We'd need to plug the sensor into it (being sure to level-shift it down to 3.3V instead of 5V like the US Digital sensor does by default)




############################################################
############################################################

## PRU code to configure the EQEP registers on the AM335x

Look at Nathaniel's kernel module,

    https://github.com/Teknoman117/beaglebot.git

root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/beaglebot/encoders/patches/sources# ls
tieqep.c


We have things like a list of the register offsets for the EQEP peripheral:

// eQEP register offsets from its base IO address
#define QPOSCNT    0x0000
#define QPOSINIT   0x0004
#define QPOSMAX    0x0008
#define QPOSCMP    0x000C
#define QPOSILAT   0x0010
#define QPOSSLAT   0x0014
#define QPOSLAT    0x0018
#define QUTMR      0x001C
#define QUPRD      0x0020    
#define QWDTMR     0x0024
#define QWDPRD     0x0026
#define QDECCTL    0x0028
#define QEPCTL     0x002A
#define QCAPCTL    0x002C
#define QPOSCTL    0x002E
#define QEINT      0x0030
#define QFLG       0x0032
#define QCLR       0x0034
#define QFRC       0x0036
#define QEPSTS     0x0038
#define QCTMR      0x003A
#define QCPRD      0x003C
#define QCTMRLAT   0x003E
#define QCPRDLAT   0x0040
#define QREVID     0x005C


Here's the function where he configures it

// Create an instance of the eQEP driver
static int eqep_probe(struct platform_device *pdev)
{

.....................

    // Read decoder control settings
    status = readw(eqep->mmio_base + QDECCTL);
    
    // Quadrature mode or direction mode
    if(of_property_read_u32(pdev->dev.of_node, "count_mode", &value))
        status = status & ~QSRC1 & ~QSRC0;
    else
        status = ((value) ? status | QSRC0 : status & ~QSRC0) & ~QSRC1;
    
    // Should we invert the qa input
    if(of_property_read_u32(pdev->dev.of_node, "invert_qa", &value))
        status = status & ~QAP;
    else
        status = (value) ? status | QAP : status & ~QAP;
    
    // Should we invert the qb input
    if(of_property_read_u32(pdev->dev.of_node, "invert_qb", &value))
        status = status & ~QBP;
    else
        status = (value) ? status | QBP : status & ~QBP;
    
    // Should we invert the index input
    if(of_property_read_u32(pdev->dev.of_node, "invert_qi", &value))
        status = status & ~QIP;
    else
        status = (value) ? status | QIP : status & ~QIP;
.....................

    // Write the decoder control settings back to the control register
    writew(status, eqep->mmio_base + QDECCTL);
    
    // Initialize the position counter to zero
    writel(0, eqep->mmio_base + QPOSINIT);
    
    // This is pretty ingenious if I do say so myself.  The eQEP subsystem has a register
    // that defined the maximum value of the encoder as an unsigned.  If the counter is zero
    // and decrements again, it is set to QPOSMAX.  If you cast -1 (signed int) to
    // to an unsigned, you will notice that -1 == UINT_MAX.  So when the counter is set to this
    // maximum position, when read into a signed int, it will equal -1.  Two's complement for 
    // the WIN!!
    writel(-1, eqep->mmio_base + QPOSMAX);
    
    // Enable some interrupts
    status = readw(eqep->mmio_base + QEINT);
    status = status | UTOF;
            // UTOF - Unit Time Period interrupt.  This is triggered when the unit timer period expires
            // 
    writew(status, eqep->mmio_base + QEINT);

.............................

The point here is that we can conver this code to PRU assembly and it should configure the EQEP register in exactly the same way.





############################################################
############################################################


## Reading the EQEP from the PRU

Here's Nathaniel's kernel module driver:

// Function to read the current position of the eQEP
static ssize_t eqep_get_position(struct device *dev, struct device_attribute *attr, char *buf)
{
    // Get the instance structure
    struct eqep_chip *eqep = dev_get_drvdata(dev);
    
    // A variable to return the position with
    s32 position = 0;
    
    // Check the mode
    if(eqep->mode == TIEQEP_MODE_ABSOLUTE)
    {
        // If we are in absolute mode, we need the current value of the eQEP hardware
        position = readl(eqep->mmio_base + QPOSCNT);
    } else if(eqep->mode == TIEQEP_MODE_RELATIVE)
    {
        // If we are in relative mode, we need the last latched value of the eQEP hardware
        position = readl(eqep->mmio_base + QPOSLAT);
    }
    
    // Return the target in string format
    return sprintf(buf, "%d\n", position);
}


So it looks like the PRU just has to read the QPOSCNT register.
