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
Text Label 2250 3500 0    50   ~ 0
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
$Comp
L Device:C C1
U 1 1 63A69FDC
P 2000 4150
F 0 "C1" H 1875 4225 50  0000 L CNN
F 1 "0.1uF" H 2025 4225 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2038 4000 50  0001 C CNN
F 3 "~" H 2000 4150 50  0001 C CNN
	1    2000 4150
	1    0    0    -1  
$EndComp
Text Label 2000 4000 0    50   ~ 0
VCC
Text Label 2000 4300 0    50   ~ 0
GND
$Comp
L Device:R R1
U 1 1 63A6AC8F
P 2750 3650
F 0 "R1" H 2820 3696 50  0000 L CNN
F 1 "10k" H 2820 3605 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 2680 3650 50  0001 C CNN
F 3 "~" H 2750 3650 50  0001 C CNN
	1    2750 3650
	1    0    0    -1  
$EndComp
Connection ~ 2750 3500
Wire Wire Line
	2750 4000 2750 3800
Text Label 2750 4000 0    50   ~ 0
VCC
$Comp
L Device:LED D1
U 1 1 63C039D3
P 6150 2500
F 0 "D1" H 6150 2425 50  0000 C CNN
F 1 "LED" H 6025 2550 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6150 2500 50  0001 C CNN
F 3 "~" H 6150 2500 50  0001 C CNN
	1    6150 2500
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 63C04E1A
P 6450 2500
F 0 "R2" V 6375 2500 50  0000 C CNN
F 1 "1k" V 6450 2500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 6380 2500 50  0001 C CNN
F 3 "~" H 6450 2500 50  0001 C CNN
	1    6450 2500
	0    1    1    0   
$EndComp
Text Label 6600 2500 0    50   ~ 0
GND
$Comp
L Device:LED D2
U 1 1 63C0938B
P 6150 2750
F 0 "D2" H 6150 2675 50  0000 C CNN
F 1 "LED" H 6025 2800 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6150 2750 50  0001 C CNN
F 3 "~" H 6150 2750 50  0001 C CNN
	1    6150 2750
	-1   0    0    1   
$EndComp
$Comp
L Device:R R3
U 1 1 63C09391
P 6450 2750
F 0 "R3" V 6375 2750 50  0000 C CNN
F 1 "1k" V 6450 2750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 6380 2750 50  0001 C CNN
F 3 "~" H 6450 2750 50  0001 C CNN
	1    6450 2750
	0    1    1    0   
$EndComp
Text Label 6600 2750 0    50   ~ 0
GND
$Comp
L Device:LED D3
U 1 1 63C09EDC
P 6150 3000
F 0 "D3" H 6150 2925 50  0000 C CNN
F 1 "LED" H 6025 3050 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6150 3000 50  0001 C CNN
F 3 "~" H 6150 3000 50  0001 C CNN
	1    6150 3000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R4
U 1 1 63C09EE2
P 6450 3000
F 0 "R4" V 6375 3000 50  0000 C CNN
F 1 "1k" V 6450 3000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 6380 3000 50  0001 C CNN
F 3 "~" H 6450 3000 50  0001 C CNN
	1    6450 3000
	0    1    1    0   
$EndComp
Text Label 6600 3000 0    50   ~ 0
GND
$Comp
L Device:LED D4
U 1 1 63C0AB6A
P 6150 3250
F 0 "D4" H 6150 3175 50  0000 C CNN
F 1 "LED" H 6025 3300 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6150 3250 50  0001 C CNN
F 3 "~" H 6150 3250 50  0001 C CNN
	1    6150 3250
	-1   0    0    1   
$EndComp
$Comp
L Device:R R5
U 1 1 63C0AB70
P 6450 3250
F 0 "R5" V 6375 3250 50  0000 C CNN
F 1 "1k" V 6450 3250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 6380 3250 50  0001 C CNN
F 3 "~" H 6450 3250 50  0001 C CNN
	1    6450 3250
	0    1    1    0   
$EndComp
Text Label 6600 3250 0    50   ~ 0
GND
$Comp
L Device:LED D5
U 1 1 63C0B66A
P 6150 3500
F 0 "D5" H 6150 3425 50  0000 C CNN
F 1 "LED" H 6025 3550 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6150 3500 50  0001 C CNN
F 3 "~" H 6150 3500 50  0001 C CNN
	1    6150 3500
	-1   0    0    1   
$EndComp
$Comp
L Device:R R6
U 1 1 63C0B670
P 6450 3500
F 0 "R6" V 6375 3500 50  0000 C CNN
F 1 "1k" V 6450 3500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 6380 3500 50  0001 C CNN
F 3 "~" H 6450 3500 50  0001 C CNN
	1    6450 3500
	0    1    1    0   
$EndComp
Text Label 6600 3500 0    50   ~ 0
GND
$Comp
L Device:LED D6
U 1 1 63C0C1EC
P 6150 3750
F 0 "D6" H 6150 3675 50  0000 C CNN
F 1 "LED" H 6025 3800 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6150 3750 50  0001 C CNN
F 3 "~" H 6150 3750 50  0001 C CNN
	1    6150 3750
	-1   0    0    1   
$EndComp
$Comp
L Device:R R7
U 1 1 63C0C1F2
P 6450 3750
F 0 "R7" V 6375 3750 50  0000 C CNN
F 1 "1k" V 6450 3750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 6380 3750 50  0001 C CNN
F 3 "~" H 6450 3750 50  0001 C CNN
	1    6450 3750
	0    1    1    0   
$EndComp
Text Label 6600 3750 0    50   ~ 0
GND
$Comp
L Device:LED D7
U 1 1 63C0D0C3
P 6150 4000
F 0 "D7" H 6150 3925 50  0000 C CNN
F 1 "LED" H 6025 4050 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6150 4000 50  0001 C CNN
F 3 "~" H 6150 4000 50  0001 C CNN
	1    6150 4000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R8
U 1 1 63C0D0C9
P 6450 4000
F 0 "R8" V 6375 4000 50  0000 C CNN
F 1 "1k" V 6450 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 6380 4000 50  0001 C CNN
F 3 "~" H 6450 4000 50  0001 C CNN
	1    6450 4000
	0    1    1    0   
$EndComp
Text Label 6600 4000 0    50   ~ 0
GND
$Comp
L Device:LED D8
U 1 1 63C0DA60
P 6150 4250
F 0 "D8" H 6150 4175 50  0000 C CNN
F 1 "LED" H 6025 4300 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6150 4250 50  0001 C CNN
F 3 "~" H 6150 4250 50  0001 C CNN
	1    6150 4250
	-1   0    0    1   
$EndComp
$Comp
L Device:R R9
U 1 1 63C0DA66
P 6450 4250
F 0 "R9" V 6375 4250 50  0000 C CNN
F 1 "1k" V 6450 4250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 6380 4250 50  0001 C CNN
F 3 "~" H 6450 4250 50  0001 C CNN
	1    6450 4250
	0    1    1    0   
$EndComp
Text Label 6600 4250 0    50   ~ 0
GND
$Comp
L Device:C C2
U 1 1 63C0E7BA
P 2425 3725
F 0 "C2" H 2300 3800 50  0000 L CNN
F 1 "0.1uF" H 2450 3800 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2463 3575 50  0001 C CNN
F 3 "~" H 2425 3725 50  0001 C CNN
	1    2425 3725
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 3500 2425 3500
Wire Wire Line
	2425 3575 2425 3500
Connection ~ 2425 3500
Wire Wire Line
	2425 3500 2750 3500
Text Label 2425 3875 0    50   ~ 0
GND
Text Label 6000 2500 0    50   ~ 0
Q0
Text Label 6000 2750 0    50   ~ 0
Q1
Text Label 6000 3000 0    50   ~ 0
Q2
Text Label 6000 3250 0    50   ~ 0
Q3
Text Label 6000 3500 0    50   ~ 0
Q4
Text Label 6000 3750 0    50   ~ 0
Q5
Text Label 6000 4000 0    50   ~ 0
Q6
Text Label 6000 4250 0    50   ~ 0
Q7
$EndSCHEMATC
