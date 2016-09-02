/****************************************************************************
* Title                 :   R Meter CLICK
* Filename              :   r_meter.h
* Author                :   CAL
* Origin Date           :   31/08/2016
* Notes                 :   Hardware layer
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials      Description
*  31/08/16         .1              CAL     Interface Created.
*
*****************************************************************************/
/**
 * @file r_meter.c
 * @brief <h3> Hardware Layer </h3>
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include "r_meter.h"
#include "r_meter_hal.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
extern sfr sbit S1;
extern sfr sbit S2;
extern sfr sbit S3;
float Gain, Rm, Rx, Voltage = 0.0, Vin;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Private Function Definitions
*******************************************************************************/
static void read_voltage_average( void );
static void calculate_r( void );
/******************************************************************************
* Public Function Definitions
*******************************************************************************/
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
        sum = sum + adc_rd;   // Sum of the 20 ADC readings
    }

    average = sum / 10;       // Average ADC value based on sum of the ADC readings
    Voltage = average / 2;    // U = (adc_rd*Vref)/1024 - 10bit ADC

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
    r_meter_hal_cs( 1 );    //Pulled high until communication begins
    Voltage = 0;
    Rx = 0;                 //ohm   Rx1=272ohm  Rx2=1065  Rx3=100000+??
    Vin = 100;              //mV - It can be read before the measurement that is not const .
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
        return 0; //Over Range
}
/*************** END OF FUNCTIONS *********************************************/