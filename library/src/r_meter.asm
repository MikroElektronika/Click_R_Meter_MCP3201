r_meter_read_voltage_average:
;r_meter.c,55 :: 		static void read_voltage_average()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;r_meter.c,59 :: 		uint8_t i = 0;
;r_meter.c,60 :: 		sum = 0;
; sum start address is: 8 (R2)
MOVS	R2, #0
;r_meter.c,62 :: 		for (i = 0; i < 10; i++ )
; i start address is: 4 (R1)
MOVS	R1, #0
; sum end address is: 8 (R2)
; i end address is: 4 (R1)
L_r_meter_read_voltage_average0:
; i start address is: 4 (R1)
; sum start address is: 8 (R2)
CMP	R1, #10
IT	CS
BCS	L_r_meter_read_voltage_average1
;r_meter.c,64 :: 		adc_rd = r_meter_get_volts();
STRH	R2, [SP, #4]
STRB	R1, [SP, #6]
BL	_r_meter_get_volts+0
LDRB	R1, [SP, #6]
LDRH	R2, [SP, #4]
; adc_rd start address is: 12 (R3)
UXTH	R3, R0
;r_meter.c,65 :: 		Delay_ms(50);
MOVW	R7, #10175
MOVT	R7, #9
NOP
NOP
L_r_meter_read_voltage_average3:
SUBS	R7, R7, #1
BNE	L_r_meter_read_voltage_average3
NOP
NOP
NOP
;r_meter.c,66 :: 		sum = sum + adc_rd;               // Sum of the 20 ADC readings
ADDS	R2, R2, R3
UXTH	R2, R2
; adc_rd end address is: 12 (R3)
;r_meter.c,62 :: 		for (i = 0; i < 10; i++ )
ADDS	R1, R1, #1
UXTB	R1, R1
;r_meter.c,67 :: 		}
; i end address is: 4 (R1)
IT	AL
BAL	L_r_meter_read_voltage_average0
L_r_meter_read_voltage_average1:
;r_meter.c,69 :: 		average = sum / 10;               // Average ADC value based on sum of the ADC readings
MOVS	R0, #10
UDIV	R0, R2, R0
UXTH	R0, R0
; sum end address is: 8 (R2)
BL	__UnsignedIntegralToFloat+0
;r_meter.c,70 :: 		Voltage = average / 2;            // U = (adc_rd*Vref)/1024 - 10bit ADC
MOV	R2, #1073741824
BL	__Div_FP+0
MOVW	R1, #lo_addr(_Voltage+0)
MOVT	R1, #hi_addr(_Voltage+0)
STR	R0, [R1, #0]
;r_meter.c,72 :: 		}
L_end_read_voltage_average:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of r_meter_read_voltage_average
r_meter_calculate_r:
;r_meter.c,74 :: 		static void calculate_r( void )
SUB	SP, SP, #8
STR	LR, [SP, #0]
;r_meter.c,76 :: 		Gain = (Voltage / Vin);
MOVW	R0, #lo_addr(_Vin+0)
MOVT	R0, #hi_addr(_Vin+0)
LDR	R2, [R0, #0]
MOVW	R0, #lo_addr(_Voltage+0)
MOVT	R0, #hi_addr(_Voltage+0)
LDR	R0, [R0, #0]
BL	__Div_FP+0
MOVW	R1, #lo_addr(_Gain+0)
MOVT	R1, #hi_addr(_Gain+0)
STR	R0, [R1, #0]
;r_meter.c,78 :: 		Rm = Rx * (Gain - 1);
MOV	R2, #1065353216
BL	__Sub_FP+0
MOVW	R1, #lo_addr(_Rx+0)
MOVT	R1, #hi_addr(_Rx+0)
LDR	R2, [R1, #0]
BL	__Mul_FP+0
MOVW	R1, #lo_addr(_Rm+0)
MOVT	R1, #hi_addr(_Rm+0)
STR	R1, [SP, #4]
STR	R0, [R1, #0]
;r_meter.c,79 :: 		Rm = Rm - 2000;
MOVW	R2, #0
MOVT	R2, #17658
BL	__Sub_FP+0
LDR	R1, [SP, #4]
STR	R0, [R1, #0]
;r_meter.c,80 :: 		}
L_end_calculate_r:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of r_meter_calculate_r
_r_meter_init:
;r_meter.c,82 :: 		void r_meter_init( void )
SUB	SP, SP, #4
STR	LR, [SP, #0]
;r_meter.c,84 :: 		r_meter_hal_init();
BL	_r_meter_hal_init+0
;r_meter.c,85 :: 		r_meter_hal_cs( 1 ); //Pulled high until communication begins
MOVS	R0, #1
BL	_r_meter_hal_cs+0
;r_meter.c,86 :: 		Voltage = 0;
MOV	R1, #0
MOVW	R0, #lo_addr(_Voltage+0)
MOVT	R0, #hi_addr(_Voltage+0)
STR	R1, [R0, #0]
;r_meter.c,87 :: 		Rx = 0;                                //ohm   Rx1=272ohm  Rx2=1065  Rx3=100000+??
MOV	R1, #0
MOVW	R0, #lo_addr(_Rx+0)
MOVT	R0, #hi_addr(_Rx+0)
STR	R1, [R0, #0]
;r_meter.c,88 :: 		Vin = 100;                             //mV - It can be read before the measurement that is not const .
MOVW	R1, #0
MOVT	R1, #17096
MOVW	R0, #lo_addr(_Vin+0)
MOVT	R0, #hi_addr(_Vin+0)
STR	R1, [R0, #0]
;r_meter.c,89 :: 		}
L_end_r_meter_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _r_meter_init
_r_meter_get_volts:
;r_meter.c,91 :: 		uint16_t r_meter_get_volts( void )
SUB	SP, SP, #24
STR	LR, [SP, #0]
;r_meter.c,93 :: 		uint8_t buffer[20] = { 0 };
ADD	R11, SP, #4
ADD	R10, R11, #20
MOVW	R12, #lo_addr(?ICSr_meter_get_volts_buffer_L0+0)
MOVT	R12, #hi_addr(?ICSr_meter_get_volts_buffer_L0+0)
BL	___CC2DW+0
;r_meter.c,94 :: 		uint16_t retval = 0;
;r_meter.c,96 :: 		r_meter_hal_cs( 0 );
MOVS	R0, #0
BL	_r_meter_hal_cs+0
;r_meter.c,97 :: 		r_meter_hal_read( &buffer, 2 );
ADD	R0, SP, #4
MOVS	R1, #2
BL	_r_meter_hal_read+0
;r_meter.c,98 :: 		r_meter_hal_cs( 1 );
MOVS	R0, #1
BL	_r_meter_hal_cs+0
;r_meter.c,100 :: 		retval = buffer[1];
ADD	R1, SP, #4
ADDS	R0, R1, #1
LDRB	R0, [R0, #0]
; retval start address is: 8 (R2)
UXTB	R2, R0
;r_meter.c,101 :: 		retval |= ( (uint16_t)buffer[0] << 8 );
LDRB	R0, [R1, #0]
LSLS	R0, R0, #8
UXTH	R0, R0
ORR	R1, R2, R0, LSL #0
UXTH	R1, R1
; retval end address is: 8 (R2)
;r_meter.c,102 :: 		retval &= 0x1FFE;
MOVW	R0, #8190
AND	R0, R1, R0, LSL #0
UXTH	R0, R0
;r_meter.c,103 :: 		retval >>= 1;
LSRS	R0, R0, #1
;r_meter.c,105 :: 		return retval;
;r_meter.c,106 :: 		}
L_end_r_meter_get_volts:
LDR	LR, [SP, #0]
ADD	SP, SP, #24
BX	LR
; end of _r_meter_get_volts
_r_meter_get_ohms:
;r_meter.c,108 :: 		float r_meter_get_ohms( void )
SUB	SP, SP, #4
STR	LR, [SP, #0]
;r_meter.c,110 :: 		Rx = 272;
MOVW	R1, #0
MOVT	R1, #17288
MOVW	R0, #lo_addr(_Rx+0)
MOVT	R0, #hi_addr(_Rx+0)
STR	R1, [R0, #0]
;r_meter.c,111 :: 		S1 = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(S1+0)
MOVT	R0, #hi_addr(S1+0)
STR	R1, [R0, #0]
;r_meter.c,112 :: 		S2 = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(S2+0)
MOVT	R0, #hi_addr(S2+0)
STR	R1, [R0, #0]
;r_meter.c,113 :: 		S3 = 0;
MOVW	R0, #lo_addr(S3+0)
MOVT	R0, #hi_addr(S3+0)
STR	R1, [R0, #0]
;r_meter.c,115 :: 		read_voltage_average();
BL	r_meter_read_voltage_average+0
;r_meter.c,117 :: 		if ( Voltage < 2000 )
MOVW	R0, #lo_addr(_Voltage+0)
MOVT	R0, #hi_addr(_Voltage+0)
LDR	R2, [R0, #0]
MOVW	R0, #0
MOVT	R0, #17658
BL	__Compare_FP+0
MOVW	R0, #0
BLE	L__r_meter_get_ohms17
MOVS	R0, #1
L__r_meter_get_ohms17:
CMP	R0, #0
IT	EQ
BEQ	L_r_meter_get_ohms5
;r_meter.c,119 :: 		calculate_r();
BL	r_meter_calculate_r+0
;r_meter.c,120 :: 		return Rm;
MOVW	R0, #lo_addr(_Rm+0)
MOVT	R0, #hi_addr(_Rm+0)
LDR	R0, [R0, #0]
IT	AL
BAL	L_end_r_meter_get_ohms
;r_meter.c,121 :: 		}
L_r_meter_get_ohms5:
;r_meter.c,122 :: 		else if (Voltage > 2000 )
MOVW	R0, #lo_addr(_Voltage+0)
MOVT	R0, #hi_addr(_Voltage+0)
LDR	R2, [R0, #0]
MOVW	R0, #0
MOVT	R0, #17658
BL	__Compare_FP+0
MOVW	R0, #0
BGE	L__r_meter_get_ohms18
MOVS	R0, #1
L__r_meter_get_ohms18:
CMP	R0, #0
IT	EQ
BEQ	L_r_meter_get_ohms7
;r_meter.c,124 :: 		Rx = 10010;
MOVW	R1, #26624
MOVT	R1, #17948
MOVW	R0, #lo_addr(_Rx+0)
MOVT	R0, #hi_addr(_Rx+0)
STR	R1, [R0, #0]
;r_meter.c,125 :: 		S1 = 0;
MOVS	R2, #0
SXTB	R2, R2
MOVW	R0, #lo_addr(S1+0)
MOVT	R0, #hi_addr(S1+0)
STR	R2, [R0, #0]
;r_meter.c,126 :: 		S2 = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(S2+0)
MOVT	R0, #hi_addr(S2+0)
STR	R1, [R0, #0]
;r_meter.c,127 :: 		S3 = 0;
MOVW	R0, #lo_addr(S3+0)
MOVT	R0, #hi_addr(S3+0)
STR	R2, [R0, #0]
;r_meter.c,129 :: 		read_voltage_average();
BL	r_meter_read_voltage_average+0
;r_meter.c,131 :: 		if (Voltage < 2000 )
MOVW	R0, #lo_addr(_Voltage+0)
MOVT	R0, #hi_addr(_Voltage+0)
LDR	R2, [R0, #0]
MOVW	R0, #0
MOVT	R0, #17658
BL	__Compare_FP+0
MOVW	R0, #0
BLE	L__r_meter_get_ohms19
MOVS	R0, #1
L__r_meter_get_ohms19:
CMP	R0, #0
IT	EQ
BEQ	L_r_meter_get_ohms8
;r_meter.c,133 :: 		calculate_r();
BL	r_meter_calculate_r+0
;r_meter.c,134 :: 		return Rm;
MOVW	R0, #lo_addr(_Rm+0)
MOVT	R0, #hi_addr(_Rm+0)
LDR	R0, [R0, #0]
IT	AL
BAL	L_end_r_meter_get_ohms
;r_meter.c,135 :: 		}
L_r_meter_get_ohms8:
;r_meter.c,136 :: 		}
L_r_meter_get_ohms7:
;r_meter.c,137 :: 		if (Voltage > 2000 )
MOVW	R0, #lo_addr(_Voltage+0)
MOVT	R0, #hi_addr(_Voltage+0)
LDR	R2, [R0, #0]
MOVW	R0, #0
MOVT	R0, #17658
BL	__Compare_FP+0
MOVW	R0, #0
BGE	L__r_meter_get_ohms20
MOVS	R0, #1
L__r_meter_get_ohms20:
CMP	R0, #0
IT	EQ
BEQ	L_r_meter_get_ohms9
;r_meter.c,139 :: 		Rx = 100100;
MOVW	R1, #33280
MOVT	R1, #18371
MOVW	R0, #lo_addr(_Rx+0)
MOVT	R0, #hi_addr(_Rx+0)
STR	R1, [R0, #0]
;r_meter.c,140 :: 		S1 = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(S1+0)
MOVT	R0, #hi_addr(S1+0)
STR	R1, [R0, #0]
;r_meter.c,141 :: 		S2 = 0;
MOVW	R0, #lo_addr(S2+0)
MOVT	R0, #hi_addr(S2+0)
STR	R1, [R0, #0]
;r_meter.c,142 :: 		S3 = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(S3+0)
MOVT	R0, #hi_addr(S3+0)
STR	R1, [R0, #0]
;r_meter.c,144 :: 		read_voltage_average();
BL	r_meter_read_voltage_average+0
;r_meter.c,146 :: 		if (Voltage < 2000 )
MOVW	R0, #lo_addr(_Voltage+0)
MOVT	R0, #hi_addr(_Voltage+0)
LDR	R2, [R0, #0]
MOVW	R0, #0
MOVT	R0, #17658
BL	__Compare_FP+0
MOVW	R0, #0
BLE	L__r_meter_get_ohms21
MOVS	R0, #1
L__r_meter_get_ohms21:
CMP	R0, #0
IT	EQ
BEQ	L_r_meter_get_ohms10
;r_meter.c,148 :: 		calculate_r();
BL	r_meter_calculate_r+0
;r_meter.c,149 :: 		return Rm;
MOVW	R0, #lo_addr(_Rm+0)
MOVT	R0, #hi_addr(_Rm+0)
LDR	R0, [R0, #0]
IT	AL
BAL	L_end_r_meter_get_ohms
;r_meter.c,150 :: 		}
L_r_meter_get_ohms10:
;r_meter.c,151 :: 		}
L_r_meter_get_ohms9:
;r_meter.c,153 :: 		if (Voltage > 2000)
MOVW	R0, #lo_addr(_Voltage+0)
MOVT	R0, #hi_addr(_Voltage+0)
LDR	R2, [R0, #0]
MOVW	R0, #0
MOVT	R0, #17658
BL	__Compare_FP+0
MOVW	R0, #0
BGE	L__r_meter_get_ohms22
MOVS	R0, #1
L__r_meter_get_ohms22:
CMP	R0, #0
IT	EQ
BEQ	L_r_meter_get_ohms11
;r_meter.c,154 :: 		return 0; //Over Range
MOV	R0, #0
IT	AL
BAL	L_end_r_meter_get_ohms
L_r_meter_get_ohms11:
;r_meter.c,155 :: 		}
L_end_r_meter_get_ohms:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _r_meter_get_ohms
