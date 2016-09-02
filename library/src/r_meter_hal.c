/****************************************************************************
* Title                 :   R Meter CLICK
* Filename              :   r_meter_hal.h
* Author                :   CAL
* Origin Date           :   31/08/2016
* Notes                 :   Hardware Access layer
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  31/08/16        .1              CAL       Interface Created.
*
*****************************************************************************/
/**
 * @file r_meter_hal.c
 * @brief <h2> HAL layer </h2>
 */
/******************************************************************************
* Includes
*******************************************************************************/

#include "r_meter_hal.h"

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
#if defined( __MIKROC_PRO_FOR_ARM__ )       || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )
static void         ( *write_spi_p )            ( unsigned int data_out );
static unsigned int ( *read_spi_p )             ( unsigned int buffer );

#elif defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_8051__ )    || \
      defined( __MIKROC_PRO_FOR_FT90x__ )
static void         ( *write_spi_p )            ( unsigned char data_out );
static unsigned char( *read_spi_p )             ( unsigned char buffer );

#elif defined( __MIKROC_PRO_FOR_PIC32__ )
static void         ( *write_spi_p )            ( unsigned long data_out );
static unsigned long( *read_spi_p )             ( unsigned long buffer );
#endif

#if defined( __MIKROC_PRO_FOR_ARM__ )     || \
    defined( __MIKROC_PRO_FOR_AVR__ )     || \
    defined( __MIKROC_PRO_FOR_PIC__ )     || \
    defined( __MIKROC_PRO_FOR_PIC32__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )   || \
    defined( __MIKROC_PRO_FOR_8051__ )    || \
    defined( __MIKROC_PRO_FOR_FT90x__ )
extern sfr sbit R_METER_CS;
#endif

/******************************************************************************
* Function Definitions
*******************************************************************************/
void r_meter_hal_cs( uint8_t logic )
{
    R_METER_CS = logic;
}

void r_meter_hal_init()
{
#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_AVR__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_8051__ )
    write_spi_p             = SPI_Wr_Ptr;
    read_spi_p              = SPI_Rd_Ptr;

#elif defined( __MIKROC_PRO_FOR_PIC__ )
    write_spi_p             = SPI1_Write;
    read_spi_p              = SPI1_Read;

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
    write_spi_p             = SPIM_Wr_Ptr;
    read_spi_p              = SPIM_Rd_Ptr;
#endif
}

void r_meter_hal_write( uint8_t* buffer, uint16_t count )
{
    uint8_t *ptr = buffer;

    while ( count-- )
        write_spi_p( *ptr++ );
}

void r_meter_hal_read( uint8_t* buffer, uint16_t count )
{
    uint8_t *ptr = buffer;

    while ( count-- )
        *ptr++ = read_spi_p( 0x00 );
}

void r_meter_hal_transfer( uint8_t* input, uint8_t* output, uint16_t count )
{
    uint8_t *in = input;
    uint8_t *out = output;

    while ( count-- )
        *out++ = read_spi_p( *in++ );
}

/*************** END OF FUNCTIONS ***************************************************************************/