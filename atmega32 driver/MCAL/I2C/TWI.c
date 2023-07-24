/*
 * TWI.c
 *
 * Created: 8/31/2021 2:34:23 PM
 *  Author: EL-talkhawy
 */ 
#include "TWI.h"

void TWI_InitMaster(u8 adress) 
{
	/* freq 400 kbps */
	TWBR = 2 ;
	CLEAR_BIT(TWSR ,TWPS0) ;
	CLEAR_BIT(TWSR ,TWPS1) ;
	/*Assign adress */
	if(adress > 0)
	{
		TWAR = adress << 1 ;
	}
	/* Enable TWI */ 
	SET_BIT(TWCR , TWEN) ;
	
}
void TWI_InitSalve(u8 adress)
{
	/*Assign adress */
	if(adress > 0)
	{
		TWAR = adress << 1 ;
	}
	/* Enable TWI */
	SET_BIT(TWCR , TWEN) ;
	
}
void TWI_SendStartCondition (void) 
{
	SET_BIT(TWCR , TWSTA) ;
	/* start job by clearing the flag */
	SET_BIT(TWCR , TWINT) ; /* must clr sw */
	/* wait till job is complete */
	while(!READ_BIT(TWCR , TWINT)) ;
	/* check if correct */
	
	/*if(TWSR == START_ACK)
	{
		return 1 ;
	}
	return 0 ;*/
	/* clr of start condition */
	
}
void TWI_SendStopCondition (void) 
{
	SET_BIT(TWCR , TWSTO) ;
	/* start job by clearing the flag */
	SET_BIT(TWCR , TWINT) ; /* must clr sw */
}

void TWI_MasterSendAdress (u8 cpy_u8adress , u8 opertion)  
{
	/* set Adress */
	TWDR = (cpy_u8adress << 1) | opertion ;
	/* clear start condition  */
	CLEAR_BIT(TWCR , TWSTA) ; /* here to write adress if not dont work*/
	/* start job by clearing the flag */
	SET_BIT(TWCR , TWINT) ; /* must clr sw */
	/* wait till job is complete */
	while(!READ_BIT(TWCR , TWINT)) ;
	/* check if correct */ /* ack */
}

void TWI_SendData (u8 data) 
{
	TWDR = data ;
	/* start job by clearing the flag */
	SET_BIT(TWCR , TWINT) ; /* must clr sw */
	/* wait till job is complete */
	while(!READ_BIT(TWCR , TWINT)) ;
	/* check if correct */
	
}
void TWI_ReadData (u8 *data) 
{
	/* start job by clearing the flag */
	SET_BIT(TWCR , TWINT) ; /* must clr sw */
	/* wait till job is complete */
	while(!READ_BIT(TWCR , TWINT)) ;
	/* check if correct */
	/* read data */ 
	*data = TWDR ;
}
void TWI_EnableAck () 
{
	SET_BIT(TWCR , TWEA) ; 
}
void TWI_DisableAck ()
{
	CLEAR_BIT(TWCR , TWEA) ;
}