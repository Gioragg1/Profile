/**
  * @Company:    Electrosen Ltd.
  * @Project:    Profile (7 Leds)

  * @File       main.c
  * @Author     Alex Molotsky
  * @Modified   Gera Gurevich
  * @Version    V1.4.0
  * @Date       12.07.2015
  * @Brief      Main Source File
  ************************************************************************************************
  * @Information :
        @Device            :  PIC18LF23K22
        @Clock             :  Internal Clock 4 MHz
        @Compiler          :  XC8 v1.32
        @MPLAB             :  MPLAB X 2.15
*/

#include "mcc_generated_files/mcc.h"
#include "global.h"

/** Main application */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    //Flag structure initializations
    Flag.Start_Power=0;      // we start - no power yet                         //gg ver 1.4
    Flag.Power_Pause==0;     // no power down yet                               //gg ver 1.4
    
    Battery_test();
   
    Battery_Status=1;

    CLRWDT();
    SWDTEN=1;

    Beep();
    Beep();
    Beep();
    LED_Red(ON);
    temp=0;
    while(temp<5){
        temp++;
        __delay_ms(100);
    }
    LED_Red(OFF);
    CLRWDT();
    LED_Green(ON);
    temp=0;
    while(temp<5){
        temp++;
        __delay_ms(100);
    }
    LED_Green(OFF);
    CLRWDT();
    
    Battery_LED_Source(ON);
    LED_Driver(ON);
    
    temp=0;
     while(temp<10){
        temp++;
        __delay_ms(100);
    }
    
    LED_Driver(ON);                                                            // rev 1.2 LED_Driver(OFF);
    __delay_ms(100);
    Battery_LED_Source(OFF);
    
    // Enable high priority global interrupts
    INTEDG0=0;                  // Interrupt on falling edge
    INTCONbits.INT0E=1;         // Enables the INT0 external interrupt
    INTCONbits.INT0F=0;         // INT0 External Interrupt Flag bit - Clear
    INTCONbits.GIE = 1;         // Global Interrupt Enable bit

    EUSART1_Initialize();
    __delay_ms(100);
    
    //__delay_ms(100);  //GG
    __delay_ms(100);  //GG
    __delay_ms(100);  //GG
    __delay_ms(100);  //GG
    __delay_ms(100);  //GG
    
    CLRWDT();

    printf( "\r\n ************************\r\n" );
    printf( "\r\n   Electrosen Ltd\r\n" );
    printf( "\r\n   Profile 7 LED\r\n" );
    printf( "\r\n   Ver 1.4\r\n" );
    printf( "\r\n ************************\r\n" );

    CLRWDT();
    EPWM1_Run_Pause(OFF);
    RCSTA1bits.SPEN=0;                                                          // 0 = Serial port disabled
//------------------------------------------------------------------------------
    while(1){
        temp=7;
        while(Flag.Start_Power==0){

            CLRWDT();
            Power_Voltage=ADC_GetConversion(Vpower_test);
            if(Power_Voltage<Real_Voltage_180)   Flag.Start_Power=1;                         //  > 180 VAC
            
            if(++temp==8){                                                      // Battery test every 64 sec
                temp=0;
                Battery_test();
                if(Battery_Voltage < LB_Sleep_mode) B_Error.Low_battery=1;      // Vbat < 4Volt
                else                                B_Error.Low_battery=0;
            }
            if(B_Error.Low_battery==0)      LED_Green(ON);
            else                            LED_Red(ON);
            __delay_ms(2);
            LED_Green(OFF);
            LED_Red(OFF);

            if(Flag.Start_Power==0){
            // No power happened yet, as going to sleep    
                CLRWDT();
                Sleep();
            }
        }
    
        __delay_ms(100);  //GG        
        Power_LED_Source(ON);
        __delay_ms(100);  //GG
    
        
        
        FB_Voltage=ADC_GetConversion(VFB_test);        
        while(FB_Voltage<850)
        {
          Power_LED_Source(OFF);
          __delay_ms(100);  //GG       
          Power_LED_Source(ON);
          __delay_ms(100);  //GG
          FB_Voltage=ADC_GetConversion(VFB_test);            
        }
        
 //       __delay_ms(100);
        LED_Green(ON);        
        LED_Driver(ON);

        EPWM1_Run_Pause(ON);
        Beep();

        EUSART1_Initialize();
        counter_5sec_event=3;

        Fast_Charger(ON);
        Flag.Fast_Charge=1;

        TMR0ON=1;                                                               // Enables Timer0
        System_Status=1;

/** @Normal Mode - AC Power 220V */
        while(Flag.Power_Pause==0){

            CLRWDT();

            if(Flag.Battery_Test==1){
                Flag.Battery_Test=0;
                Battery_test();
                if(Flag.Fast_Charge==ON){
                    if(Battery_Voltage > Battery_NC_Charge){
                        B_Error.Not_battery=1;
                        Battery_Status=4;
                    }
                    else{
                        B_Error.Not_battery=0;
                        Battery_Status=1;
                        if(Battery_Voltage > Full_Battery){                     // 5.9volt ????????
                            Fast_Charger(OFF);
                            Flag.Fast_Charge=0;
                        }
                    }
                }
                else{
                    if(Battery_Voltage < Battery_NC_nCharge){
                        B_Error.Not_battery=1;
                        Battery_Status=4;
                    }
                    else{
                        B_Error.Not_battery=0;
                        Battery_Status=1;
                    }
                }
             }

            if(Flag.Events_5sec==1){
                Flag.Events_5sec=0;
                Send_Data();

                if(B_Error.Not_battery==1){
                    LED_Green(OFF);
                    LED_Red(ON);
                    Beep();
                    LED_Red(OFF);
                    LED_Green(ON);
                }

                if(B_Error.Weekly_test_fail==1){                                // 2 blink Red LED every 5 Sec
                    LED_Green(OFF);
                    LED_Red(ON);
                    __delay_ms(100);
                    LED_Red(OFF);
                    __delay_ms(100);
                    LED_Red(ON);
                    __delay_ms(100);
                    LED_Red(OFF);
                    LED_Green(ON);
                }
                if(B_Error.Yearly_test_fail==1){                                // 3 blink Red LED every 5 Sec
                    LED_Green(OFF);
                    LED_Red(ON);                    // 1
                    __delay_ms(100);
                    LED_Red(OFF);
                    __delay_ms(100);
                    LED_Red(ON);                    // 2
                    __delay_ms(100);
                    LED_Red(OFF);
                    __delay_ms(100);
                    LED_Red(ON);                    // 3
                    __delay_ms(100);
                    LED_Red(OFF);
                    LED_Green(ON);
                }
            }
            if(Flag.Week_test==1){                                              // Weekly test
                Flag.Week_test=0;
                System_Status=3;
                Beep();
                Power_LED_Source(OFF);
                Battery_LED_Source(ON);

                while(minutes<Time_Weekly_test){                                // Weekly test
                    CLRWDT();

                    if(Flag.Battery_Test==1){
                        Flag.Battery_Test=0;
                        Battery_test();
                        if(Battery_Voltage < LB_Active_mode)    RESET();
                    }
                    if(Flag.Events_5sec==1){
                        Flag.Events_5sec=0;
                        Send_Data();
                    }
                }

                Battery_test();
                if(Battery_Voltage < LB_W_Test_mode){
                    B_Error.Weekly_test_fail=1;
                    Battery_Status=2;
                }
                else{
                    B_Error.Weekly_test_fail=0;
                    Battery_Status=1;
                }
                Battery_LED_Source(OFF);
                Power_LED_Source(ON);
                Fast_Charger(ON);
                Flag.Fast_Charge=1;
                Flag.Battery_Test=1;
            }
            if(Flag.Year_test==1){                                              // Yearly test
                Flag.Year_test=0;
                System_Status=4;
                Beep();
                seconds=0;
                minutes=0;
                hours=0;
                days=0;
                weeks=0;
                Power_LED_Source(OFF);
                Battery_LED_Source(ON);

                while(hours<2){                                                 // Yearly test 2 Hours
                    CLRWDT();

                    if(Flag.Battery_Test==1){
                        Flag.Battery_Test=0;
                        Battery_test();
                        if(Battery_Voltage < LB_Active_mode)    RESET();
                    }
                    if(Flag.Events_5sec==1){
                        Flag.Events_5sec=0;
                        Send_Data();
                    }
                }

                Battery_test();
                if(Battery_Voltage < LB_Y_Test_mode){
                    B_Error.Yearly_test_fail=1;
                    Battery_Status=3;
                }
                else{
                    B_Error.Yearly_test_fail=0;
                    Battery_Status=1;
                }
                hours=0;
                Battery_LED_Source(OFF);
                Power_LED_Source(ON);
                Fast_Charger(ON);
                Flag.Fast_Charge=1;
                Flag.Battery_Test=1;
            }
        }
        Beep();
        LED_Green(OFF);
        LED_Driver(ON);                                                         //rev 1.2 LED_Driver(OFF);
        Power_LED_Source(OFF);
        __delay_ms(100);
//        __delay_ms(100);
//        __delay_ms(100);
//        __delay_ms(100);
        Battery_LED_Source(ON);
        
         __delay_ms(100);  //GG
        FB_Voltage=ADC_GetConversion(VFB_test);        
        while(FB_Voltage<850)
        {
          Power_LED_Source(OFF);
          __delay_ms(100);  //GG       
          Power_LED_Source(ON);
          __delay_ms(100);  //GG
          FB_Voltage=ADC_GetConversion(VFB_test);            
        }
//        __delay_ms(100);
        LED_Red(ON);
        LED_Driver(ON);

        
/** @Battery Mode - AC Power pause */
        while(Flag.Power_Pause==1){
            System_Status=2;
            // Stop SW Interrupt 
            INTCONbits.INT0E=0;         // Disables the INT0 external interrupt
            INTCONbits.INT0F=0;         // INT0 External Interrupt Flag bit - Clear
    
            CLRWDT();
            if(Flag.Battery_Test==1){
                Flag.Battery_Test=0;
                Battery_test();
                if(Battery_Voltage < LB_Active_mode)    RESET();
            }            
            if(Flag.Events_5sec==1){
                Flag.Events_5sec=0;
                Send_Data();
            }
        }

        INTCONbits.INT0E=1;         // Enables the INT0 external interrupt
        INTCONbits.INT0F=0;         // INT0 External Interrupt Flag bit - Clear    
        LED_Red(OFF);
         LED_Driver(ON);                                                        // rev1.2 LED_Driver(OFF);
        Battery_LED_Source(OFF);
    }
}

//-----------------------------------------------------------------------------
void interrupt isr(){
// Interrupt Service Routine    
//----------------------------------------------------------------------------- 
        if(INT0IF==1){
            // external interrupt has occured
            // This can happen only if Test Button is pressed
            CLRWDT();

            EPWM1_Run_Pause(ON);
            Beep();
            LED_Green(ON);
            if(Flag.Start_Power==1){
                LED_Driver(ON);                                                 // rev1.2 LED_Driver(OFF);
                Power_LED_Source(OFF);
                __delay_ms(100);                                                // rev1.2
                __delay_ms(100);
                __delay_ms(50);
            }
            Battery_LED_Source(ON);
//            __delay_ms(100); // rev1.2
            
                __delay_ms(100);
            FB_Voltage=ADC_GetConversion(VFB_test);        
            while(FB_Voltage<850)
            {
                Power_LED_Source(OFF);
                __delay_ms(100);  //GG       
                Power_LED_Source(ON);
                __delay_ms(100);  //GG
                FB_Voltage=ADC_GetConversion(VFB_test);            
            }
            LED_Driver(ON);

            temp=0;
            while(SW_Test==0){
                __delay_ms(100);
                if(temp++==5){
                    temp=0;
                    Beep();                                                     // rev1.2
                    LED_Green_Toggle;
                    CLRWDT();
                }
            }

            LED_Driver(ON);                                                     // rev1.2 LED_Driver(OFF);
            Battery_LED_Source(OFF);

            Beep();

            if(Flag.Start_Power==1){
                Power_LED_Source(ON);
                __delay_ms(100);                
                FB_Voltage=ADC_GetConversion(VFB_test);        
                while(FB_Voltage<850)
                {
                    Power_LED_Source(OFF);
                    __delay_ms(100);  //GG       
                    Power_LED_Source(ON);
                    __delay_ms(100);  //GG
                    FB_Voltage=ADC_GetConversion(VFB_test);            
                }
                LED_Driver(ON);
                LED_Green(ON);
            }
            else{
                LED_Green(OFF);
                EPWM1_Run_Pause(OFF);
            }

            Fast_Charger(ON);
            Flag.Fast_Charge=1;
            Flag.Battery_Test=1;

            CLRWDT();
            INT0IF=0;
         //end external interrupt code   
        }
        
        if(TMR0IF==1){
            //timer has overflowed, causing an interrupt
            //this is 100ms inerrupt
            TMR0H=0xF3;                         // 100mSec Period
            TMR0L=0xCA;

            Power_Voltage=ADC_GetConversion(Vpower_test);
            if(Flag.Power_Pause==0){
                if(Power_Voltage>Real_Voltage_160)   Flag.Power_Pause=1;                   // < 160 VAC
            }
            else{
                if(Power_Voltage<Real_Voltage_180)   Flag.Power_Pause=0;                   // > 180 VAC
            }

            if(++counter_01_sec==10){
                //1 second counter
                counter_01_sec=0;
                
                if(++seconds==60){
                    seconds=0;
                    if(++minutes==60){
                        minutes=0;
                        if(++hours==24){
                            hours=0;
                            if(++days==7){
                                days=0;
                                Flag.Week_test=1;
                                if(++weeks==52){
                                    weeks=0;
                                    Flag.Year_test=1;
                                }
                            }
                        }
                    }
                }
                //5 seconds counter
                if(++counter_5sec_event==5){                                    // Flag "Event" every 5 Sec
                    counter_5sec_event=0;
                    Flag.Events_5sec=1;
                    Flag.Battery_Test=1;                                        // Battery test every 5 Sec
                }
                if(Flag.Fast_Charge==OFF){                                      // Slow Charge |____4Sec____|~~1Sec~~|____4Sec____|~~1Sec~~|_
                    if(++counter_slow_charge==5){
                        counter_slow_charge=0;
                        Fast_Charger(ON);
                    }
                    else Fast_Charger(OFF);
                }
            }
            TMR0IF=0;
        }
}

//------------------------------------------------------------------------------
void Beep(void){
//------------------------------------------------------------------------------    
    TRISC2=0;
    __delay_ms(100);
    TRISC2=1;
}

//------------------------------------------------------------------------------
void Send_Data(void){
//------------------------------------------------------------------------------    
/** @System_Status;             // 1-Normal mode
                                // 2-Battery mode
                                // 3-Weekly test mode
                                // 4-Yearly test mode

    @Battery_Status;            // 1-Normal
                                // 2-Low battery after weekly test
                                // 3-Low battery after yearly test
                                // 4-Not battery

    @Charge_Status              // 1-Fast charge
                                // 2-Slow charge
  */
    printf( "Vpower = %d", Power_Voltage );
    printf( " Vbattery = %d", Battery_Voltage );
    printf( " System Status = %d", System_Status );
    printf( " Battery Status = %d", Battery_Status );
    printf( " Charge Status = %d\r\n", Flag.Fast_Charge );
    printf( "\r\n");
}

//------------------------------------------------------------------------------
void Battery_test(void){
//------------------------------------------------------------------------------    
    Battery_Voltage=ADC_GetConversion(Vbat_test);
}
/** End of File */
