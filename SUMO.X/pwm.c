/*
 * File:   pwm.c
 * Author: CV
 *
 * Created on 14 de octubre de 2018, 04:08 PM
 */

//PWM periodo = (PR2 + 1)*4*Tosc*Prescaler
// 1/20KHz = (PR2 + 1)*4*(1/48MHZ)*16
// PR2 + 1 = 37.5
// PR2 = 36.5 = 36 -> 24 hex

//PWM Duty Cycle = (CCPRXL:CCPXCON<5:4>) ? TOSC ? (TMR2 Prescale Value)
//CCPRXL = PWM / Tosc * Prescaler 
// = (1/20KHz)/(1/48MHz)*16 = 150

// 150 -> 100% 
//  X  -> 98%   : X = 147  00100100 11
//  X = 0x24


#include <xc.h>
#include "config.h"

void main(){
    PR2 = 0x24;
    CCPR1L = 0x23;
    TRISCbits.RC1 = 0; //Salida
    TRISCbits.RC2 = 0;
    T2CON = 0x03;   // Prescaler 16 Timer 2 OFF
    CCP1CON = 0x0C;
    TMR2 = 0;
    T2CONbits.TMR2ON = 1; //Timer 2 ON
    while(1){
        
    }
}