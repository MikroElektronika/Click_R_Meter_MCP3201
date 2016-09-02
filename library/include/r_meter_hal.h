/****************************************************************************
* Title                 :   R Meter CLICK
* Filename              :   r_meter_hal.h
* Author                :   CAL
* Origin Date           :   31/08/2016
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials      Description
*  31/08/16    XXXXXXXXXXX         CAL      Interface Created.
*
*****************************************************************************/

/**
 * @file r_meter_hal.h
 * @brief <h2> HAL layer </h2>
 */

#ifndef R_METER_HAL_H_
#define R_METER_HAL_H_

/******************************************************************************
* Includes
*******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/******************************************************************************
* Function Prototypes
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief <h3> CS Control </h3>
 *
 * @param[in] logic - logical state of CS pin
 */
void r_meter_hal_cs( uint8_t logic );



/**
 * @brief <h3> HAL Initialization </h3>
 *
 * Hal layer initialization. Must be called before any other function.
 */
void r_meter_hal_init( void );

/**
 * @brief <h3> SPI Write </h3>
 *
 * @par
 * Writes data through SPI bus
 *
 * @note Function have no affect to the CS PIN state - chip select is
 * controled directly from HW layer.
 *
 * @param[in] buffer
 * @param[in] count
 */
void r_meter_hal_write( uint8_t* buffer, uint16_t count );

/**
 * @brief <h3> SPI Read </h3>
 *
 * @par
 * Reads data from SPI bus
 *
 * @note Function have no affect to the CS PIN state - chip select is
 * controled directly from HW layer
 *
 * @param[out] buffer
 * @param[in] count
 */
void r_meter_hal_read( uint8_t* buffer, uint16_t count );

/**
 * @brief <h3> SPI Transfer </h3>
 *
 * @par
 * Transfers data through the SPI bus.
 *
 * @note Function have no affect to the CS PIN state - chip select is
 * controled directly from HW layer
 *
 * @param[in] input
 * @param[out] output
 * @param[in] count
 */
void r_meter_hal_transfer( uint8_t* input, uint8_t* output, uint16_t count );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* R_METER_HAL_H_ */

/*** End of File **************************************************************/