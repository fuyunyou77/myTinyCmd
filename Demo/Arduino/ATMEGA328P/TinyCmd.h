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
 * Version: 1.1.0
 * Created on: 2024-10-24
 *
 * Description:
 * This file contains the implementation of the TinyCmd library.
 */

#ifndef __TINYCMD_H__
#define __TINYCMD_H__

#ifdef __cplusplus
extern "C" {
#endif

//Constant for configure TinyCmd

//Length of the command or arguments name
#define CMD_NAME_LENGTH 8

//Length of the command list with aruments after command
#define CMD_LIST_SIZE 8

//Length of the command buffer string
#define CMD_BUF_SIZE (CMD_NAME_LENGTH * CMD_LIST_SIZE + CMD_LIST_SIZE - 1)

//Maximum number of tokens in a command
#define CMD_MAX_TOKENS 4

//Maximum number of parameters in a command
#define CMD_MAX_PARAMS (CMD_MAX_TOKENS - 1)

//Maximum and minimum integer values
#define CMD_INT8_MAX 127
#define CMD_INT8_MIN -128
#define CMD_INT16_MAX 32767
#define CMD_INT16_MIN -32768
#define CMD_INT32_MAX 2147483647
#define CMD_INT32_MIN -2147483648

//Global typedefs

//Callback function type You can redefine it as you like
typedef unsigned char TinyCmd_CallBack_Ret;

//Counter type for TinyCmd(Such as i in for loop)
//When your Input buffer ecexceeds 255, you need to make this shit bigger.
typedef unsigned char TinyCmd_Counter_Type;

//Global structs

//TinyCmd input buffer struct:
//description: This struct is used to store the input buffer and the arguments
//length: The length of the input buffer
//arg: The pointer to the arguments
//input: The input buffer string
typedef struct TinyCmd_inuput{
	char input[CMD_BUF_SIZE];
	char* arg[CMD_MAX_PARAMS];
	TinyCmd_Counter_Type length;
}TinyCmd_Buffer;

//TinyCmd Command struct:
//description: When you are going to add a new command, you need to define a struct like this:
//command: The command name
//callback: The callback function pointer
typedef struct TinyCmd_Command{
	const char* command;
	TinyCmd_CallBack_Ret (*callback)(void);	
}TinyCmd_Command;

//Global enums
typedef enum{
	TINYCMD_FAILED = 0,
	TINYCMD_SUCCESS = 1,
}TinyCmd_Status;

//Global variables
extern TinyCmd_Buffer TinyCmd_buf;

//Global functions
TinyCmd_Status TinyCmd_Handler(void);
TinyCmd_Status TinyCmd_Add_Cmd(TinyCmd_Command* newCmd);
TinyCmd_Status TinyCmd_Arg_Check(const char* arg1,TinyCmd_Counter_Type p_arg2);
TinyCmd_Counter_Type TinyCmd_Arg_Get_Len(TinyCmd_Counter_Type p_arg);
TinyCmd_Status TinyCmd_Arg_To_Int32(TinyCmd_Counter_Type p_arg,int* number);
TinyCmd_Status TinyCmd_Arg_To_Int16(TinyCmd_Counter_Type p_arg,short* number);
TinyCmd_Status TinyCmd_Arg_To_Int8(TinyCmd_Counter_Type p_arg,signed char* number);
TinyCmd_Status TinyCmd_Arg_To_Float(TinyCmd_Counter_Type p_arg,float* number);
int TinyCmd_Str_To_int(const char* str);
double TinyCmd_Str_To_Float(const char* str);

#ifdef __cplusplus
}
#endif

#endif // __TINYCMD_H__