/*
 * File:   interrupt.c
 * Author: CV
 *
 * Created on 19 de octubre de 2018, 09:16 AM
 */

#include <xc.h>
#include "config.h"

void interrupt isr();

void main(void) {
    
    ADCON1bits.PCFG=0b1111;
    
    TRISB=0xFF;
    TRISD=0x00;
    
    RCONbits.IPEN=0;
    INTCONbits.GIE=1;
    INTCONbits.INT0IE=1;
    INTCON2bits.INTEDG0=1;
    
    while(1){
        PORTDbits.RD5=0;
        PORTDbits.RD4=1;
        __delay_ms(300);
        PORTDbits.RD4=0;
        __delay_ms(300);
    }
}

void interrupt vectorint(){
    PORTDbits.RD5=1;
    PORTDbits.RD5=0;     
    while(PORTBbits.RB0==1){
        
    }
    INTCONbits.INT0IF=0;
}
