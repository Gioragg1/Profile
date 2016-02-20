/**
  @Pin Manager File
  @File Name: pin_manager.c
*/

#include <xc.h>
#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x01;
    //TRISA = 0x03;         //gg ver 1.4
    //ANSELA = 0x03;        //gg ver 1.4
    
    TRISA = 0x07;         //gg ver 1.4
    ANSELA = 0x07;        //gg ver 1.4


    LATB = 0x00;
    TRISB = 0x01;
    ANSELB = 0x00;
    WPUB = 0x00;

    LATC = 0x00;                        // Battery test Enable
    TRISC = 0b11000100;
    ANSELC = 0x00;

    INTCON2bits.nRBPU = 0x01;
}
/**  End of File */