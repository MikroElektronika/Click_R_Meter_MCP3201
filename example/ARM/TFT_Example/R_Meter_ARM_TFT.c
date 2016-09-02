#include <stdint.h>
#include "r_meter.h"


//sbits
sbit S1  at GPIOA_ODR.B0;
sbit S2  at GPIOD_ODR.B10;
sbit S3  at GPIOC_ODR.B2;
sbit R_METER_CS at GPIOD_ODR.B13;

// TFT module connections
unsigned int TFT_DataPort at GPIOE_ODR;
sbit TFT_RST at GPIOE_ODR.B8;
sbit TFT_RS at GPIOE_ODR.B12;
sbit TFT_CS at GPIOE_ODR.B15;
sbit TFT_RD at GPIOE_ODR.B10;
sbit TFT_WR at GPIOE_ODR.B11;
sbit TFT_BLED at GPIOE_ODR.B9;
// End TFT module connections

//Prototypes
void system_setup( void );
static void Display_Init( void );

//Main
void main()
{
    //Local Declarations
    char txt[20] = { 0 };
    float ohms_var = 0;

    //Setup
    system_setup();
    Display_Init();

    while (1)
    {
        ohms_var = r_meter_get_ohms();
        if( ohms_var == 0 )
        {
            TFT_Set_Brush( 1, CL_WHITE, 0,0,0,0 );
            TFT_Set_Pen(CL_WHITE, 1 );
            TFT_Rectangle( 100, 100, 320, 200 );
            TFT_Set_Font(&TFT_defaultFont, CL_BLACK, FO_HORIZONTAL);
            TFT_Write_Text( "Over Range", 150, 120 );
        }
        else
        {
            FloatToStr( ohms_var, txt );
            TFT_Set_Brush( 1, CL_WHITE, 0,0,0,0 );
            TFT_Set_Pen(CL_WHITE, 1 );
            TFT_Rectangle( 100, 100, 320, 200 );
            TFT_Set_Font(&TFT_defaultFont, CL_BLACK, FO_HORIZONTAL);
            TFT_Write_Text( "OHMS :", 150, 120 );
            TFT_Write_Text(txt, 200, 120);                                                // Display inverted string on TFT
        }
        delay_ms(250);
    }
}

static void Display_Init(){
  TFT_Init_ILI9341_8bit(320, 240);
  TFT_Set_Pen(CL_WHITE, 1);
  TFT_Set_Brush(1,CL_WHITE,0,0,0,0);
  TFT_Set_Font(TFT_defaultFont, CL_BLACK, FO_HORIZONTAL);
  TFT_Fill_Screen(CL_WHITE);
  TFT_Set_Pen(CL_Black, 1);
  TFT_Line(20, 220, 300, 220);
  TFT_LIne(20,  46, 300,  46);
  TFT_Set_Font(&TFT_defaultFont, CL_RED, FO_HORIZONTAL);
  TFT_Write_Text("R Meter click", 75, 14);
  TFT_Set_Font(&TFT_defaultFont, CL_BLACK, FO_HORIZONTAL);
  TFT_Write_Text("EasyMx PRO v7 for STM32", 19, 223);
  TFT_Set_Font(&TFT_defaultFont, CL_RED, FO_HORIZONTAL);
  TFT_Write_Text("www.mikroe.com", 200, 223);
  TFT_Set_Font(&TFT_defaultFont, CL_BLACK, FO_HORIZONTAL);
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