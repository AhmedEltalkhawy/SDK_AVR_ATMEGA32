/*
 * OS.c
 *
 * Created: 10/10/2021 2:47:38 PM
 *  Author: EL-talkhawy
 */ 
#include "OS.h"

/*create an array of struct to hold the data of created task */

static OS_struct taskArray [MAX_NUM_OF_TASKS] ;

static u8 taskcounter = 0 ;

OS_feedback OS_TaskCreate (funcptr task , u8 default_time_burst , OS_state default_state) 
{
	OS_feedback temp_status = NOK_UNKNOWN ;
	
	if(task == NULLPTR)
	{
	   temp_status = NOK_NULL_POINTER ;
	}
	else if (taskcounter >= MAX_NUM_OF_TASKS)
	{
		temp_status = NOK_COUNT_LIMIT   ;
	}
	else if (default_time_burst > HYPER_PERIOD)
	{
		temp_status = NOK_TIME_LIMIT ;
	}
	else 
	{
		taskArray[taskcounter].function           = task ;
		taskArray[taskcounter].task_periodicity   = default_time_burst  ;
		taskArray[taskcounter].task_state         = default_state ;
		taskArray[taskcounter].task_counter       = 1 ;
		temp_status                               = OK ;
		++taskcounter ;
	}
}

void OS_TaskHandler (void)
{
	 u8 task_id = 0  , i;
	 for(task_id = 0 ; task_id < taskcounter ; ++task_id)
	 {
		 	if (taskArray[task_id].task_state != SUSPENDED)
		    {
				/* if the task is ready */
				if(taskArray[task_id].task_counter >= taskArray[task_id].task_periodicity) // >= to aviod if tick is lost to any reason
				{
					taskArray[task_id].task_state = READY ;
					taskArray[task_id].task_counter = 1 ;
				}
				else
				{
				  taskArray[task_id].task_counter++ ;
				}
				
			}
			else
			{
			}
	 }
}
void OS_TaskExecution(void)
{
	 u8 task_id = 0  , i;
	 for(task_id = 0 ; task_id < taskcounter ; ++task_id)
	 {
		 if (taskArray[task_id].task_state == READY)
		 {
		    taskArray[task_id].function() ;
			taskArray[task_id].task_state = BLOCKED ; 
		 }
		 
	 }
	
}
