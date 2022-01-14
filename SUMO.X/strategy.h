#ifndef STRATEGY_H
#define	STRATEGY_H

/******************************************************************************/
///////////////        Declaración de todas las acciones          //////////////
/******************************************************************************/
void accion_0(void);
void accion_1(void);
void accion_2(void);
void accion_13(void);
void accion_14(void);
void accion_15(void);
void accion_16(void);
void accion_25(void);
void accion_26(void);

/******************************************************************************/
//////////////////////        Funciones de combate            //////////////////
/******************************************************************************/
void combate(void);
void combate_gr(void);

/******************************************************************************/
//////////////////////         Macros del proyecto          ////////////////////
/******************************************************************************/

//Grados de giro - derecha
#define RSTP (50)  //45°
#define RBTP (100)  //90°
//Grados de giro - izquierda
#define LSTP (50)  // 45°
#define LBTP (100)  //90°

//Tiempos de espera
#define FLAG_TIME (33)
#define WAIT_TIME1 (8000)
#define WAIT_TIME2 (10000)
#define WAIT_TIME3 (23)
#define WAIT_TIME4 (10000) //3000
#define WAIT_TIME10 (7000)
#define WAIT_TIME11 (7000)

//Valores de tiempo para combate corto derecho
#define SRT_ST_TIME1 (184)
#define RF_ANGLE1 (30)    
#define LF_ANGLE1 (99)   

//Valores de tiempo para combate corto izquierdo
#define SRT_ST_TIME2 (184)
#define LF_ANGLE2 (30)   
#define RF_ANGLE2 (99)  

//Valores de tiempo para combate largo derecho
#define BRT_ST_TIME3 (295)
#define RF_ANGLE3 (53)     
#define LF_ANGLE3 (111)     
#define LF_ANGLE10 (125)  
#define BRT_ST_TIME10 (296)   

//Valores de tiempo para combate largo izquierdo
#define BRT_ST_TIME4 (295)     
#define LF_ANGLE4 (53)   
#define RF_ANGLE4 (111)  
#define RF_ANGLE10 (125)   
#define BRT_ST_TIME11 (296)

//Combate derecho
#define WAN_RT1 (46)      
#define WAN_ST_TIME1 (171) //260   
#define WAN_LT1 (37) //60
#define WAN_AT1  (72)  
#define WAN_TIMES1 (11) //16  
#define WAN_TIMES3 (8)   

//Combate izquierdo
#define WAN_LT2 (46)  
#define WAN_ST_TIME2 (171) //240   
#define WAN_RT2 (37) //50  
#define WAN_AT2  (110) 
#define WAN_TIMES2 (11) //16
#define WAN_TIMES4 (8) 

//Tiempo de espera hacia atrás
#define BACK_TIME1 (395)
#define BACK_TIME2 (158)
#define BACK_TIME3 (217) //165

//Tiempo de avance o retroceso general
#define FN_TIME (53)

//Tiempos de avance o retroceso particulares
#define FN_TIME2 (9868)  
#define FN_TIME3 (6579)  
#define FN_ST_TIME (13)  
#define FN_BW_TIME (26)   
#define FN_BST_TIME (197)  
#define FN_BBW_TIME (224)

//Tiempo de accion41, accion42
#define TMR_ST_TIME (338)

//Acciones de giro derecho e izquierdo
#define RCTP (23)
#define LCTP (23)
#define RCTP_M (33)
#define LCTP_M (33)
#define RCTP_H (46)
#define LCTP_H (46)

//Valor para giro alredor de Dohyo después de acción54, acción55
#define MWAN_BK_TIME (197)

////////////////////////////////////////////////////////////////////////////////

#ifdef	__cplusplus

#endif 

#ifdef	__cplusplus

#endif 

#endif

