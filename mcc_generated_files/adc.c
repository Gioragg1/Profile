/**
  @A2DC Driver File
  @File Name    adc.c

*/

#include <xc.h>
#include "adc.h"

/** Section: ADC Module APIs */

//void ADC_Initialize(void)
//{
//    // set the ADC to the options selected in the User Interface
//
//    // GO_nDONE stop; ADON enabled; CHS AN0;
//    ADCON0 = 0x01;
//
//    // VREF- connected to internal signal, AVSS; VREF+ connected to internal signal, AVDD
//    ADCON1 = 0x00;
//
//    // ADFM right; ADCS FOSC/4; ACQT 8Tad;
//    ADCON2 = 0xA4;
//
//    // ADRESL 0x0;
//    ADRESL = 0x00;
//
//    // ADRESH 0x0;
//    ADRESH = 0x00;
//
//}
void ADC_Initialize(void)
{
    // set the ADC to the options selected in the User Interface

    // FIXED VOLTAGE REFERENCE CONTROL REGISTER
    VREFCON0=0b10100000;                        // bit 5-4 FVRS<1:0>: Fixed Voltage Reference Selection bits
                                                // 10 = Fixed Voltage Reference Peripheral output is 2x (2.048V)
                                                // bit 7 FVREN: Fixed Voltage Reference Enable bit
                                                // 1 = Fixed Voltage Reference is enabled

    // GO_nDONE stop; ADON enabled; CHS AN0;
    ADCON0 = 0x01;

//    // VREF- connected to internal signal, AVSS; VREF+ connected to internal signal, AVDD
//    ADCON1 = 0x00;

    // VREF- connected to FVR; VREF+ connected to internal signal, AVDD
    ADCON1 = 0b00001000;

    // ADFM right; ADCS FOSC/4; ACQT 8Tad;
    ADCON2 = 0xA4;

    // ADRESL 0x0;
    ADRESL = 0x00;

    // ADRESH 0x0;
    ADRESH = 0x00;

}
unsigned int ADC_GetConversion(unsigned char channel)
{
    // Select the A/D channel
    ADCON0bits.CHS = channel;

    // Turn on the ADC module
    ADCON0bits.ADON = 1;
/****************************************************************/
     // Start the conversion
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.GO_nDONE);
 /****************************************************************/
    // Start the conversion
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.GO_nDONE)
    {
    }
    
    // Conversion finished, return the result
    A2D_Result.H_L.LSB=ADRESL;
    A2D_Result.H_L.MSB=ADRESH;

    return (A2D_Result.i);
}
/** End of File */