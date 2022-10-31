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
L 74xx:74HC273 U1
U 1 1 63603F32
P 3250 3000
F 0 "U1" H 3000 3650 50  0000 C CNN
F 1 "74HC273" H 3475 3650 50  0000 C CNN
F 2 "Package_DIP:DIP-20_W7.62mm" H 3250 3000 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT273.pdf" H 3250 3000 50  0001 C CNN
	1    3250 3000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x10_Male J1
U 1 1 63605023
P 1250 2900
F 0 "J1" H 1358 3481 50  0000 C CNN
F 1 "Conn_01x10_Male" H 1250 2325 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x10_P2.54mm_Vertical" H 1250 2900 50  0001 C CNN
F 3 "~" H 1250 2900 50  0001 C CNN
	1    1250 2900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x10_Male J2
U 1 1 63609ABE
P 5200 2900
F 0 "J2" H 5325 3475 50  0000 R CNN
F 1 "Conn_01x10_Male" H 5525 2325 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x10_P2.54mm_Vertical" H 5200 2900 50  0001 C CNN
F 3 "~" H 5200 2900 50  0001 C CNN
	1    5200 2900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2500 2500 2750 2500
Wire Wire Line
	2500 2600 2750 2600
Wire Wire Line
	2500 2700 2750 2700
Wire Wire Line
	2500 2800 2750 2800
Wire Wire Line
	2500 2900 2750 2900
Wire Wire Line
	2500 3000 2750 3000
Wire Wire Line
	2500 3100 2750 3100
Wire Wire Line
	2500 3200 2750 3200
Wire Wire Line
	2500 3400 2750 3400
Wire Wire Line
	2500 3500 2750 3500
Text Label 2500 3200 0    50   ~ 0
D0
Text Label 2500 2500 0    50   ~ 0
D1
Text Label 2500 2600 0    50   ~ 0
D2
Text Label 2500 3100 0    50   ~ 0
D3
Text Label 2500 3000 0    50   ~ 0
D4
Text Label 2500 2700 0    50   ~ 0
D5
Text Label 2500 2800 0    50   ~ 0
D6
Text Label 2500 2900 0    50   ~ 0
D7
Text Label 2500 3400 0    50   ~ 0
CP
Text Label 2500 3500 0    50   ~ 0
~MR
Text Label 3750 3200 0    50   ~ 0
Q0
Text Label 3750 2500 0    50   ~ 0
Q1
Text Label 3750 2600 0    50   ~ 0
Q2
Text Label 3750 3100 0    50   ~ 0
Q3
Text Label 3750 3000 0    50   ~ 0
Q4
Text Label 3750 2700 0    50   ~ 0
Q5
Text Label 3750 2800 0    50   ~ 0
Q6
Text Label 3750 2900 0    50   ~ 0
Q7
Text Label 4825 2600 0    50   ~ 0
Q0
Text Label 4825 2700 0    50   ~ 0
Q1
Text Label 4825 2800 0    50   ~ 0
Q2
Text Label 4825 2900 0    50   ~ 0
Q3
Text Label 4825 3000 0    50   ~ 0
Q4
Text Label 4825 3100 0    50   ~ 0
Q5
Text Label 4825 3200 0    50   ~ 0
Q6
Text Label 4825 3300 0    50   ~ 0
Q7
Text Label 1600 2600 0    50   ~ 0
D0
Text Label 1600 2700 0    50   ~ 0
D1
Text Label 1600 2800 0    50   ~ 0
D2
Text Label 1600 2900 0    50   ~ 0
D3
Text Label 1600 3000 0    50   ~ 0
D4
Text Label 1600 3100 0    50   ~ 0
D5
Text Label 1600 3200 0    50   ~ 0
D6
Text Label 1600 3300 0    50   ~ 0
D7
Text Label 1600 2500 0    50   ~ 0
~MR
Text Label 3250 3800 0    50   ~ 0
GND
Text Label 3250 2200 0    50   ~ 0
VCC
Text Label 1600 3400 0    50   ~ 0
GND
Text Label 4825 2500 0    50   ~ 0
VCC
Text Label 4825 3400 0    50   ~ 0
CP
Wire Wire Line
	4825 2500 5000 2500
Wire Wire Line
	4825 2600 5000 2600
Wire Wire Line
	4825 2700 5000 2700
Wire Wire Line
	4825 2800 5000 2800
Wire Wire Line
	4825 2900 5000 2900
Wire Wire Line
	4825 3000 5000 3000
Wire Wire Line
	4825 3100 5000 3100
Wire Wire Line
	4825 3200 5000 3200
Wire Wire Line
	4825 3300 5000 3300
Wire Wire Line
	4825 3400 5000 3400
Wire Wire Line
	1450 2500 1600 2500
Wire Wire Line
	1450 2600 1600 2600
Wire Wire Line
	1450 2700 1600 2700
Wire Wire Line
	1450 2800 1600 2800
Wire Wire Line
	1450 2900 1600 2900
Wire Wire Line
	1450 3000 1600 3000
Wire Wire Line
	1450 3100 1600 3100
Wire Wire Line
	1450 3200 1600 3200
Wire Wire Line
	1450 3300 1600 3300
Wire Wire Line
	1450 3400 1600 3400
$EndSCHEMATC
