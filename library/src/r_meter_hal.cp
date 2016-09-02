#line 1 "//VBOXSVR/corey/Projects/ClickLibraries/R_Meter_Click/library/src/r_meter_hal.c"
#line 1 "//vboxsvr/corey/projects/clicklibraries/r_meter_click/library/include/r_meter_hal.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"





typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;



typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdbool.h"



 typedef char _Bool;
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stddef.h"



typedef long ptrdiff_t;


 typedef unsigned long size_t;

typedef unsigned long wchar_t;
#line 44 "//vboxsvr/corey/projects/clicklibraries/r_meter_click/library/include/r_meter_hal.h"
void r_meter_hal_cs( uint8_t logic );
#line 53 "//vboxsvr/corey/projects/clicklibraries/r_meter_click/library/include/r_meter_hal.h"
void r_meter_hal_init( void );
#line 67 "//vboxsvr/corey/projects/clicklibraries/r_meter_click/library/include/r_meter_hal.h"
void r_meter_hal_write( uint8_t* buffer, uint16_t count );
#line 81 "//vboxsvr/corey/projects/clicklibraries/r_meter_click/library/include/r_meter_hal.h"
void r_meter_hal_read( uint8_t* buffer, uint16_t count );
#line 96 "//vboxsvr/corey/projects/clicklibraries/r_meter_click/library/include/r_meter_hal.h"
void r_meter_hal_transfer( uint8_t* input, uint8_t* output, uint16_t count );
#line 29 "//VBOXSVR/corey/Projects/ClickLibraries/R_Meter_Click/library/src/r_meter_hal.c"
static void ( *write_spi_p ) ( unsigned int data_out );
static unsigned int ( *read_spi_p ) ( unsigned int buffer );
#line 51 "//VBOXSVR/corey/Projects/ClickLibraries/R_Meter_Click/library/src/r_meter_hal.c"
extern sfr sbit R_METER_CS;
#line 57 "//VBOXSVR/corey/Projects/ClickLibraries/R_Meter_Click/library/src/r_meter_hal.c"
void r_meter_hal_cs( uint8_t logic )
{
 R_METER_CS = logic;
}

void r_meter_hal_init()
{
#line 69 "//VBOXSVR/corey/Projects/ClickLibraries/R_Meter_Click/library/src/r_meter_hal.c"
 write_spi_p = SPI_Wr_Ptr;
 read_spi_p = SPI_Rd_Ptr;
#line 80 "//VBOXSVR/corey/Projects/ClickLibraries/R_Meter_Click/library/src/r_meter_hal.c"
}

void r_meter_hal_write( uint8_t* buffer, uint16_t count )
{
 uint8_t *ptr = buffer;

 while( count-- )
 write_spi_p( *ptr++ );
}

void r_meter_hal_read( uint8_t* buffer, uint16_t count )
{
 uint8_t *ptr = buffer;

 while( count-- )
 *ptr++ = read_spi_p( 0x00 );
}

void r_meter_hal_transfer( uint8_t* input, uint8_t* output, uint16_t count )
{
 uint8_t *in = input;
 uint8_t *out = output;

 while( count-- )
 *out++ = read_spi_p( *in++ );
}
