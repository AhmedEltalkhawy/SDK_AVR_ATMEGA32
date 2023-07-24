/*
 * ultrasonic.c
 *
 * Created: 5/19/2021 1:48:29 AM
 *  Author: EL-talkhawy
 */ 

/*#include "ultrasonic.h"
#include "Timers.h"

static volatile u16 t1 , t2 ;
static volatile u8 flag = 0 ; 

static void ICU_Func (void)
{
	if(flag == 0)
	{
		t1 = ICR1 ;
		flag = 1 ; 
		T1_ICU_SelectEdge(ICES1_FALLING) ;
	}
	else if (flag == 1)
	{
		t2 = ICR1 ;
		flag = 2 ;
	}
}

void UlLTRASONIC_Init (void)
{
	//T1_Init() //here if we use only timer here
	T1_ICU_SetCallBack(ICU_Func) ;
}

void UlLTRASONIC_Read (void)
{
	u16 d , time ;
	T1_ICU_InterruptEnable() ;
	flag = 0 ;
	
}*/
