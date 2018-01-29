pru reads eqep, compares to sysfs entry for eqep.

The concern here is that I use nathaniel lewis's C code to init the
eqep registers, then I use the PRU to read the reg. I'm not sure if
these two systems play nice together. So we'll compare what the NL's
sysfs driver says with what teh PRU says.


NOTE: can use jpp_test_eqep to spit out just the sysfs, to make sure that's working. see run-test.

NOTE: They seem to match.

NOTE: There seems to be a mismatch between where the eqep sysfs is stored. In the old days (on Zulu BB) it was in 

"/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep"

but my stock BB (Victor) doesn't have a "platform" directory. It's in

"/sys/devices/ocp.3/48302000.epwmss/48302180.eqep"

as specificed in NL's page

https://github.com/Teknoman117/beaglebot/tree/master/encoders



Conclusion:
- must use C code to init eqep registers

==========================================
Example output of ./run-test:



root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/02-eqep-cmp-to-sysfs# ./run-test
jpp_test_eqep.c:8:0: warning: "EQEP_SYSFS" redefined [enabled by default]
jadcpwmeqep.h:67:0: note: this is the location of the previous definition
Running jpp_test_eqep
Note: I'm using the qQEP sysfs entry:/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep, so make sure that exists!!
Calling constructor...
Setting period...
Starting loop...
test 4:
Shaft: 0
Shaft: -5
Shaft: -5
Shaft: -4
Shaft: -6
Shaft: -49
Shaft: -202
Shaft: -366
Shaft: -504
Shaft: -688
Shaft: -832
Shaft: -942
Shaft: -948
Shaft: -863
Shaft: -657
Shaft: -389
Shaft: -139
Shaft: -63
Shaft: -64
Shaft: -64
Shaft: -64
Shaft: -63
Shaft: 56
Shaft: 265
Shaft: 457
Shaft: 721
Shaft: 960
Shaft: 980
Shaft: 980
Shaft: 980
Shaft: 980
Shaft: 980
Shaft: 1024
Shaft: 1297
Shaft: 1516
Shaft: 1541
Shaft: 1551
Shaft: 1545
Shaft: 1476
Shaft: 1341
Shaft: 1135
Shaft: 901
Shaft: 772
Shaft: 704
Shaft: 711
Shaft: 815
Shaft: 1036
Shaft: 1292
Shaft: 1479
Shaft: 1485
Shaft: 1458
Shaft: 1446
Shaft: 1446
Shaft: 1237
Shaft: 905
Shaft: 845
Shaft: 846
Shaft: 846
Shaft: 839
Shaft: 694
Shaft: 416
Shaft: 173
Shaft: -1
Shaft: 19
Shaft: 160
Shaft: 407
Shaft: 700
Shaft: 825
Shaft: 824
Shaft: 824
Shaft: 819
Shaft: 1029
Shaft: 1349
Shaft: 1589
Shaft: 1703
Shaft: 1735
Shaft: 1726
Shaft: 1636
Shaft: 1445
Shaft: 1202
Shaft: 1061
Shaft: 1025
Shaft: 1091
Shaft: 1302
Shaft: 1535
Shaft: 1788
Shaft: 1838
Shaft: 1833
Shaft: 1834
Shaft: 1828
Shaft: 1815
Shaft: 1778
Shaft: 1699
Shaft: 1500
Shaft: 1189
Shaft: 848
Shaft: 856
Shaft: 858
Shaft: 858
Shaft: 822
Shaft: 609
Shaft: 368
Shaft: 178
Shaft: -79
Shaft: -314
Shaft: -313
Shaft: -313
Shaft: -313
Shaft: -313
Shaft: -313
Shaft: -394
Shaft: -641
Shaft: -879
Shaft: -937
Shaft: -816
Shaft: -542
Shaft: -210
Shaft: 13
Shaft: 10
Shaft: 10
Shaft: -9
Shaft: 145
Shaft: 523
Shaft: 705
Shaft: 717
Shaft: 720
Shaft: 701
Shaft: 632
Shaft: 508
Shaft: 335
Shaft: 70
Shaft: -135
Shaft: -88
Shaft: 248
Shaft: 595
Shaft: 583
Shaft: 580
Shaft: 566
Shaft: 881
Shaft: 1234
Shaft: 1209
Shaft: 1209
Shaft: 1209
Shaft: 1264
Shaft: 1537
Shaft: 1445
Shaft: 1444
Shaft: 1449
Shaft: 1799
Shaft: 2184
Shaft: 2335
Shaft: 2335
Shaft: 2321
Shaft: 2381
Shaft: 2860
Shaft: 3001
Shaft: 2962
Shaft: 2958
Shaft: 2955
Shaft: 3291
Shaft: 3626
Shaft: 3510
Shaft: 3514
Shaft: 3514
Shaft: 3978
Shaft: 4385
Shaft: 4363
Shaft: 4367
Shaft: 4368
Shaft: 4673
Shaft: 5201
Shaft: 5251
Shaft: 5251
Shaft: 5251
Shaft: 5282
Shaft: 5843
Shaft: 6045
Shaft: 6100
Shaft: 6100
Shaft: 6100
Shaft: 6532
Shaft: 6926
Shaft: 6929
Shaft: 6929
Shaft: 6929
Shaft: 7340
Shaft: 7634
Shaft: 7613
Shaft: 7610
Shaft: 7610
Shaft: 7849
Shaft: 8298
Shaft: 8443
Shaft: 8450
Shaft: 8451
Shaft: 8458
Shaft: 8847
Shaft: 9186
Shaft: 9201
Shaft: 9200





==========================================

Example output of ./run:

root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/02-eqep-cmp-to-sysfs# !!
./run
Building .bin file eqep-cmp-to-sysfs.p


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 28 word(s)

Building .c file eqep-cmp-to-sysfs.c to make eqep-cmp-to-sysfs
(Careful - does your .c load the correct .p / .bin?)
Running eqep-cmp-to-sysfs
Hey, if you get a seg fault, make sure the EBB-PRU-Example device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo EBB-PRU-Example > /sys/devices/bone_capemgr.9/slots
Note: I'm using the qQEP sysfs entry:/sys/devices/ocp.3/48302000.epwmss/48302180.eqep, so make sure that exists!!
Calling constructor...
Setting period...
Starting loop...
executing bin file: ./eqep-cmp-to-sysfs.bin
Waiting...
Iter 0/150, val0: 3		 val1: 200038895	 sysfs:3
Iter 1/150, val0: 3		 val1: 240279245	 sysfs:3
Iter 2/150, val0: 4294967268		 val1: 280479495	 sysfs:-28
Iter 3/150, val0: 4294967086		 val1: 320699795	 sysfs:-210
Iter 4/150, val0: 4294966786		 val1: 360920095	 sysfs:-511
Iter 5/150, val0: 4294966468		 val1: 401120345	 sysfs:-828
Iter 6/150, val0: 4294966216		 val1: 441340645	 sysfs:-1080
Iter 7/150, val0: 4294966404		 val1: 481560945	 sysfs:-891
Iter 8/150, val0: 4294967124		 val1: 521741157	 sysfs:-171
Iter 9/150, val0: 4294967166		 val1: 561941407	 sysfs:-130
Iter 10/150, val0: 4294967167		 val1: 602141657	 sysfs:-129
Iter 11/150, val0: 386		 val1: 642321859	 sysfs:387
Iter 12/150, val0: 914		 val1: 682522109	 sysfs:914
Iter 13/150, val0: 928		 val1: 722722359	 sysfs:928
Iter 14/150, val0: 918		 val1: 762922609	 sysfs:918
Iter 15/150, val0: 1274		 val1: 803122859	 sysfs:1276
Iter 16/150, val0: 1959		 val1: 843323109	 sysfs:1960
Iter 17/150, val0: 1889		 val1: 883543409	 sysfs:1889
Iter 18/150, val0: 1874		 val1: 923763709	 sysfs:1874
Iter 19/150, val0: 2247		 val1: 963984009	 sysfs:2248
Iter 20/150, val0: 2850		 val1: 1004164211	 sysfs:2850
Iter 21/150, val0: 2794		 val1: 1044364461	 sysfs:2794
Iter 22/150, val0: 2794		 val1: 1084564711	 sysfs:2793
Iter 23/150, val0: 2859		 val1: 1124744911	 sysfs:2859
Iter 24/150, val0: 3538		 val1: 1164925111	 sysfs:3540
Iter 25/150, val0: 3857		 val1: 1205125361	 sysfs:3857
Iter 26/150, val0: 3858		 val1: 1245345661	 sysfs:3858
Iter 27/150, val0: 4192		 val1: 1285545911	 sysfs:4193
Iter 28/150, val0: 4688		 val1: 1325746161	 sysfs:4689
Iter 29/150, val0: 4795		 val1: 1365966461	 sysfs:4795
Iter 30/150, val0: 4794		 val1: 1406186761	 sysfs:4794
Iter 31/150, val0: 5079		 val1: 1446366961	 sysfs:5081
Iter 32/150, val0: 5519		 val1: 1486547161	 sysfs:5519
Iter 33/150, val0: 5372		 val1: 1526747411	 sysfs:5372
Iter 34/150, val0: 4700		 val1: 1566927611	 sysfs:4698
Iter 35/150, val0: 4538		 val1: 1607107811	 sysfs:4538
Iter 36/150, val0: 4538		 val1: 1647308061	 sysfs:4538
Iter 37/150, val0: 4356		 val1: 1687508311	 sysfs:4355
Iter 38/150, val0: 3686		 val1: 1727728611	 sysfs:3684
Iter 39/150, val0: 3635		 val1: 1767948915	 sysfs:3635
Iter 40/150, val0: 3626		 val1: 1808149165	 sysfs:3626
Iter 41/150, val0: 3185		 val1: 1848369467	 sysfs:3184
Iter 42/150, val0: 2455		 val1: 1888549669	 sysfs:2456
Iter 43/150, val0: 2455		 val1: 1928729869	 sysfs:2455
Iter 44/150, val0: 2290		 val1: 1968930121	 sysfs:2289
Iter 45/150, val0: 1536		 val1: 2009110321	 sysfs:1533
Iter 46/150, val0: 1292		 val1: 2049290521	 sysfs:1292
Iter 47/150, val0: 1274		 val1: 2089490771	 sysfs:1274
Iter 48/150, val0: 711		 val1: 2129711073	 sysfs:709
Iter 49/150, val0: 110		 val1: 2169911323	 sysfs:110
Iter 50/150, val0: 108		 val1: 2210111573	 sysfs:108
Iter 51/150, val0: 4294967013		 val1: 2250331873	 sysfs:-284
Iter 52/150, val0: 4294966242		 val1: 2290552173	 sysfs:-1054
Iter 53/150, val0: 4294966229		 val1: 2330752423	 sysfs:-1067
Iter 54/150, val0: 4294966092		 val1: 2370932623	 sysfs:-1205
Iter 55/150, val0: 4294965252		 val1: 2411132873	 sysfs:-2047
Iter 56/150, val0: 4294965053		 val1: 2451313075	 sysfs:-2243
Iter 57/150, val0: 4294964997		 val1: 2491513325	 sysfs:-2301
Iter 58/150, val0: 4294964258		 val1: 2531713577	 sysfs:-3042
Iter 59/150, val0: 4294963904		 val1: 2571913827	 sysfs:-3393
Iter 60/150, val0: 4294963877		 val1: 2612114081	 sysfs:-3420
Iter 61/150, val0: 4294963292		 val1: 2652334381	 sysfs:-4006
Iter 62/150, val0: 4294962606		 val1: 2692554681	 sysfs:-4690
Iter 63/150, val0: 4294962622		 val1: 2732754931	 sysfs:-4674
Iter 64/150, val0: 4294962240		 val1: 2772975231	 sysfs:-5058
Iter 65/150, val0: 4294961574		 val1: 2813175483	 sysfs:-5722
Iter 66/150, val0: 4294961576		 val1: 2853355683	 sysfs:-5720
Iter 67/150, val0: 4294961308		 val1: 2893555933	 sysfs:-5988
Iter 68/150, val0: 4294960971		 val1: 2933736133	 sysfs:-6325
Iter 69/150, val0: 4294960970		 val1: 2973936383	 sysfs:-6326
Iter 70/150, val0: 4294960672		 val1: 3014116585	 sysfs:-6625
Iter 71/150, val0: 4294960134		 val1: 3054336885	 sysfs:-7162
Iter 72/150, val0: 4294960128		 val1: 3094577237	 sysfs:-7168
Iter 73/150, val0: 4294959953		 val1: 3134777487	 sysfs:-7344
Iter 74/150, val0: 4294959153		 val1: 3174977737	 sysfs:-8143
Iter 75/150, val0: 4294959202		 val1: 3215198037	 sysfs:-8094
Iter 76/150, val0: 4294959024		 val1: 3255398287	 sysfs:-8273
Iter 77/150, val0: 4294958025		 val1: 3295618587	 sysfs:-9272
Iter 78/150, val0: 4294958041		 val1: 3335798789	 sysfs:-9255
Iter 79/150, val0: 4294957867		 val1: 3375999039	 sysfs:-9430
Iter 80/150, val0: 4294957095		 val1: 3416199291	 sysfs:-10201
Iter 81/150, val0: 4294957209		 val1: 3456379491	 sysfs:-10087
Iter 82/150, val0: 4294957879		 val1: 3496579741	 sysfs:-9415
Iter 83/150, val0: 4294958070		 val1: 3536779991	 sysfs:-9226
Iter 84/150, val0: 4294958074		 val1: 3576980241	 sysfs:-9222
Iter 85/150, val0: 4294959005		 val1: 3617200541	 sysfs:-8290
Iter 86/150, val0: 4294958951		 val1: 3657400791	 sysfs:-8345
Iter 87/150, val0: 4294959092		 val1: 3697621093	 sysfs:-8202
Iter 88/150, val0: 4294959571		 val1: 3737841393	 sysfs:-7725
Iter 89/150, val0: 4294959563		 val1: 3778041645	 sysfs:-7733
Iter 90/150, val0: 4294960322		 val1: 3818241895	 sysfs:-6972
Iter 91/150, val0: 4294960415		 val1: 3858442145	 sysfs:-6881
Iter 92/150, val0: 4294960431		 val1: 3898622345	 sysfs:-6865
Iter 93/150, val0: 4294961089		 val1: 3938802547	 sysfs:-6206
Iter 94/150, val0: 4294961188		 val1: 3979002797	 sysfs:-6108
Iter 95/150, val0: 4294961196		 val1: 4019203047	 sysfs:-6100
Iter 96/150, val0: 4294962109		 val1: 4059403297	 sysfs:-5185
Iter 97/150, val0: 4294962143		 val1: 4099603547	 sysfs:-5153
Iter 98/150, val0: 4294962509		 val1: 4139803801	 sysfs:-4784
Iter 99/150, val0: 4294963059		 val1: 4180024101	 sysfs:-4237
Iter 100/150, val0: 4294963067		 val1: 4220224353	 sysfs:-4229
Iter 101/150, val0: 4294963984		 val1: 4260424603	 sysfs:-3310
Iter 102/150, val0: 4294963921		 val1: 4294967295	 sysfs:-3375
Iter 103/150, val0: 4294963934		 val1: 4294967295	 sysfs:-3361
Iter 104/150, val0: 4294964641		 val1: 4294967295	 sysfs:-2653
Iter 105/150, val0: 4294964789		 val1: 4294967295	 sysfs:-2507
Iter 106/150, val0: 4294964811		 val1: 4294967295	 sysfs:-2484
Iter 107/150, val0: 4294965755		 val1: 4294967295	 sysfs:-1541
Iter 108/150, val0: 4294965669		 val1: 4294967295	 sysfs:-1627
Iter 109/150, val0: 4294966330		 val1: 4294967295	 sysfs:-964
Iter 110/150, val0: 4294966584		 val1: 4294967295	 sysfs:-712
Iter 111/150, val0: 4294966685		 val1: 4294967295	 sysfs:-609
Iter 112/150, val0: 173		 val1: 4294967295	 sysfs:173
Iter 113/150, val0: 137		 val1: 4294967295	 sysfs:137
Iter 114/150, val0: 909		 val1: 4294967295	 sysfs:912
Iter 115/150, val0: 1041		 val1: 4294967295	 sysfs:1041
Iter 116/150, val0: 1359		 val1: 4294967295	 sysfs:1364
Iter 117/150, val0: 1918		 val1: 4294967295	 sysfs:1918
Iter 118/150, val0: 1841		 val1: 4294967295	 sysfs:1841
Iter 119/150, val0: 2604		 val1: 4294967295	 sysfs:2605
Iter 120/150, val0: 2701		 val1: 4294967295	 sysfs:2701
Iter 121/150, val0: 3160		 val1: 4294967295	 sysfs:3162
Iter 122/150, val0: 3362		 val1: 4294967295	 sysfs:3362
Iter 123/150, val0: 3456		 val1: 4294967295	 sysfs:3457
Iter 124/150, val0: 4111		 val1: 4294967295	 sysfs:4111
Iter 125/150, val0: 3954		 val1: 4294967295	 sysfs:3953
Iter 126/150, val0: 2704		 val1: 4294967295	 sysfs:2704
Iter 127/150, val0: 2754		 val1: 4294967295	 sysfs:2754
Iter 128/150, val0: 3483		 val1: 4294967295	 sysfs:3484
Iter 129/150, val0: 3364		 val1: 4294967295	 sysfs:3364
Iter 130/150, val0: 3386		 val1: 4294967295	 sysfs:3388
Iter 131/150, val0: 3881		 val1: 4294967295	 sysfs:3881
Iter 132/150, val0: 3881		 val1: 4294967295	 sysfs:3881
Iter 133/150, val0: 4756		 val1: 4294967295	 sysfs:4758
Iter 134/150, val0: 4774		 val1: 4294967295	 sysfs:4774
Iter 135/150, val0: 4774		 val1: 4294967295	 sysfs:4774
Iter 136/150, val0: 5296		 val1: 4294967295	 sysfs:5298
Iter 137/150, val0: 5394		 val1: 4294967295	 sysfs:5392
Iter 138/150, val0: 4167		 val1: 4294967295	 sysfs:4167
Iter 139/150, val0: 4246		 val1: 4294967295	 sysfs:4247
Iter 140/150, val0: 4816		 val1: 4294967295	 sysfs:4817
Iter 141/150, val0: 4816		 val1: 4294967295	 sysfs:4816
Iter 142/150, val0: 5486		 val1: 4294967295	 sysfs:5487
Iter 143/150, val0: 5615		 val1: 4294967295	 sysfs:5615
Iter 144/150, val0: 5693		 val1: 4294967295	 sysfs:5694
Iter 145/150, val0: 5963		 val1: 4294967295	 sysfs:5963
Iter 146/150, val0: 5985		 val1: 4294967295	 sysfs:5986
Iter 147/150, val0: 6838		 val1: 4294967295	 sysfs:6838
Iter 148/150, val0: 6713		 val1: 4294967295	 sysfs:6713
Iter 149/150, val0: 7471		 val1: 4294967295	 sysfs:7472
Shutting down.
root@beaglebone:/home/debian/BB_PRU_stuff/EQEP/02-eqep-cmp-to-sysfs# 
