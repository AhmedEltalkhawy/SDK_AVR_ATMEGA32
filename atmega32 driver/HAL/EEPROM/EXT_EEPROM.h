/*
 * EXT_EEPROM.h
 *
 * Created: 9/2/2021 12:21:15 AM
 *  Author: EL-talkhawy
 */ 

#ifndef EXT_EEPROM_H_
#define EXT_EEPROM_H_

#include "StdTypes.h"
#include "Utils.h"
#include "MemMAP.h" 
#include "TWI.h"

void EXTEEPROM_WriteByte (u8 EEP_Adress, u8 Byte_Adress , u8 data) ;
void EXTEEPROM_WriteBlock (u8 EEP_Adress, u8 Bl_Adress , u8* dataarr , u8 datasize) ;

void EXTEEPROM_ReadByte (u8 EEP_Adress, u8 Byte_Adress , u8* data) ;
void EXTEEPROM_ReadBlock (u8 EEP_Adress, u8 Bl_Adress ,u8* dataarr , u8 datasize) ;






#endif /* EXT_EEPROM_H_ */