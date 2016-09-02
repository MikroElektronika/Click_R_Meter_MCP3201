![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

![Diff Pressure Click](http://cdn.mikroe.com/img/click/r-meter/gallery/r-meter-click-02.png)

---
[Product Page](http://www.mikroe.com/click/r-meter/)

[Manual Page](http://docs.mikroe.com/R_Meter_click)

---

### General Description

Description Coming Soon...


---

### Example

#### Configuration
* MCU:             STM32F107VC
* Dev.Board:       EasyMx Pro v7
* Oscillator:      72 Mhz internal
* Ext. Modules:    Diff Pressure click
* SW:              MikroC PRO for ARM 4.7.4

```

/*      Functions
 ****************************/
#include <stdint.h>
#include "r_meter.h"

//sbits
sbit S1  at GPIOA_ODR.B0;
sbit S2  at GPIOD_ODR.B10;
sbit S3  at GPIOC_ODR.B2;
sbit R_METER_CS at GPIOD_ODR.B13;

//Prototypes
void system_setup( void );


    
//Main
void main()
{
    //Local Declarations
    char txt[20] = { 0 };
    float ohms_var = 0;
    
    //Setup
    system_setup();

    while (1)
    {
        ohms_var = r_meter_get_ohms();
        if( ohms_var == 0 )
            UART1_Write_Text( "Over Range\r\n" );
        else
        {
            FloatToStr( ohms_var, txt );
            UART1_Write_Text( "OHMS: " );
            UART1_Write_Text( txt );
            UART1_Write_Text( "\r\n" );
        }
        delay_ms(250);
    }
}

void system_setup( void )
{
    
    // GPIOs
    GPIO_Digital_Output( &GPIOD_BASE, _GPIO_PINMASK_10 | _GPIO_PINMASK_13 );
    GPIO_Digital_Output( &GPIOC_BASE, _GPIO_PINMASK_2 );
    GPIO_Digital_Output( &GPIOA_BASE, _GPIO_PINMASK_0 );
    GPIO_Digital_Input( &GPIOA_BASE, _GPIO_PINMASK_4 );

    //UART
    UART1_Init(9600);                      // Initialize UART module at 9600 bps
    Delay_ms(100);                         // Wait for UART module to stabilize
    UART1_Write_Text( "Starting\r\n" );
    
    //ADC
    //ADC1_Init();  //For direct analog values
    Delay_ms(200);
    UART1_Write_Text( "UART Initialized\r\n" );
    SPI3_Init_Advanced( _SPI_FPCLK_DIV4,
                          _SPI_MASTER | _SPI_8_BIT | _SPI_CLK_IDLE_LOW |
                          _SPI_SECOND_CLK_EDGE_TRANSITION | _SPI_MSB_FIRST |
                          _SPI_SS_DISABLE | _SPI_SSM_ENABLE |
                          _SPI_SSI_1,
                          &_GPIO_MODULE_SPI3_PC10_11_12 );

    Delay_ms( 200 );
    UART1_Write_Text( "SPI Initialized\r\n" );

    r_meter_init();
    UART1_Write_Text( "R Meter Initialized\r\n" );
}
```


