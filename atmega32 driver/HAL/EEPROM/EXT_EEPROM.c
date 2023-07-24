/*
 * EXT_EEPROM.c
 *
 * Created: 9/2/2021 12:21:40 AM
 *  Author: EL-talkhawy
 */ 
#include "EXT_EEPROM.h"

#define F_CPU 8000000
#include <util/delay.h>

void EXTEEPROM_WriteByte (u8 EEP_Adress, u8 Byte_Adress , u8 data) 
{
	TWI_SendStartCondition() ;
	TWI_MasterSendAdress(EEP_Adress , 0) ;
	TWI_SendData(Byte_Adress) ;
	TWI_SendData(data) ;
	TWI_SendStopCondition() ;
}
void EXTEEPROM_WriteBlock (u8 EEP_Adress, u8 Bl_Adress , u8* dataarr , u8 datasize) 
{
	u8 i ;
	TWI_SendStartCondition() ;
	TWI_MasterSendAdress(EEP_Adress , 0) ;
	TWI_SendData(Bl_Adress) ;
	for(i=0 ; i < datasize ; ++i)
	{
		TWI_SendData(dataarr[i]) ;
	}
    TWI_SendStopCondition() ;
}
void EXTEEPROM_ReadBlock (u8 EEP_Adress, u8 Bl_Adress ,u8* dataarr , u8 datasize)
{
	u8 i ;
	TWI_SendStartCondition() ;
	TWI_MasterSendAdress(EEP_Adress , 0) ;
	TWI_SendData(Bl_Adress) ;
	//TWI_SendStopCondition() ;
	TWI_SendStartCondition() ;
	TWI_MasterSendAdress(EEP_Adress , 1) ;
	
	for(i=0 ; i < datasize ; ++i)
	{
		TWI_ReadData(&dataarr[i]) ;
	}
	TWI_SendStopCondition() ;
}


void EXTEEPROM_ReadByte (u8 EEP_Adress, u8 Byte_Adress , u8* data)
{
	TWI_SendStartCondition() ;
	TWI_MasterSendAdress(EEP_Adress , 0) ;
	TWI_SendData(Byte_Adress) ;
	//TWI_SendStopCondition() ;
	TWI_SendStartCondition() ;
	TWI_MasterSendAdress(EEP_Adress , 1) ;
	TWI_ReadData(data) ; 
	TWI_SendStopCondition() ;
}


