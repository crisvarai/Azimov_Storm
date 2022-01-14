/*
 * File:   strategy.c
 * Author: CV
 *
 * Created on 10 de noviembre de 2018, 07:19 PM
 */

#include <xc.h>
#include "strategy.h"
#include "functions.h"
#include "awake.h"

/******************************************************************************/
//////////////////////        Acciones de movimiento            ////////////////
/******************************************************************************/
void accion_0(void)
{
    INTCONbits.GIE = 0;
    int a,j;
    for (j=1; j<=FLAG_TIME; j++)
    {
        a = opo_sen();
        a = a & 0xE8;
        switch(a)
        {
            case 8:
                gir_der(RSTP);
                return;
                break;
            case 32:
                gir_izq(LSTP);
                return;
                break;
            case 64:
                gir_der(RBTP);
                return;
                break;
            case 128:
                gir_izq(LBTP);
                return;
                break;
            default:
                detener(1);
                break;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
void accion_1(void)
{
    INTCONbits.GIE = 0;
    int d,i;

	gir_der(FLAG_TIME);
	
	gir_der(RF_ANGLE1);
	for(i=0;i<=SRT_ST_TIME1; i++){
		d = line_sen();
        d = d & 0xC0;
		if(d!=0) {atras(70);break;}
		todo(1);
		}
	gir_izq(LF_ANGLE1);
}
////////////////////////////////////////////////////////////////////////////////
void accion_2(void)
{
    INTCONbits.GIE = 0;
    int d,i;

	gir_izq(FLAG_TIME);
	
	gir_izq(LF_ANGLE2);
	for(i=0;i<=SRT_ST_TIME2;i++){
		d = line_sen();
        d = d & 0xC0;
		if(d!=0) {atras(70);break;}
		todo(1);
		}
	gir_der(RF_ANGLE2);
}
////////////////////////////////////////////////////////////////////////////////
void accion_13(void)
{
    INTCONbits.GIE = 0;
	int  a,j,i,d;
	atras(FLAG_TIME);
	for(i=0;i<= BACK_TIME2;i++){
		d = line_sen();
		d = d & 0x30;
		if(d!=0) {todo(50);break;}
		atras(1);
		}
          todo(30);
	for(j=1;j<=(WAIT_TIME4);j++){
		detener(1);
		a = opo_sen();
		a = a & 0xF8;
		if(a!=0){
			return;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
void accion_14(void)
{ 
    INTCONbits.GIE = 0;
	int  a,j,i,d;
	gir_izq(FLAG_TIME);
	gir_izq(WAIT_TIME3);
	for(i=0; i<= BACK_TIME3; i++){
		d = line_sen();
		d = d & 0x30;
		if(d!=0) {todo(100);break;}
		atras(1);
		}
           todo(60);
	for(j=1;j<=(WAIT_TIME4);j++){
		todo(1);
		a = opo_sen();
		a = a & 0xF8;
		if(a!=0){
			return;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
void accion_15(void)
{ 
    INTCONbits.GIE = 0;
	int  a,j,i,d;
	gir_der(FLAG_TIME);
	gir_der(WAIT_TIME3);
	for(i=0; i<= BACK_TIME3; i++){
		d = line_sen();
		d = d & 0x30;
		if(d!=0) {todo(100);break;}
		atras(1);
		}
           todo(60);
	for(j=1;j<=(WAIT_TIME4);j++){
		todo(1);
		a = opo_sen();
		a = a & 0xF8;
		if(a!=0){
			return;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
void accion_16(void)
{
    INTCONbits.GIE = 0;
	int d,j;

		for(j=0;j<=2000;j++){
		todo(1);
		d = line_sen();
        d = d & 0xC0;
		if(d!=0) break;
	}
    atras(100);
}
////////////////////////////////////////////////////////////////////////////////
void accion_25(void)
{
    INTCONbits.GIE = 0;
    int a,d,i,j,k,start;
    int flag = 1;
    j=0;
    k=0;
    
    gir_der(WAN_RT1);
    
    while(flag == 1)
    {
        for (i=0; i<=WAN_ST_TIME1; i++)
        { 
            d = line_sen();
            d = d & 0xC0;
            //linea();
            
            if(d != 0)
            {
                atras(110);
                gir_izq(90);
                break;
            }
            
            todo(1);
            a = opo_sen();
            a = a & 0x10;
            if(a != 0)
            {
                combate(); //Cambiar por la función de combate
            }
            else if (k >= WAN_TIMES1)
            {
                a = opo_sen();
				a = a & 0xB0; //Cambiar considerando la interrupción
                
				if(a == 16 || a == 32 || a == 48 || a == 128 || a == 144 || a == 160 || a == 176)
				{
					combate(); //Cambiar por la función de combate
				}
                else;
            }
                else;
		}
		gir_izq(WAN_LT1);

		k++;
		if(k >= WAN_TIMES1)
		{
			k = 0;
			j++;
		}
		if(j >= 1) flag = 0;
        
        start = PORTAbits.RA4;
        if (start == 0)
        {
            break;
        }
	}
	gir_izq(WAN_AT1);
}
////////////////////////////////////////////////////////////////////////////////
void accion_26(void)
{ 
    INTCONbits.GIE = 0;
    int a,d,i,j,k,start;
    int flag = 1;
    j=0;
    k=0;
    
    gir_izq(WAN_LT2);
    
    while(flag == 1)
    {
        for (i=0; i<=WAN_ST_TIME2; i++)
        {
            d = line_sen();
            d = d & 0xC0;
            //linea();
            
            if(d != 0)
            {
                atras(110); //55
                gir_der(90); //45
                break;
            }
            
            todo(1);
            a = opo_sen();
            a = a & 0x10;
            if(a != 0)
            {
                combate(); //Cambiar por la función de combate
            }
            else if (k >= WAN_TIMES2)
            {
                a = opo_sen();
				a = a & 0x58; //Cambiar considerando la interrupción
                
				if(a == 8 || a == 16 || a == 24 || a == 64 || a == 72 || a == 80 || a == 88)
				{ 
					combate(); //Cambiar por la función de combate3
				}
                else;
            }
                else;
		}
		gir_der(WAN_RT2);

		k++;
		if(k >= WAN_TIMES2)
		{
			k = 0;
			j++;
		}
		if(j >= 1) flag = 0;
        
        start = PORTAbits.RA4;
        if (start == 0)
        {
            break;
        }
	}
	gir_der(WAN_AT2); 
}

/******************************************************************************/
//////////////////////        Acciones de combate            ///////////////////
/******************************************************************************/
void combate(void)
{
    INTCONbits.GIE = 1;    
    int a,count,t,rt,start;
    count = 0;
    Int_Ext();
    t = 53;
    rt = 237; // Cambiar a 180
    
    while(1)
    {
        a = opo_sen();

        switch(a)
        {
            case  24: 
                gir_s_der(40);
                todo(t);
                break;
			case  72: 
                gir_s_der(66);
                todo(t);
                break;
			case  80: 
                gir_s_der(66);
                todo(t);
                break;
			case  88: 
                gir_s_der(66);
                todo(t);
                break;
			case  96: 
                gir_s_der(66);
                todo(t);
                break;
			case  104: 
                gir_s_der(66);
                todo(t);
                break;
			case  112: 
                gir_s_der(66);
                todo(t);
                break;
			case  120: 
                gir_s_der(66);
                todo(t);
                break;
			case   48: 
                gir_s_izq(40);
                todo(t);
                break;
            case  136: 
                gir_s_izq(66);
                todo(t);
                break;
			case  144: 
                gir_s_izq(66);
                todo(t);
                break;
			case  152: 
                gir_s_izq(66);
                todo(t);
                break;
			case  160: 
                gir_s_izq(66);
                todo(t);
                break;
			case  168: 
                gir_s_izq(66);
                todo(t);
                break;
			case  176: 
                gir_s_izq(66);
                todo(t);
                break;
			case  184: 
                gir_s_izq(66);
                todo(t);
                break;
			case  8: 
                gir_der(RSTP+3);
                break;
			case  32: 
                gir_izq(LSTP+3);
                break;
			case  64: 
                gir_der(RBTP+3);
                break;
			case 128: 
                gir_izq(LBTP+3);
                break;
			default: 
                todo(53);
                break;
        }
        
        count = count + 1;
        
        if (count > rt)
        {
            awake2();
            count=0;
        }
        
        start = PORTAbits.RA4;
        if (start == 0)
        {
            break;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
void combate_gr(void)
{
    INTCONbits.GIE = 0;    
    int a,count,t,rt,start;
    count = 0;
    Int_Ext();
    t = 53;
    rt = 237; // Cambiar a 180
    
    while(1)
    {
        a = opo_sen();

        switch(a)
        {
            case  24: 
                gir_s_der(40);
                todo(t);
                break;
			case  72: 
                gir_s_der(66);
                todo(t);
                break;
			case  80: 
                gir_s_der(66);
                todo(t);
                break;
			case  88: 
                gir_s_der(66);
                todo(t);
                break;
			case  96: 
                gir_s_der(66);
                todo(t);
                break;
			case  104: 
                gir_s_der(66);
                todo(t);
                break;
			case  112: 
                gir_s_der(66);
                todo(t);
                break;
			case  120: 
                gir_s_der(66);
                todo(t);
                break;
			case   48: 
                gir_s_izq(40);
                todo(t);
                break;
            case  136: 
                gir_s_izq(66);
                todo(t);
                break;
			case  144: 
                gir_s_izq(66);
                todo(t);
                break;
			case  152: 
                gir_s_izq(66);
                todo(t);
                break;
			case  160: 
                gir_s_izq(66);
                todo(t);
                break;
			case  168: 
                gir_s_izq(66);
                todo(t);
                break;
			case  176: 
                gir_s_izq(66);
                todo(t);
                break;
			case  184: 
                gir_s_izq(66);
                todo(t);
                break;
			case  8: 
                gir_der(RSTP+3);
                break;
			case  32: 
                gir_izq(LSTP+3);
                break;
			case  64: 
                gir_der(RBTP+3);
                break;
			case 128: 
                gir_izq(LBTP+3);
                break;
			default: 
                todo(53);
                break;
        }
        
        count = count + 1;
        
        if (count > rt)
        {
            awake2();
            count=0;
        }
        
        start = PORTAbits.RA4;
        if (start == 0)
        {
            break;
        }
    }
}