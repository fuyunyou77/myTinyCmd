/*
 * Copyright 2024 Civic_Crab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * File: TinyCmd.h
 * Author: Civic_Crab
 * Version: 1.0.0
 * Created on: 2024-10-24
 *
 * Description:
 * This file contains the implementation of the TinyCmd library.
 */

#ifndef __TINYCMD_H__
#define __TINYCMD_H__

//Constant for configure TinyCmd
#define CMD_NAME_LENGTH 8
#define CMD_LIST_SIZE 8
#define CMD_BUF_SIZE 64
#define CMD_MAX_TOKENS 4
#define CMD_MAX_PARAMS (CMD_MAX_TOKENS - 1)


typedef unsigned char TinyCmd_CallBack_Ret;
typedef unsigned char TinyCmd_Counter_Type;

//Global structs
typedef struct TinyCmd_Command{
	char command[CMD_NAME_LENGTH];
	TinyCmd_CallBack_Ret (*callback)(void);	
}TinyCmd_Command;

//Global enums
typedef enum{
	TINYCMD_FAILED = -1,
	TINYCMD_SUCCESS = 0,
}TinyCmd_Status;

//Global functions
TinyCmd_Status Tiny_Command_Handler(void);
TinyCmd_Status TinyCmd_Add_Cmd(TinyCmd_Command* newCmd);
TinyCmd_Status TinyCmd_Arg_Check(char* arg1,TinyCmd_Counter_Type p_arg2);
TinyCmd_Status TinyCmd_PutChar(char c);
TinyCmd_Status TinyCmd_PutString(char* str);


#endif // __TINYCMD_H__