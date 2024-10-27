#include "USART.h"
#include "Delay.h"
#include "TinyCmd.h"
#include "stm32f10x.h"

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA,&GPIO_InitStruct); 	
}

TinyCmd_CallBack_Ret LED_Callback(void)
{
	//Command: LED ON
	//Effect: Turn on LED on PA1.
	if(TinyCmd_Arg_Check("ON",0) == TINYCMD_SUCCESS)
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
		return TINYCMD_SUCCESS;
	}
	//Command: LED OFF
	//Effect: Turn off LED on PA1.
	else if(TinyCmd_Arg_Check("OFF",0) == TINYCMD_SUCCESS)
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
		return TINYCMD_SUCCESS;
	}
	//Command: LED Blink n_times
	//Effect: LED on PA1 blink n_times .
	else if(TinyCmd_Arg_Check("Blink",0))
	{
		uint8_t n_times = 0;
		TinyCmd_Arg_To_Num(1,&n_times,TINYCMD_UINT8);
		TinyCmd_Report("Blink %d times",n_times);
		for(; n_times > 0; n_times--)
		{
			GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
			Delay_ms(200);
			GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
			Delay_ms(200);
		}
		
	}
	return TINYCMD_FAILED;
}

//Create a new command with command:LED and callback function
TinyCmd_Command Cmd1 = {.command = "LED",.callback = LED_Callback};

int main(void)
{       
	USART1_Init();
	LED_Init();
	//Put created command into command list is mandatory.
	TinyCmd_Add_Cmd(&Cmd1);
	
	//If you want to use TinyCmd_Report (A simplified printf-like function)
	//you need to evaluate a function to TinyCmd_SendChar to send a single character
	TinyCmd_SendChar = USART1_Write_Char;
	TinyCmd_Report("Hello TinyCmd %d %f",666,3.14);
	
	while(1)
	{
		
	}
}

//USART interrupt is a nice way to receive command from other device
//You can also implement this in main loop.
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        uint8_t received_byte = USART_ReceiveData(USART1);
	
        if (TinyCmd_buf.length < CMD_BUF_SIZE)
        {
            TinyCmd_buf.input[TinyCmd_buf.length++] = received_byte;
		
            if (received_byte == '\n' || received_byte == '\r')
            {
		//Send received string to USART1
		TinyCmd_Report("String received:%s",TinyCmd_buf.input);
		//Run command given by input buffer.
		TinyCmd_Handler();
            }
        }

        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}