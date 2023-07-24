/*
 * OS.h
 *
 * Created: 10/10/2021 2:47:53 PM
 *  Author: EL-talkhawy
 */ 


#ifndef OS_H_
#define OS_H_

#include "StdTypes.h"

#define		MAX_NUM_OF_TASKS  ((u8)3) 
#define     HYPER_PERIOD       ((u8)6)

typedef void (*funcptr)(void) ;

typedef enum
{
	BLOCKED , 
	READY , 
	SUSPENDED
	
}OS_state;

/* task control block */
typedef struct
{
	funcptr     function ;
	u8          task_periodicity ;
	u8          task_counter      ;
	OS_state    task_state  ;
	
}OS_struct;

typedef enum 
{
	OK ,
	NOK_NULL_POINTER , // you send null 
	NOK_COUNT_LIMIT ,
	NOK_TIME_LIMIT , // perdicitiy bigger than hyper period
	NOK_UNKNOWN
	
}OS_feedback;

OS_feedback OS_TaskCreate (funcptr task , u8 default_time_burst , OS_state default_state) ;

void OS_TaskHandler (void) ;
void OS_TaskExecution (void) ;






#endif /* OS_H_ */