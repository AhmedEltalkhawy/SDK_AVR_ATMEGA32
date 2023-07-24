 /*
 * UARTStackh.h
 *
 * Created: 6/2/2021 6:14:13 PM
 *  Author: EL-talkhawy
 */ 


#ifndef UARTSTACKH_H_
#define UARTSTACKH_H_

#include "StdTypes.h"

#define  STACKSIZE 5 

typedef enum 
{
	STACKEMPTY = 0 ,
	STACKFULL = 0 ,
	DONE = 1 
}STACKReturntype;

STACKReturntype push (u8 data) ;
STACKReturntype pop (u8* pdata) ;
	
	




#endif /* UARTSTACKH_H_ */