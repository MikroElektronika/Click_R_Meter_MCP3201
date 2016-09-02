#line 1 "//VBOXSVR/corey/Projects/ClickLibraries/R_Meter_Click/library/src/r_meter.c"
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
#line 1 "//vboxsvr/corey/projects/clicklibraries/r_meter_click/library/include/r_meter.h"
#line 142 "//vboxsvr/corey/projects/clicklibraries/r_meter_click/library/include/r_meter.h"
void r_meter_init( void );
#line 151 "//vboxsvr/corey/projects/clicklibraries/r_meter_click/library/include/r_meter.h"
uint16_t r_meter_get_volts( void );
#line 160 "//vboxsvr/corey/projects/clicklibraries/r_meter_click/library/include/r_meter.h"
float r_meter_get_ohms( void );
#line 1 "//vboxsvr/corey/projects/clicklibraries/r_meter_click/library/include/r_meter_hal.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"
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
#line 39 "//VBOXSVR/corey/Projects/ClickLibraries/R_Meter_Click/library/src/r_meter.c"
extern sfr sbit S1;
extern sfr sbit S2;
extern sfr sbit S3;
float Gain, Rm, Rx, Voltage = 0.0, Vin;
#line 50 "//VBOXSVR/corey/Projects/ClickLibraries/R_Meter_Click/library/src/r_meter.c"
static void read_voltage_average( void );
static void calculate_r( void );
#line 55 "//VBOXSVR/corey/Projects/ClickLibraries/R_Meter_Click/library/src/r_meter.c"
static void read_voltage_average()
{
 uint16_t adc_rd, sum;
 float average;
 uint8_t i = 0;
 sum = 0;

 for (i = 0; i < 10; i++ )
 {
 adc_rd = r_meter_get_volts();
 Delay_ms(50);
 sum = sum + adc_rd;
 }

 average = sum / 10;
 Voltage = average / 2;

}

static void calculate_r( void )
{
 Gain = (Voltage / Vin);

 Rm = Rx * (Gain - 1);
 Rm = Rm - 2000;
}

void r_meter_init( void )
{
 r_meter_hal_init();
 r_meter_hal_cs( 1 );
 Voltage = 0;
 Rx = 0;
 Vin = 100;
}

uint16_t r_meter_get_volts( void )
{
 uint8_t buffer[20] = { 0 };
 uint16_t retval = 0;

 r_meter_hal_cs( 0 );
 r_meter_hal_read( &buffer, 2 );
 r_meter_hal_cs( 1 );

 retval = buffer[1];
 retval |= ( (uint16_t)buffer[0] << 8 );
 retval &= 0x1FFE;
 retval >>= 1;

 return retval;
}

float r_meter_get_ohms( void )
{
 Rx = 272;
 S1 = 1;
 S2 = 0;
 S3 = 0;

 read_voltage_average();

 if ( Voltage < 2000 )
 {
 calculate_r();
 return Rm;
 }
 else if (Voltage > 2000 )
 {
 Rx = 10010;
 S1 = 0;
 S2 = 1;
 S3 = 0;

 read_voltage_average();

 if (Voltage < 2000 )
 {
 calculate_r();
 return Rm;
 }
 }
 if (Voltage > 2000 )
 {
 Rx = 100100;
 S1 = 0;
 S2 = 0;
 S3 = 1;

 read_voltage_average();

 if (Voltage < 2000 )
 {
 calculate_r();
 return Rm;
 }
 }

 if (Voltage > 2000)
 return 0;
}
