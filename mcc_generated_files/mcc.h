/**
    @MPLAB® Code Configurator Header File
    @File Name: mcc.h
*/

#ifndef MCC_H
#define	MCC_H
#include <xc.h>
#include "pin_manager.h"
#include "adc.h"
#include "eusart1.h"
#include "epwm1.h"

#define _XTAL_FREQ  4000000

void SYSTEM_Initialize(void);
void OSCILLATOR_Initialize(void);
void TMR0_Initialize(void);

#endif	/* MCC_H */
/** End of File */