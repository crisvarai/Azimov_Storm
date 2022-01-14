/*
 * File:   functions.c
 * Author: Cristian Vallejo
 *
 * Created on 31 de octubre de 2018, 07:18 AM
 */

#include <xc.h>
#include "functions.h"

/******************************************************************************/
//////////////////////     Inicialización del PIC      /////////////////////////
/******************************************************************************/
void ini_pic(void)
{
    //SPPCON = 0;	//disable SPP
    //SSPCON1 = 0; //disable SPI functionality 
    //CCP1CON = 0; //disable both ccp modules
    //CCP2CON = 0;
    //ADCON0 = 0; //disable ADC function 
    ADCON1=0x0F;	//make all of port A and port E digital
    //CVRCON = 0; //more disables 
    //HLVDCON = 0;
    //CMCON = 0x07; //disable comparators
    
    //RCONbits.POR = 0;
    
    INTCON2bits.RBPU = 0; // Pull-up enable 
    UCONbits.USBEN = 0; // USB module and supporting circuitry disabled (device detached)
    UCFGbits.UTRDIS = 1; //  On-chip transceiver disabled; digital transceiver interface enabled
    
    TRISA = 0xFF; // 0-3,5 Entradas (Trimpots) // 4 Entrada (Arrancador)
    TRISB = 0xFF; // Entradas (Sensores de Oponente)
    TRISC = 0xF8; // 0-2 Salidas (Control de motores) // 3 Entrada (No existe) // 4-7 Entradas (Sensor de línea)
    TRISD = 0x08; // 0-2 Salidas (Control de motores) // 3 Entrada (Mosfet) // 4-7 Salidas (LED´s)
    TRISE = 0xFF; // Entradas (Dipswitch)
    
    T0CONbits.TMR0ON = 0;
}

/******************************************************************************/
///////////////////////////          PWM            ////////////////////////////
/******************************************************************************/

//PWM periodo = (PR2 + 1)*4*Tosc*Prescaler
// 1/20KHz = (PR2 + 1)*4*(1/48MHZ)*16
// PR2 + 1 = 37.5
// PR2 = 36.5 = 36 -> 24 hex

//PWM Duty Cycle = (CCPRXL:CCPXCON<5:4>) ? TOSC ? (TMR2 Prescale Value)
//CCPRXL = PWM / Tosc * Prescaler 
// = (1/20KHz)/(1/48MHz)*16 = 150

// 150 -> 100% 
//  X  -> 50%   : X = 75  ???00010010 11?
//  X = 0x12

void ini_pwm(void)
{
    PR2 = 0x24;
    CCPR1L = 0x23;
    CCPR2L = 0x23;
    T2CON = 0x03;   // Prescaler 16 Timer 2 OFF
    CCP1CON = 0x0C;
    CCP2CON = 0x0C;
    TMR2 = 0;
    T2CONbits.TMR2ON = 1; //Timer 2 ON
}

/******************************************************************************/
////////////////////////         Retardo corto        //////////////////////////
/******************************************************************************/
void retardo_c(int t)
{
    int i;
	for (i=0;i<t;i++)
    {}
	return;
}

/******************************************************************************/
///////////////////////          Retardo largo        //////////////////////////
/******************************************************************************/
void retardo_l(int t)
{
    int i;
	for (i=0;i<t;i++)
    {
        retardo_c(400);
    }
	return;
}

/******************************************************************************/
////////////////////////         Leer Dipswitch        /////////////////////////
/******************************************************************************/
unsigned char dip_in(void)
{
    unsigned char i;
	i = PORTE;
	i = ~i;
	i = i&0x07;
	return(i);
}

/******************************************************************************/
////////////////////////        Valor de Interruptor        ////////////////////
/******************************************************************************/
int val_sw(void)
{
    unsigned char i, j;
    int k;
    i = PORTEbits.RE1;
    j = PORTEbits.RE2;
    
    if (i == 0 && j == 0)
    {
        k = 1;
        //PORTDbits.RD5 = 1;
    }
    else if (i == 0 && j == 1)
    {
        k = 2;
        //PORTDbits.RD6 = 1;
    }
    else if (i == 1 && j == 0)
    {
        k = 3;
        //PORTDbits.RD4 = 1;
    }
    else
    {
        k = 0;
    }
    return(k);
}

/******************************************************************************/
/////////////////        Funcion de Interrupción Externa        ////////////////
/******************************************************************************/

void Int_Ext(void){
    INTCONbits.INT0IE = 1; // Habilitar INT0 
    INTCONbits.INT0IF = 0; //FLag 0
    INTCON2bits.INTEDG0 = 1; //Flanco ascendete
    //INTCONbits.GIE = 1;
}

/******************************************************************************/
/////////////////        Funcion para leer sensor de oponente        ///////////
/******************************************************************************/
unsigned char opo_sen(void)
{
	unsigned char i;
	i = PORTB;
	i = ~i;
	i = i&0xF8;
    //i = i&0xFF;
	return(i);
}

/******************************************************************************/
/////////////////         Funcion para leer sensor de linea        /////////////
/******************************************************************************/
unsigned char line_sen(void)
{
	unsigned char i;
	i = PORTC;
	i = ~i;
	i = i&0xF0;
	return(i);
}

/******************************************************************************/
////////////         Funcion para leer sensor de linea (maña)        ///////////
/******************************************************************************/
/*
unsigned char line_sen_ma(void)
{
    int t, q, w, e ,r;
	unsigned char i, a;
	i = PORTC;
	i = ~i;
	i = i&0xF0;
    switch(i)
    {
        case 16:
            for(t=0; t<20; t++)
            {
                q = PORTCbits.RC6;
                q = ~q;
                if (q == 1)
                {
                    a = 0x10;
                } else
                {
                  break;
                }
            }
            return;
            break;
        case 32:
            for(t=0; t<20; t++)
            {
                w = PORTCbits.RC7;
                w = ~w;
                if (w == 1)
                {
                    a = 0x20;
                } else
                {
                  break;
                }
            }
            return;
            break;
        case 64:
            for(t=0; t<20; t++)
            {
                e = PORTCbits.RC7;
                e = ~e;
                if (e == 1)
                {
                    a = 0x40;
                } else
                {
                  break;
                }
            }
            return;
            break;
        case 128:
            for(t=0; t<20; t++)
            {
                r = PORTCbits.RC7;
                r = ~r;
                if (r == 1)
                {
                    a = 0x80;
                } else
                {
                  break;
                }
            }
            return;
            break;
        default:
            a = 0x00;
            break;
    }
	return(a);
}
*/
/******************************************************************************/
/////////////////         Funciones para control de motores         ////////////
/******************************************************************************/
void detener(int t)
{
    PORTC = 0x0F;
    PORTD = 0x0F;
    retardo_l(t);
}
////////////////////////////////////////////////////////////////////////////////
void libre(int t)
{
    PORTC = 0x0F;
    PORTD = 0x0A;
    retardo_l(t);
}
////////////////////////////////////////////////////////////////////////////////
void todo(int t)
{
    PORTC = 0x01;
    PORTD = 0x02;
    retardo_l(t);
}
////////////////////////////////////////////////////////////////////////////////
void atras(int t)
{
    PORTC = 0x00;
    PORTD = 0x05;
    retardo_l(t);
}
////////////////////////////////////////////////////////////////////////////////
void gir_izq(int t)
{
    libre(30);
    PORTC = 0x00;
    PORTD = 0x03;
    retardo_l(t);
    detener(25);
}
////////////////////////////////////////////////////////////////////////////////
void gir_der(int t)
{
    libre(30);
    PORTC = 0x01;
    PORTD = 0x04;
    retardo_l(t);
    detener(25);
}
////////////////////////////////////////////////////////////////////////////////
void gir_s_izq(int t)
{
    libre(25);
    PORTC = 0x00;
    PORTD = 0x02;
    retardo_l(t);
    detener(25); 
}
////////////////////////////////////////////////////////////////////////////////
void gir_s_der(int t)
{
    libre(25);
    PORTC = 0x01;
    PORTD = 0x00;
    retardo_l(t);
    detener(25); 
}
////////////////////////////////////////////////////////////////////////////////
void gir_a_izq(int t)
{
    libre(25);
    PORTC = 0x00;
    PORTD = 0x04;
    retardo_l(t);
    detener(25); 
}
////////////////////////////////////////////////////////////////////////////////
void gir_a_der(int t)
{
    libre(25);
    PORTC = 0x00;
    PORTD = 0x01;
    retardo_l(t);
    detener(25); 
}
/*
void linea(void) {
    int d, t;
    d = line_sen();
    d = d & 0xC0;
    
    switch(d)
    {
        case 64:
            for(t=0; t<20; t++)
            {
                d = PORTCbits.RC6;
                if (d == 0)
                {
                    d = 1;
                } else
                {
                    d = 0;
                }
            }
            break;
        case 128:
            for(t=0; t<20; t++)
            {
                d = PORTCbits.RC7;
                if (d == 0)
                {
                    d = 1;
                } else
                {
                    d = 0;
                }
            }
            break;  
    }
}
*/