/*
 * File:   main.c
 * Author: EDVNIL
 *
 * Created 21 maj 2023
 * Nils Edvardsson
 * PIC12F683
 * 4 bit A/D with individual out
 */

// PIC12F683 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Detect (BOR enabled)
#pragma config IESO = OFF        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

#include <xc.h>
#define PIN_1 GP0
#define PIN_2 GP1
#define PIN_3 GP2
#define PIN_4 GP5

void initAD(void)
{
    char x=0;
    ANSEL = 0b00001000; // make an3 to analog channel
    ADCON0 =0b00001100; // use GP4 as A/D input
    for(x=0; x < 32; x++){}
    ADFM = 0;   // ADRESH = msb 8-bit
    ADON = 1;   // activate A/D of the mcu
    for(x=0; x < 32; x++){}
    
}
void main(void) {
    OSCCON = 0b01001000; // 1Mhz oscillator (is enough)
    GPIO = 0;
    TRISIO = 0b00010000; // we need to make the analog pin to a digital input
    initAD();
    while(1)
    {
        GO_DONE = 1;
        while(GO_DONE){}
        char result = ADRESH;
        result >>=4;
        PIN_1 = (result & 0b0001) ? 1 : 0;
        PIN_2 = (result & 0b0010) ? 1 : 0;
        PIN_3 = (result & 0b0100) ? 1 : 0;
        PIN_4 = (result & 0b1000) ? 1 : 0;
        /*
        if(result & 0b0001){
            PIN_1 = 1;
        }else{
            PIN_1 = 0;
        }
        if(result & 0b0010){
            PIN_2 = 1;
        }else{
            PIN_2 = 0;
        }
        if(result & 0b0100){
            PIN_3 = 1;
        }else{
            PIN_3 = 0;
        }
        if(result & 0b1000){
            PIN_4 = 1;
        }else{
            PIN_4 = 0;
        }
        */
    }
    return;
}
