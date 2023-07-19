/*
 * File:   main.c
 * Author: mateus
 *
 * Created on 1 de Julho de 2023, 22:15
 */

// PIC16F886 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#pragma config FOSC = EC        // Oscillator Selection bits (EC: I/O function on RA6/OSC2/CLKOUT pin, CLKIN on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include "delay.h"




__EEPROM_DATA(1, 3, 2, 6, 4, 12, 8, 9);     //half-step activation sequence


typedef struct{
    unsigned char low:2;
    unsigned char middle:4;         //struct to manipulate portB bits
    unsigned char high:2;
}threeNibbles_t;

threeNibbles_t portBnibbles @ 0x06;


void stepper_init(){

    TRISB &= 0b11000011;
    ANSELH &= 0b010100; //portB - RB2 to RB6
    PORTB &= 0b11000011;


}




void stepper_set(int steps, unsigned int step_time){     //half-step activation on portB
    static int i = 0;
    while(steps != 0){
        portBnibbles.middle = eeprom_read(steps>=0?i++:i--);
        steps += (steps>=0)?(-1:1);
        i = (i>7)?(0:( i<0 ? 7:i));
        for(int j = 0; j<step_time; j++){
            delay_ms(1);
        }
    }

}









void main(void) {    
    stepper_init();
    GIE = 1;
    while(1){
        stepper_set(-10, 30);
    }


}