/**
  @EUSART1 Driver API Header File
  @File Name eusart1.h

*/

#ifndef _EUSART1_H
#define _EUSART1_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define EUSART1_DataReady  (PIR1bits.RC1IF)

void EUSART1_Initialize(void);
uint8_t EUSART1_Read(void);
void EUSART1_Write(uint8_t txData);

#endif  // _EUSART1_H
/** End of File */