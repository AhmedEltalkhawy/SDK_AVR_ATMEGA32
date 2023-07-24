/*
 * atmega32 driver.c
 *
 * Created: 1/28/2021 6:47:17 AM
 * Author : EL-talkhawy
 */ 


#include "DIO_Interface.h"
#include "Timers.h"
#include "Timers_Services.h"
#include "LCD.h"
#include "Motors.h"
#include "KeyPad.h"
#include "ADC.h"
#include "Servo.h"
#include "Sensor.h"
#include "EX_Interrupt.h"
#include "UART.h"
#include "UART_Services.h"
#include "UARTStackh.h"
#include "SPI.h"
#include "TWI.h"
#include "EXT_EEPROM.h"
#include "RTOS.h"
#include "OS.h"
#include "TASK.h"
#define  F_CPU 8000000
#include <util/delay.h>*

static volatile u8 fullflag = 0 ;
void LCD_WriteStringcon (u8* str) 
{
	int i , j ;
	for(i=0 ; i < 2 ; ++i)
	{
		for (j=0 ; j < 16 ; ++j)
		{		
			LCD_GoTo(i , j) ;
			LCD_WriteString(str) ;
			_delay_ms(100) ;
			LCD_GoTo(i , j) ;
			LCD_WriteString("     ") ;
		}
	}
	/*int l = 0  , i ;
		while(str[l])
		  ++l ; 
		for(i = l ; i >1 ; --i)
		{
			LCD_WriteString(str+i-1) ;
			_delay_ms(100) ;
			LCD_ClearDisplay() ;
		}
		for(i=0 ; i<16 ; ++i)
		{
			LCD_GoTo(0,i) ;
			LCD_WriteString(str) ;
			_delay_ms(100) ;
			LCD_ClearDisplay() ;
		}
		for(i = l ; i >1 ; --i)
		{
			LCD_GoTo(1,0) ;
			LCD_WriteString(str+i-1) ;
			_delay_ms(100) ;
			LCD_ClearDisplay() ;
		}
		for(i=0 ; i<16 ; ++i)
		{
			LCD_GoTo(1,i) ;
			LCD_WriteString(str) ;
			_delay_ms(100) ;
			LCD_ClearDisplay() ;
		}*/
		
	
}
void LCD_CharAscii (void)
{
	int i ;
	for(i= 'A'; i <= 'z' ; ++i)
	{
		LCD_GoTo(0 ,6) ;
		LCD_WriteChar(i) ;
		LCD_GoTo(1 ,7) ;
		LCD_WriteString("   ") ;
		LCD_GoTo(1 ,7) ;
		LCD_WriteNumber(i) ;
		_delay_ms(100) ;
	}
	
	
}
void LCD_2men ()
{
	u8 i ;
	LCD_WriteChar('A') ;
	LCD_GoTo(0,15) ;
	LCD_WriteChar('B') ;
	for ( i = 1 ; i<=15 ; ++i)
	{
		LCD_GoTo(0,i) ;
		LCD_WriteChar('>') ;
		_delay_ms(100) ;
		LCD_GoTo(0,i) ;
		LCD_WriteChar(' ') ;
	}
	LCD_GoTo(0,i-1) ;
	LCD_WriteChar('D') ;
	_delay_ms(1000) ;
	LCD_GoTo(0,i-1) ;
	LCD_WriteChar('C') ;
}
void Calculator (void)
{
	u8 key = NO_KEY  ;
	static u8 op , flag = 1  , res_flag = 0;
	static u16 num1 , num2  , result = 0   ; 
	key = KEYPAD_GetEntry() ; 
	if(key != NO_KEY)
	{
		
		if(res_flag == 1 )
		{
			if(key ==  '+' || key ==  '-' || key ==  '*' || key ==  '/')
			{
				num1 = result ;
				LCD_GoTo(0,0) ;
				LCD_WriteString("               ") ;
				LCD_GoTo(0,0) ;
				LCD_WriteNumber(num1) ;
				
			}
			else 
			{
				result = 0 ;
			}
			
		}
		if((key>='0' && key<= '9') &&(flag ==1))
		{
			LCD_WriteChar(key) ;
			num1 = num1 *10 + (key - '0') ;
		}
		else if (key == '*' || key == '+' || key == '-' || key == '/' )
		{
			LCD_WriteChar(key) ; 
			op = key ;
			flag = 0 ;
		}
		else if((key>='0' && key<= '9') &&(flag ==0))
		{
			LCD_WriteChar(key) ;
			num2 = num2 *10 + (key - '0') ;
		}
		else if (key == '=')
		{
			LCD_WriteChar(key) ;
			switch(op)
			{
				case  '+' : 
				result = num1 + num2 ; 
				break ; 
				case  '-' :
				result = num1 - num2 ;
				break ;
				case  '*' :
				result = num1 * num2 ;
				break ;
				case  '/' :
				result = num1 / num2 ;
				break ;
			}
			LCD_GoTo(0,0) ;
			LCD_WriteString("      ") ;
			LCD_GoTo(0,0) ;
			LCD_WriteNumber(result) ;
			num1 = 0 ; 
			num2 = 0 ;
			flag = 1 ;
			op = 0 ; 
			res_flag = 1 ;
		}
		else if (key == 'c')
		{
			LCD_ClearDisplay() ;
			res_flag = 0 ;
		}
	}
	
	
}
void Converter (void)
{
	u8 key = NO_KEY ; 
	static u16 num = 0 ;
	static u8 flag = 1 , from = NO_KEY , to = NO_KEY ;
	key = KEYPAD_GetEntry() ;
	if(key== 'c' || flag == 1)
	{
		from = NO_KEY ; 
		to = NO_KEY ;
		LCD_GoTo(1,0) ;
		LCD_WriteString("                              ") ;
		LCD_GoTo(0,0) ;
		LCD_WriteString("                              ") ;
		LCD_GoTo(0,0) ;
		flag = 0 ;
		LCD_WriteString("Hello Bro") ;
		_delay_ms(100) ; 
		LCD_GoTo(0,0) ;
		LCD_WriteString("                  ") ;
		LCD_GoTo(0,0) ;
		LCD_WriteString("Start NOW :)") ; 
		_delay_ms(100) ; 
		LCD_GoTo(0,0) ;
		LCD_WriteString("                 ") ;
		LCD_GoTo(0,0) ; 
		LCD_WriteString("Convert From :") ;
		LCD_GoTo(1,0) ;
		LCD_WriteString("1 DEC 2 BIN 3 HEX") ;
		while(from == NO_KEY)
		{
			from = KEYPAD_GetEntry()  ;
		}
		LCD_GoTo(0,0) ;
		LCD_WriteString("                 ") ;
		LCD_GoTo(0,0) ;
		LCD_WriteString("Convert For :") ;
		while((to = KEYPAD_GetEntry())== NO_KEY) ;	
		LCD_GoTo(0,0) ;
		LCD_WriteString("                                  ") ;
		LCD_GoTo(0,0) ;
		switch (from)
		{
			case '1' : 
			LCD_WriteString("DEC :") ;
			break ;
			case '2' :
			LCD_WriteString("BIN :") ;
			break ;
			case '3' :
			LCD_WriteString("HEX :") ;
			break ;
			default:
			LCD_WriteString("Enter Correct Number") ;
		}	
		LCD_GoTo(1,0) ;
		LCD_WriteString("                                  ") ;
		LCD_GoTo(1,0) ;
		switch (to)
		{
			case '1' :
			LCD_WriteString("DEC :") ;
			break ;
			case '2' :
			LCD_WriteString("BIN :") ;
			break ;
			case '3' :
			LCD_WriteString("HEX :") ;
			break ;
			default:
			LCD_WriteString("Enter Correct Number") ;
		}
		LCD_GoTo(0,5) ;
	}
	else
	{
		if((from == '1') && (key>='0' && key <='9'))
		{
			LCD_WriteChar(key) ;
			num = num*10 + (key - '0') ;
		}
		else if((from =='2' ) && (key>='0' && key <='1'))
		{
			LCD_WriteChar(key) ;
			num = num*2 + (key - '0') ;
		}
		else if((from == '3') && ((key>='0' && key <='9')||(key >= 'A' && key<='F')))
		{
			LCD_WriteChar(key) ;
			if((key>='0' && key <='9'))
			   num = num *16 + (key - '0') ;
			 else 
			   num = num*16 +(key -'A' +10) ;
		}
		else if (key == '=')
		{
			LCD_GoTo(1,5) ;
			LCD_WriteString("        ") ;
			LCD_GoTo(1,5) ;
			switch(to)
			{
				case '1' :
				LCD_WriteNumber(num) ;
				break ;
				case '2' :
				LCD_WriteBin(num) ;
				break ;
				case '3' :
				LCD_WriteHex(num) ;
				break ;
			}
			num = 0 ;
			LCD_GoTo(0,5) ;
			LCD_WriteString("      ") ;
			LCD_GoTo(0,5) ;
		}
	}
	
	
	
	
}

void RX_Func (void)
{
	u8 data = UART_ReceiveNoBlock() ;
	if(push(data) == STACKFULL)
	{
		fullflag = 1 ; // indictor as stack is full 
	}
}

void EX_IN0_Func(void)
{
	DIO_WritePort(PC, 0x81) ;
	_delay_ms(300) ;
	DIO_WritePort(PC, 0x42) ;
	_delay_ms(300) ;
	DIO_WritePort(PC, 0x24) ;
	_delay_ms(300) ;
	DIO_WritePort(PC, 0x18) ;
	_delay_ms(300) ;
}
void EX_IN1_Func(void)
{
	DIO_WritePIN(PINC1 , HIGH) ;
	_delay_ms(200) ;
}

unsigned char Seg_Led [] = {0x3f , 0x06 ,0x5b , 0x4f , 0x66 , 0x6d , 0x7d ,0x07 ,0x7f ,0x6f,0x77,0x7c,0x39,0x5e,0xf1,0x71} ;
volatile u8 flag = 1 ;

void Timer0_Func (void)
{
	static u16 c = 0 ;
	TCNT0 = 6 ; 
	++c ;
	if(c % 50 == 0 )
	{
		flag = 1 ;
	}
	if(c % 100 == 0)
	{
		flag = 2 ;
	}
	if(c == 4000)
	{
		flag = 3 ; 
		c = 0 ;
	}
}

void Segment_Display_Dec_f (unsigned char num)
{
	unsigned char x , y ;
	x = num %10 ;
	y= num/10 ;
	SET_BIT(PORTC ,6) ;
	CLEAR_BIT(PORTC,7) ;
	PORTA = Seg_Led[x] << 1;
	_delay_ms(50) ;
	SET_BIT(PORTC ,7) ;
	CLEAR_BIT(PORTC,6) ;
	PORTA = Seg_Led[y] <<1 ;
	_delay_ms(50) ;
	_delay_ms(1000) ;
}
u8 writedataarr [2] = {0x14 , 0x12 } ;
u8 readdataarr [2] = {0x01 , 0x01 } ;
void EE_W()
{
	u8 i ;
	for(i=0 ; i< 2 ; ++i)
	{
		EXTEEPROM_WriteByte (0x51 ,0x60 +i , writedataarr[i]) ;
	}
}
void EE_R ()
{
	u8 i ; 
	for(i=0 ; i < 2 ; ++i)
	{
		EXTEEPROM_ReadByte(0X51 , 0x60+i , &readdataarr[i]) ;
	}
}
volatile u16 a  ;
void t0f (void)
{
	TCNT0 = 6 ; 
	a++ ;
	if(a == 4000)
	{ 
		OS_TaskHandler() ;
		a = 0 ;
	
	}
	
}

/************** RTOS ***********************/
volatile static u16 u16_100USCount = 0 ;
volatile static u16 u16_MilliSCount = 0 ;
volatile static u16 u16_SecondSCount = 0 ;

void vMillisIncrement (void)
{
	TCNT0 = 156 ;
	u16_100USCount++ ;
	if(u16_100USCount >= 10)
	{
		u16_100USCount = 0 ;
		u16_MilliSCount ++ ; 
	}
	if(u16_MilliSCount >= 1000)
	{
		u16_MilliSCount = 0 ;
		//u16_SecondSCount++ ;
		/* call scheduler handler */
		OS_TaskHandler() ;
	}
	

	
}
void InitScheduler (void)
{
	/* init timer0 */
	Timer0_Init( TIMER0_NORMAL_MODE,TIMER0_SCALER_8 ,OCO_DISCONNECTED) ;
	TCNT0 = 156 ;
	Timer0_OV_InterruptEnable() ;
	Timer0_OVF_SetCallBack(vMillisIncrement) ;
	
	//OS_TaskCreate(Task1SLcdUpdate , 1 , BLOCKED) ;
	OS_TaskCreate(Task2SBlink , 2 , BLOCKED) ;
	OS_TaskCreate(Task3SBlink , 3 , BLOCKED) ;
}

void InitECU (void)
{
	DIO_Init() ;
	LCD_Init() ; 
	sei() ;
}
/*******************************************/

int main (void)
{
	
	InitECU() ;
	InitScheduler() ;
 	while(1)
	{
		OS_TaskExecution();
	}
}



