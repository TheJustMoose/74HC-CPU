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
L 74xx:74LS283 U1
U 1 1 62ADB17D
P 3250 2250
F 0 "U1" H 3000 2925 50  0000 C CNN
F 1 "74LS283" H 3450 2925 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 3250 2250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS283" H 3250 2250 50  0001 C CNN
	1    3250 2250
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS283 U2
U 1 1 62ADC308
P 3250 4500
F 0 "U2" H 3000 5175 50  0000 C CNN
F 1 "74LS283" H 3450 5175 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 3250 4500 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS283" H 3250 4500 50  0001 C CNN
	1    3250 4500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J1
U 1 1 62ADD682
P 1000 2400
F 0 "J1" H 1050 1850 50  0000 C CNN
F 1 "Conn_01x08_Male" H 1000 2800 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Horizontal" H 1000 2400 50  0001 C CNN
F 3 "~" H 1000 2400 50  0001 C CNN
	1    1000 2400
	1    0    0    1   
$EndComp
$Comp
L Connector:Conn_01x08_Male J3
U 1 1 62AE3CF8
P 6700 3150
F 0 "J3" H 6750 2600 50  0000 C CNN
F 1 "Conn_01x08_Male" H 6700 3550 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Horizontal" H 6700 3150 50  0001 C CNN
F 3 "~" H 6700 3150 50  0001 C CNN
	1    6700 3150
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x08_Male J2
U 1 1 62AE45BC
P 1000 3900
F 0 "J2" H 1050 3350 50  0000 C CNN
F 1 "Conn_01x08_Male" H 1000 4300 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Horizontal" H 1000 3900 50  0001 C CNN
F 3 "~" H 1000 3900 50  0001 C CNN
	1    1000 3900
	1    0    0    1   
$EndComp
Text Label 1200 2000 0    50   ~ 0
B0
Text Label 1200 2100 0    50   ~ 0
B1
Text Label 1200 2200 0    50   ~ 0
B2
Text Label 1200 2300 0    50   ~ 0
B3
Text Label 1200 2400 0    50   ~ 0
B4
Text Label 1200 2500 0    50   ~ 0
B5
Text Label 1200 2600 0    50   ~ 0
B6
Text Label 1200 2700 0    50   ~ 0
B7
Text Label 1200 3500 0    50   ~ 0
A0
Text Label 1200 3600 0    50   ~ 0
A1
Text Label 1200 3700 0    50   ~ 0
A2
Text Label 1200 3800 0    50   ~ 0
A3
Text Label 1200 3900 0    50   ~ 0
A4
Text Label 1200 4000 0    50   ~ 0
A5
Text Label 1200 4100 0    50   ~ 0
A6
Text Label 1200 4200 0    50   ~ 0
A7
Wire Wire Line
	6250 2750 6500 2750
Wire Wire Line
	6250 2850 6500 2850
Wire Wire Line
	6250 2950 6500 2950
Wire Wire Line
	6250 3050 6500 3050
Wire Wire Line
	6250 3150 6500 3150
Wire Wire Line
	6250 3250 6500 3250
Wire Wire Line
	6250 3350 6500 3350
Wire Wire Line
	6250 3450 6500 3450
Text Label 6250 2750 0    50   ~ 0
O0
Text Label 6250 2850 0    50   ~ 0
O1
Text Label 6250 2950 0    50   ~ 0
O2
Text Label 6250 3050 0    50   ~ 0
O3
Text Label 6250 3150 0    50   ~ 0
O4
Text Label 6250 3250 0    50   ~ 0
O5
Text Label 6250 3350 0    50   ~ 0
O6
Text Label 6250 3450 0    50   ~ 0
O7
$Comp
L 74xx:74LS573 U3
U 1 1 62AED4B1
P 5750 2950
F 0 "U3" H 5750 3931 50  0000 C CNN
F 1 "74LS573" H 5750 3840 50  0000 C CNN
F 2 "Package_DIP:DIP-20_W7.62mm" H 5750 2950 50  0001 C CNN
F 3 "74xx/74hc573.pdf" H 5750 2950 50  0001 C CNN
	1    5750 2950
	1    0    0    1   
$EndComp
$Comp
L Connector:Conn_01x05_Male J4
U 1 1 62AF6747
P 1000 5200
F 0 "J4" H 1025 4900 50  0000 C CNN
F 1 "Conn_01x05_Male" H 1108 5490 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Horizontal" H 1000 5200 50  0001 C CNN
F 3 "~" H 1000 5200 50  0001 C CNN
	1    1000 5200
	1    0    0    1   
$EndComp
Text Label 1200 5400 0    50   ~ 0
~OE(C)
Text Label 1200 5300 0    50   ~ 0
~OE
$Comp
L power:GND #PWR0101
U 1 1 62AF92FA
P 3250 5300
F 0 "#PWR0101" H 3250 5050 50  0001 C CNN
F 1 "GND" H 3255 5127 50  0000 C CNN
F 2 "" H 3250 5300 50  0001 C CNN
F 3 "" H 3250 5300 50  0001 C CNN
	1    3250 5300
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0102
U 1 1 62AF9AA1
P 3250 3700
F 0 "#PWR0102" H 3250 3550 50  0001 C CNN
F 1 "VCC" H 3265 3873 50  0000 C CNN
F 2 "" H 3250 3700 50  0001 C CNN
F 3 "" H 3250 3700 50  0001 C CNN
	1    3250 3700
	1    0    0    -1  
$EndComp
Text Label 1200 5200 0    50   ~ 0
GND
Text Label 1200 5100 0    50   ~ 0
VCC
Text Label 1200 5000 0    50   ~ 0
Latch
Wire Wire Line
	2500 1950 2750 1950
Wire Wire Line
	2500 2050 2750 2050
Wire Wire Line
	2500 2150 2750 2150
Wire Wire Line
	2500 2250 2750 2250
Wire Wire Line
	2500 2450 2750 2450
Wire Wire Line
	2500 2550 2750 2550
Wire Wire Line
	2500 2650 2750 2650
Wire Wire Line
	2500 2750 2750 2750
Wire Wire Line
	2500 4200 2750 4200
Wire Wire Line
	2500 4300 2750 4300
Wire Wire Line
	2500 4400 2750 4400
Wire Wire Line
	2500 4500 2750 4500
Wire Wire Line
	2500 4700 2750 4700
Wire Wire Line
	2500 4800 2750 4800
Wire Wire Line
	2500 4900 2750 4900
Wire Wire Line
	2500 5000 2750 5000
Text Label 2500 1950 0    50   ~ 0
A0
Text Label 2500 2050 0    50   ~ 0
A1
Text Label 2500 2150 0    50   ~ 0
A2
Text Label 2500 2250 0    50   ~ 0
A3
Text Label 2500 4200 0    50   ~ 0
A4
Text Label 2500 4300 0    50   ~ 0
A5
Text Label 2500 4400 0    50   ~ 0
A6
Text Label 2500 4500 0    50   ~ 0
A7
Text Label 2500 2450 0    50   ~ 0
B0
Text Label 2500 2550 0    50   ~ 0
B1
Text Label 2500 2650 0    50   ~ 0
B2
Text Label 2500 2750 0    50   ~ 0
B3
Text Label 2500 4700 0    50   ~ 0
B4
Text Label 2500 4800 0    50   ~ 0
B5
Text Label 2500 4900 0    50   ~ 0
B6
Text Label 2500 5000 0    50   ~ 0
B7
Wire Wire Line
	3750 1750 4850 1750
Wire Wire Line
	4850 1750 4850 2750
Wire Wire Line
	4850 2750 5250 2750
Wire Wire Line
	3750 1850 4725 1850
Wire Wire Line
	4725 1850 4725 2850
Wire Wire Line
	4725 2850 5250 2850
Wire Wire Line
	3750 1950 4600 1950
Wire Wire Line
	4600 1950 4600 2950
Wire Wire Line
	4600 2950 5250 2950
Wire Wire Line
	3750 2050 4475 2050
Wire Wire Line
	4475 2050 4475 3050
Wire Wire Line
	4475 3050 5250 3050
Wire Wire Line
	3750 4300 4850 4300
Wire Wire Line
	4850 4300 4850 3450
Wire Wire Line
	4850 3450 5250 3450
Wire Wire Line
	3750 4200 4750 4200
Wire Wire Line
	4750 4200 4750 3350
Wire Wire Line
	4750 3350 5250 3350
Wire Wire Line
	3750 4100 4625 4100
Wire Wire Line
	4625 4100 4625 3250
Wire Wire Line
	4625 3250 5250 3250
Wire Wire Line
	3750 4000 4475 4000
Wire Wire Line
	4475 4000 4475 3150
Wire Wire Line
	4475 3150 5250 3150
Wire Wire Line
	3750 2250 3750 3400
Wire Wire Line
	3750 3400 2750 3400
Wire Wire Line
	2750 3400 2750 4000
$Comp
L Connector:Conn_01x01_Male J?
U 1 1 62B23640
P 1600 1700
F 0 "J?" H 1600 1825 50  0000 C CNN
F 1 "Conn_01x01_Male" H 1650 1625 50  0000 C CNN
F 2 "" H 1600 1700 50  0001 C CNN
F 3 "~" H 1600 1700 50  0001 C CNN
	1    1600 1700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J?
U 1 1 62B24097
P 4525 4500
F 0 "J?" H 4497 4524 50  0000 R CNN
F 1 "Conn_01x01_Male" H 4497 4433 50  0000 R CNN
F 2 "" H 4525 4500 50  0001 C CNN
F 3 "~" H 4525 4500 50  0001 C CNN
	1    4525 4500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3750 4500 4325 4500
Text Label 3850 4500 0    50   ~ 0
ADD_COUT
$Comp
L 74xGxx:74AHC1G08 U?
U 1 1 62B28F88
P 5125 1750
F 0 "U?" V 5054 1880 50  0000 L CNN
F 1 "74AHC1G08" V 5145 1880 50  0000 L CNN
F 2 "" H 5125 1750 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 5125 1750 50  0001 C CNN
	1    5125 1750
	0    1    1    0   
$EndComp
Text Label 5175 1450 0    50   ~ 0
~OE
Wire Wire Line
	5075 1250 5075 1450
Text Label 5075 1250 0    50   ~ 0
~OE(C)
Wire Wire Line
	5125 2000 5125 2450
Wire Wire Line
	5125 2450 5250 2450
Wire Wire Line
	5000 2550 5250 2550
Text Label 5000 2550 0    50   ~ 0
Latch
$Comp
L power:GND #PWR?
U 1 1 62B2EF0E
P 5750 3750
F 0 "#PWR?" H 5750 3500 50  0001 C CNN
F 1 "GND" H 5755 3577 50  0000 C CNN
F 2 "" H 5750 3750 50  0001 C CNN
F 3 "" H 5750 3750 50  0001 C CNN
	1    5750 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 62B2F67D
P 3250 3050
F 0 "#PWR?" H 3250 2800 50  0001 C CNN
F 1 "GND" H 3255 2877 50  0000 C CNN
F 2 "" H 3250 3050 50  0001 C CNN
F 3 "" H 3250 3050 50  0001 C CNN
	1    3250 3050
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 62B300C2
P 3250 1450
F 0 "#PWR?" H 3250 1300 50  0001 C CNN
F 1 "VCC" H 3265 1623 50  0000 C CNN
F 2 "" H 3250 1450 50  0001 C CNN
F 3 "" H 3250 1450 50  0001 C CNN
	1    3250 1450
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 62B30B45
P 5750 2150
F 0 "#PWR?" H 5750 2000 50  0001 C CNN
F 1 "VCC" H 5765 2323 50  0000 C CNN
F 2 "" H 5750 2150 50  0001 C CNN
F 3 "" H 5750 2150 50  0001 C CNN
	1    5750 2150
	1    0    0    -1  
$EndComp
$Comp
L 74xGxx:74AHC1G08 U?
U 1 1 62B312EB
P 2325 1650
F 0 "U?" H 2300 1917 50  0000 C CNN
F 1 "74AHC1G08" H 2300 1826 50  0000 C CNN
F 2 "" H 2325 1650 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 2325 1650 50  0001 C CNN
	1    2325 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2575 1650 2675 1650
Wire Wire Line
	2675 1650 2675 1750
Wire Wire Line
	2675 1750 2750 1750
Wire Wire Line
	1800 1700 2025 1700
Wire Wire Line
	1775 1600 2025 1600
Text Label 1775 1600 0    50   ~ 0
~OE
Text Label 1800 1700 0    50   ~ 0
ADD_CIN
$EndSCHEMATC
