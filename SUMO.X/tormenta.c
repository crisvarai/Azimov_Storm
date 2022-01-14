/*
 * File:   sensor.c
 * Author: Cristian Vallejo
 *
 * Created on 28 de octubre de 2018, 11:17 PM
 */

#include <xc.h>
#include <pic18f4550.h>  
#include "config.h"
#include "functions.h"
#include "strategy.h"
#include "awake.h"

/******************************************************************************/
////////////////////          Rutina de Interrupción            ////////////////
/******************************************************************************/

void __interrupt() INT_isr(void){
    //PORTDbits.RD4 = 1;
    //retardo_l(500);
    //PORTDbits.RD4 = 0;
    int d,a,t1,t2,t3,dip;
    d = line_sen();
    d = d & 0xF0;
    a = opo_sen();
    a = a & 0xF8;
    dip = dip_in();
    t1 = 329; // 125
    t2 = 74; // 56
    t3 = 59; // 15
    
    switch(d){
        case  0: break;
        case  80:  atras(79); libre(13); gir_a_izq(131); libre(13); atras(197); gir_der(66); atras(329); break;
        case  160: atras(79); libre(13); gir_a_der(131); libre(13); atras(197); gir_izq(66); atras(329); break;
        case  128: atras(t1); if(a!=0){detener(t3);break;} else{gir_izq(t2);break;} break;
        case  64:  atras(t1); if(a!=0){detener(t3);break;} else{gir_der(t2);break;} break;
        case  192: atras(t1); if(a!=0){detener(t3);break;} else{gir_der(t2+20);break;} break;
        case  224: detener(2630);break;
        case  176: detener(2630);break;
        case  112: detener(2630);break;
        case  240: detener(2630);break;
        default:  todo(1);break;
    }

    INTCONbits.INT0IF = 0; //FLag 0
}

/******************************************************************************/
////////////////////////          Main Program            //////////////////////
/******************************************************************************/

void main(void) {
    INTCONbits.GIE = 0;
    int start,j;
    ini_pic(); //Iniciar PIC18F4550

    while(1){
        
        detener(1);
        start = PORTAbits.RA4;
        while(start == 0)
        {
            start = PORTAbits.RA4;
            detener(1);
        }
        j = dip_in();
        Int_Ext();
        INTCONbits.GIE = 1;
        ini_pwm();
        
        switch(j){
        case  0: 
            //accion_0();
            //combate();
            atras(280);
            detener(50);
            CCPR1L = 0x23;
            CCPR2L = 26;
            gir_der(90);
            PORTC = 0x01;
            PORTD = 0x02;
            retardo_l(2000);
            detener(1000);
            break;
        case  1: 
            //accion_1();
            //combate();
            atras(280);
            detener(50);
            CCPR1L = 0x23;
            CCPR2L = 26;
            gir_der(95);
            PORTC = 0x01;
            PORTD = 0x02;
            retardo_l(2000);
            detener(1000);
            break;
        case  2: 
            //accion_2();
            //combate();
            atras(280);
            detener(50);
            CCPR1L = 0x23;
            CCPR2L = 26;
            gir_der(100);
            PORTC = 0x01;
            PORTD = 0x02;
            retardo_l(2000);
            detener(1000);
            break;
        case 3:
            //accion_0();
            //combate_gr();
            atras(290);
            detener(50);
            CCPR1L = 0x23;
            CCPR2L = 26;
            gir_der(100);
            PORTC = 0x01;
            PORTD = 0x02;
            retardo_l(2000);
            detener(1000);
            break;
        case 4:
            //accion_1();
            //combate_gr();
            atras(300);
            detener(50);
            CCPR1L = 0x23;
            CCPR2L = 26;
            gir_der(100);
            PORTC = 0x01;
            PORTD = 0x02;
            retardo_l(2000);
            detener(1000);
            break;
        case 5:
            //accion_2();
            //combate_gr();
            //combate();
            atras(400);
            detener(50);
            CCPR1L = 0x23;
            CCPR2L = 26;
            gir_der(100);
            PORTC = 0x01;
            PORTD = 0x02;
            retardo_l(2000);
            detener(1000);
            break;
        case 6:
            //accion_25();
            //detener(3000);
            //combate_gr();
            break;
        case 7:
            accion_0();
            combate();
            break;
        default:
            detener(1);
            break;
    }
    }
}

/*
void main(void) {
    //int j;
    ini_pic(); //Iniciar PIC18F4550
    int start, t, h=0, g=0;

    while(1){
        detener(1);
        ini_pwm();
        //j = val_sw();
        start = PORTAbits.RA4;
        h = PORTCbits.RC6;
        g = PORTCbits.RC7;
        while(start == 1)
        {
        if (h == 0 || g == 0)
        {
            for(t=0; t<20; t++)
            {
                start = PORTAbits.RA4;
                h = PORTCbits.RC6;
                g = PORTCbits.RC7;
                if (h == 0 || g == 0)
                {
                    atras(150);
                    gir_der(100);
                    detener(1000);
                } else
                {
                  break;
                }
            }
        } else
        {
        todo(1);
        }
        start = PORTAbits.RA4;
        h = PORTCbits.RC6;
        g = PORTCbits.RC7;
        }
        detener(1);
    }
}
*/

/*
void main(void) {
    ini_pic();
    //ini_pwm();
    int start,s;
        
    while(1){
        start = PORTAbits.RA4;
        while (start == 1)
        {
            s = opo_sen();
            s = s & 0x06;
            
            if(s == 6)
            {
                PORTDbits.RD4 = 1;
            } else
            {
                PORTDbits.RD4 = 0;
            }
            start = PORTAbits.RA4;
        }
    }
}
*/

/*
void main(void) {
    ini_pic();
    //__delay_ms(1000);
    ini_pwm();
    int h = 0, t;
    //accion_0();
    while(1){
        h = PORTCbits.RC6;
        
        if (h == 0)
        {
            for(t=0; t<20; t++)
            {
                h = PORTCbits.RC6;
                if (h == 0)
                {
                    atras(300);
                    detener(10000);
                } else
                {
                    break;
                }
            }
        } else
        {
        todo(1);
        }
    }
}
*/

