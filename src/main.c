/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include <string.h>
#include "adc_ic.h"

#define DEBUG 1

#ifdef DEBUG
#include <stdio.h>
#endif


uint8_t buffer[32];
volatile bool transferStatus = false;
volatile int global_tick = 0;

uint32_t txData = 15;
uint16_t rxData;
void SPI2_Slave_Select(int);

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    adcStartup();
    adc_channel_data adc;
    
    while ( true )
    {
        //spiSendReceiveArrays(dataTx, dataRx, numberOfBytes);
        bool result = readData(&adc);   
        #ifdef DEBUG
        if (result == true){
            printf("true\r\n");
        }
        printf("channel 0 : %d\r\n", adc.channel0);
        printf("channel 1 : %d\r\n", adc.channel1);
        printf("channel 2 : %d\r\n", adc.channel2);
        printf("channel 3 : %d\r\n", adc.channel3);
        printf("\r\n");
        #endif
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

void SPI2_Slave_Select(int num){

    switch(num){
        case 1:
            SPI2_NCS_Clear();
            CORETIMER_DelayMs(2);
            break;
            
        default:
            SPI2_NCS_Set();
            CORETIMER_DelayMs(2);
            break;
    }
    
}
/*******************************************************************************
 End of File
*/

