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
L Connector:Conn_01x04_Male J1
U 1 1 6482061C
P 3050 2700
F 0 "J1" H 2950 2600 50  0000 C CNN
F 1 "Conn_01x04_Male" H 3000 2850 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x02_P2.54mm_Horizontal" H 3050 2700 50  0001 C CNN
F 3 "~" H 3050 2700 50  0001 C CNN
	1    3050 2700
	1    0    0    1   
$EndComp
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 6482170D
P 3050 3400
F 0 "J2" H 2950 3350 50  0000 C CNN
F 1 "Conn_01x04_Male" H 2975 3575 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x02_P2.54mm_Horizontal" H 3050 3400 50  0001 C CNN
F 3 "~" H 3050 3400 50  0001 C CNN
	1    3050 3400
	1    0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Male J4
U 1 1 64822EFE
P 3025 4900
F 0 "J4" H 2925 4850 50  0000 C CNN
F 1 "Conn_01x02_Male" H 2900 4975 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 3025 4900 50  0001 C CNN
F 3 "~" H 3025 4900 50  0001 C CNN
	1    3025 4900
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 64823720
P 5000 4100
F 0 "#PWR02" H 5000 3850 50  0001 C CNN
F 1 "GND" H 5005 3927 50  0000 C CNN
F 2 "" H 5000 4100 50  0001 C CNN
F 3 "" H 5000 4100 50  0001 C CNN
	1    5000 4100
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
P 3350 4900
F 0 "#PWR04" H 3350 4650 50  0001 C CNN
F 1 "GND" H 3355 4727 50  0000 C CNN
F 2 "" H 3350 4900 50  0001 C CNN
F 3 "" H 3350 4900 50  0001 C CNN
	1    3350 4900
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR03
U 1 1 64824981
P 3350 4800
F 0 "#PWR03" H 3350 4650 50  0001 C CNN
F 1 "VCC" H 3365 4973 50  0000 C CNN
F 2 "" H 3350 4800 50  0001 C CNN
F 3 "" H 3350 4800 50  0001 C CNN
	1    3350 4800
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
	4250 3800 4500 3800
Wire Wire Line
	4250 2900 4500 2900
Wire Wire Line
	4250 3000 4500 3000
Wire Wire Line
	4250 3100 4500 3100
Wire Wire Line
	4250 3200 4500 3200
Wire Wire Line
	4250 3400 4500 3400
Wire Wire Line
	4250 3500 4500 3500
Text Label 4250 3800 0    50   ~ 0
~E
Text Label 4250 3400 0    50   ~ 0
S0
Text Label 4250 3500 0    50   ~ 0
S1
Text Label 5500 2500 0    50   ~ 0
O0
Text Label 3250 2800 0    50   ~ 0
I3
Text Label 3250 2700 0    50   ~ 0
I2
Text Label 3250 2600 0    50   ~ 0
I1
Text Label 3250 2500 0    50   ~ 0
I0
Text Label 3250 3200 0    50   ~ 0
I4
Text Label 3250 3300 0    50   ~ 0
I5
Text Label 3250 3400 0    50   ~ 0
I6
Text Label 3250 3500 0    50   ~ 0
I7
Text Label 3250 4150 0    50   ~ 0
~E
Text Label 3250 4050 0    50   ~ 0
S0
Text Label 3250 3950 0    50   ~ 0
S1
$Comp
L power:PWR_FLAG #FLG01
U 1 1 64827DB2
P 3550 4800
F 0 "#FLG01" H 3550 4875 50  0001 C CNN
F 1 "PWR_FLAG" H 3800 4875 50  0000 C CNN
F 2 "" H 3550 4800 50  0001 C CNN
F 3 "~" H 3550 4800 50  0001 C CNN
	1    3550 4800
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 648288F5
P 3550 4900
F 0 "#FLG02" H 3550 4975 50  0001 C CNN
F 1 "PWR_FLAG" H 3300 4975 50  0000 C CNN
F 2 "" H 3550 4900 50  0001 C CNN
F 3 "~" H 3550 4900 50  0001 C CNN
	1    3550 4900
	-1   0    0    1   
$EndComp
Wire Wire Line
	3225 4800 3350 4800
Wire Wire Line
	3225 4900 3350 4900
Wire Wire Line
	3350 4800 3550 4800
Connection ~ 3350 4800
Wire Wire Line
	3350 4900 3550 4900
Connection ~ 3350 4900
$Comp
L Device:C C1
U 1 1 64829BAA
P 4500 4900
F 0 "C1" H 4615 4946 50  0000 L CNN
F 1 "C" H 4615 4855 50  0000 L CNN
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
Text Label 3250 5500 0    50   ~ 0
O0
$Comp
L 74xx:74LS151 U1
U 1 1 64D15F99
P 5000 3100
F 0 "U1" H 4775 3850 50  0000 C CNN
F 1 "74LS151" H 5225 3850 50  0000 C CNN
F 2 "Package_SO:SO-16_3.9x9.9mm_P1.27mm" H 5000 3100 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS151" H 5000 3100 50  0001 C CNN
	1    5000 3100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J3
U 1 1 64D1A0A6
P 3050 3950
F 0 "J3" H 2975 3900 50  0000 C CNN
F 1 "Conn_01x04_Male" H 2925 3700 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 3050 3950 50  0001 C CNN
F 3 "~" H 3050 3950 50  0001 C CNN
	1    3050 3950
	1    0    0    -1  
$EndComp
Text Label 3250 3850 0    50   ~ 0
S2
Text Label 4250 3600 0    50   ~ 0
S2
Wire Wire Line
	4250 3600 4500 3600
Text Label 4250 2800 0    50   ~ 0
I3
Text Label 4250 2700 0    50   ~ 0
I2
Text Label 4250 2600 0    50   ~ 0
I1
Text Label 4250 2500 0    50   ~ 0
I0
Text Label 4250 2900 0    50   ~ 0
I4
Text Label 4250 3000 0    50   ~ 0
I5
Text Label 4250 3100 0    50   ~ 0
I6
Text Label 4250 3200 0    50   ~ 0
I7
NoConn ~ 5500 2600
$Comp
L Connector:Conn_01x01_Male J5
U 1 1 64D2003B
P 3050 5500
F 0 "J5" H 3158 5681 50  0000 C CNN
F 1 "Conn_01x01_Male" H 3075 5425 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Horizontal" H 3050 5500 50  0001 C CNN
F 3 "~" H 3050 5500 50  0001 C CNN
	1    3050 5500
	1    0    0    -1  
$EndComp
$EndSCHEMATC
