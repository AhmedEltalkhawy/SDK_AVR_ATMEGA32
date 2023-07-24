/*
 * UARTStack.c
 *
 * Created: 6/2/2021 6:13:46 PM
 *  Author: EL-talkhawy
 */ 

#include "StdTypes.h"
#include "UARTStackh.h"

static stack [STACKSIZE] ; 
static u8 sp ; 

STACKReturntype push (u8 data) 
{
	if (sp == STACKSIZE)
	{
		return STACKFULL ;
	}
	stack[sp] = data ; 
	sp = sp+1 ; 
	return DONE ;
	
}
STACKReturntype pop (u8* pdata) 
{
	if (sp == 0)
	{
		return STACKEMPTY ;
	}
	--sp ; 
	*pdata = stack[sp] ; 
	return DONE ;
	
}
