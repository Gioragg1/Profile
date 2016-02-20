/**
  @A2DC Generated Driver API Header File
  @File Name    adc.h

*/

#ifndef _ADC_H
#define _ADC_H

#include <xc.h>

/** Section: ADC Module APIs */

#define Vbat_test       0x0
#define Vpower_test     0x01
#define VFB_test        0x02

union{
	struct{
		unsigned char LSB;
		unsigned char MSB;
	}H_L;
	unsigned int i;
} A2D_Result;

void ADC_Initialize(void);
unsigned int ADC_GetConversion(unsigned char channel);

#endif	//_ADC_H
/** End of File */

