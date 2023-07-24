/*
 * RTOS.c
 *
 * Created: 9/6/2021 12:52:19 PM
 *  Author: EL-talkhawy
 */ 

/*#include "RTOS.h"
Task_t task_arr [TASK_NUM] = {0} ;

static void Algoithim (void)
{
	u8 i ; 
	for(i=0 ; i < TASK_NUM ; ++i)
	{
		if(task_arr[i].func != NULLPTR)
		{
		
			if(task_arr[i].taskcounter ==0)
			{
				task_arr[i].runme = 1 ;
				task_arr[i].taskcounter = task_arr[i].periodicity ;
			}
			else
			{
				task_arr[i].taskcounter-- ;
			}
		}
	}
}
u8 RTOS_Start ()
{
	Timer0_Init(TIMER0_CTC_MODE , TIMER0_SCALER_64 ,OCO_DISCONNECTED) ;
	Timer0_OC_SetCallBack(Algoithim) ;
	//OCR0 = 125 ;
	Timer0_OC_InterruptEnable() ;
	sei() ;
}
u8 RTOS_CreateTask (u8 priority ,u16 periodicity , void (*task)(void))
{
	u8 error = OK ;
	if((priority < TASK_NUM) && (task != NULLPTR))
	{
		task_arr[priority].periodicity = periodicity ;
		task_arr[priority].func= task ;
		task_arr[priority].runme= 0 ;
		task_arr[priority].taskcounter= 0 ;
	}
	else
	{
		error = N_OK ;
	}
	return error ;
	
}
void RTOS_Dispather(void)
{
	u8 i ; 
	for(i= 0 ; i < TASK_NUM ; ++i)
	{
		if(task_arr[i].func != NULLPTR)
		{
			if(task_arr[i].runme ==1)
			{
				task_arr[i].runme = 0 ;
				task_arr[i].func() ;
			}
		}
	}
}*/