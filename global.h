/**
  * @Company:    Electrosen Ltd.
  * @Project:    Profile (7 Leds)

  * @File       global.h
  * @Author     Alex Molotsky
  * @Version    V1.0.1
  * @Date       03.08.2014
  * @Brief      Define all global variables and constants and subroutines for main program & headers
  ************************************************************************************************
*/

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

// #define _XTAL_FREQ 4000000

#define BIT0	0x01
#define BIT1	0x02
#define BIT2	0x04
#define BIT3	0x08
#define BIT4	0x10
#define BIT5	0x20
#define BIT6	0x40
#define BIT7	0x80

#define ON		1
#define OFF		0

#define High		1
#define Low		0

#define OUT		0
#define IN              1

//LEDs
#define LED_Red(b)          (b==0) ? (LATB &= ~BIT5) : (LATB |= BIT5)
#define LED_Green(b)        (b==0) ? (LATB &= ~BIT4) : (LATB |= BIT4)
#define LED_Red_Toggle      (LATB ^= BIT5)
#define LED_Green_Toggle    (LATB ^= BIT4)

#define Battey_test_EN(b)       (b==1) ? (LATC &= ~BIT0) : (LATC |= BIT0)
#define Battey_test_IO(b)       (b==0) ? (TRISA &= ~BIT0) : (TRISA |= BIT0)
#define Battey_test_IO_port(b)  (b==0) ? (LATA &= ~BIT0) : (LATA |= BIT0)
#define Fast_Charger(b)         (b==1) ? (LATC &= ~BIT1) : (LATC |= BIT1)
#define LED_Driver(b)           (b==0) ? (LATC &= ~BIT3) : (LATC |= BIT3)
#define Power_LED_Source(b)     (b==0) ? (LATC &= ~BIT4) : (LATC |= BIT4)
#define Battery_LED_Source(b)   (b==0) ? (LATC &= ~BIT5) : (LATC |= BIT5)

//Buttons
#define SW_Test		PORTBbits.RB0

#define EPWM1_Run_Pause(b)      (b==0) ? (T2CON &= ~BIT2) : (T2CON |= BIT2)

#define Battery_NC_nCharge      372             // 240             // 3.2 volt
#define Battery_NC_Charge       930             // 570             // 8.0 volt
#define LB_Sleep_mode           465             // 288             // 4.0 volt
#define LB_W_Test_mode          535             // 330             // 4.6 volt
#define LB_Y_Test_mode          477             // 296             // 4.1 volt
#define LB_Active_mode          442             // 275             // 3.8 volt Stop ->go to Sleep
#define Full_Battery            686             // 420             // 5.9 volt

#define Time_Weekly_test        2               // 2 min
#define Real_Voltage_160        530             
#define Real_Voltage_180        450             

union {
    struct {
        unsigned Start_Power            :1;
        unsigned Battery_Test           :1;
        unsigned Fast_Charge            :1;
        unsigned Power_Pause            :1;
        unsigned Week_test              :1;
        unsigned Year_test              :1;
        unsigned Events_5sec            :1;
    };
} Flag;
union {
    struct {
        unsigned Low_battery            :1;
        unsigned Weekly_test_fail       :1;
        unsigned Yearly_test_fail       :1;
        unsigned Not_battery            :1;
    };
} B_Error;

unsigned char temp;
unsigned char counter_01_sec;
unsigned char seconds;
unsigned char minutes;
unsigned char hours;
unsigned char days;
unsigned char weeks;

unsigned char counter_5sec_event;
unsigned char counter_slow_charge;

unsigned int Power_Voltage;
unsigned int Battery_Voltage;
unsigned int FB_Voltage;
unsigned char System_Status;            // 1-Normal mode
                                        // 2-Battery mode
                                        // 3-Weekly test mode
                                        // 4-Yearly test mode

unsigned char Battery_Status;           // 1-Normal
                                        // 2-Low battery after weekly test
                                        // 3-Low battery after yearly test

void Beep(void);
void Send_Data(void);
void Battery_test(void);

//#define	Nop()		asm(" nop")

//bit Flag_Start;
//bit Flag_Re_Start;
//unsigned char Timer;
//unsigned char seconds;
//unsigned char minutes;
//unsigned char hours;
//
//
//void INIT_GLOBAL_PORTS(void);
//void Interrupt_SW_OFF_Galay(unsigned char k);
//void Interrupt_SW_ON_Key(unsigned char k);
//void PWM_init(void);
//void Beep(void);
//void Read_DIP_Switch(void);
//
//void interrupt Switch_Int(void);

#endif //__GLOBAL_H__
/** End of File */

