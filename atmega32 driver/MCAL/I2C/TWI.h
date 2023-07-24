/*
 * TWI.h
 *
 * Created: 8/31/2021 2:33:50 PM
 *  Author: EL-talkhawy
 */ 


#ifndef TWI_H_
#define TWI_H_


#include "Utils.h"
#include "StdTypes.h"
#include "MemMAP.h"

void TWI_InitMaster(u8 adress) ;
void TWI_InitSalve(u8 adress)  ;

void TWI_SendStartCondition (void) ;
void TWI_SendStopCondition  (void) ;

void TWI_MasterSendAdress (u8 adress , u8 opertion)  ;

void TWI_SendData (u8 data) ;
void TWI_ReadData (u8 *data) ;

void TWI_EnableAck () ;
void TWI_DisableAck () ;


/* TWI states */
/* For Master mode **/
#define START_ACK 0x08
#define REP_START_ACK 0x10
#define SLAVE_W_ACK 0x18
#define SLAVE_W_NACK 0x20
#define SLAVE_DATA_ACK 0x28
#define SLAVE_DATA_NACK 0x30
#define SLAVE_R_ACK 0x40
#define SLAVE_R_NACK 0x48
#define MASTER_R_DATA_ACK 0x50
#define MASTER_R_DATA_NACK 0x58



/* For Slave mode **/
#define SLAVE_ADDRESS_W_ACK 0x60
#define SLAVE_GEN_CALL_ACK 0x70
#define SLAVE_DATA_REC_ACK 0x80
#define SLAVE_DATA_REC_NACK 0x88




#define TWSR_MASK 0xF8




#endif /* TWI_H_ */