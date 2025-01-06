EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
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
L 74xx:74LS153 U1
U 1 1 6481F9B7
P 5000 3200
F 0 "U1" H 4775 4075 50  0000 C CNN
F 1 "74LS153" H 5200 4075 50  0000 C CNN
F 2 "Package_SO:SO-16_3.9x9.9mm_P1.27mm" H 5000 3200 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS153" H 5000 3200 50  0001 C CNN
	1    5000 3200
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J1
U 1 1 6482061C
P 3050 2600
F 0 "J1" H 3158 2881 50  0000 C CNN
F 1 "Conn_01x04_Male" H 2925 2350 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 3050 2600 50  0001 C CNN
F 3 "~" H 3050 2600 50  0001 C CNN
	1    3050 2600
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 6482170D
P 3050 3300
F 0 "J2" H 3158 3581 50  0000 C CNN
F 1 "Conn_01x04_Male" H 2925 3050 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 3050 3300 50  0001 C CNN
F 3 "~" H 3050 3300 50  0001 C CNN
	1    3050 3300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 64822571
P 3050 3950
F 0 "J3" H 3158 4231 50  0000 C CNN
F 1 "Conn_01x03_Male" H 2925 3800 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Horizontal" H 3050 3950 50  0001 C CNN
F 3 "~" H 3050 3950 50  0001 C CNN
	1    3050 3950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J4
U 1 1 64822EFE
P 3050 4500
F 0 "J4" H 3050 4600 50  0000 C CNN
F 1 "Conn_01x02_Male" H 2775 4325 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 3050 4500 50  0001 C CNN
F 3 "~" H 3050 4500 50  0001 C CNN
	1    3050 4500
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 64823720
P 5000 4300
F 0 "#PWR02" H 5000 4050 50  0001 C CNN
F 1 "GND" H 5005 4127 50  0000 C CNN
F 2 "" H 5000 4300 50  0001 C CNN
F 3 "" H 5000 4300 50  0001 C CNN
	1    5000 4300
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR01
U 1 1 64823E02
P 5000 2200
F 0 "#PWR01" H 5000 2050 50  0001 C CNN
F 1 "VCC" H 5015 2373 50  0000 C CNN
F 2 "" H 5000 2200 50  0001 C CNN
F 3 "" H 5000 2200 50  0001 C CNN
	1    5000 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 64824427
P 3375 4500
F 0 "#PWR04" H 3375 4250 50  0001 C CNN
F 1 "GND" H 3380 4327 50  0000 C CNN
F 2 "" H 3375 4500 50  0001 C CNN
F 3 "" H 3375 4500 50  0001 C CNN
	1    3375 4500
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR03
U 1 1 64824981
P 3375 4400
F 0 "#PWR03" H 3375 4250 50  0001 C CNN
F 1 "VCC" H 3390 4573 50  0000 C CNN
F 2 "" H 3375 4400 50  0001 C CNN
F 3 "" H 3375 4400 50  0001 C CNN
	1    3375 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2500 4500 2500
Wire Wire Line
	4250 2600 4500 2600
Wire Wire Line
	4250 2700 4500 2700
Wire Wire Line
	4250 2800 4500 2800
Wire Wire Line
	4250 3000 4500 3000
Wire Wire Line
	4250 3200 4500 3200
Wire Wire Line
	4250 3300 4500 3300
Wire Wire Line
	4250 3400 4500 3400
Wire Wire Line
	4250 3500 4500 3500
Wire Wire Line
	4250 3700 4500 3700
Wire Wire Line
	4250 3900 4500 3900
Wire Wire Line
	4250 4000 4500 4000
Text Label 4250 3000 0    50   ~ 0
~E
Text Label 4250 3700 0    50   ~ 0
~E
Text Label 4250 3900 0    50   ~ 0
S0
Text Label 4250 4000 0    50   ~ 0
S1
Text Label 4250 2500 0    50   ~ 0
A0
Text Label 4250 2600 0    50   ~ 0
B0
Text Label 4250 2700 0    50   ~ 0
C0
Text Label 4250 2800 0    50   ~ 0
D0
Text Label 4250 3200 0    50   ~ 0
A1
Text Label 4250 3300 0    50   ~ 0
B1
Text Label 4250 3400 0    50   ~ 0
C1
Text Label 4250 3500 0    50   ~ 0
D1
Text Label 5500 2500 0    50   ~ 0
O0
Text Label 5500 3200 0    50   ~ 0
O1
Text Label 3250 2800 0    50   ~ 0
A0
Text Label 3250 2700 0    50   ~ 0
B0
Text Label 3250 2600 0    50   ~ 0
B1
Text Label 3250 2500 0    50   ~ 0
A1
Text Label 3250 3200 0    50   ~ 0
D0
Text Label 3250 3300 0    50   ~ 0
C0
Text Label 3250 3400 0    50   ~ 0
C1
Text Label 3250 3500 0    50   ~ 0
D1
Text Label 3250 3950 0    50   ~ 0
~E
Text Label 3250 4050 0    50   ~ 0
S0
Text Label 3250 3850 0    50   ~ 0
S1
$Comp
L power:PWR_FLAG #FLG01
U 1 1 64827DB2
P 3575 4400
F 0 "#FLG01" H 3575 4475 50  0001 C CNN
F 1 "PWR_FLAG" H 3825 4475 50  0000 C CNN
F 2 "" H 3575 4400 50  0001 C CNN
F 3 "~" H 3575 4400 50  0001 C CNN
	1    3575 4400
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 648288F5
P 3575 4500
F 0 "#FLG02" H 3575 4575 50  0001 C CNN
F 1 "PWR_FLAG" H 3325 4575 50  0000 C CNN
F 2 "" H 3575 4500 50  0001 C CNN
F 3 "~" H 3575 4500 50  0001 C CNN
	1    3575 4500
	-1   0    0    1   
$EndComp
Wire Wire Line
	3250 4400 3375 4400
Wire Wire Line
	3250 4500 3375 4500
Wire Wire Line
	3375 4400 3575 4400
Connection ~ 3375 4400
Wire Wire Line
	3375 4500 3575 4500
Connection ~ 3375 4500
$Comp
L Device:C C1
U 1 1 64829BAA
P 4500 4900
F 0 "C1" H 4615 4946 50  0000 L CNN
F 1 "0.1uF" H 4615 4855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 4538 4750 50  0001 C CNN
F 3 "~" H 4500 4900 50  0001 C CNN
	1    4500 4900
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR05
U 1 1 6482A265
P 4500 4750
F 0 "#PWR05" H 4500 4600 50  0001 C CNN
F 1 "VCC" H 4515 4923 50  0000 C CNN
F 2 "" H 4500 4750 50  0001 C CNN
F 3 "" H 4500 4750 50  0001 C CNN
	1    4500 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 6482A974
P 4500 5050
F 0 "#PWR06" H 4500 4800 50  0001 C CNN
F 1 "GND" H 4505 4877 50  0000 C CNN
F 2 "" H 4500 5050 50  0001 C CNN
F 3 "" H 4500 5050 50  0001 C CNN
	1    4500 5050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J5
U 1 1 6482D8C1
P 3050 5150
F 0 "J5" H 3158 5331 50  0000 C CNN
F 1 "Conn_01x02_Male" H 2925 5000 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 3050 5150 50  0001 C CNN
F 3 "~" H 3050 5150 50  0001 C CNN
	1    3050 5150
	1    0    0    -1  
$EndComp
Text Label 3250 5250 0    50   ~ 0
O0
Text Label 3250 5150 0    50   ~ 0
O1
$EndSCHEMATC
