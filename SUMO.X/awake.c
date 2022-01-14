/*
 * File:   awake.c
 * Author: CV
 *
 * Created on 17 de noviembre de 2018, 09:50 PM
 */


#include <xc.h>
#include "awake.h"
#include "functions.h"
#include "strategy.h"

/******************************************************************************/
////////////////            Funciones de segundo intento          //////////////
/******************************************************************************/
void awake2(void)
{
    INTCONbits.GIE = 0;
    int d,i;
    detener(20);
    atras(198);
    detener(20);
	gir_der(FLAG_TIME);
	
	gir_der(RF_ANGLE1);
	for(i=0;i<=SRT_ST_TIME1; i++)
    {
		d = line_sen();
		d = d & 0x03;
		if(d != 0) 
        {
            atras(130);
            break;
        }
		todo(1);
	}
	gir_izq(150);	
}
