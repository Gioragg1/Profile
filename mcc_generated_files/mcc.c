/**
  @MPLAB® Code Configurator Source File
  @File Name: mcc.c
*/

// Configuration bits: selected in the GUI

// CONFIG1H
#pragma config IESO = OFF    // Internal/External Oscillator Switchover bit->Oscillator Switchover mode disabled
#pragma config PLLCFG = OFF    // 4X PLL Enable->Oscillator used directly
#pragma config PRICLKEN = OFF    // Primary clock enable bit->Primary clock can be disabled by software
#pragma config FOSC = INTIO67    // Oscillator Selection bits->Internal oscillator block
#pragma config FCMEN = OFF    // Fail-Safe Clock Monitor Enable bit->Fail-Safe Clock Monitor disabled

// CONFIG2L
#pragma config BOREN = SBORDIS    // Brown-out Reset Enable bits->Brown-out Reset enabled in hardware only (SBOREN is disabled)
#pragma config BORV = 190    // Brown Out Reset Voltage bits->VBOR set to 1.90 V nominal
#pragma config PWRTEN = OFF    // Power-up Timer Enable bit->Power up timer disabled

// CONFIG2H
#pragma config WDTPS = 2048    // Watchdog Timer Postscale Select bits->1:2048
#pragma config WDTEN = SWON    // Watchdog Timer Enable bits->WDT is controlled by SWDTEN bit of the WDTCON register

// CONFIG3H
#pragma config CCP2MX = PORTC1    // CCP2 MUX bit->CCP2 input/output is multiplexed with RC1
#pragma config P2BMX = PORTB5    // ECCP2 B output mux bit->P2B is on RB5
#pragma config HFOFST = ON    // HFINTOSC Fast Start-up->HFINTOSC output and ready status are not delayed by the oscillator stable status
#pragma config PBADEN = ON    // PORTB A/D Enable bit->PORTB<5:0> pins are configured as analog input channels on Reset
#pragma config CCP3MX = PORTB5    // P3A/CCP3 Mux bit->P3A/CCP3 input/output is multiplexed with RB5
#pragma config MCLRE = EXTMCLR    // MCLR Pin Enable bit->MCLR pin enabled, RE3 input pin disabled
#pragma config T3CMX = PORTC0    // Timer3 Clock input mux bit->T3CKI is on RC0

// CONFIG4L
#pragma config LVP = OFF    // Single-Supply ICSP Enable bit->Single-Supply ICSP disabled
#pragma config STVREN = ON    // Stack Full/Underflow Reset Enable bit->Stack full/underflow will cause Reset
#pragma config XINST = OFF    // Extended Instruction Set Enable bit->Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
#pragma config DEBUG = OFF    // Background Debug->Disabled

// CONFIG5L
#pragma config CP1 = OFF    // Code Protection Block 1->Block 1 (001000-001FFFh) not code-protected
#pragma config CP0 = OFF    // Code Protection Block 0->Block 0 (000200-000FFFh) not code-protected

// CONFIG5H
#pragma config CPB = OFF    // Boot Block Code Protection bit->Boot block (000000-0001FFh) not code-protected
#pragma config CPD = OFF    // Data EEPROM Code Protection bit->Data EEPROM not code-protected

// CONFIG6L
#pragma config WRT0 = OFF    // Write Protection Block 0->Block 0 (000200-000FFFh) not write-protected
#pragma config WRT1 = OFF    // Write Protection Block 1->Block 1 (001000-001FFFh) not write-protected

// CONFIG6H
#pragma config WRTC = OFF    // Configuration Register Write Protection bit->Configuration registers (300000-3000FFh) not write-protected
#pragma config WRTD = OFF    // Data EEPROM Write Protection bit->Data EEPROM not write-protected
#pragma config WRTB = OFF    // Boot Block Write Protection bit->Boot Block (000000-0001FFh) not write-protected

// CONFIG7L
#pragma config EBTR1 = OFF    // Table Read Protection Block 1->Block 1 (001000-001FFFh) not protected from table reads executed in other blocks
#pragma config EBTR0 = OFF    // Table Read Protection Block 0->Block 0 (000200-000FFFh) not protected from table reads executed in other blocks

// CONFIG7H
#pragma config EBTRB = OFF    // Boot Block Table Read Protection bit->Boot Block (000000-0001FFh) not protected from table reads executed in other blocks

#include "mcc.h"

void SYSTEM_Initialize(void)
{
    OSCILLATOR_Initialize();
    PIN_MANAGER_Initialize();

    ADC_Initialize();
    
//    EUSART1_Initialize();

    TMR2_Initialize();
    EPWM1_Initialize();
    EPWM1_LoadDutyValue(511);


   TMR0_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // SCS INTOSC; IDLEN disabled; IRCF 4MHz_HFINTOSC/4; 
    OSCCON = 0x52;
    // PRISD enabled; MFIOSEL disabled; SOSCGO disabled; 
    OSCCON2 = 0x04;
    // INTSRC disabled; PLLEN disabled; TUN 0x00; 
    OSCTUNE = 0x00;
    // Set the secondary oscillator
}
void TMR0_Initialize(void){
    T0CONbits.T08BIT=0;                 // Timer0 is configured as a 16-bit timer/counter
    T0CONbits.T0CS=0;                   // Internal instruction cycle clock
    T0CONbits.PSA=0;                    // Timer0 prescaler is assigned
    T0CONbits.T0PS2=1;                  // 1:32 prescale value
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS0=0;

    TMR0IP=1;                           // TMR0 Overflow Interrupt High Priority
    TMR0IE=1;                           // Enables the TMR0 overflow interrupt
    TMR0IF=0;                           // TMR0 Overflow Interrupt Flag bit - Clear

    TMR0H=0xF3;                         // 100mSec Period
    TMR0L=0xCA;

    TMR0ON=0;                           // Disables Timer0
}
/** End of File */