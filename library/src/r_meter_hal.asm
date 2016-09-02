_r_meter_hal_cs:
;r_meter_hal.c,57 :: 		void r_meter_hal_cs( uint8_t logic )
; logic start address is: 0 (R0)
SUB	SP, SP, #4
; logic end address is: 0 (R0)
; logic start address is: 0 (R0)
;r_meter_hal.c,59 :: 		R_METER_CS = logic;
MOVW	R1, #lo_addr(R_METER_CS+0)
MOVT	R1, #hi_addr(R_METER_CS+0)
STR	R0, [R1, #0]
; logic end address is: 0 (R0)
;r_meter_hal.c,60 :: 		}
L_end_r_meter_hal_cs:
ADD	SP, SP, #4
BX	LR
; end of _r_meter_hal_cs
_r_meter_hal_init:
;r_meter_hal.c,62 :: 		void r_meter_hal_init()
SUB	SP, SP, #4
;r_meter_hal.c,69 :: 		write_spi_p             = SPI_Wr_Ptr;
MOVW	R0, #lo_addr(_SPI_Wr_Ptr+0)
MOVT	R0, #hi_addr(_SPI_Wr_Ptr+0)
LDR	R1, [R0, #0]
MOVW	R0, #lo_addr(r_meter_hal_write_spi_p+0)
MOVT	R0, #hi_addr(r_meter_hal_write_spi_p+0)
STR	R1, [R0, #0]
;r_meter_hal.c,70 :: 		read_spi_p              = SPI_Rd_Ptr;
MOVW	R0, #lo_addr(_SPI_Rd_Ptr+0)
MOVT	R0, #hi_addr(_SPI_Rd_Ptr+0)
LDR	R1, [R0, #0]
MOVW	R0, #lo_addr(r_meter_hal_read_spi_p+0)
MOVT	R0, #hi_addr(r_meter_hal_read_spi_p+0)
STR	R1, [R0, #0]
;r_meter_hal.c,80 :: 		}
L_end_r_meter_hal_init:
ADD	SP, SP, #4
BX	LR
; end of _r_meter_hal_init
_r_meter_hal_write:
;r_meter_hal.c,82 :: 		void r_meter_hal_write( uint8_t* buffer, uint16_t count )
; count start address is: 4 (R1)
; buffer start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
UXTH	R2, R1
; count end address is: 4 (R1)
; buffer end address is: 0 (R0)
; buffer start address is: 0 (R0)
; count start address is: 8 (R2)
;r_meter_hal.c,84 :: 		uint8_t *ptr = buffer;
; ptr start address is: 4 (R1)
MOV	R1, R0
; buffer end address is: 0 (R0)
; count end address is: 8 (R2)
; ptr end address is: 4 (R1)
UXTH	R0, R2
;r_meter_hal.c,86 :: 		while( count-- )
L_r_meter_hal_write0:
; ptr start address is: 4 (R1)
; count start address is: 0 (R0)
; count start address is: 0 (R0)
UXTH	R3, R0
SUBS	R2, R0, #1
UXTH	R0, R2
; count end address is: 0 (R0)
CMP	R3, #0
IT	EQ
BEQ	L_r_meter_hal_write1
; count end address is: 0 (R0)
;r_meter_hal.c,87 :: 		write_spi_p( *ptr++ );
; count start address is: 0 (R0)
LDRB	R2, [R1, #0]
UXTB	R4, R2
STRH	R0, [SP, #4]
STR	R1, [SP, #8]
UXTH	R0, R4
MOVW	R4, #lo_addr(r_meter_hal_write_spi_p+0)
MOVT	R4, #hi_addr(r_meter_hal_write_spi_p+0)
LDR	R4, [R4, #0]
BLX	R4
LDR	R1, [SP, #8]
LDRH	R0, [SP, #4]
ADDS	R1, R1, #1
; count end address is: 0 (R0)
; ptr end address is: 4 (R1)
IT	AL
BAL	L_r_meter_hal_write0
L_r_meter_hal_write1:
;r_meter_hal.c,88 :: 		}
L_end_r_meter_hal_write:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _r_meter_hal_write
_r_meter_hal_read:
;r_meter_hal.c,90 :: 		void r_meter_hal_read( uint8_t* buffer, uint16_t count )
; buffer start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
STRH	R1, [SP, #8]
; buffer end address is: 0 (R0)
; buffer start address is: 0 (R0)
;r_meter_hal.c,92 :: 		uint8_t *ptr = buffer;
STR	R0, [SP, #4]
; buffer end address is: 0 (R0)
;r_meter_hal.c,94 :: 		while( count-- )
L_r_meter_hal_read2:
LDRH	R3, [SP, #8]
LDRH	R2, [SP, #8]
SUBS	R2, R2, #1
STRH	R2, [SP, #8]
CMP	R3, #0
IT	EQ
BEQ	L_r_meter_hal_read3
;r_meter_hal.c,95 :: 		*ptr++ = read_spi_p( 0x00 );
MOVS	R0, #0
MOVW	R4, #lo_addr(r_meter_hal_read_spi_p+0)
MOVT	R4, #hi_addr(r_meter_hal_read_spi_p+0)
LDR	R4, [R4, #0]
BLX	R4
LDR	R2, [SP, #4]
STRB	R0, [R2, #0]
LDR	R2, [SP, #4]
ADDS	R2, R2, #1
STR	R2, [SP, #4]
IT	AL
BAL	L_r_meter_hal_read2
L_r_meter_hal_read3:
;r_meter_hal.c,96 :: 		}
L_end_r_meter_hal_read:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _r_meter_hal_read
_r_meter_hal_transfer:
;r_meter_hal.c,98 :: 		void r_meter_hal_transfer( uint8_t* input, uint8_t* output, uint16_t count )
; output start address is: 4 (R1)
; input start address is: 0 (R0)
SUB	SP, SP, #16
STR	LR, [SP, #0]
STRH	R2, [SP, #12]
; output end address is: 4 (R1)
; input end address is: 0 (R0)
; input start address is: 0 (R0)
; output start address is: 4 (R1)
;r_meter_hal.c,100 :: 		uint8_t *in = input;
STR	R0, [SP, #4]
; input end address is: 0 (R0)
;r_meter_hal.c,101 :: 		uint8_t *out = output;
STR	R1, [SP, #8]
; output end address is: 4 (R1)
;r_meter_hal.c,103 :: 		while( count-- )
L_r_meter_hal_transfer4:
LDRH	R4, [SP, #12]
LDRH	R3, [SP, #12]
SUBS	R3, R3, #1
STRH	R3, [SP, #12]
CMP	R4, #0
IT	EQ
BEQ	L_r_meter_hal_transfer5
;r_meter_hal.c,104 :: 		*out++ = read_spi_p( *in++ );
LDR	R3, [SP, #4]
LDRB	R3, [R3, #0]
UXTB	R4, R3
UXTH	R0, R4
MOVW	R4, #lo_addr(r_meter_hal_read_spi_p+0)
MOVT	R4, #hi_addr(r_meter_hal_read_spi_p+0)
LDR	R4, [R4, #0]
BLX	R4
LDR	R3, [SP, #8]
STRB	R0, [R3, #0]
LDR	R3, [SP, #8]
ADDS	R3, R3, #1
STR	R3, [SP, #8]
LDR	R3, [SP, #4]
ADDS	R3, R3, #1
STR	R3, [SP, #4]
IT	AL
BAL	L_r_meter_hal_transfer4
L_r_meter_hal_transfer5:
;r_meter_hal.c,105 :: 		}
L_end_r_meter_hal_transfer:
LDR	LR, [SP, #0]
ADD	SP, SP, #16
BX	LR
; end of _r_meter_hal_transfer
