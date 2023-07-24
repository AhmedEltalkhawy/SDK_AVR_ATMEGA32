/*
 * TASK.c
 *
 * Created: 10/10/2021 2:48:14 PM
 *  Author: EL-talkhawy
 */ 
#include "TASK.h"
void Task1SLcdUpdate (void)
{
	static u8 lcd_MSec = 1 ;
	LCD_GoTo(0,0) ;
	LCD_WriteString("seconds") ;
	LCD_GoTo(0, 9) ; 
	LCD_WriteNumber(lcd_MSec) ; 
	if(lcd_MSec >=60)
	{
		lcd_MSec = 1 ;
	}

}

void Task2SBlink (void)
{
	DIO_TogglePIN(PINA0) ;
	
}
void Task3SBlink (void)
{
	DIO_TogglePIN(PINB2) ;
}
