/**
  @ECCP1 Driver Header File
  @File Name    epwm1.h

 */

#ifndef _EPWM1_H
#define _EPWM1_H

#include <xc.h>
#include <stdint.h>

/**
  Section: EPWM Module APIs
*/

void EPWM1_Initialize(void);
void EPWM1_LoadDutyValue(uint16_t dutyValue);
void TMR2_Initialize(void);

#endif  // _EPWM1_H
/** End of File */
