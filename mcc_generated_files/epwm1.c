/**
  @ECCP1 Driver File
  @File Name    epwm1.c

 */

#include <xc.h>
#include "epwm1.h"

/**
  Section: Macro Declarations
*/

#define PWM1_INITIALIZE_DUTY_VALUE    511

/**
  Section: EPWM Module APIs
*/

void EPWM1_Initialize (void)
{
    // Set the PWM to the options selected in MPLAB® Code Configurator

    // P1M single; CCP1M P1AP1Chi_P1BP1Dhi; DC1B 48;
    CCP1CON = 0x3C;

    // PSS1BD P1BP1D_0; CCP1AS disabled; CCP1ASE operating; PSS1AC P1AP1C_0;
    ECCP1AS = 0x00;

    // P1RSEN automatic_restart; P1DC 0;
    PWM1CON = 0x80;

    // STR1A P1A_to_CCP1M; STR1C P1C_to_port; STR1B P1B_to_port; STR1D P1D_to_port; STR1SYNC start_at_begin;
    PSTR1CON = 0x01;

    // CCPR1L 127;
    CCPR1L = 0x7F;

    // CCPR1H 0x0;
    CCPR1H = 0x00;

    // Selecting Timer2
    CCPTMRS0bits.C1TSEL = 0x0;
}

void EPWM1_LoadDutyValue(uint16_t dutyValue)
{
   // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR1L = ((dutyValue & 0x03FC)>>2);
    
   // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP1CON = (CCP1CON & 0xCF) | ((dutyValue & 0x0003)<<4);
}

void TMR2_Initialize(void)
{
    // Set TMR2 to the options selected in the User Interface

    // TMR2ON off; T2CKPS 1:1; T2OUTPS 1:1; 
    T2CON = 0x00;

    // PR2 255; 
    PR2 = 0xFF;

    // TMR2 0x0; 
    TMR2 = 0x00;

    // Clearing IF flag.
    PIR1bits.TMR2IF = 0;

    // Start the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 1;
}
/** End of File */
