EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74xx:74HC245 U1
U 1 1 62110D18
P 2125 2750
F 0 "U1" H 1900 3425 50  0000 C CNN
F 1 "74HC245" H 2350 3425 50  0000 C CNN
F 2 "Package_DIP:DIP-20_W7.62mm" H 2125 2750 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC245" H 2125 2750 50  0001 C CNN
	1    2125 2750
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC245 U8
U 1 1 62111D19
P 2125 4750
F 0 "U8" H 1900 5425 50  0000 C CNN
F 1 "74HC245" H 2350 5425 50  0000 C CNN
F 2 "Package_DIP:DIP-20_W7.62mm" H 2125 4750 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC245" H 2125 4750 50  0001 C CNN
	1    2125 4750
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC245 U14
U 1 1 621136CA
P 2125 6750
F 0 "U14" H 1900 7425 50  0000 C CNN
F 1 "74HC245" H 2350 7425 50  0000 C CNN
F 2 "Package_DIP:DIP-20_W7.62mm" H 2125 6750 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC245" H 2125 6750 50  0001 C CNN
	1    2125 6750
	1    0    0    -1  
$EndComp
$Comp
L CommonLibrary:CMD U2
U 1 1 62116D81
P 3725 3750
F 0 "U2" H 4125 4725 50  0000 C CNN
F 1 "CMD" H 4125 4634 50  0000 C CNN
F 2 "CommonLibrary:CMD" H 3725 4100 50  0001 C CNN
F 3 "" H 3725 4100 50  0001 C CNN
	1    3725 3750
	1    0    0    -1  
$EndComp
$Comp
L CommonLibrary:CMD U3
U 1 1 6211CA07
P 5475 3750
F 0 "U3" H 5875 4725 50  0000 C CNN
F 1 "CMD" H 5875 4634 50  0000 C CNN
F 2 "CommonLibrary:CMD" H 5475 4100 50  0001 C CNN
F 3 "" H 5475 4100 50  0001 C CNN
	1    5475 3750
	1    0    0    -1  
$EndComp
Text Notes 3950 4750 0    100  ~ 0
MUL
Text Notes 5600 4750 0    100  ~ 0
ADD[C]
$Comp
L CommonLibrary:CMD U4
U 1 1 6211F4EA
P 7225 3750
F 0 "U4" H 7625 4725 50  0000 C CNN
F 1 "CMD" H 7625 4634 50  0000 C CNN
F 2 "CommonLibrary:CMD" H 7225 4100 50  0001 C CNN
F 3 "" H 7225 4100 50  0001 C CNN
	1    7225 3750
	1    0    0    -1  
$EndComp
Text Notes 7475 4750 0    100  ~ 0
AND
$Comp
L CommonLibrary:CMD U5
U 1 1 6212165F
P 8975 3750
F 0 "U5" H 9375 4725 50  0000 C CNN
F 1 "CMD" H 9375 4634 50  0000 C CNN
F 2 "CommonLibrary:CMD" H 8975 4100 50  0001 C CNN
F 3 "" H 8975 4100 50  0001 C CNN
	1    8975 3750
	1    0    0    -1  
$EndComp
Text Notes 9250 4750 0    100  ~ 0
OR
$Comp
L CommonLibrary:CMD U6
U 1 1 621230EF
P 10725 3750
F 0 "U6" H 11125 4725 50  0000 C CNN
F 1 "CMD" H 11125 4634 50  0000 C CNN
F 2 "CommonLibrary:CMD" H 10725 4100 50  0001 C CNN
F 3 "" H 10725 4100 50  0001 C CNN
	1    10725 3750
	1    0    0    -1  
$EndComp
Text Notes 10975 4750 0    100  ~ 0
XOR
$Comp
L CommonLibrary:CMD U7
U 1 1 62124F18
P 12475 3750
F 0 "U7" H 12875 4725 50  0000 C CNN
F 1 "CMD" H 12875 4634 50  0000 C CNN
F 2 "CommonLibrary:CMD" H 12475 4100 50  0001 C CNN
F 3 "" H 12475 4100 50  0001 C CNN
	1    12475 3750
	1    0    0    -1  
$EndComp
Text Notes 12600 4750 0    100  ~ 0
CMP[C]
$Comp
L CommonLibrary:CMD U9
U 1 1 62126C83
P 5475 6250
F 0 "U9" H 5875 7225 50  0000 C CNN
F 1 "CMD" H 5875 7134 50  0000 C CNN
F 2 "CommonLibrary:CMD" H 5475 6600 50  0001 C CNN
F 3 "" H 5475 6600 50  0001 C CNN
	1    5475 6250
	1    0    0    -1  
$EndComp
$Comp
L CommonLibrary:CMD U10
U 1 1 62129053
P 7225 6250
F 0 "U10" H 7625 7225 50  0000 C CNN
F 1 "CMD" H 7625 7134 50  0000 C CNN
F 2 "CommonLibrary:CMD" H 7225 6600 50  0001 C CNN
F 3 "" H 7225 6600 50  0001 C CNN
	1    7225 6250
	1    0    0    -1  
$EndComp
$Comp
L CommonLibrary:CMD U11
U 1 1 62129F2D
P 8975 6250
F 0 "U11" H 9375 7225 50  0000 C CNN
F 1 "CMD" H 9375 7134 50  0000 C CNN
F 2 "CommonLibrary:CMD" H 8975 6600 50  0001 C CNN
F 3 "" H 8975 6600 50  0001 C CNN
	1    8975 6250
	1    0    0    -1  
$EndComp
$Comp
L CommonLibrary:CMD U12
U 1 1 6212AA06
P 10725 6250
F 0 "U12" H 11125 7225 50  0000 C CNN
F 1 "CMD" H 11125 7134 50  0000 C CNN
F 2 "CommonLibrary:CMD" H 10725 6600 50  0001 C CNN
F 3 "" H 10725 6600 50  0001 C CNN
	1    10725 6250
	1    0    0    -1  
$EndComp
Text Notes 5525 7250 0    100  ~ 0
CLR/SET
Text Notes 7350 7250 0    100  ~ 0
LSL[C]
Text Notes 9100 7250 0    100  ~ 0
LSR[C]
Text Notes 10800 7250 0    100  ~ 0
INV/MOV
$Comp
L CommonLibrary:CMD U13
U 1 1 6213B6E2
P 12475 6250
F 0 "U13" H 12875 7225 50  0000 C CNN
F 1 "CMD" H 12875 7134 50  0000 C CNN
F 2 "CommonLibrary:CMD" H 12475 6600 50  0001 C CNN
F 3 "" H 12475 6600 50  0001 C CNN
	1    12475 6250
	1    0    0    -1  
$EndComp
Text Notes 12775 7250 0    100  ~ 0
ZF
$Comp
L Connector:Conn_01x08_Male J1
U 1 1 6213EE21
P 1175 2550
F 0 "J1" H 1283 3031 50  0000 C CNN
F 1 "Conn_01x08_Male" H 1200 2075 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 1175 2550 50  0001 C CNN
F 3 "~" H 1175 2550 50  0001 C CNN
	1    1175 2550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J2
U 1 1 62140D6E
P 1175 4550
F 0 "J2" H 1283 5031 50  0000 C CNN
F 1 "Conn_01x08_Male" H 1200 4075 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 1175 4550 50  0001 C CNN
F 3 "~" H 1175 4550 50  0001 C CNN
	1    1175 4550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J3
U 1 1 6214293B
P 1175 6550
F 0 "J3" H 1283 7031 50  0000 C CNN
F 1 "Conn_01x08_Male" H 1200 6075 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 1175 6550 50  0001 C CNN
F 3 "~" H 1175 6550 50  0001 C CNN
	1    1175 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1375 2250 1625 2250
Wire Wire Line
	1375 2350 1625 2350
Wire Wire Line
	1375 2450 1625 2450
Wire Wire Line
	1375 2550 1625 2550
Wire Wire Line
	1375 2650 1625 2650
Wire Wire Line
	1375 2750 1625 2750
Wire Wire Line
	1375 2850 1625 2850
Wire Wire Line
	1375 2950 1625 2950
Wire Wire Line
	1375 4250 1625 4250
Wire Wire Line
	1375 4350 1625 4350
Wire Wire Line
	1375 4450 1625 4450
Wire Wire Line
	1375 4550 1625 4550
Wire Wire Line
	1375 4650 1625 4650
Wire Wire Line
	1375 4750 1625 4750
Wire Wire Line
	1375 4850 1625 4850
Wire Wire Line
	1375 4950 1625 4950
Wire Wire Line
	1375 6250 1625 6250
Wire Wire Line
	1375 6350 1625 6350
Wire Wire Line
	1375 6450 1625 6450
Wire Wire Line
	1375 6550 1625 6550
Wire Wire Line
	1375 6650 1625 6650
Wire Wire Line
	1375 6750 1625 6750
Wire Wire Line
	1375 6850 1625 6850
Wire Wire Line
	1375 6950 1625 6950
$Comp
L power:GND #PWR04
U 1 1 6214F397
P 2125 3550
F 0 "#PWR04" H 2125 3300 50  0001 C CNN
F 1 "GND" H 2300 3475 50  0000 C CNN
F 2 "" H 2125 3550 50  0001 C CNN
F 3 "" H 2125 3550 50  0001 C CNN
	1    2125 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 6214FFE5
P 2125 5550
F 0 "#PWR020" H 2125 5300 50  0001 C CNN
F 1 "GND" H 2300 5475 50  0000 C CNN
F 2 "" H 2125 5550 50  0001 C CNN
F 3 "" H 2125 5550 50  0001 C CNN
	1    2125 5550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR033
U 1 1 6215072E
P 2125 7550
F 0 "#PWR033" H 2125 7300 50  0001 C CNN
F 1 "GND" H 2300 7475 50  0000 C CNN
F 2 "" H 2125 7550 50  0001 C CNN
F 3 "" H 2125 7550 50  0001 C CNN
	1    2125 7550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 621534CA
P 1475 3150
F 0 "R1" V 1575 3100 50  0000 C CNN
F 1 "10k" V 1475 3150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 1405 3150 50  0001 C CNN
F 3 "~" H 1475 3150 50  0001 C CNN
	1    1475 3150
	0    1    1    0   
$EndComp
$Comp
L power:VCC #PWR02
U 1 1 62154B82
P 1325 3150
F 0 "#PWR02" H 1325 3000 50  0001 C CNN
F 1 "VCC" V 1340 3277 50  0000 L CNN
F 2 "" H 1325 3150 50  0001 C CNN
F 3 "" H 1325 3150 50  0001 C CNN
	1    1325 3150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 621566AE
P 1475 5150
F 0 "R2" V 1575 5100 50  0000 C CNN
F 1 "10k" V 1475 5150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 1405 5150 50  0001 C CNN
F 3 "~" H 1475 5150 50  0001 C CNN
	1    1475 5150
	0    1    1    0   
$EndComp
$Comp
L power:VCC #PWR018
U 1 1 62156C32
P 1325 5150
F 0 "#PWR018" H 1325 5000 50  0001 C CNN
F 1 "VCC" V 1340 5277 50  0000 L CNN
F 2 "" H 1325 5150 50  0001 C CNN
F 3 "" H 1325 5150 50  0001 C CNN
	1    1325 5150
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR032
U 1 1 62157C7F
P 1625 7250
F 0 "#PWR032" H 1625 7000 50  0001 C CNN
F 1 "GND" H 1630 7077 50  0000 C CNN
F 2 "" H 1625 7250 50  0001 C CNN
F 3 "" H 1625 7250 50  0001 C CNN
	1    1625 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1625 7150 1625 7250
Connection ~ 1625 7250
$Comp
L power:GND #PWR019
U 1 1 62158A16
P 1625 5250
F 0 "#PWR019" H 1625 5000 50  0001 C CNN
F 1 "GND" H 1800 5175 50  0000 C CNN
F 2 "" H 1625 5250 50  0001 C CNN
F 3 "" H 1625 5250 50  0001 C CNN
	1    1625 5250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 621593FE
P 1625 3250
F 0 "#PWR03" H 1625 3000 50  0001 C CNN
F 1 "GND" H 1800 3175 50  0000 C CNN
F 2 "" H 1625 3250 50  0001 C CNN
F 3 "" H 1625 3250 50  0001 C CNN
	1    1625 3250
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR01
U 1 1 6215A2AB
P 2125 1950
F 0 "#PWR01" H 2125 1800 50  0001 C CNN
F 1 "VCC" H 2140 2123 50  0000 C CNN
F 2 "" H 2125 1950 50  0001 C CNN
F 3 "" H 2125 1950 50  0001 C CNN
	1    2125 1950
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR05
U 1 1 6215AECA
P 2125 3950
F 0 "#PWR05" H 2125 3800 50  0001 C CNN
F 1 "VCC" H 2140 4123 50  0000 C CNN
F 2 "" H 2125 3950 50  0001 C CNN
F 3 "" H 2125 3950 50  0001 C CNN
	1    2125 3950
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR021
U 1 1 6215B994
P 2125 5950
F 0 "#PWR021" H 2125 5800 50  0001 C CNN
F 1 "VCC" H 2140 6123 50  0000 C CNN
F 2 "" H 2125 5950 50  0001 C CNN
F 3 "" H 2125 5950 50  0001 C CNN
	1    2125 5950
	1    0    0    -1  
$EndComp
Text Label 2625 2250 0    50   ~ 0
A0
Text Label 2625 2350 0    50   ~ 0
A1
Text Label 2625 2450 0    50   ~ 0
A2
Text Label 2625 2550 0    50   ~ 0
A3
Text Label 2625 2650 0    50   ~ 0
A4
Text Label 2625 2750 0    50   ~ 0
A5
Text Label 2625 2850 0    50   ~ 0
A6
Text Label 2625 2950 0    50   ~ 0
A7
Text Label 2625 4250 0    50   ~ 0
B0
Text Label 2625 4350 0    50   ~ 0
B1
Text Label 2625 4450 0    50   ~ 0
B2
Text Label 2625 4550 0    50   ~ 0
B3
Text Label 2625 4650 0    50   ~ 0
B4
Text Label 2625 4750 0    50   ~ 0
B5
Text Label 2625 4850 0    50   ~ 0
B6
Text Label 2625 4950 0    50   ~ 0
B7
Text Label 2625 6250 0    50   ~ 0
O0
Text Label 2625 6350 0    50   ~ 0
O1
Text Label 2625 6450 0    50   ~ 0
O2
Text Label 2625 6550 0    50   ~ 0
O3
Text Label 2625 6650 0    50   ~ 0
O4
Text Label 2625 6750 0    50   ~ 0
O5
Text Label 2625 6850 0    50   ~ 0
O6
Text Label 2625 6950 0    50   ~ 0
O7
Text Label 4625 3300 0    50   ~ 0
O0
Text Label 4625 3400 0    50   ~ 0
O1
Text Label 4625 3500 0    50   ~ 0
O2
Text Label 4625 3600 0    50   ~ 0
O3
Text Label 4625 3700 0    50   ~ 0
O4
Text Label 4625 3800 0    50   ~ 0
O5
Text Label 4625 3900 0    50   ~ 0
O6
Text Label 4625 4000 0    50   ~ 0
O7
Text Label 6375 3300 0    50   ~ 0
O0
Text Label 6375 3400 0    50   ~ 0
O1
Text Label 6375 3500 0    50   ~ 0
O2
Text Label 6375 3600 0    50   ~ 0
O3
Text Label 6375 3700 0    50   ~ 0
O4
Text Label 6375 3800 0    50   ~ 0
O5
Text Label 6375 3900 0    50   ~ 0
O6
Text Label 6375 4000 0    50   ~ 0
O7
Text Label 8125 3300 0    50   ~ 0
O0
Text Label 8125 3400 0    50   ~ 0
O1
Text Label 8125 3500 0    50   ~ 0
O2
Text Label 8125 3600 0    50   ~ 0
O3
Text Label 8125 3700 0    50   ~ 0
O4
Text Label 8125 3800 0    50   ~ 0
O5
Text Label 8125 3900 0    50   ~ 0
O6
Text Label 8125 4000 0    50   ~ 0
O7
Text Label 9875 3300 0    50   ~ 0
O0
Text Label 9875 3400 0    50   ~ 0
O1
Text Label 9875 3500 0    50   ~ 0
O2
Text Label 9875 3600 0    50   ~ 0
O3
Text Label 9875 3700 0    50   ~ 0
O4
Text Label 9875 3800 0    50   ~ 0
O5
Text Label 9875 3900 0    50   ~ 0
O6
Text Label 9875 4000 0    50   ~ 0
O7
Text Label 11625 3300 0    50   ~ 0
O0
Text Label 11625 3400 0    50   ~ 0
O1
Text Label 11625 3500 0    50   ~ 0
O2
Text Label 11625 3600 0    50   ~ 0
O3
Text Label 11625 3700 0    50   ~ 0
O4
Text Label 11625 3800 0    50   ~ 0
O5
Text Label 11625 3900 0    50   ~ 0
O6
Text Label 11625 4000 0    50   ~ 0
O7
Text Label 13375 3300 0    50   ~ 0
O0
Text Label 13375 3400 0    50   ~ 0
O1
Text Label 13375 3500 0    50   ~ 0
O2
Text Label 13375 3600 0    50   ~ 0
O3
Text Label 13375 3700 0    50   ~ 0
O4
Text Label 13375 3800 0    50   ~ 0
O5
Text Label 13375 3900 0    50   ~ 0
O6
Text Label 13375 4000 0    50   ~ 0
O7
Text Label 13375 5800 0    50   ~ 0
O0
Text Label 13375 5900 0    50   ~ 0
O1
Text Label 13375 6000 0    50   ~ 0
O2
Text Label 13375 6100 0    50   ~ 0
O3
Text Label 13375 6200 0    50   ~ 0
O4
Text Label 13375 6300 0    50   ~ 0
O5
Text Label 13375 6400 0    50   ~ 0
O6
Text Label 13375 6500 0    50   ~ 0
O7
Text Label 11625 5800 0    50   ~ 0
O0
Text Label 11625 5900 0    50   ~ 0
O1
Text Label 11625 6000 0    50   ~ 0
O2
Text Label 11625 6100 0    50   ~ 0
O3
Text Label 11625 6200 0    50   ~ 0
O4
Text Label 11625 6300 0    50   ~ 0
O5
Text Label 11625 6400 0    50   ~ 0
O6
Text Label 11625 6500 0    50   ~ 0
O7
Text Label 9875 5800 0    50   ~ 0
O0
Text Label 9875 5900 0    50   ~ 0
O1
Text Label 9875 6000 0    50   ~ 0
O2
Text Label 9875 6100 0    50   ~ 0
O3
Text Label 9875 6200 0    50   ~ 0
O4
Text Label 9875 6300 0    50   ~ 0
O5
Text Label 9875 6400 0    50   ~ 0
O6
Text Label 9875 6500 0    50   ~ 0
O7
Text Label 8125 5800 0    50   ~ 0
O0
Text Label 8125 5900 0    50   ~ 0
O1
Text Label 8125 6000 0    50   ~ 0
O2
Text Label 8125 6100 0    50   ~ 0
O3
Text Label 8125 6200 0    50   ~ 0
O4
Text Label 8125 6300 0    50   ~ 0
O5
Text Label 8125 6400 0    50   ~ 0
O6
Text Label 8125 6500 0    50   ~ 0
O7
Text Label 6375 5800 0    50   ~ 0
O0
Text Label 6375 5900 0    50   ~ 0
O1
Text Label 6375 6000 0    50   ~ 0
O2
Text Label 6375 6100 0    50   ~ 0
O3
Text Label 6375 6200 0    50   ~ 0
O4
Text Label 6375 6300 0    50   ~ 0
O5
Text Label 6375 6400 0    50   ~ 0
O6
Text Label 6375 6500 0    50   ~ 0
O7
Wire Wire Line
	3625 3000 3500 3000
Wire Wire Line
	3625 3100 3500 3100
Wire Wire Line
	3625 3200 3500 3200
Wire Wire Line
	3625 3300 3500 3300
Wire Wire Line
	3625 3400 3500 3400
Wire Wire Line
	3625 3500 3500 3500
Wire Wire Line
	3625 3600 3500 3600
Wire Wire Line
	3625 3700 3500 3700
Text Label 3500 3000 0    50   ~ 0
A0
Text Label 3500 3100 0    50   ~ 0
A1
Text Label 3500 3200 0    50   ~ 0
A2
Text Label 3500 3300 0    50   ~ 0
A3
Text Label 3500 3400 0    50   ~ 0
A4
Text Label 3500 3500 0    50   ~ 0
A5
Text Label 3500 3600 0    50   ~ 0
A6
Text Label 3500 3700 0    50   ~ 0
A7
Wire Wire Line
	3625 3800 3500 3800
Wire Wire Line
	3625 3900 3500 3900
Wire Wire Line
	3625 4000 3500 4000
Wire Wire Line
	3625 4100 3500 4100
Wire Wire Line
	3625 4200 3500 4200
Wire Wire Line
	3625 4300 3500 4300
Wire Wire Line
	3625 4400 3500 4400
Wire Wire Line
	3625 4500 3500 4500
Text Label 3500 3800 0    50   ~ 0
B0
Text Label 3500 3900 0    50   ~ 0
B1
Text Label 3500 4000 0    50   ~ 0
B2
Text Label 3500 4100 0    50   ~ 0
B3
Text Label 3500 4200 0    50   ~ 0
B4
Text Label 3500 4300 0    50   ~ 0
B5
Text Label 3500 4400 0    50   ~ 0
B6
Text Label 3500 4500 0    50   ~ 0
B7
Wire Wire Line
	5375 3000 5250 3000
Wire Wire Line
	5375 3100 5250 3100
Wire Wire Line
	5375 3200 5250 3200
Wire Wire Line
	5375 3300 5250 3300
Wire Wire Line
	5375 3400 5250 3400
Wire Wire Line
	5375 3500 5250 3500
Wire Wire Line
	5375 3600 5250 3600
Wire Wire Line
	5375 3700 5250 3700
Text Label 5250 3000 0    50   ~ 0
A0
Text Label 5250 3100 0    50   ~ 0
A1
Text Label 5250 3200 0    50   ~ 0
A2
Text Label 5250 3300 0    50   ~ 0
A3
Text Label 5250 3400 0    50   ~ 0
A4
Text Label 5250 3500 0    50   ~ 0
A5
Text Label 5250 3600 0    50   ~ 0
A6
Text Label 5250 3700 0    50   ~ 0
A7
Wire Wire Line
	5375 3800 5250 3800
Wire Wire Line
	5375 3900 5250 3900
Wire Wire Line
	5375 4000 5250 4000
Wire Wire Line
	5375 4100 5250 4100
Wire Wire Line
	5375 4200 5250 4200
Wire Wire Line
	5375 4300 5250 4300
Wire Wire Line
	5375 4400 5250 4400
Wire Wire Line
	5375 4500 5250 4500
Text Label 5250 3800 0    50   ~ 0
B0
Text Label 5250 3900 0    50   ~ 0
B1
Text Label 5250 4000 0    50   ~ 0
B2
Text Label 5250 4100 0    50   ~ 0
B3
Text Label 5250 4200 0    50   ~ 0
B4
Text Label 5250 4300 0    50   ~ 0
B5
Text Label 5250 4400 0    50   ~ 0
B6
Text Label 5250 4500 0    50   ~ 0
B7
Wire Wire Line
	7125 3000 7000 3000
Wire Wire Line
	7125 3100 7000 3100
Wire Wire Line
	7125 3200 7000 3200
Wire Wire Line
	7125 3300 7000 3300
Wire Wire Line
	7125 3400 7000 3400
Wire Wire Line
	7125 3500 7000 3500
Wire Wire Line
	7125 3600 7000 3600
Wire Wire Line
	7125 3700 7000 3700
Text Label 7000 3000 0    50   ~ 0
A0
Text Label 7000 3100 0    50   ~ 0
A1
Text Label 7000 3200 0    50   ~ 0
A2
Text Label 7000 3300 0    50   ~ 0
A3
Text Label 7000 3400 0    50   ~ 0
A4
Text Label 7000 3500 0    50   ~ 0
A5
Text Label 7000 3600 0    50   ~ 0
A6
Text Label 7000 3700 0    50   ~ 0
A7
Wire Wire Line
	7125 3800 7000 3800
Wire Wire Line
	7125 3900 7000 3900
Wire Wire Line
	7125 4000 7000 4000
Wire Wire Line
	7125 4100 7000 4100
Wire Wire Line
	7125 4200 7000 4200
Wire Wire Line
	7125 4300 7000 4300
Wire Wire Line
	7125 4400 7000 4400
Wire Wire Line
	7125 4500 7000 4500
Text Label 7000 3800 0    50   ~ 0
B0
Text Label 7000 3900 0    50   ~ 0
B1
Text Label 7000 4000 0    50   ~ 0
B2
Text Label 7000 4100 0    50   ~ 0
B3
Text Label 7000 4200 0    50   ~ 0
B4
Text Label 7000 4300 0    50   ~ 0
B5
Text Label 7000 4400 0    50   ~ 0
B6
Text Label 7000 4500 0    50   ~ 0
B7
Wire Wire Line
	8875 3000 8750 3000
Wire Wire Line
	8875 3100 8750 3100
Wire Wire Line
	8875 3200 8750 3200
Wire Wire Line
	8875 3300 8750 3300
Wire Wire Line
	8875 3400 8750 3400
Wire Wire Line
	8875 3500 8750 3500
Wire Wire Line
	8875 3600 8750 3600
Wire Wire Line
	8875 3700 8750 3700
Text Label 8750 3000 0    50   ~ 0
A0
Text Label 8750 3100 0    50   ~ 0
A1
Text Label 8750 3200 0    50   ~ 0
A2
Text Label 8750 3300 0    50   ~ 0
A3
Text Label 8750 3400 0    50   ~ 0
A4
Text Label 8750 3500 0    50   ~ 0
A5
Text Label 8750 3600 0    50   ~ 0
A6
Text Label 8750 3700 0    50   ~ 0
A7
Wire Wire Line
	8875 3800 8750 3800
Wire Wire Line
	8875 3900 8750 3900
Wire Wire Line
	8875 4000 8750 4000
Wire Wire Line
	8875 4100 8750 4100
Wire Wire Line
	8875 4200 8750 4200
Wire Wire Line
	8875 4300 8750 4300
Wire Wire Line
	8875 4400 8750 4400
Wire Wire Line
	8875 4500 8750 4500
Text Label 8750 3800 0    50   ~ 0
B0
Text Label 8750 3900 0    50   ~ 0
B1
Text Label 8750 4000 0    50   ~ 0
B2
Text Label 8750 4100 0    50   ~ 0
B3
Text Label 8750 4200 0    50   ~ 0
B4
Text Label 8750 4300 0    50   ~ 0
B5
Text Label 8750 4400 0    50   ~ 0
B6
Text Label 8750 4500 0    50   ~ 0
B7
Wire Wire Line
	10625 3000 10500 3000
Wire Wire Line
	10625 3100 10500 3100
Wire Wire Line
	10625 3200 10500 3200
Wire Wire Line
	10625 3300 10500 3300
Wire Wire Line
	10625 3400 10500 3400
Wire Wire Line
	10625 3500 10500 3500
Wire Wire Line
	10625 3600 10500 3600
Wire Wire Line
	10625 3700 10500 3700
Text Label 10500 3000 0    50   ~ 0
A0
Text Label 10500 3100 0    50   ~ 0
A1
Text Label 10500 3200 0    50   ~ 0
A2
Text Label 10500 3300 0    50   ~ 0
A3
Text Label 10500 3400 0    50   ~ 0
A4
Text Label 10500 3500 0    50   ~ 0
A5
Text Label 10500 3600 0    50   ~ 0
A6
Text Label 10500 3700 0    50   ~ 0
A7
Wire Wire Line
	10625 3800 10500 3800
Wire Wire Line
	10625 3900 10500 3900
Wire Wire Line
	10625 4000 10500 4000
Wire Wire Line
	10625 4100 10500 4100
Wire Wire Line
	10625 4200 10500 4200
Wire Wire Line
	10625 4300 10500 4300
Wire Wire Line
	10625 4400 10500 4400
Wire Wire Line
	10625 4500 10500 4500
Text Label 10500 3800 0    50   ~ 0
B0
Text Label 10500 3900 0    50   ~ 0
B1
Text Label 10500 4000 0    50   ~ 0
B2
Text Label 10500 4100 0    50   ~ 0
B3
Text Label 10500 4200 0    50   ~ 0
B4
Text Label 10500 4300 0    50   ~ 0
B5
Text Label 10500 4400 0    50   ~ 0
B6
Text Label 10500 4500 0    50   ~ 0
B7
Wire Wire Line
	12375 3000 12250 3000
Wire Wire Line
	12375 3100 12250 3100
Wire Wire Line
	12375 3200 12250 3200
Wire Wire Line
	12375 3300 12250 3300
Wire Wire Line
	12375 3400 12250 3400
Wire Wire Line
	12375 3500 12250 3500
Wire Wire Line
	12375 3600 12250 3600
Wire Wire Line
	12375 3700 12250 3700
Text Label 12250 3000 0    50   ~ 0
A0
Text Label 12250 3100 0    50   ~ 0
A1
Text Label 12250 3200 0    50   ~ 0
A2
Text Label 12250 3300 0    50   ~ 0
A3
Text Label 12250 3400 0    50   ~ 0
A4
Text Label 12250 3500 0    50   ~ 0
A5
Text Label 12250 3600 0    50   ~ 0
A6
Text Label 12250 3700 0    50   ~ 0
A7
Wire Wire Line
	12375 3800 12250 3800
Wire Wire Line
	12375 3900 12250 3900
Wire Wire Line
	12375 4000 12250 4000
Wire Wire Line
	12375 4100 12250 4100
Wire Wire Line
	12375 4200 12250 4200
Wire Wire Line
	12375 4300 12250 4300
Wire Wire Line
	12375 4400 12250 4400
Wire Wire Line
	12375 4500 12250 4500
Text Label 12250 3800 0    50   ~ 0
B0
Text Label 12250 3900 0    50   ~ 0
B1
Text Label 12250 4000 0    50   ~ 0
B2
Text Label 12250 4100 0    50   ~ 0
B3
Text Label 12250 4200 0    50   ~ 0
B4
Text Label 12250 4300 0    50   ~ 0
B5
Text Label 12250 4400 0    50   ~ 0
B6
Text Label 12250 4500 0    50   ~ 0
B7
Wire Wire Line
	12375 5500 12250 5500
Wire Wire Line
	12375 5600 12250 5600
Wire Wire Line
	12375 5700 12250 5700
Wire Wire Line
	12375 5800 12250 5800
Wire Wire Line
	12375 5900 12250 5900
Wire Wire Line
	12375 6000 12250 6000
Wire Wire Line
	12375 6100 12250 6100
Wire Wire Line
	12375 6200 12250 6200
Text Label 12250 5500 0    50   ~ 0
A0
Text Label 12250 5600 0    50   ~ 0
A1
Text Label 12250 5700 0    50   ~ 0
A2
Text Label 12250 5800 0    50   ~ 0
A3
Text Label 12250 5900 0    50   ~ 0
A4
Text Label 12250 6000 0    50   ~ 0
A5
Text Label 12250 6100 0    50   ~ 0
A6
Text Label 12250 6200 0    50   ~ 0
A7
Wire Wire Line
	12375 6300 12250 6300
Wire Wire Line
	12375 6400 12250 6400
Wire Wire Line
	12375 6500 12250 6500
Wire Wire Line
	12375 6600 12250 6600
Wire Wire Line
	12375 6700 12250 6700
Wire Wire Line
	12375 6800 12250 6800
Wire Wire Line
	12375 6900 12250 6900
Wire Wire Line
	12375 7000 12250 7000
Text Label 12250 6300 0    50   ~ 0
B0
Text Label 12250 6400 0    50   ~ 0
B1
Text Label 12250 6500 0    50   ~ 0
B2
Text Label 12250 6600 0    50   ~ 0
B3
Text Label 12250 6700 0    50   ~ 0
B4
Text Label 12250 6800 0    50   ~ 0
B5
Text Label 12250 6900 0    50   ~ 0
B6
Text Label 12250 7000 0    50   ~ 0
B7
Wire Wire Line
	10625 5500 10500 5500
Wire Wire Line
	10625 5600 10500 5600
Wire Wire Line
	10625 5700 10500 5700
Wire Wire Line
	10625 5800 10500 5800
Wire Wire Line
	10625 5900 10500 5900
Wire Wire Line
	10625 6000 10500 6000
Wire Wire Line
	10625 6100 10500 6100
Wire Wire Line
	10625 6200 10500 6200
Text Label 10500 5500 0    50   ~ 0
A0
Text Label 10500 5600 0    50   ~ 0
A1
Text Label 10500 5700 0    50   ~ 0
A2
Text Label 10500 5800 0    50   ~ 0
A3
Text Label 10500 5900 0    50   ~ 0
A4
Text Label 10500 6000 0    50   ~ 0
A5
Text Label 10500 6100 0    50   ~ 0
A6
Text Label 10500 6200 0    50   ~ 0
A7
Wire Wire Line
	10625 6300 10500 6300
Wire Wire Line
	10625 6400 10500 6400
Wire Wire Line
	10625 6500 10500 6500
Wire Wire Line
	10625 6600 10500 6600
Wire Wire Line
	10625 6700 10500 6700
Wire Wire Line
	10625 6800 10500 6800
Wire Wire Line
	10625 6900 10500 6900
Wire Wire Line
	10625 7000 10500 7000
Text Label 10500 6300 0    50   ~ 0
B0
Text Label 10500 6400 0    50   ~ 0
B1
Text Label 10500 6500 0    50   ~ 0
B2
Text Label 10500 6600 0    50   ~ 0
B3
Text Label 10500 6700 0    50   ~ 0
B4
Text Label 10500 6800 0    50   ~ 0
B5
Text Label 10500 6900 0    50   ~ 0
B6
Text Label 10500 7000 0    50   ~ 0
B7
Wire Wire Line
	8875 5500 8750 5500
Wire Wire Line
	8875 5600 8750 5600
Wire Wire Line
	8875 5700 8750 5700
Wire Wire Line
	8875 5800 8750 5800
Wire Wire Line
	8875 5900 8750 5900
Wire Wire Line
	8875 6000 8750 6000
Wire Wire Line
	8875 6100 8750 6100
Wire Wire Line
	8875 6200 8750 6200
Text Label 8750 5500 0    50   ~ 0
A0
Text Label 8750 5600 0    50   ~ 0
A1
Text Label 8750 5700 0    50   ~ 0
A2
Text Label 8750 5800 0    50   ~ 0
A3
Text Label 8750 5900 0    50   ~ 0
A4
Text Label 8750 6000 0    50   ~ 0
A5
Text Label 8750 6100 0    50   ~ 0
A6
Text Label 8750 6200 0    50   ~ 0
A7
Wire Wire Line
	8875 6300 8750 6300
Wire Wire Line
	8875 6400 8750 6400
Wire Wire Line
	8875 6500 8750 6500
Wire Wire Line
	8875 6600 8750 6600
Wire Wire Line
	8875 6700 8750 6700
Wire Wire Line
	8875 6800 8750 6800
Wire Wire Line
	8875 6900 8750 6900
Wire Wire Line
	8875 7000 8750 7000
Text Label 8750 6300 0    50   ~ 0
B0
Text Label 8750 6400 0    50   ~ 0
B1
Text Label 8750 6500 0    50   ~ 0
B2
Text Label 8750 6600 0    50   ~ 0
B3
Text Label 8750 6700 0    50   ~ 0
B4
Text Label 8750 6800 0    50   ~ 0
B5
Text Label 8750 6900 0    50   ~ 0
B6
Text Label 8750 7000 0    50   ~ 0
B7
Wire Wire Line
	7125 5500 7000 5500
Wire Wire Line
	7125 5600 7000 5600
Wire Wire Line
	7125 5700 7000 5700
Wire Wire Line
	7125 5800 7000 5800
Wire Wire Line
	7125 5900 7000 5900
Wire Wire Line
	7125 6000 7000 6000
Wire Wire Line
	7125 6100 7000 6100
Wire Wire Line
	7125 6200 7000 6200
Text Label 7000 5500 0    50   ~ 0
A0
Text Label 7000 5600 0    50   ~ 0
A1
Text Label 7000 5700 0    50   ~ 0
A2
Text Label 7000 5800 0    50   ~ 0
A3
Text Label 7000 5900 0    50   ~ 0
A4
Text Label 7000 6000 0    50   ~ 0
A5
Text Label 7000 6100 0    50   ~ 0
A6
Text Label 7000 6200 0    50   ~ 0
A7
Wire Wire Line
	7125 6300 7000 6300
Wire Wire Line
	7125 6400 7000 6400
Wire Wire Line
	7125 6500 7000 6500
Wire Wire Line
	7125 6600 7000 6600
Wire Wire Line
	7125 6700 7000 6700
Wire Wire Line
	7125 6800 7000 6800
Wire Wire Line
	7125 6900 7000 6900
Wire Wire Line
	7125 7000 7000 7000
Text Label 7000 6300 0    50   ~ 0
B0
Text Label 7000 6400 0    50   ~ 0
B1
Text Label 7000 6500 0    50   ~ 0
B2
Text Label 7000 6600 0    50   ~ 0
B3
Text Label 7000 6700 0    50   ~ 0
B4
Text Label 7000 6800 0    50   ~ 0
B5
Text Label 7000 6900 0    50   ~ 0
B6
Text Label 7000 7000 0    50   ~ 0
B7
Wire Wire Line
	5375 5500 5250 5500
Wire Wire Line
	5375 5600 5250 5600
Wire Wire Line
	5375 5700 5250 5700
Wire Wire Line
	5375 5800 5250 5800
Wire Wire Line
	5375 5900 5250 5900
Wire Wire Line
	5375 6000 5250 6000
Wire Wire Line
	5375 6100 5250 6100
Wire Wire Line
	5375 6200 5250 6200
Text Label 5250 5500 0    50   ~ 0
A0
Text Label 5250 5600 0    50   ~ 0
A1
Text Label 5250 5700 0    50   ~ 0
A2
Text Label 5250 5800 0    50   ~ 0
A3
Text Label 5250 5900 0    50   ~ 0
A4
Text Label 5250 6000 0    50   ~ 0
A5
Text Label 5250 6100 0    50   ~ 0
A6
Text Label 5250 6200 0    50   ~ 0
A7
Wire Wire Line
	5375 6300 5250 6300
Wire Wire Line
	5375 6400 5250 6400
Wire Wire Line
	5375 6500 5250 6500
Wire Wire Line
	5375 6600 5250 6600
Wire Wire Line
	5375 6700 5250 6700
Wire Wire Line
	5375 6800 5250 6800
Wire Wire Line
	5375 6900 5250 6900
Wire Wire Line
	5375 7000 5250 7000
Text Label 5250 6300 0    50   ~ 0
B0
Text Label 5250 6400 0    50   ~ 0
B1
Text Label 5250 6500 0    50   ~ 0
B2
Text Label 5250 6600 0    50   ~ 0
B3
Text Label 5250 6700 0    50   ~ 0
B4
Text Label 5250 6800 0    50   ~ 0
B5
Text Label 5250 6900 0    50   ~ 0
B6
Text Label 5250 7000 0    50   ~ 0
B7
$Comp
L Connector:Conn_01x01_Male J4
U 1 1 621D0C4C
P 1200 8000
F 0 "J4" H 1308 8181 50  0000 C CNN
F 1 "Conn_01x01_Male" H 1308 8090 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Horizontal" H 1200 8000 50  0001 C CNN
F 3 "~" H 1200 8000 50  0001 C CNN
	1    1200 8000
	1    0    0    -1  
$EndComp
Text Label 1400 8000 0    50   ~ 0
Latch
Text Label 4625 4200 0    50   ~ 0
Latch
$Comp
L power:VCC #PWR06
U 1 1 621D2327
P 4625 4275
F 0 "#PWR06" H 4625 4125 50  0001 C CNN
F 1 "VCC" V 4625 4400 50  0000 L CNN
F 2 "" H 4625 4275 50  0001 C CNN
F 3 "" H 4625 4275 50  0001 C CNN
	1    4625 4275
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR012
U 1 1 621E5DCB
P 4625 4350
F 0 "#PWR012" H 4625 4100 50  0001 C CNN
F 1 "GND" V 4625 4225 50  0000 R CNN
F 2 "" H 4625 4350 50  0001 C CNN
F 3 "" H 4625 4350 50  0001 C CNN
	1    4625 4350
	0    -1   -1   0   
$EndComp
Text Label 6375 4200 0    50   ~ 0
Latch
$Comp
L power:VCC #PWR07
U 1 1 6221EACE
P 6375 4275
F 0 "#PWR07" H 6375 4125 50  0001 C CNN
F 1 "VCC" V 6375 4400 50  0000 L CNN
F 2 "" H 6375 4275 50  0001 C CNN
F 3 "" H 6375 4275 50  0001 C CNN
	1    6375 4275
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 6221EAD4
P 6375 4350
F 0 "#PWR013" H 6375 4100 50  0001 C CNN
F 1 "GND" V 6375 4225 50  0000 R CNN
F 2 "" H 6375 4350 50  0001 C CNN
F 3 "" H 6375 4350 50  0001 C CNN
	1    6375 4350
	0    -1   -1   0   
$EndComp
Text Label 8125 4200 0    50   ~ 0
Latch
$Comp
L power:VCC #PWR08
U 1 1 622319EB
P 8125 4275
F 0 "#PWR08" H 8125 4125 50  0001 C CNN
F 1 "VCC" V 8125 4400 50  0000 L CNN
F 2 "" H 8125 4275 50  0001 C CNN
F 3 "" H 8125 4275 50  0001 C CNN
	1    8125 4275
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR014
U 1 1 622319F1
P 8125 4350
F 0 "#PWR014" H 8125 4100 50  0001 C CNN
F 1 "GND" V 8125 4225 50  0000 R CNN
F 2 "" H 8125 4350 50  0001 C CNN
F 3 "" H 8125 4350 50  0001 C CNN
	1    8125 4350
	0    -1   -1   0   
$EndComp
Text Label 9875 4200 0    50   ~ 0
Latch
$Comp
L power:VCC #PWR09
U 1 1 62244D24
P 9875 4275
F 0 "#PWR09" H 9875 4125 50  0001 C CNN
F 1 "VCC" V 9875 4400 50  0000 L CNN
F 2 "" H 9875 4275 50  0001 C CNN
F 3 "" H 9875 4275 50  0001 C CNN
	1    9875 4275
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR015
U 1 1 62244D2A
P 9875 4350
F 0 "#PWR015" H 9875 4100 50  0001 C CNN
F 1 "GND" V 9875 4225 50  0000 R CNN
F 2 "" H 9875 4350 50  0001 C CNN
F 3 "" H 9875 4350 50  0001 C CNN
	1    9875 4350
	0    -1   -1   0   
$EndComp
Text Label 11625 4200 0    50   ~ 0
Latch
$Comp
L power:VCC #PWR010
U 1 1 62257A4B
P 11625 4275
F 0 "#PWR010" H 11625 4125 50  0001 C CNN
F 1 "VCC" V 11625 4400 50  0000 L CNN
F 2 "" H 11625 4275 50  0001 C CNN
F 3 "" H 11625 4275 50  0001 C CNN
	1    11625 4275
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR016
U 1 1 62257A51
P 11625 4350
F 0 "#PWR016" H 11625 4100 50  0001 C CNN
F 1 "GND" V 11625 4225 50  0000 R CNN
F 2 "" H 11625 4350 50  0001 C CNN
F 3 "" H 11625 4350 50  0001 C CNN
	1    11625 4350
	0    -1   -1   0   
$EndComp
Text Label 13375 4200 0    50   ~ 0
Latch
$Comp
L power:VCC #PWR011
U 1 1 6226AAEE
P 13375 4275
F 0 "#PWR011" H 13375 4125 50  0001 C CNN
F 1 "VCC" V 13375 4400 50  0000 L CNN
F 2 "" H 13375 4275 50  0001 C CNN
F 3 "" H 13375 4275 50  0001 C CNN
	1    13375 4275
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR017
U 1 1 6226AAF4
P 13375 4350
F 0 "#PWR017" H 13375 4100 50  0001 C CNN
F 1 "GND" V 13375 4225 50  0000 R CNN
F 2 "" H 13375 4350 50  0001 C CNN
F 3 "" H 13375 4350 50  0001 C CNN
	1    13375 4350
	0    -1   -1   0   
$EndComp
Text Label 13375 6700 0    50   ~ 0
Latch
$Comp
L power:VCC #PWR026
U 1 1 6227DFD1
P 13375 6775
F 0 "#PWR026" H 13375 6625 50  0001 C CNN
F 1 "VCC" V 13375 6900 50  0000 L CNN
F 2 "" H 13375 6775 50  0001 C CNN
F 3 "" H 13375 6775 50  0001 C CNN
	1    13375 6775
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR031
U 1 1 6227DFD7
P 13375 6850
F 0 "#PWR031" H 13375 6600 50  0001 C CNN
F 1 "GND" V 13375 6725 50  0000 R CNN
F 2 "" H 13375 6850 50  0001 C CNN
F 3 "" H 13375 6850 50  0001 C CNN
	1    13375 6850
	0    -1   -1   0   
$EndComp
Text Label 11625 6700 0    50   ~ 0
Latch
$Comp
L power:VCC #PWR025
U 1 1 6229165A
P 11625 6775
F 0 "#PWR025" H 11625 6625 50  0001 C CNN
F 1 "VCC" V 11625 6900 50  0000 L CNN
F 2 "" H 11625 6775 50  0001 C CNN
F 3 "" H 11625 6775 50  0001 C CNN
	1    11625 6775
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR030
U 1 1 62291660
P 11625 6850
F 0 "#PWR030" H 11625 6600 50  0001 C CNN
F 1 "GND" V 11625 6725 50  0000 R CNN
F 2 "" H 11625 6850 50  0001 C CNN
F 3 "" H 11625 6850 50  0001 C CNN
	1    11625 6850
	0    -1   -1   0   
$EndComp
Text Label 9875 6700 0    50   ~ 0
Latch
$Comp
L power:VCC #PWR024
U 1 1 622A43EF
P 9875 6775
F 0 "#PWR024" H 9875 6625 50  0001 C CNN
F 1 "VCC" V 9875 6900 50  0000 L CNN
F 2 "" H 9875 6775 50  0001 C CNN
F 3 "" H 9875 6775 50  0001 C CNN
	1    9875 6775
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR029
U 1 1 622A43F5
P 9875 6850
F 0 "#PWR029" H 9875 6600 50  0001 C CNN
F 1 "GND" V 9875 6725 50  0000 R CNN
F 2 "" H 9875 6850 50  0001 C CNN
F 3 "" H 9875 6850 50  0001 C CNN
	1    9875 6850
	0    -1   -1   0   
$EndComp
Text Label 8125 6700 0    50   ~ 0
Latch
$Comp
L power:VCC #PWR023
U 1 1 622B771D
P 8125 6775
F 0 "#PWR023" H 8125 6625 50  0001 C CNN
F 1 "VCC" V 8125 6900 50  0000 L CNN
F 2 "" H 8125 6775 50  0001 C CNN
F 3 "" H 8125 6775 50  0001 C CNN
	1    8125 6775
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR028
U 1 1 622B7723
P 8125 6850
F 0 "#PWR028" H 8125 6600 50  0001 C CNN
F 1 "GND" V 8125 6725 50  0000 R CNN
F 2 "" H 8125 6850 50  0001 C CNN
F 3 "" H 8125 6850 50  0001 C CNN
	1    8125 6850
	0    -1   -1   0   
$EndComp
Text Label 6375 6700 0    50   ~ 0
Latch
$Comp
L power:VCC #PWR022
U 1 1 622CADCA
P 6375 6775
F 0 "#PWR022" H 6375 6625 50  0001 C CNN
F 1 "VCC" V 6375 6900 50  0000 L CNN
F 2 "" H 6375 6775 50  0001 C CNN
F 3 "" H 6375 6775 50  0001 C CNN
	1    6375 6775
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR027
U 1 1 622CADD0
P 6375 6850
F 0 "#PWR027" H 6375 6600 50  0001 C CNN
F 1 "GND" V 6375 6725 50  0000 R CNN
F 2 "" H 6375 6850 50  0001 C CNN
F 3 "" H 6375 6850 50  0001 C CNN
	1    6375 6850
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 623D2F8A
P 2000 9000
F 0 "H1" H 2100 9046 50  0000 L CNN
F 1 "MountingHole" H 2100 8955 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 2000 9000 50  0001 C CNN
F 3 "~" H 2000 9000 50  0001 C CNN
	1    2000 9000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 623D3AD8
P 2000 9250
F 0 "H2" H 2100 9296 50  0000 L CNN
F 1 "MountingHole" H 2100 9205 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 2000 9250 50  0001 C CNN
F 3 "~" H 2000 9250 50  0001 C CNN
	1    2000 9250
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 623D3D1B
P 2000 9500
F 0 "H3" H 2100 9546 50  0000 L CNN
F 1 "MountingHole" H 2100 9455 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 2000 9500 50  0001 C CNN
F 3 "~" H 2000 9500 50  0001 C CNN
	1    2000 9500
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 623D3EFA
P 2000 9750
F 0 "H4" H 2100 9796 50  0000 L CNN
F 1 "MountingHole" H 2100 9705 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 2000 9750 50  0001 C CNN
F 3 "~" H 2000 9750 50  0001 C CNN
	1    2000 9750
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H5
U 1 1 623ED712
P 2000 10000
F 0 "H5" H 2100 10046 50  0000 L CNN
F 1 "MountingHole" H 2100 9955 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 2000 10000 50  0001 C CNN
F 3 "~" H 2000 10000 50  0001 C CNN
	1    2000 10000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J6
U 1 1 62169AD4
P 6525 4800
F 0 "J6" H 6625 4925 50  0000 C CNN
F 1 "Conn_01x02_Male" V 6450 4750 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 6525 4800 50  0001 C CNN
F 3 "~" H 6525 4800 50  0001 C CNN
	1    6525 4800
	0    1    -1   0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J10
U 1 1 6216BCD1
P 13525 4800
F 0 "J10" H 13625 4925 50  0000 C CNN
F 1 "Conn_01x02_Male" V 13450 4750 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 13525 4800 50  0001 C CNN
F 3 "~" H 13525 4800 50  0001 C CNN
	1    13525 4800
	0    1    -1   0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J13
U 1 1 6216E909
P 10025 7300
F 0 "J13" H 10125 7425 50  0000 C CNN
F 1 "Conn_01x02_Male" V 9950 7250 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 10025 7300 50  0001 C CNN
F 3 "~" H 10025 7300 50  0001 C CNN
	1    10025 7300
	0    1    -1   0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J12
U 1 1 6216F92C
P 8275 7300
F 0 "J12" H 8375 7425 50  0000 C CNN
F 1 "Conn_01x02_Male" V 8200 7250 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 8275 7300 50  0001 C CNN
F 3 "~" H 8275 7300 50  0001 C CNN
	1    8275 7300
	0    1    -1   0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J11
U 1 1 6217092C
P 6525 7300
F 0 "J11" H 6625 7425 50  0000 C CNN
F 1 "Conn_01x02_Male" V 6450 7250 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 6525 7300 50  0001 C CNN
F 3 "~" H 6525 7300 50  0001 C CNN
	1    6525 7300
	0    1    -1   0   
$EndComp
Wire Wire Line
	4625 4425 4775 4425
Wire Wire Line
	4775 4425 4775 4600
Wire Wire Line
	6375 4500 6425 4500
Wire Wire Line
	6425 4500 6425 4600
Wire Wire Line
	6375 4425 6525 4425
Wire Wire Line
	6525 4425 6525 4600
Wire Wire Line
	8125 4425 8275 4425
Wire Wire Line
	8275 4425 8275 4600
Wire Wire Line
	9875 4425 10025 4425
Wire Wire Line
	10025 4425 10025 4600
Wire Wire Line
	11625 4425 11775 4425
Wire Wire Line
	11775 4425 11775 4600
Wire Wire Line
	13375 4500 13425 4500
Wire Wire Line
	13425 4500 13425 4600
Wire Wire Line
	13375 4425 13525 4425
Wire Wire Line
	13525 4425 13525 4600
Wire Wire Line
	11625 7000 11675 7000
Wire Wire Line
	11675 7000 11675 7100
Wire Wire Line
	11625 6925 11775 6925
Wire Wire Line
	11775 6925 11775 7100
Wire Wire Line
	9875 7000 9925 7000
Wire Wire Line
	9925 7000 9925 7100
Wire Wire Line
	9875 6925 10025 6925
Wire Wire Line
	10025 6925 10025 7100
Wire Wire Line
	8125 7000 8175 7000
Wire Wire Line
	8175 7000 8175 7100
Wire Wire Line
	8125 6925 8275 6925
Wire Wire Line
	8275 6925 8275 7100
Wire Wire Line
	6375 7000 6425 7000
Wire Wire Line
	6425 7000 6425 7100
Wire Wire Line
	6375 6925 6525 6925
Wire Wire Line
	6525 6925 6525 7100
NoConn ~ 13375 6925
NoConn ~ 13375 7000
$Comp
L Connector:Conn_01x02_Male J14
U 1 1 6216E38D
P 11775 7300
F 0 "J14" H 11875 7425 50  0000 C CNN
F 1 "Conn_01x02_Male" V 11700 7250 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 11775 7300 50  0001 C CNN
F 3 "~" H 11775 7300 50  0001 C CNN
	1    11775 7300
	0    1    -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J5
U 1 1 624B6AB7
P 4775 4800
F 0 "J5" V 4929 4712 50  0000 R CNN
F 1 "Conn_01x01_Male" V 4700 5150 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Horizontal" H 4775 4800 50  0001 C CNN
F 3 "~" H 4775 4800 50  0001 C CNN
	1    4775 4800
	0    -1   -1   0   
$EndComp
NoConn ~ 4625 4500
$Comp
L Connector:Conn_01x01_Male J7
U 1 1 62518F97
P 8275 4800
F 0 "J7" V 8429 4712 50  0000 R CNN
F 1 "Conn_01x01_Male" V 8200 5150 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Horizontal" H 8275 4800 50  0001 C CNN
F 3 "~" H 8275 4800 50  0001 C CNN
	1    8275 4800
	0    -1   -1   0   
$EndComp
NoConn ~ 8125 4500
NoConn ~ 9875 4500
NoConn ~ 11625 4500
$Comp
L Connector:Conn_01x01_Male J8
U 1 1 6255C10E
P 10025 4800
F 0 "J8" V 10179 4712 50  0000 R CNN
F 1 "Conn_01x01_Male" V 9950 5150 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Horizontal" H 10025 4800 50  0001 C CNN
F 3 "~" H 10025 4800 50  0001 C CNN
	1    10025 4800
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J9
U 1 1 6255C551
P 11775 4800
F 0 "J9" V 11929 4712 50  0000 R CNN
F 1 "Conn_01x01_Male" V 11700 5150 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Horizontal" H 11775 4800 50  0001 C CNN
F 3 "~" H 11775 4800 50  0001 C CNN
	1    11775 4800
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J15
U 1 1 625AB9EB
P 4200 8100
F 0 "J15" H 4280 8092 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 4280 8001 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2_1x02_P5.00mm_Horizontal" H 4200 8100 50  0001 C CNN
F 3 "~" H 4200 8100 50  0001 C CNN
	1    4200 8100
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 625AD84F
P 4000 8100
F 0 "#PWR0101" H 4000 7850 50  0001 C CNN
F 1 "GND" H 4005 7927 50  0000 C CNN
F 2 "" H 4000 8100 50  0001 C CNN
F 3 "" H 4000 8100 50  0001 C CNN
	1    4000 8100
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0102
U 1 1 625AE604
P 4000 8000
F 0 "#PWR0102" H 4000 7850 50  0001 C CNN
F 1 "VCC" H 4015 8173 50  0000 C CNN
F 2 "" H 4000 8000 50  0001 C CNN
F 3 "" H 4000 8000 50  0001 C CNN
	1    4000 8000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
