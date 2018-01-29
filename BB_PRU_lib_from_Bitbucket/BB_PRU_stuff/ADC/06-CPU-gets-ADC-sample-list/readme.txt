Here is a program for sampling several precisely-sampled ADC values. 
The C program starts the PRU code, which continuously samples the ADC every 5ms to a length-64 buffer in PRU data ram. 
When the C program sets the lowest bit in the PRU0 data ram address 0, the PRU copies the last 64 ADC samples to the PRU data ram at addresses 0x00000004 to 0x00000404. Each sample consists of:
- which sample number. this is just an increasing number that the pru increments each time it samples the adc.
- cycle count. this is the # of cycles the pru executed since the start of the program. Note that at 200MHz, the pru executes a million cycles in 5ms, so the cycle count is typically close to an integer multiple of a million
- adc value: this is 0 - 4095, which maps to 0 - 1.8V. ADC channel 0. (P9_39).
- a4a4a4a4. (reserved value) (will be the eqep position some day)


Sample output:



CPU 1-second pause beween asking:

root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# !!

./run
I'm in: 
/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list
Building .bin file cpu-reads-adc.p


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 144 word(s)

Building .c file cpu-reads-adc.c to make cpu-reads-adc
(Careful - does your .c load the correct .p / .bin?)
Running cpu-reads-adc
Hey, if you get a seg fault, make sure the EBB-PRU-Example device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo EBB-PRU-Example > /sys/devices/bone_capemgr.9/slots
executing bin file: ./cpu-reads-adc.bin
Waiting for "Data ready" bit...
Got it!
i:0	#: 138	cycles: 138000010	ms: 690.000050	ADC: 2044	eyecatch: a4a4a4a4
i:1	#: 139	cycles: 139000013	ms: 695.000065	ADC: 2045	eyecatch: a4a4a4a4
i:2	#: 140	cycles: 140000012	ms: 700.000060	ADC: 2046	eyecatch: a4a4a4a4
i:3	#: 141	cycles: 141000010	ms: 705.000050	ADC: 2045	eyecatch: a4a4a4a4
i:4	#: 142	cycles: 142000013	ms: 710.000065	ADC: 2044	eyecatch: a4a4a4a4
i:5	#: 143	cycles: 143000012	ms: 715.000060	ADC: 2044	eyecatch: a4a4a4a4
i:6	#: 144	cycles: 144000010	ms: 720.000050	ADC: 2045	eyecatch: a4a4a4a4
i:7	#: 145	cycles: 145000013	ms: 725.000065	ADC: 2045	eyecatch: a4a4a4a4
i:8	#: 146	cycles: 146000012	ms: 730.000060	ADC: 2045	eyecatch: a4a4a4a4
i:9	#: 147	cycles: 147000010	ms: 735.000050	ADC: 2045	eyecatch: a4a4a4a4
i:10	#: 148	cycles: 148000013	ms: 740.000065	ADC: 2045	eyecatch: a4a4a4a4
i:11	#: 149	cycles: 149000012	ms: 745.000060	ADC: 2048	eyecatch: a4a4a4a4
i:12	#: 150	cycles: 150000010	ms: 750.000050	ADC: 2048	eyecatch: a4a4a4a4
i:13	#: 151	cycles: 151000013	ms: 755.000065	ADC: 2044	eyecatch: a4a4a4a4
i:14	#: 152	cycles: 152000012	ms: 760.000060	ADC: 2044	eyecatch: a4a4a4a4
i:15	#: 153	cycles: 153000010	ms: 765.000050	ADC: 2044	eyecatch: a4a4a4a4
i:16	#: 154	cycles: 154000013	ms: 770.000065	ADC: 2044	eyecatch: a4a4a4a4
i:17	#: 155	cycles: 155000012	ms: 775.000060	ADC: 2045	eyecatch: a4a4a4a4
i:18	#: 156	cycles: 156000010	ms: 780.000050	ADC: 2044	eyecatch: a4a4a4a4
i:19	#: 157	cycles: 157000013	ms: 785.000065	ADC: 2044	eyecatch: a4a4a4a4
i:20	#: 158	cycles: 158000012	ms: 790.000060	ADC: 2048	eyecatch: a4a4a4a4
i:21	#: 159	cycles: 159000010	ms: 795.000050	ADC: 2048	eyecatch: a4a4a4a4
i:22	#: 160	cycles: 160000013	ms: 800.000065	ADC: 2044	eyecatch: a4a4a4a4
i:23	#: 161	cycles: 161000012	ms: 805.000060	ADC: 2044	eyecatch: a4a4a4a4
i:24	#: 162	cycles: 162000010	ms: 810.000050	ADC: 2045	eyecatch: a4a4a4a4
i:25	#: 163	cycles: 163000013	ms: 815.000065	ADC: 2048	eyecatch: a4a4a4a4
i:26	#: 164	cycles: 164000012	ms: 820.000060	ADC: 2046	eyecatch: a4a4a4a4
i:27	#: 165	cycles: 165000010	ms: 825.000050	ADC: 2048	eyecatch: a4a4a4a4
i:28	#: 166	cycles: 166000013	ms: 830.000065	ADC: 2045	eyecatch: a4a4a4a4
i:29	#: 167	cycles: 167000012	ms: 835.000060	ADC: 2045	eyecatch: a4a4a4a4
i:30	#: 168	cycles: 168000010	ms: 840.000050	ADC: 2044	eyecatch: a4a4a4a4
i:31	#: 169	cycles: 169000013	ms: 845.000065	ADC: 2045	eyecatch: a4a4a4a4
i:32	#: 170	cycles: 170000012	ms: 850.000060	ADC: 2048	eyecatch: a4a4a4a4
i:33	#: 171	cycles: 171000010	ms: 855.000050	ADC: 2045	eyecatch: a4a4a4a4
i:34	#: 172	cycles: 172000013	ms: 860.000065	ADC: 2045	eyecatch: a4a4a4a4
i:35	#: 173	cycles: 173000012	ms: 865.000060	ADC: 2044	eyecatch: a4a4a4a4
i:36	#: 174	cycles: 174000010	ms: 870.000050	ADC: 2045	eyecatch: a4a4a4a4
i:37	#: 175	cycles: 175000013	ms: 875.000065	ADC: 2044	eyecatch: a4a4a4a4
i:38	#: 176	cycles: 176000012	ms: 880.000060	ADC: 2044	eyecatch: a4a4a4a4
i:39	#: 177	cycles: 177000010	ms: 885.000050	ADC: 2045	eyecatch: a4a4a4a4
i:40	#: 178	cycles: 178000013	ms: 890.000065	ADC: 2045	eyecatch: a4a4a4a4
i:41	#: 179	cycles: 179000012	ms: 895.000060	ADC: 2044	eyecatch: a4a4a4a4
i:42	#: 180	cycles: 180000010	ms: 900.000050	ADC: 2048	eyecatch: a4a4a4a4
i:43	#: 181	cycles: 181000013	ms: 905.000065	ADC: 2044	eyecatch: a4a4a4a4
i:44	#: 182	cycles: 182000012	ms: 910.000060	ADC: 2045	eyecatch: a4a4a4a4
i:45	#: 183	cycles: 183000010	ms: 915.000050	ADC: 2045	eyecatch: a4a4a4a4
i:46	#: 184	cycles: 184000013	ms: 920.000065	ADC: 2046	eyecatch: a4a4a4a4
i:47	#: 185	cycles: 185000012	ms: 925.000060	ADC: 2044	eyecatch: a4a4a4a4
i:48	#: 186	cycles: 186000010	ms: 930.000050	ADC: 2044	eyecatch: a4a4a4a4
i:49	#: 187	cycles: 187000013	ms: 935.000065	ADC: 2045	eyecatch: a4a4a4a4
i:50	#: 188	cycles: 188000012	ms: 940.000060	ADC: 2044	eyecatch: a4a4a4a4
i:51	#: 189	cycles: 189000010	ms: 945.000050	ADC: 2045	eyecatch: a4a4a4a4
i:52	#: 190	cycles: 190000013	ms: 950.000065	ADC: 2045	eyecatch: a4a4a4a4
i:53	#: 191	cycles: 191000012	ms: 955.000060	ADC: 2043	eyecatch: a4a4a4a4
i:54	#: 192	cycles: 192000010	ms: 960.000050	ADC: 2045	eyecatch: a4a4a4a4
i:55	#: 193	cycles: 193000011	ms: 965.000055	ADC: 2045	eyecatch: a4a4a4a4
i:56	#: 194	cycles: 194000010	ms: 970.000050	ADC: 2045	eyecatch: a4a4a4a4
i:57	#: 195	cycles: 195000013	ms: 975.000065	ADC: 2045	eyecatch: a4a4a4a4
i:58	#: 196	cycles: 196000012	ms: 980.000060	ADC: 2045	eyecatch: a4a4a4a4
i:59	#: 197	cycles: 197000010	ms: 985.000050	ADC: 2045	eyecatch: a4a4a4a4
i:60	#: 198	cycles: 198000013	ms: 990.000065	ADC: 2045	eyecatch: a4a4a4a4
i:61	#: 199	cycles: 199000012	ms: 995.000060	ADC: 2045	eyecatch: a4a4a4a4
i:62	#: 200	cycles: 200000010	ms: 1000.000050	ADC: 2045	eyecatch: a4a4a4a4
i:63	#: 201	cycles: 201000013	ms: 1005.000065	ADC: 2044	eyecatch: a4a4a4a4
Waiting for "Data ready" bit...
Got it!
i:0	#: 347	cycles: 347000012	ms: 1735.000060	ADC: 2046	eyecatch: a4a4a4a4
i:1	#: 348	cycles: 348000010	ms: 1740.000050	ADC: 2045	eyecatch: a4a4a4a4
i:2	#: 349	cycles: 349000013	ms: 1745.000065	ADC: 2044	eyecatch: a4a4a4a4
i:3	#: 350	cycles: 350000012	ms: 1750.000060	ADC: 2044	eyecatch: a4a4a4a4
i:4	#: 351	cycles: 351000010	ms: 1755.000050	ADC: 2044	eyecatch: a4a4a4a4
i:5	#: 352	cycles: 352000013	ms: 1760.000065	ADC: 2044	eyecatch: a4a4a4a4
i:6	#: 353	cycles: 353000012	ms: 1765.000060	ADC: 2048	eyecatch: a4a4a4a4
i:7	#: 354	cycles: 354000010	ms: 1770.000050	ADC: 2045	eyecatch: a4a4a4a4
i:8	#: 355	cycles: 355000013	ms: 1775.000065	ADC: 2046	eyecatch: a4a4a4a4
i:9	#: 356	cycles: 356000012	ms: 1780.000060	ADC: 2045	eyecatch: a4a4a4a4
i:10	#: 357	cycles: 357000010	ms: 1785.000050	ADC: 2045	eyecatch: a4a4a4a4
i:11	#: 358	cycles: 358000013	ms: 1790.000065	ADC: 2044	eyecatch: a4a4a4a4
i:12	#: 359	cycles: 359000012	ms: 1795.000060	ADC: 2045	eyecatch: a4a4a4a4
i:13	#: 360	cycles: 360000010	ms: 1800.000050	ADC: 2045	eyecatch: a4a4a4a4
i:14	#: 361	cycles: 361000013	ms: 1805.000065	ADC: 2045	eyecatch: a4a4a4a4
i:15	#: 362	cycles: 362000012	ms: 1810.000060	ADC: 2043	eyecatch: a4a4a4a4
i:16	#: 363	cycles: 363000010	ms: 1815.000050	ADC: 2045	eyecatch: a4a4a4a4
i:17	#: 364	cycles: 364000013	ms: 1820.000065	ADC: 2044	eyecatch: a4a4a4a4
i:18	#: 365	cycles: 365000012	ms: 1825.000060	ADC: 2043	eyecatch: a4a4a4a4
i:19	#: 366	cycles: 366000010	ms: 1830.000050	ADC: 2045	eyecatch: a4a4a4a4
i:20	#: 367	cycles: 367000013	ms: 1835.000065	ADC: 2043	eyecatch: a4a4a4a4
i:21	#: 368	cycles: 368000012	ms: 1840.000060	ADC: 2048	eyecatch: a4a4a4a4
i:22	#: 369	cycles: 369000010	ms: 1845.000050	ADC: 2045	eyecatch: a4a4a4a4
i:23	#: 370	cycles: 370000013	ms: 1850.000065	ADC: 2043	eyecatch: a4a4a4a4
i:24	#: 371	cycles: 371000012	ms: 1855.000060	ADC: 2044	eyecatch: a4a4a4a4
i:25	#: 372	cycles: 372000010	ms: 1860.000050	ADC: 2045	eyecatch: a4a4a4a4
i:26	#: 373	cycles: 373000013	ms: 1865.000065	ADC: 2045	eyecatch: a4a4a4a4
i:27	#: 374	cycles: 374000012	ms: 1870.000060	ADC: 2045	eyecatch: a4a4a4a4
i:28	#: 375	cycles: 375000010	ms: 1875.000050	ADC: 2045	eyecatch: a4a4a4a4
i:29	#: 376	cycles: 376000013	ms: 1880.000065	ADC: 2045	eyecatch: a4a4a4a4
i:30	#: 377	cycles: 377000012	ms: 1885.000060	ADC: 2045	eyecatch: a4a4a4a4
i:31	#: 378	cycles: 378000010	ms: 1890.000050	ADC: 2044	eyecatch: a4a4a4a4
i:32	#: 379	cycles: 379000013	ms: 1895.000065	ADC: 2045	eyecatch: a4a4a4a4
i:33	#: 380	cycles: 380000012	ms: 1900.000060	ADC: 2045	eyecatch: a4a4a4a4
i:34	#: 381	cycles: 381000010	ms: 1905.000050	ADC: 2045	eyecatch: a4a4a4a4
i:35	#: 382	cycles: 382000013	ms: 1910.000065	ADC: 2044	eyecatch: a4a4a4a4
i:36	#: 383	cycles: 383000012	ms: 1915.000060	ADC: 2045	eyecatch: a4a4a4a4
i:37	#: 384	cycles: 384000010	ms: 1920.000050	ADC: 2044	eyecatch: a4a4a4a4
i:38	#: 385	cycles: 385000011	ms: 1925.000055	ADC: 2045	eyecatch: a4a4a4a4
i:39	#: 386	cycles: 386000010	ms: 1930.000050	ADC: 2044	eyecatch: a4a4a4a4
i:40	#: 387	cycles: 387000013	ms: 1935.000065	ADC: 2048	eyecatch: a4a4a4a4
i:41	#: 388	cycles: 388000012	ms: 1940.000060	ADC: 2045	eyecatch: a4a4a4a4
i:42	#: 389	cycles: 389000010	ms: 1945.000050	ADC: 2045	eyecatch: a4a4a4a4
i:43	#: 390	cycles: 390000013	ms: 1950.000065	ADC: 2044	eyecatch: a4a4a4a4
i:44	#: 391	cycles: 391000012	ms: 1955.000060	ADC: 2045	eyecatch: a4a4a4a4
i:45	#: 392	cycles: 392000010	ms: 1960.000050	ADC: 2048	eyecatch: a4a4a4a4
i:46	#: 393	cycles: 393000013	ms: 1965.000065	ADC: 2044	eyecatch: a4a4a4a4
i:47	#: 394	cycles: 394000012	ms: 1970.000060	ADC: 2044	eyecatch: a4a4a4a4
i:48	#: 395	cycles: 395000010	ms: 1975.000050	ADC: 2046	eyecatch: a4a4a4a4
i:49	#: 396	cycles: 396000013	ms: 1980.000065	ADC: 2044	eyecatch: a4a4a4a4
i:50	#: 397	cycles: 397000012	ms: 1985.000060	ADC: 2046	eyecatch: a4a4a4a4
i:51	#: 398	cycles: 398000010	ms: 1990.000050	ADC: 2045	eyecatch: a4a4a4a4
i:52	#: 399	cycles: 399000013	ms: 1995.000065	ADC: 2045	eyecatch: a4a4a4a4
i:53	#: 400	cycles: 400000012	ms: 2000.000060	ADC: 2043	eyecatch: a4a4a4a4
i:54	#: 401	cycles: 401000010	ms: 2005.000050	ADC: 2045	eyecatch: a4a4a4a4
i:55	#: 402	cycles: 402000013	ms: 2010.000065	ADC: 2045	eyecatch: a4a4a4a4
i:56	#: 403	cycles: 403000012	ms: 2015.000060	ADC: 2044	eyecatch: a4a4a4a4
i:57	#: 404	cycles: 404000010	ms: 2020.000050	ADC: 2045	eyecatch: a4a4a4a4
i:58	#: 405	cycles: 405000013	ms: 2025.000065	ADC: 2044	eyecatch: a4a4a4a4
i:59	#: 406	cycles: 406000012	ms: 2030.000060	ADC: 2044	eyecatch: a4a4a4a4
i:60	#: 407	cycles: 407000010	ms: 2035.000050	ADC: 2044	eyecatch: a4a4a4a4
i:61	#: 408	cycles: 408000013	ms: 2040.000065	ADC: 2046	eyecatch: a4a4a4a4
i:62	#: 409	cycles: 409000012	ms: 2045.000060	ADC: 2045	eyecatch: a4a4a4a4
i:63	#: 410	cycles: 410000010	ms: 2050.000050	ADC: 2044	eyecatch: a4a4a4a4
Waiting for "Data ready" bit...
Got it!
i:0	#: 557	cycles: 557000012	ms: 2785.000060	ADC: 2044	eyecatch: a4a4a4a4
i:1	#: 558	cycles: 558000010	ms: 2790.000050	ADC: 2044	eyecatch: a4a4a4a4
i:2	#: 559	cycles: 559000013	ms: 2795.000065	ADC: 2044	eyecatch: a4a4a4a4
i:3	#: 560	cycles: 560000012	ms: 2800.000060	ADC: 2043	eyecatch: a4a4a4a4
i:4	#: 561	cycles: 561000010	ms: 2805.000050	ADC: 2047	eyecatch: a4a4a4a4
i:5	#: 562	cycles: 562000013	ms: 2810.000065	ADC: 2044	eyecatch: a4a4a4a4
i:6	#: 563	cycles: 563000012	ms: 2815.000060	ADC: 2045	eyecatch: a4a4a4a4
i:7	#: 564	cycles: 564000010	ms: 2820.000050	ADC: 2047	eyecatch: a4a4a4a4
i:8	#: 565	cycles: 565000013	ms: 2825.000065	ADC: 2047	eyecatch: a4a4a4a4
i:9	#: 566	cycles: 566000012	ms: 2830.000060	ADC: 2043	eyecatch: a4a4a4a4
i:10	#: 567	cycles: 567000010	ms: 2835.000050	ADC: 2046	eyecatch: a4a4a4a4
i:11	#: 568	cycles: 568000013	ms: 2840.000065	ADC: 2045	eyecatch: a4a4a4a4
i:12	#: 569	cycles: 569000012	ms: 2845.000060	ADC: 2044	eyecatch: a4a4a4a4
i:13	#: 570	cycles: 570000010	ms: 2850.000050	ADC: 2045	eyecatch: a4a4a4a4
i:14	#: 571	cycles: 571000013	ms: 2855.000065	ADC: 2045	eyecatch: a4a4a4a4
i:15	#: 572	cycles: 572000012	ms: 2860.000060	ADC: 2045	eyecatch: a4a4a4a4
i:16	#: 573	cycles: 573000010	ms: 2865.000050	ADC: 2045	eyecatch: a4a4a4a4
i:17	#: 574	cycles: 574000013	ms: 2870.000065	ADC: 2045	eyecatch: a4a4a4a4
i:18	#: 575	cycles: 575000012	ms: 2875.000060	ADC: 2045	eyecatch: a4a4a4a4
i:19	#: 576	cycles: 576000010	ms: 2880.000050	ADC: 2044	eyecatch: a4a4a4a4
i:20	#: 577	cycles: 577000011	ms: 2885.000055	ADC: 2043	eyecatch: a4a4a4a4
i:21	#: 578	cycles: 578000010	ms: 2890.000050	ADC: 2048	eyecatch: a4a4a4a4
i:22	#: 579	cycles: 579000013	ms: 2895.000065	ADC: 2045	eyecatch: a4a4a4a4
i:23	#: 580	cycles: 580000012	ms: 2900.000060	ADC: 2045	eyecatch: a4a4a4a4
i:24	#: 581	cycles: 581000010	ms: 2905.000050	ADC: 2045	eyecatch: a4a4a4a4
i:25	#: 582	cycles: 582000013	ms: 2910.000065	ADC: 2048	eyecatch: a4a4a4a4
i:26	#: 583	cycles: 583000012	ms: 2915.000060	ADC: 2045	eyecatch: a4a4a4a4
i:27	#: 584	cycles: 584000010	ms: 2920.000050	ADC: 2045	eyecatch: a4a4a4a4
i:28	#: 585	cycles: 585000013	ms: 2925.000065	ADC: 2045	eyecatch: a4a4a4a4
i:29	#: 586	cycles: 586000012	ms: 2930.000060	ADC: 2044	eyecatch: a4a4a4a4
i:30	#: 587	cycles: 587000010	ms: 2935.000050	ADC: 2045	eyecatch: a4a4a4a4
i:31	#: 588	cycles: 588000013	ms: 2940.000065	ADC: 2048	eyecatch: a4a4a4a4
i:32	#: 589	cycles: 589000012	ms: 2945.000060	ADC: 2048	eyecatch: a4a4a4a4
i:33	#: 590	cycles: 590000010	ms: 2950.000050	ADC: 2044	eyecatch: a4a4a4a4
i:34	#: 591	cycles: 591000013	ms: 2955.000065	ADC: 2045	eyecatch: a4a4a4a4
i:35	#: 592	cycles: 592000012	ms: 2960.000060	ADC: 2046	eyecatch: a4a4a4a4
i:36	#: 593	cycles: 593000010	ms: 2965.000050	ADC: 2046	eyecatch: a4a4a4a4
i:37	#: 594	cycles: 594000013	ms: 2970.000065	ADC: 2046	eyecatch: a4a4a4a4
i:38	#: 595	cycles: 595000012	ms: 2975.000060	ADC: 2044	eyecatch: a4a4a4a4
i:39	#: 596	cycles: 596000010	ms: 2980.000050	ADC: 2048	eyecatch: a4a4a4a4
i:40	#: 597	cycles: 597000013	ms: 2985.000065	ADC: 2048	eyecatch: a4a4a4a4
i:41	#: 598	cycles: 598000012	ms: 2990.000060	ADC: 2048	eyecatch: a4a4a4a4
i:42	#: 599	cycles: 599000010	ms: 2995.000050	ADC: 2044	eyecatch: a4a4a4a4
i:43	#: 600	cycles: 600000013	ms: 3000.000065	ADC: 2048	eyecatch: a4a4a4a4
i:44	#: 601	cycles: 601000012	ms: 3005.000060	ADC: 2045	eyecatch: a4a4a4a4
i:45	#: 602	cycles: 602000010	ms: 3010.000050	ADC: 2044	eyecatch: a4a4a4a4
i:46	#: 603	cycles: 603000013	ms: 3015.000065	ADC: 2044	eyecatch: a4a4a4a4
i:47	#: 604	cycles: 604000012	ms: 3020.000060	ADC: 2045	eyecatch: a4a4a4a4
i:48	#: 605	cycles: 605000010	ms: 3025.000050	ADC: 2045	eyecatch: a4a4a4a4
i:49	#: 606	cycles: 606000013	ms: 3030.000065	ADC: 2046	eyecatch: a4a4a4a4
i:50	#: 607	cycles: 607000012	ms: 3035.000060	ADC: 2044	eyecatch: a4a4a4a4
i:51	#: 608	cycles: 608000010	ms: 3040.000050	ADC: 2045	eyecatch: a4a4a4a4
i:52	#: 609	cycles: 609000013	ms: 3045.000065	ADC: 2048	eyecatch: a4a4a4a4
i:53	#: 610	cycles: 610000012	ms: 3050.000060	ADC: 2045	eyecatch: a4a4a4a4
i:54	#: 611	cycles: 611000010	ms: 3055.000050	ADC: 2048	eyecatch: a4a4a4a4
i:55	#: 612	cycles: 612000013	ms: 3060.000065	ADC: 2048	eyecatch: a4a4a4a4
i:56	#: 613	cycles: 613000012	ms: 3065.000060	ADC: 2044	eyecatch: a4a4a4a4
i:57	#: 614	cycles: 614000010	ms: 3070.000050	ADC: 2045	eyecatch: a4a4a4a4
i:58	#: 615	cycles: 615000013	ms: 3075.000065	ADC: 2044	eyecatch: a4a4a4a4
i:59	#: 616	cycles: 616000012	ms: 3080.000060	ADC: 2045	eyecatch: a4a4a4a4
i:60	#: 617	cycles: 617000010	ms: 3085.000050	ADC: 2044	eyecatch: a4a4a4a4
i:61	#: 618	cycles: 618000013	ms: 3090.000065	ADC: 2045	eyecatch: a4a4a4a4
i:62	#: 619	cycles: 619000012	ms: 3095.000060	ADC: 2044	eyecatch: a4a4a4a4
i:63	#: 620	cycles: 620000010	ms: 3100.000050	ADC: 2045	eyecatch: a4a4a4a4
Waiting for "Data ready" bit...
Got it!
i:0	#: 767	cycles: 767000012	ms: 3835.000060	ADC: 2045	eyecatch: a4a4a4a4
i:1	#: 768	cycles: 768000010	ms: 3840.000050	ADC: 2048	eyecatch: a4a4a4a4
i:2	#: 769	cycles: 769000011	ms: 3845.000055	ADC: 2046	eyecatch: a4a4a4a4
i:3	#: 770	cycles: 770000010	ms: 3850.000050	ADC: 2045	eyecatch: a4a4a4a4
i:4	#: 771	cycles: 771000013	ms: 3855.000065	ADC: 2045	eyecatch: a4a4a4a4
i:5	#: 772	cycles: 772000012	ms: 3860.000060	ADC: 2048	eyecatch: a4a4a4a4
i:6	#: 773	cycles: 773000010	ms: 3865.000050	ADC: 2045	eyecatch: a4a4a4a4
i:7	#: 774	cycles: 774000013	ms: 3870.000065	ADC: 2045	eyecatch: a4a4a4a4
i:8	#: 775	cycles: 775000012	ms: 3875.000060	ADC: 2044	eyecatch: a4a4a4a4
i:9	#: 776	cycles: 776000010	ms: 3880.000050	ADC: 2045	eyecatch: a4a4a4a4
i:10	#: 777	cycles: 777000013	ms: 3885.000065	ADC: 2044	eyecatch: a4a4a4a4
i:11	#: 778	cycles: 778000012	ms: 3890.000060	ADC: 2044	eyecatch: a4a4a4a4
i:12	#: 779	cycles: 779000010	ms: 3895.000050	ADC: 2045	eyecatch: a4a4a4a4
i:13	#: 780	cycles: 780000013	ms: 3900.000065	ADC: 2044	eyecatch: a4a4a4a4
i:14	#: 781	cycles: 781000012	ms: 3905.000060	ADC: 2045	eyecatch: a4a4a4a4
i:15	#: 782	cycles: 782000010	ms: 3910.000050	ADC: 2044	eyecatch: a4a4a4a4
i:16	#: 783	cycles: 783000013	ms: 3915.000065	ADC: 2045	eyecatch: a4a4a4a4
i:17	#: 784	cycles: 784000012	ms: 3920.000060	ADC: 2045	eyecatch: a4a4a4a4
i:18	#: 785	cycles: 785000010	ms: 3925.000050	ADC: 2044	eyecatch: a4a4a4a4
i:19	#: 786	cycles: 786000013	ms: 3930.000065	ADC: 2044	eyecatch: a4a4a4a4
i:20	#: 787	cycles: 787000012	ms: 3935.000060	ADC: 2043	eyecatch: a4a4a4a4
i:21	#: 788	cycles: 788000010	ms: 3940.000050	ADC: 2048	eyecatch: a4a4a4a4
i:22	#: 789	cycles: 789000013	ms: 3945.000065	ADC: 2044	eyecatch: a4a4a4a4
i:23	#: 790	cycles: 790000012	ms: 3950.000060	ADC: 2045	eyecatch: a4a4a4a4
i:24	#: 791	cycles: 791000010	ms: 3955.000050	ADC: 2044	eyecatch: a4a4a4a4
i:25	#: 792	cycles: 792000013	ms: 3960.000065	ADC: 2045	eyecatch: a4a4a4a4
i:26	#: 793	cycles: 793000012	ms: 3965.000060	ADC: 2045	eyecatch: a4a4a4a4
i:27	#: 794	cycles: 794000010	ms: 3970.000050	ADC: 2045	eyecatch: a4a4a4a4
i:28	#: 795	cycles: 795000013	ms: 3975.000065	ADC: 2045	eyecatch: a4a4a4a4
i:29	#: 796	cycles: 796000012	ms: 3980.000060	ADC: 2044	eyecatch: a4a4a4a4
i:30	#: 797	cycles: 797000010	ms: 3985.000050	ADC: 2044	eyecatch: a4a4a4a4
i:31	#: 798	cycles: 798000013	ms: 3990.000065	ADC: 2044	eyecatch: a4a4a4a4
i:32	#: 799	cycles: 799000012	ms: 3995.000060	ADC: 2045	eyecatch: a4a4a4a4
i:33	#: 800	cycles: 800000010	ms: 4000.000050	ADC: 2045	eyecatch: a4a4a4a4
i:34	#: 801	cycles: 801000013	ms: 4005.000065	ADC: 2045	eyecatch: a4a4a4a4
i:35	#: 802	cycles: 802000012	ms: 4010.000060	ADC: 2042	eyecatch: a4a4a4a4
i:36	#: 803	cycles: 803000010	ms: 4015.000050	ADC: 2045	eyecatch: a4a4a4a4
i:37	#: 804	cycles: 804000013	ms: 4020.000065	ADC: 2045	eyecatch: a4a4a4a4
i:38	#: 805	cycles: 805000012	ms: 4025.000060	ADC: 2046	eyecatch: a4a4a4a4
i:39	#: 806	cycles: 806000010	ms: 4030.000050	ADC: 2044	eyecatch: a4a4a4a4
i:40	#: 807	cycles: 807000013	ms: 4035.000065	ADC: 2044	eyecatch: a4a4a4a4
i:41	#: 808	cycles: 808000012	ms: 4040.000060	ADC: 2045	eyecatch: a4a4a4a4
i:42	#: 809	cycles: 809000010	ms: 4045.000050	ADC: 2045	eyecatch: a4a4a4a4
i:43	#: 810	cycles: 810000013	ms: 4050.000065	ADC: 2045	eyecatch: a4a4a4a4
i:44	#: 811	cycles: 811000012	ms: 4055.000060	ADC: 2044	eyecatch: a4a4a4a4
i:45	#: 812	cycles: 812000010	ms: 4060.000050	ADC: 2045	eyecatch: a4a4a4a4
i:46	#: 813	cycles: 813000013	ms: 4065.000065	ADC: 2045	eyecatch: a4a4a4a4
i:47	#: 814	cycles: 814000012	ms: 4070.000060	ADC: 2044	eyecatch: a4a4a4a4
i:48	#: 815	cycles: 815000010	ms: 4075.000050	ADC: 2044	eyecatch: a4a4a4a4
i:49	#: 816	cycles: 816000013	ms: 4080.000065	ADC: 2045	eyecatch: a4a4a4a4
i:50	#: 817	cycles: 817000012	ms: 4085.000060	ADC: 2044	eyecatch: a4a4a4a4
i:51	#: 818	cycles: 818000010	ms: 4090.000050	ADC: 2044	eyecatch: a4a4a4a4
i:52	#: 819	cycles: 819000013	ms: 4095.000065	ADC: 2045	eyecatch: a4a4a4a4
i:53	#: 820	cycles: 820000012	ms: 4100.000060	ADC: 2045	eyecatch: a4a4a4a4
i:54	#: 821	cycles: 821000010	ms: 4105.000050	ADC: 2048	eyecatch: a4a4a4a4
i:55	#: 822	cycles: 822000013	ms: 4110.000065	ADC: 2044	eyecatch: a4a4a4a4
i:56	#: 823	cycles: 823000012	ms: 4115.000060	ADC: 2045	eyecatch: a4a4a4a4
i:57	#: 824	cycles: 824000010	ms: 4120.000050	ADC: 2048	eyecatch: a4a4a4a4
i:58	#: 825	cycles: 825000013	ms: 4125.000065	ADC: 2045	eyecatch: a4a4a4a4
i:59	#: 826	cycles: 826000012	ms: 4130.000060	ADC: 2044	eyecatch: a4a4a4a4
i:60	#: 827	cycles: 827000010	ms: 4135.000050	ADC: 2044	eyecatch: a4a4a4a4
i:61	#: 828	cycles: 828000013	ms: 4140.000065	ADC: 2043	eyecatch: a4a4a4a4
i:62	#: 829	cycles: 829000012	ms: 4145.000060	ADC: 2046	eyecatch: a4a4a4a4
i:63	#: 830	cycles: 830000010	ms: 4150.000050	ADC: 2045	eyecatch: a4a4a4a4
Waiting for "Data ready" bit...
Got it!
i:0	#: 977	cycles: 977000013	ms: 4885.000065	ADC: 2044	eyecatch: a4a4a4a4
i:1	#: 978	cycles: 978000012	ms: 4890.000060	ADC: 2044	eyecatch: a4a4a4a4
i:2	#: 979	cycles: 979000010	ms: 4895.000050	ADC: 2045	eyecatch: a4a4a4a4
i:3	#: 980	cycles: 980000013	ms: 4900.000065	ADC: 2048	eyecatch: a4a4a4a4
i:4	#: 981	cycles: 981000012	ms: 4905.000060	ADC: 2044	eyecatch: a4a4a4a4
i:5	#: 982	cycles: 982000010	ms: 4910.000050	ADC: 2045	eyecatch: a4a4a4a4
i:6	#: 983	cycles: 983000013	ms: 4915.000065	ADC: 2048	eyecatch: a4a4a4a4
i:7	#: 984	cycles: 984000012	ms: 4920.000060	ADC: 2044	eyecatch: a4a4a4a4
i:8	#: 985	cycles: 985000010	ms: 4925.000050	ADC: 2045	eyecatch: a4a4a4a4
i:9	#: 986	cycles: 986000013	ms: 4930.000065	ADC: 2045	eyecatch: a4a4a4a4
i:10	#: 987	cycles: 987000012	ms: 4935.000060	ADC: 2043	eyecatch: a4a4a4a4
i:11	#: 988	cycles: 988000010	ms: 4940.000050	ADC: 2045	eyecatch: a4a4a4a4
i:12	#: 989	cycles: 989000013	ms: 4945.000065	ADC: 2044	eyecatch: a4a4a4a4
i:13	#: 990	cycles: 990000012	ms: 4950.000060	ADC: 2044	eyecatch: a4a4a4a4
i:14	#: 991	cycles: 991000010	ms: 4955.000050	ADC: 2045	eyecatch: a4a4a4a4
i:15	#: 992	cycles: 992000013	ms: 4960.000065	ADC: 2044	eyecatch: a4a4a4a4
i:16	#: 993	cycles: 993000012	ms: 4965.000060	ADC: 2045	eyecatch: a4a4a4a4
i:17	#: 994	cycles: 994000010	ms: 4970.000050	ADC: 2045	eyecatch: a4a4a4a4
i:18	#: 995	cycles: 995000013	ms: 4975.000065	ADC: 2047	eyecatch: a4a4a4a4
i:19	#: 996	cycles: 996000012	ms: 4980.000060	ADC: 2044	eyecatch: a4a4a4a4
i:20	#: 997	cycles: 997000010	ms: 4985.000050	ADC: 2045	eyecatch: a4a4a4a4
i:21	#: 998	cycles: 998000013	ms: 4990.000065	ADC: 2045	eyecatch: a4a4a4a4
i:22	#: 999	cycles: 999000012	ms: 4995.000060	ADC: 2046	eyecatch: a4a4a4a4
i:23	#: 1000	cycles: 1000000010	ms: 5000.000050	ADC: 2045	eyecatch: a4a4a4a4
i:24	#: 1001	cycles: 1001000013	ms: 5005.000065	ADC: 2045	eyecatch: a4a4a4a4
i:25	#: 1002	cycles: 1002000012	ms: 5010.000060	ADC: 2044	eyecatch: a4a4a4a4
i:26	#: 1003	cycles: 1003000010	ms: 5015.000050	ADC: 2045	eyecatch: a4a4a4a4
i:27	#: 1004	cycles: 1004000013	ms: 5020.000065	ADC: 2045	eyecatch: a4a4a4a4
i:28	#: 1005	cycles: 1005000012	ms: 5025.000060	ADC: 2047	eyecatch: a4a4a4a4
i:29	#: 1006	cycles: 1006000010	ms: 5030.000050	ADC: 2044	eyecatch: a4a4a4a4
i:30	#: 1007	cycles: 1007000013	ms: 5035.000065	ADC: 2044	eyecatch: a4a4a4a4
i:31	#: 1008	cycles: 1008000012	ms: 5040.000060	ADC: 2044	eyecatch: a4a4a4a4
i:32	#: 1009	cycles: 1009000010	ms: 5045.000050	ADC: 2044	eyecatch: a4a4a4a4
i:33	#: 1010	cycles: 1010000013	ms: 5050.000065	ADC: 2044	eyecatch: a4a4a4a4
i:34	#: 1011	cycles: 1011000012	ms: 5055.000060	ADC: 2048	eyecatch: a4a4a4a4
i:35	#: 1012	cycles: 1012000010	ms: 5060.000050	ADC: 2044	eyecatch: a4a4a4a4
i:36	#: 1013	cycles: 1013000013	ms: 5065.000065	ADC: 2044	eyecatch: a4a4a4a4
i:37	#: 1014	cycles: 1014000012	ms: 5070.000060	ADC: 2048	eyecatch: a4a4a4a4
i:38	#: 1015	cycles: 1015000010	ms: 5075.000050	ADC: 2045	eyecatch: a4a4a4a4
i:39	#: 1016	cycles: 1016000013	ms: 5080.000065	ADC: 2045	eyecatch: a4a4a4a4
i:40	#: 1017	cycles: 1017000012	ms: 5085.000060	ADC: 2046	eyecatch: a4a4a4a4
i:41	#: 1018	cycles: 1018000010	ms: 5090.000050	ADC: 2045	eyecatch: a4a4a4a4
i:42	#: 1019	cycles: 1019000013	ms: 5095.000065	ADC: 2044	eyecatch: a4a4a4a4
i:43	#: 1020	cycles: 1020000012	ms: 5100.000060	ADC: 2048	eyecatch: a4a4a4a4
i:44	#: 1021	cycles: 1021000010	ms: 5105.000050	ADC: 2048	eyecatch: a4a4a4a4
i:45	#: 1022	cycles: 1022000013	ms: 5110.000065	ADC: 2046	eyecatch: a4a4a4a4
i:46	#: 1023	cycles: 1023000012	ms: 5115.000060	ADC: 2045	eyecatch: a4a4a4a4
i:47	#: 1024	cycles: 1024000010	ms: 5120.000050	ADC: 2045	eyecatch: a4a4a4a4
i:48	#: 1025	cycles: 1025000011	ms: 5125.000055	ADC: 2044	eyecatch: a4a4a4a4
i:49	#: 1026	cycles: 1026000010	ms: 5130.000050	ADC: 2044	eyecatch: a4a4a4a4
i:50	#: 1027	cycles: 1027000013	ms: 5135.000065	ADC: 2044	eyecatch: a4a4a4a4
i:51	#: 1028	cycles: 1028000012	ms: 5140.000060	ADC: 2048	eyecatch: a4a4a4a4
i:52	#: 1029	cycles: 1029000010	ms: 5145.000050	ADC: 2044	eyecatch: a4a4a4a4
i:53	#: 1030	cycles: 1030000013	ms: 5150.000065	ADC: 2045	eyecatch: a4a4a4a4
i:54	#: 1031	cycles: 1031000012	ms: 5155.000060	ADC: 2045	eyecatch: a4a4a4a4
i:55	#: 1032	cycles: 1032000010	ms: 5160.000050	ADC: 2045	eyecatch: a4a4a4a4
i:56	#: 1033	cycles: 1033000013	ms: 5165.000065	ADC: 2044	eyecatch: a4a4a4a4
i:57	#: 1034	cycles: 1034000012	ms: 5170.000060	ADC: 2045	eyecatch: a4a4a4a4
i:58	#: 1035	cycles: 1035000010	ms: 5175.000050	ADC: 2045	eyecatch: a4a4a4a4
i:59	#: 1036	cycles: 1036000013	ms: 5180.000065	ADC: 2044	eyecatch: a4a4a4a4
i:60	#: 1037	cycles: 1037000012	ms: 5185.000060	ADC: 2043	eyecatch: a4a4a4a4
i:61	#: 1038	cycles: 1038000010	ms: 5190.000050	ADC: 2045	eyecatch: a4a4a4a4
i:62	#: 1039	cycles: 1039000013	ms: 5195.000065	ADC: 2046	eyecatch: a4a4a4a4
i:63	#: 1040	cycles: 1040000012	ms: 5200.000060	ADC: 2044	eyecatch: a4a4a4a4
Shutting down.
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# 






You can see that the CPU is missing samples between its two queries,
because it waited for a second between them. If the CPU pauses less,
like 20ms between asking, the two 64-sample buffers will overlap.




CPU 20ms-pause between asking:



root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# !!
./run
I'm in: 
/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list
Building .bin file cpu-reads-adc.p


PRU Assembler Version 0.84
Copyright (C) 2005-2013 by Texas Instruments Inc.


Pass 2 : 0 Error(s), 0 Warning(s)

Writing Code Image of 144 word(s)

Building .c file cpu-reads-adc.c to make cpu-reads-adc
(Careful - does your .c load the correct .p / .bin?)
Running cpu-reads-adc
Hey, if you get a seg fault, make sure the EBB-PRU-Example device tree overlay has been loaded!!
Here's the cmd: root@beaglebone:/home/debian/beaglebone_pru_adc/src# echo EBB-PRU-Example > /sys/devices/bone_capemgr.9/slots
executing bin file: ./cpu-reads-adc.bin
Waiting for "Data ready" bit...
Got it!
i:0	#: 138	cycles: 138000010	ms: 690.000050	ADC: 2045	eyecatch: a4a4a4a4
i:1	#: 139	cycles: 139000013	ms: 695.000065	ADC: 2044	eyecatch: a4a4a4a4
i:2	#: 140	cycles: 140000012	ms: 700.000060	ADC: 2046	eyecatch: a4a4a4a4
i:3	#: 141	cycles: 141000010	ms: 705.000050	ADC: 2045	eyecatch: a4a4a4a4
i:4	#: 142	cycles: 142000013	ms: 710.000065	ADC: 2045	eyecatch: a4a4a4a4
i:5	#: 143	cycles: 143000012	ms: 715.000060	ADC: 2044	eyecatch: a4a4a4a4
i:6	#: 144	cycles: 144000010	ms: 720.000050	ADC: 2045	eyecatch: a4a4a4a4
i:7	#: 145	cycles: 145000013	ms: 725.000065	ADC: 2044	eyecatch: a4a4a4a4
i:8	#: 146	cycles: 146000012	ms: 730.000060	ADC: 2045	eyecatch: a4a4a4a4
i:9	#: 147	cycles: 147000010	ms: 735.000050	ADC: 2045	eyecatch: a4a4a4a4
i:10	#: 148	cycles: 148000013	ms: 740.000065	ADC: 2048	eyecatch: a4a4a4a4
i:11	#: 149	cycles: 149000012	ms: 745.000060	ADC: 2044	eyecatch: a4a4a4a4
i:12	#: 150	cycles: 150000010	ms: 750.000050	ADC: 2046	eyecatch: a4a4a4a4
i:13	#: 151	cycles: 151000013	ms: 755.000065	ADC: 2044	eyecatch: a4a4a4a4
i:14	#: 152	cycles: 152000012	ms: 760.000060	ADC: 2044	eyecatch: a4a4a4a4
i:15	#: 153	cycles: 153000010	ms: 765.000050	ADC: 2045	eyecatch: a4a4a4a4
i:16	#: 154	cycles: 154000013	ms: 770.000065	ADC: 2044	eyecatch: a4a4a4a4
i:17	#: 155	cycles: 155000012	ms: 775.000060	ADC: 2045	eyecatch: a4a4a4a4
i:18	#: 156	cycles: 156000010	ms: 780.000050	ADC: 2045	eyecatch: a4a4a4a4
i:19	#: 157	cycles: 157000013	ms: 785.000065	ADC: 2043	eyecatch: a4a4a4a4
i:20	#: 158	cycles: 158000012	ms: 790.000060	ADC: 2045	eyecatch: a4a4a4a4
i:21	#: 159	cycles: 159000010	ms: 795.000050	ADC: 2044	eyecatch: a4a4a4a4
i:22	#: 160	cycles: 160000013	ms: 800.000065	ADC: 2044	eyecatch: a4a4a4a4
i:23	#: 161	cycles: 161000012	ms: 805.000060	ADC: 2044	eyecatch: a4a4a4a4
i:24	#: 162	cycles: 162000010	ms: 810.000050	ADC: 2044	eyecatch: a4a4a4a4
i:25	#: 163	cycles: 163000013	ms: 815.000065	ADC: 2044	eyecatch: a4a4a4a4
i:26	#: 164	cycles: 164000012	ms: 820.000060	ADC: 2044	eyecatch: a4a4a4a4
i:27	#: 165	cycles: 165000010	ms: 825.000050	ADC: 2045	eyecatch: a4a4a4a4
i:28	#: 166	cycles: 166000013	ms: 830.000065	ADC: 2045	eyecatch: a4a4a4a4
i:29	#: 167	cycles: 167000012	ms: 835.000060	ADC: 2048	eyecatch: a4a4a4a4
i:30	#: 168	cycles: 168000010	ms: 840.000050	ADC: 2044	eyecatch: a4a4a4a4
i:31	#: 169	cycles: 169000013	ms: 845.000065	ADC: 2045	eyecatch: a4a4a4a4
i:32	#: 170	cycles: 170000012	ms: 850.000060	ADC: 2045	eyecatch: a4a4a4a4
i:33	#: 171	cycles: 171000010	ms: 855.000050	ADC: 2045	eyecatch: a4a4a4a4
i:34	#: 172	cycles: 172000013	ms: 860.000065	ADC: 2048	eyecatch: a4a4a4a4
i:35	#: 173	cycles: 173000012	ms: 865.000060	ADC: 2044	eyecatch: a4a4a4a4
i:36	#: 174	cycles: 174000010	ms: 870.000050	ADC: 2043	eyecatch: a4a4a4a4
i:37	#: 175	cycles: 175000013	ms: 875.000065	ADC: 2043	eyecatch: a4a4a4a4
i:38	#: 176	cycles: 176000012	ms: 880.000060	ADC: 2045	eyecatch: a4a4a4a4
i:39	#: 177	cycles: 177000010	ms: 885.000050	ADC: 2044	eyecatch: a4a4a4a4
i:40	#: 178	cycles: 178000013	ms: 890.000065	ADC: 2045	eyecatch: a4a4a4a4
i:41	#: 179	cycles: 179000012	ms: 895.000060	ADC: 2044	eyecatch: a4a4a4a4
i:42	#: 180	cycles: 180000010	ms: 900.000050	ADC: 2044	eyecatch: a4a4a4a4
i:43	#: 181	cycles: 181000013	ms: 905.000065	ADC: 2044	eyecatch: a4a4a4a4
i:44	#: 182	cycles: 182000012	ms: 910.000060	ADC: 2044	eyecatch: a4a4a4a4
i:45	#: 183	cycles: 183000010	ms: 915.000050	ADC: 2044	eyecatch: a4a4a4a4
i:46	#: 184	cycles: 184000013	ms: 920.000065	ADC: 2044	eyecatch: a4a4a4a4
i:47	#: 185	cycles: 185000012	ms: 925.000060	ADC: 2044	eyecatch: a4a4a4a4
i:48	#: 186	cycles: 186000010	ms: 930.000050	ADC: 2044	eyecatch: a4a4a4a4
i:49	#: 187	cycles: 187000013	ms: 935.000065	ADC: 2044	eyecatch: a4a4a4a4
i:50	#: 188	cycles: 188000012	ms: 940.000060	ADC: 2045	eyecatch: a4a4a4a4
i:51	#: 189	cycles: 189000010	ms: 945.000050	ADC: 2045	eyecatch: a4a4a4a4
i:52	#: 190	cycles: 190000013	ms: 950.000065	ADC: 2044	eyecatch: a4a4a4a4
i:53	#: 191	cycles: 191000012	ms: 955.000060	ADC: 2044	eyecatch: a4a4a4a4
i:54	#: 192	cycles: 192000010	ms: 960.000050	ADC: 2044	eyecatch: a4a4a4a4
i:55	#: 193	cycles: 193000011	ms: 965.000055	ADC: 2044	eyecatch: a4a4a4a4
i:56	#: 194	cycles: 194000010	ms: 970.000050	ADC: 2044	eyecatch: a4a4a4a4
i:57	#: 195	cycles: 195000013	ms: 975.000065	ADC: 2046	eyecatch: a4a4a4a4
i:58	#: 196	cycles: 196000012	ms: 980.000060	ADC: 2044	eyecatch: a4a4a4a4
i:59	#: 197	cycles: 197000010	ms: 985.000050	ADC: 2044	eyecatch: a4a4a4a4
i:60	#: 198	cycles: 198000013	ms: 990.000065	ADC: 2044	eyecatch: a4a4a4a4
i:61	#: 199	cycles: 199000012	ms: 995.000060	ADC: 2045	eyecatch: a4a4a4a4
i:62	#: 200	cycles: 200000010	ms: 1000.000050	ADC: 2045	eyecatch: a4a4a4a4
i:63	#: 201	cycles: 201000013	ms: 1005.000065	ADC: 2044	eyecatch: a4a4a4a4
Waiting for "Data ready" bit...
Got it!
i:0	#: 152	cycles: 152000012	ms: 760.000060	ADC: 2044	eyecatch: a4a4a4a4
i:1	#: 153	cycles: 153000010	ms: 765.000050	ADC: 2045	eyecatch: a4a4a4a4
i:2	#: 154	cycles: 154000013	ms: 770.000065	ADC: 2044	eyecatch: a4a4a4a4
i:3	#: 155	cycles: 155000012	ms: 775.000060	ADC: 2045	eyecatch: a4a4a4a4
i:4	#: 156	cycles: 156000010	ms: 780.000050	ADC: 2045	eyecatch: a4a4a4a4
i:5	#: 157	cycles: 157000013	ms: 785.000065	ADC: 2043	eyecatch: a4a4a4a4
i:6	#: 158	cycles: 158000012	ms: 790.000060	ADC: 2045	eyecatch: a4a4a4a4
i:7	#: 159	cycles: 159000010	ms: 795.000050	ADC: 2044	eyecatch: a4a4a4a4
i:8	#: 160	cycles: 160000013	ms: 800.000065	ADC: 2044	eyecatch: a4a4a4a4
i:9	#: 161	cycles: 161000012	ms: 805.000060	ADC: 2044	eyecatch: a4a4a4a4
i:10	#: 162	cycles: 162000010	ms: 810.000050	ADC: 2044	eyecatch: a4a4a4a4
i:11	#: 163	cycles: 163000013	ms: 815.000065	ADC: 2044	eyecatch: a4a4a4a4
i:12	#: 164	cycles: 164000012	ms: 820.000060	ADC: 2044	eyecatch: a4a4a4a4
i:13	#: 165	cycles: 165000010	ms: 825.000050	ADC: 2045	eyecatch: a4a4a4a4
i:14	#: 166	cycles: 166000013	ms: 830.000065	ADC: 2045	eyecatch: a4a4a4a4
i:15	#: 167	cycles: 167000012	ms: 835.000060	ADC: 2048	eyecatch: a4a4a4a4
i:16	#: 168	cycles: 168000010	ms: 840.000050	ADC: 2044	eyecatch: a4a4a4a4
i:17	#: 169	cycles: 169000013	ms: 845.000065	ADC: 2045	eyecatch: a4a4a4a4
i:18	#: 170	cycles: 170000012	ms: 850.000060	ADC: 2045	eyecatch: a4a4a4a4
i:19	#: 171	cycles: 171000010	ms: 855.000050	ADC: 2045	eyecatch: a4a4a4a4
i:20	#: 172	cycles: 172000013	ms: 860.000065	ADC: 2048	eyecatch: a4a4a4a4
i:21	#: 173	cycles: 173000012	ms: 865.000060	ADC: 2044	eyecatch: a4a4a4a4
i:22	#: 174	cycles: 174000010	ms: 870.000050	ADC: 2043	eyecatch: a4a4a4a4
i:23	#: 175	cycles: 175000013	ms: 875.000065	ADC: 2043	eyecatch: a4a4a4a4
i:24	#: 176	cycles: 176000012	ms: 880.000060	ADC: 2045	eyecatch: a4a4a4a4
i:25	#: 177	cycles: 177000010	ms: 885.000050	ADC: 2044	eyecatch: a4a4a4a4
i:26	#: 178	cycles: 178000013	ms: 890.000065	ADC: 2045	eyecatch: a4a4a4a4
i:27	#: 179	cycles: 179000012	ms: 895.000060	ADC: 2044	eyecatch: a4a4a4a4
i:28	#: 180	cycles: 180000010	ms: 900.000050	ADC: 2044	eyecatch: a4a4a4a4
i:29	#: 181	cycles: 181000013	ms: 905.000065	ADC: 2044	eyecatch: a4a4a4a4
i:30	#: 182	cycles: 182000012	ms: 910.000060	ADC: 2044	eyecatch: a4a4a4a4
i:31	#: 183	cycles: 183000010	ms: 915.000050	ADC: 2044	eyecatch: a4a4a4a4
i:32	#: 184	cycles: 184000013	ms: 920.000065	ADC: 2044	eyecatch: a4a4a4a4
i:33	#: 185	cycles: 185000012	ms: 925.000060	ADC: 2044	eyecatch: a4a4a4a4
i:34	#: 186	cycles: 186000010	ms: 930.000050	ADC: 2044	eyecatch: a4a4a4a4
i:35	#: 187	cycles: 187000013	ms: 935.000065	ADC: 2044	eyecatch: a4a4a4a4
i:36	#: 188	cycles: 188000012	ms: 940.000060	ADC: 2045	eyecatch: a4a4a4a4
i:37	#: 189	cycles: 189000010	ms: 945.000050	ADC: 2045	eyecatch: a4a4a4a4
i:38	#: 190	cycles: 190000013	ms: 950.000065	ADC: 2044	eyecatch: a4a4a4a4
i:39	#: 191	cycles: 191000012	ms: 955.000060	ADC: 2044	eyecatch: a4a4a4a4
i:40	#: 192	cycles: 192000010	ms: 960.000050	ADC: 2044	eyecatch: a4a4a4a4
i:41	#: 193	cycles: 193000011	ms: 965.000055	ADC: 2044	eyecatch: a4a4a4a4
i:42	#: 194	cycles: 194000010	ms: 970.000050	ADC: 2044	eyecatch: a4a4a4a4
i:43	#: 195	cycles: 195000013	ms: 975.000065	ADC: 2046	eyecatch: a4a4a4a4
i:44	#: 196	cycles: 196000012	ms: 980.000060	ADC: 2044	eyecatch: a4a4a4a4
i:45	#: 197	cycles: 197000010	ms: 985.000050	ADC: 2044	eyecatch: a4a4a4a4
i:46	#: 198	cycles: 198000013	ms: 990.000065	ADC: 2044	eyecatch: a4a4a4a4
i:47	#: 199	cycles: 199000012	ms: 995.000060	ADC: 2045	eyecatch: a4a4a4a4
i:48	#: 200	cycles: 200000010	ms: 1000.000050	ADC: 2045	eyecatch: a4a4a4a4
i:49	#: 201	cycles: 201000013	ms: 1005.000065	ADC: 2044	eyecatch: a4a4a4a4
i:50	#: 202	cycles: 202000012	ms: 1010.000060	ADC: 2045	eyecatch: a4a4a4a4
i:51	#: 203	cycles: 203000010	ms: 1015.000050	ADC: 2044	eyecatch: a4a4a4a4
i:52	#: 204	cycles: 204000013	ms: 1020.000065	ADC: 2044	eyecatch: a4a4a4a4
i:53	#: 205	cycles: 205000012	ms: 1025.000060	ADC: 2044	eyecatch: a4a4a4a4
i:54	#: 206	cycles: 206000010	ms: 1030.000050	ADC: 2044	eyecatch: a4a4a4a4
i:55	#: 207	cycles: 207000013	ms: 1035.000065	ADC: 2044	eyecatch: a4a4a4a4
i:56	#: 208	cycles: 208000012	ms: 1040.000060	ADC: 2045	eyecatch: a4a4a4a4
i:57	#: 209	cycles: 209000010	ms: 1045.000050	ADC: 2045	eyecatch: a4a4a4a4
i:58	#: 210	cycles: 210000013	ms: 1050.000065	ADC: 2044	eyecatch: a4a4a4a4
i:59	#: 211	cycles: 211000012	ms: 1055.000060	ADC: 2044	eyecatch: a4a4a4a4
i:60	#: 212	cycles: 212000010	ms: 1060.000050	ADC: 2044	eyecatch: a4a4a4a4
i:61	#: 213	cycles: 213000013	ms: 1065.000065	ADC: 2044	eyecatch: a4a4a4a4
i:62	#: 214	cycles: 214000012	ms: 1070.000060	ADC: 2044	eyecatch: a4a4a4a4
i:63	#: 215	cycles: 215000010	ms: 1075.000050	ADC: 2046	eyecatch: a4a4a4a4
Waiting for "Data ready" bit...
Got it!
i:0	#: 166	cycles: 166000013	ms: 830.000065	ADC: 2045	eyecatch: a4a4a4a4
i:1	#: 167	cycles: 167000012	ms: 835.000060	ADC: 2048	eyecatch: a4a4a4a4
i:2	#: 168	cycles: 168000010	ms: 840.000050	ADC: 2044	eyecatch: a4a4a4a4
i:3	#: 169	cycles: 169000013	ms: 845.000065	ADC: 2045	eyecatch: a4a4a4a4
i:4	#: 170	cycles: 170000012	ms: 850.000060	ADC: 2045	eyecatch: a4a4a4a4
i:5	#: 171	cycles: 171000010	ms: 855.000050	ADC: 2045	eyecatch: a4a4a4a4
i:6	#: 172	cycles: 172000013	ms: 860.000065	ADC: 2048	eyecatch: a4a4a4a4
i:7	#: 173	cycles: 173000012	ms: 865.000060	ADC: 2044	eyecatch: a4a4a4a4
i:8	#: 174	cycles: 174000010	ms: 870.000050	ADC: 2043	eyecatch: a4a4a4a4
i:9	#: 175	cycles: 175000013	ms: 875.000065	ADC: 2043	eyecatch: a4a4a4a4
i:10	#: 176	cycles: 176000012	ms: 880.000060	ADC: 2045	eyecatch: a4a4a4a4
i:11	#: 177	cycles: 177000010	ms: 885.000050	ADC: 2044	eyecatch: a4a4a4a4
i:12	#: 178	cycles: 178000013	ms: 890.000065	ADC: 2045	eyecatch: a4a4a4a4
i:13	#: 179	cycles: 179000012	ms: 895.000060	ADC: 2044	eyecatch: a4a4a4a4
i:14	#: 180	cycles: 180000010	ms: 900.000050	ADC: 2044	eyecatch: a4a4a4a4
i:15	#: 181	cycles: 181000013	ms: 905.000065	ADC: 2044	eyecatch: a4a4a4a4
i:16	#: 182	cycles: 182000012	ms: 910.000060	ADC: 2044	eyecatch: a4a4a4a4
i:17	#: 183	cycles: 183000010	ms: 915.000050	ADC: 2044	eyecatch: a4a4a4a4
i:18	#: 184	cycles: 184000013	ms: 920.000065	ADC: 2044	eyecatch: a4a4a4a4
i:19	#: 185	cycles: 185000012	ms: 925.000060	ADC: 2044	eyecatch: a4a4a4a4
i:20	#: 186	cycles: 186000010	ms: 930.000050	ADC: 2044	eyecatch: a4a4a4a4
i:21	#: 187	cycles: 187000013	ms: 935.000065	ADC: 2044	eyecatch: a4a4a4a4
i:22	#: 188	cycles: 188000012	ms: 940.000060	ADC: 2045	eyecatch: a4a4a4a4
i:23	#: 189	cycles: 189000010	ms: 945.000050	ADC: 2045	eyecatch: a4a4a4a4
i:24	#: 190	cycles: 190000013	ms: 950.000065	ADC: 2044	eyecatch: a4a4a4a4
i:25	#: 191	cycles: 191000012	ms: 955.000060	ADC: 2044	eyecatch: a4a4a4a4
i:26	#: 192	cycles: 192000010	ms: 960.000050	ADC: 2044	eyecatch: a4a4a4a4
i:27	#: 193	cycles: 193000011	ms: 965.000055	ADC: 2044	eyecatch: a4a4a4a4
i:28	#: 194	cycles: 194000010	ms: 970.000050	ADC: 2044	eyecatch: a4a4a4a4
i:29	#: 195	cycles: 195000013	ms: 975.000065	ADC: 2046	eyecatch: a4a4a4a4
i:30	#: 196	cycles: 196000012	ms: 980.000060	ADC: 2044	eyecatch: a4a4a4a4
i:31	#: 197	cycles: 197000010	ms: 985.000050	ADC: 2044	eyecatch: a4a4a4a4
i:32	#: 198	cycles: 198000013	ms: 990.000065	ADC: 2044	eyecatch: a4a4a4a4
i:33	#: 199	cycles: 199000012	ms: 995.000060	ADC: 2045	eyecatch: a4a4a4a4
i:34	#: 200	cycles: 200000010	ms: 1000.000050	ADC: 2045	eyecatch: a4a4a4a4
i:35	#: 201	cycles: 201000013	ms: 1005.000065	ADC: 2044	eyecatch: a4a4a4a4
i:36	#: 202	cycles: 202000012	ms: 1010.000060	ADC: 2045	eyecatch: a4a4a4a4
i:37	#: 203	cycles: 203000010	ms: 1015.000050	ADC: 2044	eyecatch: a4a4a4a4
i:38	#: 204	cycles: 204000013	ms: 1020.000065	ADC: 2044	eyecatch: a4a4a4a4
i:39	#: 205	cycles: 205000012	ms: 1025.000060	ADC: 2044	eyecatch: a4a4a4a4
i:40	#: 206	cycles: 206000010	ms: 1030.000050	ADC: 2044	eyecatch: a4a4a4a4
i:41	#: 207	cycles: 207000013	ms: 1035.000065	ADC: 2044	eyecatch: a4a4a4a4
i:42	#: 208	cycles: 208000012	ms: 1040.000060	ADC: 2045	eyecatch: a4a4a4a4
i:43	#: 209	cycles: 209000010	ms: 1045.000050	ADC: 2045	eyecatch: a4a4a4a4
i:44	#: 210	cycles: 210000013	ms: 1050.000065	ADC: 2044	eyecatch: a4a4a4a4
i:45	#: 211	cycles: 211000012	ms: 1055.000060	ADC: 2044	eyecatch: a4a4a4a4
i:46	#: 212	cycles: 212000010	ms: 1060.000050	ADC: 2044	eyecatch: a4a4a4a4
i:47	#: 213	cycles: 213000013	ms: 1065.000065	ADC: 2044	eyecatch: a4a4a4a4
i:48	#: 214	cycles: 214000012	ms: 1070.000060	ADC: 2044	eyecatch: a4a4a4a4
i:49	#: 215	cycles: 215000010	ms: 1075.000050	ADC: 2046	eyecatch: a4a4a4a4
i:50	#: 216	cycles: 216000013	ms: 1080.000065	ADC: 2044	eyecatch: a4a4a4a4
i:51	#: 217	cycles: 217000012	ms: 1085.000060	ADC: 2044	eyecatch: a4a4a4a4
i:52	#: 218	cycles: 218000010	ms: 1090.000050	ADC: 2044	eyecatch: a4a4a4a4
i:53	#: 219	cycles: 219000013	ms: 1095.000065	ADC: 2045	eyecatch: a4a4a4a4
i:54	#: 220	cycles: 220000012	ms: 1100.000060	ADC: 2044	eyecatch: a4a4a4a4
i:55	#: 221	cycles: 221000010	ms: 1105.000050	ADC: 2048	eyecatch: a4a4a4a4
i:56	#: 222	cycles: 222000013	ms: 1110.000065	ADC: 2044	eyecatch: a4a4a4a4
i:57	#: 223	cycles: 223000012	ms: 1115.000060	ADC: 2048	eyecatch: a4a4a4a4
i:58	#: 224	cycles: 224000010	ms: 1120.000050	ADC: 2043	eyecatch: a4a4a4a4
i:59	#: 225	cycles: 225000013	ms: 1125.000065	ADC: 2043	eyecatch: a4a4a4a4
i:60	#: 226	cycles: 226000012	ms: 1130.000060	ADC: 2044	eyecatch: a4a4a4a4
i:61	#: 227	cycles: 227000010	ms: 1135.000050	ADC: 2045	eyecatch: a4a4a4a4
i:62	#: 228	cycles: 228000013	ms: 1140.000065	ADC: 2045	eyecatch: a4a4a4a4
i:63	#: 229	cycles: 229000012	ms: 1145.000060	ADC: 2044	eyecatch: a4a4a4a4
Waiting for "Data ready" bit...
Got it!
i:0	#: 198	cycles: 198000013	ms: 990.000065	ADC: 2044	eyecatch: a4a4a4a4
i:1	#: 199	cycles: 199000012	ms: 995.000060	ADC: 2045	eyecatch: a4a4a4a4
i:2	#: 200	cycles: 200000010	ms: 1000.000050	ADC: 2045	eyecatch: a4a4a4a4
i:3	#: 201	cycles: 201000013	ms: 1005.000065	ADC: 2044	eyecatch: a4a4a4a4
i:4	#: 202	cycles: 202000012	ms: 1010.000060	ADC: 2045	eyecatch: a4a4a4a4
i:5	#: 203	cycles: 203000010	ms: 1015.000050	ADC: 2044	eyecatch: a4a4a4a4
i:6	#: 204	cycles: 204000013	ms: 1020.000065	ADC: 2044	eyecatch: a4a4a4a4
i:7	#: 205	cycles: 205000012	ms: 1025.000060	ADC: 2044	eyecatch: a4a4a4a4
i:8	#: 206	cycles: 206000010	ms: 1030.000050	ADC: 2044	eyecatch: a4a4a4a4
i:9	#: 207	cycles: 207000013	ms: 1035.000065	ADC: 2044	eyecatch: a4a4a4a4
i:10	#: 208	cycles: 208000012	ms: 1040.000060	ADC: 2045	eyecatch: a4a4a4a4
i:11	#: 209	cycles: 209000010	ms: 1045.000050	ADC: 2045	eyecatch: a4a4a4a4
i:12	#: 210	cycles: 210000013	ms: 1050.000065	ADC: 2044	eyecatch: a4a4a4a4
i:13	#: 211	cycles: 211000012	ms: 1055.000060	ADC: 2044	eyecatch: a4a4a4a4
i:14	#: 212	cycles: 212000010	ms: 1060.000050	ADC: 2044	eyecatch: a4a4a4a4
i:15	#: 213	cycles: 213000013	ms: 1065.000065	ADC: 2044	eyecatch: a4a4a4a4
i:16	#: 214	cycles: 214000012	ms: 1070.000060	ADC: 2044	eyecatch: a4a4a4a4
i:17	#: 215	cycles: 215000010	ms: 1075.000050	ADC: 2046	eyecatch: a4a4a4a4
i:18	#: 216	cycles: 216000013	ms: 1080.000065	ADC: 2044	eyecatch: a4a4a4a4
i:19	#: 217	cycles: 217000012	ms: 1085.000060	ADC: 2044	eyecatch: a4a4a4a4
i:20	#: 218	cycles: 218000010	ms: 1090.000050	ADC: 2044	eyecatch: a4a4a4a4
i:21	#: 219	cycles: 219000013	ms: 1095.000065	ADC: 2045	eyecatch: a4a4a4a4
i:22	#: 220	cycles: 220000012	ms: 1100.000060	ADC: 2044	eyecatch: a4a4a4a4
i:23	#: 221	cycles: 221000010	ms: 1105.000050	ADC: 2048	eyecatch: a4a4a4a4
i:24	#: 222	cycles: 222000013	ms: 1110.000065	ADC: 2044	eyecatch: a4a4a4a4
i:25	#: 223	cycles: 223000012	ms: 1115.000060	ADC: 2048	eyecatch: a4a4a4a4
i:26	#: 224	cycles: 224000010	ms: 1120.000050	ADC: 2043	eyecatch: a4a4a4a4
i:27	#: 225	cycles: 225000013	ms: 1125.000065	ADC: 2043	eyecatch: a4a4a4a4
i:28	#: 226	cycles: 226000012	ms: 1130.000060	ADC: 2044	eyecatch: a4a4a4a4
i:29	#: 227	cycles: 227000010	ms: 1135.000050	ADC: 2045	eyecatch: a4a4a4a4
i:30	#: 228	cycles: 228000013	ms: 1140.000065	ADC: 2045	eyecatch: a4a4a4a4
i:31	#: 229	cycles: 229000012	ms: 1145.000060	ADC: 2044	eyecatch: a4a4a4a4
i:32	#: 230	cycles: 230000010	ms: 1150.000050	ADC: 2045	eyecatch: a4a4a4a4
i:33	#: 231	cycles: 231000013	ms: 1155.000065	ADC: 2043	eyecatch: a4a4a4a4
i:34	#: 232	cycles: 232000012	ms: 1160.000060	ADC: 2044	eyecatch: a4a4a4a4
i:35	#: 233	cycles: 233000010	ms: 1165.000050	ADC: 2045	eyecatch: a4a4a4a4
i:36	#: 234	cycles: 234000013	ms: 1170.000065	ADC: 2044	eyecatch: a4a4a4a4
i:37	#: 235	cycles: 235000012	ms: 1175.000060	ADC: 2045	eyecatch: a4a4a4a4
i:38	#: 236	cycles: 236000010	ms: 1180.000050	ADC: 2044	eyecatch: a4a4a4a4
i:39	#: 237	cycles: 237000013	ms: 1185.000065	ADC: 2044	eyecatch: a4a4a4a4
i:40	#: 238	cycles: 238000012	ms: 1190.000060	ADC: 2045	eyecatch: a4a4a4a4
i:41	#: 239	cycles: 239000010	ms: 1195.000050	ADC: 2044	eyecatch: a4a4a4a4
i:42	#: 240	cycles: 240000013	ms: 1200.000065	ADC: 2045	eyecatch: a4a4a4a4
i:43	#: 241	cycles: 241000012	ms: 1205.000060	ADC: 2045	eyecatch: a4a4a4a4
i:44	#: 242	cycles: 242000010	ms: 1210.000050	ADC: 2044	eyecatch: a4a4a4a4
i:45	#: 243	cycles: 243000013	ms: 1215.000065	ADC: 2044	eyecatch: a4a4a4a4
i:46	#: 244	cycles: 244000012	ms: 1220.000060	ADC: 2044	eyecatch: a4a4a4a4
i:47	#: 245	cycles: 245000010	ms: 1225.000050	ADC: 2045	eyecatch: a4a4a4a4
i:48	#: 246	cycles: 246000013	ms: 1230.000065	ADC: 2045	eyecatch: a4a4a4a4
i:49	#: 247	cycles: 247000012	ms: 1235.000060	ADC: 2044	eyecatch: a4a4a4a4
i:50	#: 248	cycles: 248000010	ms: 1240.000050	ADC: 2045	eyecatch: a4a4a4a4
i:51	#: 249	cycles: 249000013	ms: 1245.000065	ADC: 2044	eyecatch: a4a4a4a4
i:52	#: 250	cycles: 250000012	ms: 1250.000060	ADC: 2045	eyecatch: a4a4a4a4
i:53	#: 251	cycles: 251000010	ms: 1255.000050	ADC: 2044	eyecatch: a4a4a4a4
i:54	#: 252	cycles: 252000013	ms: 1260.000065	ADC: 2044	eyecatch: a4a4a4a4
i:55	#: 253	cycles: 253000012	ms: 1265.000060	ADC: 2045	eyecatch: a4a4a4a4
i:56	#: 254	cycles: 254000010	ms: 1270.000050	ADC: 2045	eyecatch: a4a4a4a4
i:57	#: 255	cycles: 255000013	ms: 1275.000065	ADC: 2045	eyecatch: a4a4a4a4
i:58	#: 256	cycles: 256000012	ms: 1280.000060	ADC: 2044	eyecatch: a4a4a4a4
i:59	#: 257	cycles: 257000013	ms: 1285.000065	ADC: 2044	eyecatch: a4a4a4a4
i:60	#: 258	cycles: 258000012	ms: 1290.000060	ADC: 2044	eyecatch: a4a4a4a4
i:61	#: 259	cycles: 259000010	ms: 1295.000050	ADC: 2044	eyecatch: a4a4a4a4
i:62	#: 260	cycles: 260000013	ms: 1300.000065	ADC: 2044	eyecatch: a4a4a4a4
i:63	#: 261	cycles: 261000012	ms: 1305.000060	ADC: 2044	eyecatch: a4a4a4a4
Waiting for "Data ready" bit...
Got it!
i:0	#: 250	cycles: 250000012	ms: 1250.000060	ADC: 2045	eyecatch: a4a4a4a4
i:1	#: 251	cycles: 251000010	ms: 1255.000050	ADC: 2044	eyecatch: a4a4a4a4
i:2	#: 252	cycles: 252000013	ms: 1260.000065	ADC: 2044	eyecatch: a4a4a4a4
i:3	#: 253	cycles: 253000012	ms: 1265.000060	ADC: 2045	eyecatch: a4a4a4a4
i:4	#: 254	cycles: 254000010	ms: 1270.000050	ADC: 2045	eyecatch: a4a4a4a4
i:5	#: 255	cycles: 255000013	ms: 1275.000065	ADC: 2045	eyecatch: a4a4a4a4
i:6	#: 256	cycles: 256000012	ms: 1280.000060	ADC: 2044	eyecatch: a4a4a4a4
i:7	#: 257	cycles: 257000013	ms: 1285.000065	ADC: 2044	eyecatch: a4a4a4a4
i:8	#: 258	cycles: 258000012	ms: 1290.000060	ADC: 2044	eyecatch: a4a4a4a4
i:9	#: 259	cycles: 259000010	ms: 1295.000050	ADC: 2044	eyecatch: a4a4a4a4
i:10	#: 260	cycles: 260000013	ms: 1300.000065	ADC: 2044	eyecatch: a4a4a4a4
i:11	#: 261	cycles: 261000012	ms: 1305.000060	ADC: 2044	eyecatch: a4a4a4a4
i:12	#: 262	cycles: 262000010	ms: 1310.000050	ADC: 2044	eyecatch: a4a4a4a4
i:13	#: 263	cycles: 263000013	ms: 1315.000065	ADC: 2044	eyecatch: a4a4a4a4
i:14	#: 264	cycles: 264000012	ms: 1320.000060	ADC: 2045	eyecatch: a4a4a4a4
i:15	#: 265	cycles: 265000010	ms: 1325.000050	ADC: 2044	eyecatch: a4a4a4a4
i:16	#: 266	cycles: 266000013	ms: 1330.000065	ADC: 2044	eyecatch: a4a4a4a4
i:17	#: 267	cycles: 267000012	ms: 1335.000060	ADC: 2045	eyecatch: a4a4a4a4
i:18	#: 268	cycles: 268000010	ms: 1340.000050	ADC: 2044	eyecatch: a4a4a4a4
i:19	#: 269	cycles: 269000013	ms: 1345.000065	ADC: 2045	eyecatch: a4a4a4a4
i:20	#: 270	cycles: 270000012	ms: 1350.000060	ADC: 2044	eyecatch: a4a4a4a4
i:21	#: 271	cycles: 271000010	ms: 1355.000050	ADC: 2045	eyecatch: a4a4a4a4
i:22	#: 272	cycles: 272000013	ms: 1360.000065	ADC: 2043	eyecatch: a4a4a4a4
i:23	#: 273	cycles: 273000012	ms: 1365.000060	ADC: 2044	eyecatch: a4a4a4a4
i:24	#: 274	cycles: 274000010	ms: 1370.000050	ADC: 2044	eyecatch: a4a4a4a4
i:25	#: 275	cycles: 275000013	ms: 1375.000065	ADC: 2048	eyecatch: a4a4a4a4
i:26	#: 276	cycles: 276000012	ms: 1380.000060	ADC: 2045	eyecatch: a4a4a4a4
i:27	#: 277	cycles: 277000010	ms: 1385.000050	ADC: 2044	eyecatch: a4a4a4a4
i:28	#: 278	cycles: 278000013	ms: 1390.000065	ADC: 2045	eyecatch: a4a4a4a4
i:29	#: 279	cycles: 279000012	ms: 1395.000060	ADC: 2044	eyecatch: a4a4a4a4
i:30	#: 280	cycles: 280000010	ms: 1400.000050	ADC: 2045	eyecatch: a4a4a4a4
i:31	#: 281	cycles: 281000013	ms: 1405.000065	ADC: 2045	eyecatch: a4a4a4a4
i:32	#: 282	cycles: 282000012	ms: 1410.000060	ADC: 2044	eyecatch: a4a4a4a4
i:33	#: 283	cycles: 283000010	ms: 1415.000050	ADC: 2044	eyecatch: a4a4a4a4
i:34	#: 284	cycles: 284000013	ms: 1420.000065	ADC: 2048	eyecatch: a4a4a4a4
i:35	#: 285	cycles: 285000012	ms: 1425.000060	ADC: 2045	eyecatch: a4a4a4a4
i:36	#: 286	cycles: 286000010	ms: 1430.000050	ADC: 2044	eyecatch: a4a4a4a4
i:37	#: 287	cycles: 287000013	ms: 1435.000065	ADC: 2044	eyecatch: a4a4a4a4
i:38	#: 288	cycles: 288000012	ms: 1440.000060	ADC: 2045	eyecatch: a4a4a4a4
i:39	#: 289	cycles: 289000010	ms: 1445.000050	ADC: 2044	eyecatch: a4a4a4a4
i:40	#: 290	cycles: 290000013	ms: 1450.000065	ADC: 2044	eyecatch: a4a4a4a4
i:41	#: 291	cycles: 291000012	ms: 1455.000060	ADC: 2047	eyecatch: a4a4a4a4
i:42	#: 292	cycles: 292000010	ms: 1460.000050	ADC: 2044	eyecatch: a4a4a4a4
i:43	#: 293	cycles: 293000013	ms: 1465.000065	ADC: 2045	eyecatch: a4a4a4a4
i:44	#: 294	cycles: 294000012	ms: 1470.000060	ADC: 2043	eyecatch: a4a4a4a4
i:45	#: 295	cycles: 295000010	ms: 1475.000050	ADC: 2045	eyecatch: a4a4a4a4
i:46	#: 296	cycles: 296000013	ms: 1480.000065	ADC: 2044	eyecatch: a4a4a4a4
i:47	#: 297	cycles: 297000012	ms: 1485.000060	ADC: 2045	eyecatch: a4a4a4a4
i:48	#: 298	cycles: 298000010	ms: 1490.000050	ADC: 2045	eyecatch: a4a4a4a4
i:49	#: 299	cycles: 299000013	ms: 1495.000065	ADC: 2044	eyecatch: a4a4a4a4
i:50	#: 300	cycles: 300000012	ms: 1500.000060	ADC: 2044	eyecatch: a4a4a4a4
i:51	#: 301	cycles: 301000010	ms: 1505.000050	ADC: 2044	eyecatch: a4a4a4a4
i:52	#: 302	cycles: 302000013	ms: 1510.000065	ADC: 2044	eyecatch: a4a4a4a4
i:53	#: 303	cycles: 303000012	ms: 1515.000060	ADC: 2044	eyecatch: a4a4a4a4
i:54	#: 304	cycles: 304000010	ms: 1520.000050	ADC: 2043	eyecatch: a4a4a4a4
i:55	#: 305	cycles: 305000013	ms: 1525.000065	ADC: 2044	eyecatch: a4a4a4a4
i:56	#: 306	cycles: 306000012	ms: 1530.000060	ADC: 2045	eyecatch: a4a4a4a4
i:57	#: 307	cycles: 307000010	ms: 1535.000050	ADC: 2044	eyecatch: a4a4a4a4
i:58	#: 308	cycles: 308000013	ms: 1540.000065	ADC: 2045	eyecatch: a4a4a4a4
i:59	#: 309	cycles: 309000012	ms: 1545.000060	ADC: 2044	eyecatch: a4a4a4a4
i:60	#: 310	cycles: 310000010	ms: 1550.000050	ADC: 2044	eyecatch: a4a4a4a4
i:61	#: 311	cycles: 311000013	ms: 1555.000065	ADC: 2048	eyecatch: a4a4a4a4
i:62	#: 312	cycles: 312000012	ms: 1560.000060	ADC: 2045	eyecatch: a4a4a4a4
i:63	#: 313	cycles: 313000010	ms: 1565.000050	ADC: 2045	eyecatch: a4a4a4a4
Shutting down.



//////////////////////////////////////////////////////////////////////



This was a huge pain to debug, but the pru debugger and gdb helped a lot. 

See how-to-debug-the-beaglebone-pru-assembly-code.ogv here:

2016-08-26 16:07:55 [roseline@roseline-controller-2 ~] 
$ ls -lstrah | tail
4.0K -rwxr-xr-x  1 roseline roseline  736 Aug 26 08:32 backup-BB
4.0K drwx------ 29 roseline roseline 4.0K Aug 26 09:05 .config
4.0K drwxrwxr-x  4 roseline roseline 4.0K Aug 26 09:11 BB_Backups
4.0K drwxr-xr-x  5 roseline roseline 4.0K Aug 26 10:03 Downloads
2.1M -rw-rw-r--  1 roseline roseline 2.1M Aug 26 10:58 out-5.ogv
800K -rw-rw-r--  1 roseline roseline 798K Aug 26 11:11 out-6.ogv
133M -rw-rw-r--  1 roseline roseline 133M Aug 26 13:33 how-to-debug-the-beaglebone-pru-assembly-code.ogv
4.0K -rw-rw-r--  1 roseline roseline 1.3K Aug 26 13:33 gtk-recordMyDesktop-crash.log
4.0K drwxr-xr-x 58 roseline roseline 4.0K Aug 26 14:08 .
 36K -rw-------  1 roseline roseline  36K Aug 26 14:32 .bash_history
2016-08-26 16:07:58 [roseline@roseline-controller-2 ~] 



////////////////////////////////////////////
// Warning about memory addresses




In the old days I thought:

	// note that addrs have units of 32-bits, not bytes.
	// ie, diff btwn addr 0x00000000 and 0x00000001 is 4 bytes, not 1 byte
	// note: confusingingly, in cmds like SBBO that take an offset, the
	// offset is given in bytes.
	// eg
	// MOV R1, 0xDEADBEEF // some value
	// MOV R2, 0x00000100 // start of some buffer
	// SBBO R1, R2, 12, 4 
	// now 0xDEADBEEF is 12 bytes (3 words = 3 ints) past addr 0x100,
	// at addr 0x103.

THis is wrong.

Fucking fuck, it turns out that pru data ram addresses have units of bytes,
but the pru debugger labels the data memory in units of words (4-bytes). This leads to confusion!

So if you do a cmd like "move the number 0xdeadbeef to address 0x101" like this assembly cmd

mov r1, 0xdeadbeef
mov r2, 0x00000101  // pru data ram addr 0x101
sbbo r1, r2, 0, 4

it shows up in the pru debugger in address 0x40, with a weird offset:

PRU0> d 0 1000
d 0 1000
Absolute addr = 0x0000, offset = 0x0000, Len = 1000
[0x0000] 0x00000000 0x11111111 0x11111111 0x11111111
[0x0004] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0008] 0x11111111 0x11111111 0x11111111 0x11111111
[0x000c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0010] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0014] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0018] 0x11111111 0x11111111 0x11111111 0x11111111
[0x001c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0020] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0024] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0028] 0x11111111 0x11111111 0x11111111 0x11111111
[0x002c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0030] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0034] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0038] 0x11111111 0x11111111 0x11111111 0x11111111
[0x003c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0040] 0xadbeef11 0x111111de 0x11111111 0x11111111  <--- here is our value.
[0x0044] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0048] 0x11111111 0x11111111 0x11111111 0x11111111
[0x004c] 0x11111111 0x11111111 0x11111111 0x11111111

when the pru dbgger says 0x0040, that's in 4-byte chunks, so it's actually 0x40 * 4 = 0x100 bytes from data ram addr 0. 

Moreover, we've moved the number "1" into address 0x101 (bytes), and since the debugger shows us u32's with <high-order bits> on the left and <low-order bits> on the right, the line

[0x0040] 0xadbeef11 0x111111de 0x11111111 0x11111111  <--- here is our value.

actually means that the number 0xdeadbeef has been inserted 0x101 bytes from the start, as desired.


	
However, in our C code, since our poitner to the data ram is an unsigned int (4-bytes),
incrementing that pointer will move it forward by 4 bytes. Jesus.


For example, here we are in the PRU debugger, about to write R21 (0x1) into addr R17 (0x101) (where 0x0 is pru data ram base), offset by R8 (0), and writing 4 bytes.

PRU0> gss
gss
Running (will run until a breakpoint is hit or a key is pressed)....

Register info for PRU0
    Control register: 0x00000109
      Reset PC:0x0000  STOPPED, SINGLE_STEP, COUNTER_ENABLED, NOT_SLEEPING, PROC_DISABLED

    Program counter: 0x005b
      Current instruction: SBBO R21, R17, R8, 4

    R00: 0x0000000a    R08: 0x00000000    R16: 0xc03baf73    R24: 0xcb0edc25
    R01: 0x00000800    R09: 0x00000000    R17: 0x00000101    R25: 0xa13ce8ee
    R02: 0x00000fff    R10: 0x00000002    R18: 0x00000001    R26: 0xc37deeba
    R03: 0x00000040    R11: 0x00000000    R19: 0x00022000    R27: 0xbfbc0d6f
    R04: 0xfffffff8    R12: 0x0000000a    R20: 0x0002200c    R28: 0x61b8bd59
    R05: 0x000f4240    R13: 0x00000002    R21: 0x00000001    R29: 0xd1a23a79
    R06: 0x44e0d000    R14: 0x00000800    R22: 0xfe14b171    R30: 0x7fa3b06a
    R07: 0x44e0d100    R15: 0x0000000a    R23: 0x3506ebed    R31: 0x00000000


Before we execute that line, here's what the relevant part of hte data ram looks like. As you can see, the PRU debugger considers address 0x0004 to be 4 32-bit words after address 0x0000. So it looks like the pru debugger 

PRU0> d 0 1000
d 0 1000
Absolute addr = 0x0000, offset = 0x0000, Len = 1000
[0x0000] 0x00000000 0x11111111 0x11111111 0x11111111
[0x0004] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0008] 0x11111111 0x11111111 0x11111111 0x11111111
[0x000c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0010] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0014] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0018] 0x11111111 0x11111111 0x11111111 0x11111111
[0x001c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0020] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0024] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0028] 0x11111111 0x11111111 0x11111111 0x11111111
[0x002c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0030] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0034] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0038] 0x11111111 0x11111111 0x11111111 0x11111111
[0x003c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0040] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0044] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0048] 0x11111111 0x11111111 0x11111111 0x11111111
[0x004c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0050] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0054] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0058] 0x11111111 0x11111111 0x11111111 0x11111111
[0x005c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0060] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0064] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0068] 0x11111111 0x11111111 0x11111111 0x11111111
[0x006c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0070] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0074] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0078] 0x11111111 0x11111111 0x11111111 0x11111111
[0x007c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0080] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0084] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0088] 0x11111111 0x11111111 0x11111111 0x11111111
[0x008c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0090] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0094] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0098] 0x11111111 0x11111111 0x11111111 0x11111111
[0x009c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00a0] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00a4] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00a8] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00ac] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00b0] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00b4] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00b8] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00bc] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00c0] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00c4] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00c8] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00cc] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00d0] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00d4] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00d8] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00dc] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00e0] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00e4] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00e8] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00ec] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00f0] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00f4] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00f8] 0x11111111 0x11111111 0x11111111 0x11111111
[0x00fc] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0100] 0x11111111 0x22222222 0x22222222 0x22222222
[0x0104] 0x22222222 0x22222222 0x22222222 0x22222222
[0x0108] 0x22222222 0x22222222 0x22222222 0x22222222
[0x010c] 0x22222222 0x22222222 0x22222222 0x22222222
[0x0110] 0x22222222 0x22222222 0x22222222 0x22222222
[0x0114] 0x22222222 0x22222222 0x22222222 0x22222222
[0x0118] 0x22222222 0x22222222 0x22222222 0x22222222
[0x011c] 0x22222222 0x22222222 0x22222222 0x22222222
[0x0120] 0x22222222 0x22222222 0x22222222 0x22222222
[0x0124] 0x22222222 0x22222222 0x22222222 0x22222222
[0x0128] 0x22222222 0x22222222 0x22222222 0x22222222
[0x012c] 0x22222222 0x22222222 0x22222222 0x22222222


After:

PRU0> d 0 1000
d 0 1000
Absolute addr = 0x0000, offset = 0x0000, Len = 1000
[0x0000] 0x00000000 0x11111111 0x11111111 0x11111111
[0x0004] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0008] 0x11111111 0x11111111 0x11111111 0x11111111
[0x000c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0010] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0014] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0018] 0x11111111 0x11111111 0x11111111 0x11111111
[0x001c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0020] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0024] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0028] 0x11111111 0x11111111 0x11111111 0x11111111
[0x002c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0030] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0034] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0038] 0x11111111 0x11111111 0x11111111 0x11111111
[0x003c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0040] 0x00000111 0x11111100 0x11111111 0x11111111
[0x0044] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0048] 0x11111111 0x11111111 0x11111111 0x11111111
[0x004c] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0050] 0x11111111 0x11111111 0x11111111 0x11111111
[0x0054] 0x11111111 0x11111111 0x11111111 0x11111111

You can see that address `[0x0040]` has some weird stuff going on.

What's happened is that we're seeing an endian problem as well as a pru-debugger-labels-ram-weirdly problem.

You can use devmem to see what's actually in the ram:

The PRU0 data ram offset is 0x4a300000, so if we mistakenly trust the PRU, we won't see our previous 0x1 value:


root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300040
/dev/mem opened.
Memory mapped at address 0xb6f2a000.
Value at address 0x4A300040 (0xb6f2a040): 0x11111111
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300041
/dev/mem opened.
Memory mapped at address 0xb6fd6000.
Value at address 0x4A300041 (0xb6fd6041): 0x11111111
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300042
/dev/mem opened.
Memory mapped at address 0xb6f6a000.
Value at address 0x4A300042 (0xb6f6a042): 0x11111111
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300043
/dev/mem opened.
Memory mapped at address 0xb6f87000.
Value at address 0x4A300043 (0xb6f87043): 0x11111111
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300044
/dev/mem opened.
Memory mapped at address 0xb6fd4000.
Value at address 0x4A300044 (0xb6fd4044): 0x11111111



However, if we look at the actual bytes... You can see that it reads in units of bytes. The "1" slowly creeps across as we move our 32-bit window over 1 byte at a time.


root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300100
/dev/mem opened.
Memory mapped at address 0xb6f81000.
Value at address 0x4A300100 (0xb6f81100): 0x111
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300101
/dev/mem opened.
Memory mapped at address 0xb6f69000.
Value at address 0x4A300101 (0xb6f69101): 0x1
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300102
/dev/mem opened.
Memory mapped at address 0xb6f59000.
Value at address 0x4A300102 (0xb6f59102): 0x11000000
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300103
/dev/mem opened.
Memory mapped at address 0xb6f08000.
Value at address 0x4A300103 (0xb6f08103): 0x11110000
root@beaglebone:/home/debian/BB_PRU_stuff/ADC/06-CPU-gets-ADC-sample-list# /home/debian/devmem/devmem2 0x4a300104
/dev/mem opened.
Memory mapped at address 0xb6fa5000.
Value at address 0x4A300104 (0xb6fa5104): 0x11111100


Here is how to make it work:


PRU0> r
r
Register info for PRU0
    Control register: 0x00000109
      Reset PC:0x0000  STOPPED, SINGLE_STEP, COUNTER_ENABLED, NOT_SLEEPING, PROC_DISABLED

    Program counter: 0x005b
      Current instruction: SBBO R21, R17, R8, 4

    R00: 0x0000000a    R08: 0x00000000    R16: 0xc03baf73    R24: 0xcb0edc25
    R01: 0x000007fc    R09: 0x00000000    R17: 0x00000404    R25: 0xa13ce8ee
    R02: 0x00000fff    R10: 0x00000002    R18: 0x00000004    R26: 0xc37deeba
    R03: 0x00000040    R11: 0x00000000    R19: 0x00022000    R27: 0xbfbc0d6f
    R04: 0xfe73447d    R12: 0x0000000a    R20: 0x0002200c    R28: 0x61b8bd59
    R05: 0x000f4240    R13: 0x00000002    R21: 0x00000001    R29: 0xd1a23a79
    R06: 0x44e0d000    R14: 0x000007fc    R22: 0xfe14b171    R30: 0x7fa3b06a
    R07: 0x44e0d100    R15: 0x0000000a    R23: 0x3506ebed    R31: 0x00000000

PRU0> ss
ss
Register info for PRU0
    Control register: 0x00000109
      Reset PC:0x0000  STOPPED, SINGLE_STEP, COUNTER_ENABLED, NOT_SLEEPING, PROC_DISABLED

    Program counter: 0x005c
      Current instruction: ADD R8, R8, 0x04

    R00: 0x0000000a    R08: 0x00000000    R16: 0xc03baf73    R24: 0xcb0edc25
    R01: 0x000007fc    R09: 0x00000000    R17: 0x00000404    R25: 0xa13ce8ee
    R02: 0x00000fff    R10: 0x00000002    R18: 0x00000004    R26: 0xc37deeba
    R03: 0x00000040    R11: 0x00000000    R19: 0x00022000    R27: 0xbfbc0d6f
    R04: 0xfe73447d    R12: 0x0000000a    R20: 0x0002200c    R28: 0x61b8bd59
    R05: 0x000f4240    R13: 0x00000002    R21: 0x00000001    R29: 0xd1a23a79
    R06: 0x44e0d000    R14: 0x000007fc    R22: 0xfe14b171    R30: 0x7fa3b06a
    R07: 0x44e0d100    R15: 0x0000000a    R23: 0x3506ebed    R31: 0x00000000

PRU0> d 0 1000
d 0 1000
Absolute addr = 0x0000, offset = 0x0000, Len = 1000
[0x0000] 0x00000000 0x33333333 0x33333333 0x33333333 
[0x0004] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0008] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x000c] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0010] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0014] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0018] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x001c] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0020] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0024] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0028] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x002c] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0030] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0034] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0038] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x003c] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0040] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0044] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0048] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x004c] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0050] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0054] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0058] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x005c] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0060] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0064] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0068] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x006c] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0070] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0074] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0078] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x007c] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0080] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0084] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0088] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x008c] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0090] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0094] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0098] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x009c] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00a0] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00a4] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00a8] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00ac] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00b0] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00b4] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00b8] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00bc] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00c0] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00c4] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00c8] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00cc] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00d0] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00d4] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00d8] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00dc] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00e0] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00e4] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00e8] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00ec] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00f0] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00f4] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00f8] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x00fc] 0x33333333 0x33333333 0x33333333 0x33333333 
[0x0100] 0x33333333 0x00000001 0x77777777 0x77777777  <-- worked!! 
[0x0104] 0x77777777 0x77777777 0x77777777 0x77777777 
[0x0108] 0x77777777 0x77777777 0x77777777 0x77777777 
[0x010c] 0x77777777 0x77777777 0x77777777 0x77777777 
[0x0110] 0x77777777 0x77777777 0x77777777 0x77777777 
[0x0114] 0x77777777 0x77777777 0x77777777 0x77777777 
[0x0118] 0x77777777 0x77777777 0x77777777 0x77777777 
[0x011c] 0x77777777 0x77777777 0x77777777 0x77777777 
[0x0120] 0x77777777 0x77777777 0x77777777 0x77777777 
[0x0124] 0x77777777 0x77777777 0x77777777 0x77777777 
[0x0128] 0x77777777 0x77777777 0x77777777 0x77777777 
[0x012c] 0x77777777 0x77777777 0x77777777 0x77777777 
[0x0130] 0x77777777 0x77777777 0x77777777 0x77777777 
[0x0134] 0x77777777 0x77777777 0x77777777 0x77777777 
