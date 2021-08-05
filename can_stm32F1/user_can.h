/***************************************************
*Name file				:		user_can.h
*Day							:		24/03/2016	
*Athor						:   Vu Viet Hoang
*************************************************/


#ifndef __USER_CAN_H
#define __USER_CAN_H    24032016

#include "main.h"


void NVIC_Configuration(void);
void CAN_Configuration(void);
void Init_RxMes(CanRxMsg *RxMessage);

void Delay(void);
#endif
