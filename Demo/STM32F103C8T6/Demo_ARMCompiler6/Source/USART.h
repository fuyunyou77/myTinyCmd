/**
 * File Name: USART.h
 * 
 * Copyright © 2023 Civic_Crab. All rights reserved.
 * 
 * Author: Civic_Crab
 * Creation Date: Oct 1, 2020
 * Version: 1.0.0
 * 
 * Description: This file prodides USART functions implementation
 */


#ifndef	_USART_H_
#define	_USART_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"                  // Device header

#define USART1_BAUD_RATE (115200)

/* Functions -----------------------------------------------------------------*/
void USART1_Init(void);
void USART1_Write_Char(char ch);
void USART1_Write_String(char *str);


#endif	//_USART_H_