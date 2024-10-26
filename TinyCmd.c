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
 * File: TinyCmd.c
 * Author: Civic_Crab
 * Version: 1.1.0
 * Created on: 2024-10-24
 *
 * Description:
 * This file contains the implementation of the TinyCmd library.
 */

#include "TinyCmd.h"

#ifndef NULL
#define NULL ((void *)0)
#endif //NULL

//Local structs
typedef struct TinyCmd_List {
    TinyCmd_Command* list[CMD_LIST_SIZE];
    TinyCmd_Counter_Type length;

}TinyCmd_List;

//Local Variables
static char* strtok_next = NULL; 
TinyCmd_List TinyCmdRunning_Cmd;
TinyCmd_Counter_Type token_count;

//Global Variables
TinyCmd_Buffer TinyCmd_buf;

//Local Function

//If <string.h> is included,TinyCmd will use functions in <string.h>,instead of the following functions.
static int TinyCmd_strcmp(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    while (*str1 == *str2) {
        if (*str1 == '\0') {
            return 0;
        }
        str1++;
        str2++;
    }

    return (unsigned char)*str1 - (unsigned char)*str2;
}

//Unused function
// static char* TinyCmd_strcpy(char* dest, const char* src) {
//     if (dest == NULL || src == NULL) {
//         return NULL;
//     }

//     char* dest_ptr = dest;
//     while ((*dest_ptr++ = *src++) != '\0') {

// 	}

//     return dest;
// }

static char* TinyCmd_strchr(const char* str, int c) {
    if (str == NULL) {
        return NULL;
    }

    while (*str != '\0') {
        if (*str == (char)c) {
            return (char*)str;
        }
        str++;
    }

    if ((char)c == '\0') {
        return (char*)str;
    }

    return NULL;
}

static char* TinyCmd_strtok_s(char* str, const char* delim, char** saveptr) {
    char* start;
    char* end;

    if (str != NULL) {
        *saveptr = str;
    }

    if (*saveptr == NULL) {
        return NULL;
    }

    start = *saveptr;
    while (*start && TinyCmd_strchr(delim, *start)) {
        start++;
    }

    if (*start == '\0') {
        *saveptr = NULL;
        return NULL;
    }

    end = start;
    while (*end && !TinyCmd_strchr(delim, *end)) {
        end++;
    }

    if (*end) {
        *end = '\0';
        *saveptr = end + 1;
    }
    else {
        *saveptr = NULL;
    }

    return start;
}

static TinyCmd_Counter_Type TinyCmd_strlen(const char* str) {
    const char* p = str;
    while (*p != '\0') {
        p++;
    }
    return p - str;
}

static TinyCmd_Status TinyCmd_Buf_Clear(void)
{
    TinyCmd_Counter_Type i = 0;
    for(i = 0; i < CMD_MAX_PARAMS; i++) {
        TinyCmd_buf.arg[i] = NULL;
    }
    for(i = 0; i < CMD_BUF_SIZE; i++) {
        TinyCmd_buf.input[i] = '\0';
    }
    TinyCmd_buf.length = 0;
    
    return TINYCMD_SUCCESS;
}

//TinyCmd_Status TinyCmd_trim(char *str)
//Description:Trim the unnecessary shit(' ','\r','\n') characters from the end of the string.
static void TinyCmd_trim(char *str) {
    TinyCmd_Counter_Type len = 0;
    while (str[len] != '\0') {
        len++;
    }

    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\r' || str[len - 1] == '\n')) {
        str[--len] = '\0';
    }
}

//Global functions

//TinyCmd_Status TinyCmd_Init(void):
//Description:Call this function when TinyCmd_buf is filled ,namely after you call TinyCmd_PutString()
//Returns:
//        TINYCMD_SUCCESS: Initialization successful.
//        TINYCMD_FAILED: Initialization failed.
TinyCmd_Status TinyCmd_Handler(void) {
    TinyCmd_Counter_Type i = 0;
    const char* delims = " ";
    char* context;

    TinyCmd_trim(TinyCmd_buf.input);

    //Read Command
    char* token = TinyCmd_strtok_s(TinyCmd_buf.input, delims, &context);
    char* command = token;

    //Read arguments
    token = TinyCmd_strtok_s(NULL, delims ,&context);

    while (token != NULL) {
        if (token_count < CMD_MAX_TOKENS) {
            TinyCmd_buf.arg[i++] = token;
        }
        else {
            // Maximum number of tokens reached.
            strtok_next = NULL;
            break;
        }
        token = TinyCmd_strtok_s(NULL, delims ,&context);
    }

    //Excute callback function of command
    for (i = 0; i < TinyCmdRunning_Cmd.length; i++) {
        
        if (!TinyCmd_strcmp(command, TinyCmdRunning_Cmd.list[i]->command)) 
        {
            TinyCmdRunning_Cmd.list[i]->callback();
            //Clear TinyCmd_buf
            TinyCmd_Buf_Clear();
            return TINYCMD_SUCCESS;
        }
    }

    //Clear TinyCmd_buf
    TinyCmd_Buf_Clear();
    return TINYCMD_FAILED;
}

//TinyCmd_Status TinyCmd_Add_Cmd(TinyCmd_Command* newCmd):
//Description:Add a new command to the TinyCmdRunning_Cmd list.
//args:
//        newCmd: Pointer to the TinyCmd_Command struct containing the command and callback function.
//Returns:
//        TINYCMD_SUCCESS: Command added successfully.
//        TINYCMD_FAILED: Command addition failed.
TinyCmd_Status TinyCmd_Add_Cmd(TinyCmd_Command* newCmd)
{
    if (newCmd == NULL){
        return TINYCMD_FAILED;
    }
    else{
        if(newCmd->callback != NULL){
            TinyCmdRunning_Cmd.list[TinyCmdRunning_Cmd.length++] = newCmd;
            return TINYCMD_SUCCESS;
        }
        else{
            return TINYCMD_FAILED;
        }
    }
}


//TinyCmd_Status TinyCmd_Arg_Check(char* arg1,TinyCmd_Counter_Type p_arg):
//Description:Check if the argument at position p_arg2 matches the given argument arg1.
//args:
//        arg1: Pointer to the argument string to compare.
//        p_arg2: Position of the argument in the TinyCmd_buf.arg array.
//Returns:
//        TINYCMD_SUCCESS: Argument matches.
//        TINYCMD_FAILED: Argument does not match.
TinyCmd_Status TinyCmd_Arg_Check(char* arg1,TinyCmd_Counter_Type p_arg2)
{
    if(!TinyCmd_strcmp(arg1,TinyCmd_buf.arg[p_arg2]))
    {
        return TINYCMD_SUCCESS;
    }
    else{
        return TINYCMD_FAILED;
    }
        
}

//char* TinyCmd_Arg_Get_Len(TinyCmd_Counter_Type p_arg):
//Description:Get the length of the argument at position p_arg from the TinyCmd_buf.arg array.
//args:
//        p_arg: Position of the argument in the TinyCmd_buf.arg array.
//Returns:
//        Length of the argument string.
TinyCmd_Counter_Type TinyCmd_Arg_Get_Len(TinyCmd_Counter_Type p_arg)
{
    return TinyCmd_strlen(TinyCmd_buf.arg[p_arg]);
}

static TinyCmd_Status TinyCmd_isdigit(int c) {
    return (c >= '0' && c <= '9');
}

static TinyCmd_Status TinyCmd_isspace(int c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

//int TinyCmd_Str_To_int(const char* str):
//Description:Convert a string to an integer.
//args:
//        str: String to convert.
//Returns:
//        Integer value of the string.
int TinyCmd_Str_To_int(const char* str) {
    if (str == NULL) {
        return 0;
    }

    while (TinyCmd_isspace(*str)) {
        str++;
    }

    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    int result = 0;
    while (TinyCmd_isdigit(*str)) {
        int digit = *str - '0';

        if (result > (CMD_INT32_MAX - digit) / 10) {
            return (sign == 1) ? CMD_INT32_MAX : CMD_INT32_MIN;
        }

        result = result * 10 + digit;
        str++;
    }

    return result * sign;
}

//double TinyCmd_Str_To_Float(const char* str):
//Description:Convert a string to a floating-point number.
//args:
//        str: String to convert.
//Returns:
//        Floating-point value of the string.
double TinyCmd_Str_To_Float(const char* str) 
{
    if (str == NULL) {
        return 0.0;
    }

    while (TinyCmd_isspace(*str)) {
        str++;
    }

    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    double integer_part = 0;
    while (TinyCmd_isdigit(*str)) {
        int digit = *str - '0';
        integer_part = integer_part * 10 + digit;
        str++;
    }

    if (*str == '.') {
        str++;
    } else {
        return integer_part * sign;
    }

    double fractional_part = 0;
    double divisor = 1.0;
    while (TinyCmd_isdigit(*str)) {
        int digit = *str - '0';
        fractional_part = fractional_part * 10 + digit;
        divisor *= 10;
        str++;
    }

    double result = integer_part + (fractional_part / divisor);
    return result * sign;
}

//int TinyCmd_Arg_To_Int(TinyCmd_Counter_Type p_arg):
//Description:Convert the argument at position p_arg to an integer.
//args:
//        p_arg: Position of the argument in the TinyCmd_buf.arg array.
//Returns:
//        Integer value of the argument.
TinyCmd_Status TinyCmd_Arg_To_Int32(TinyCmd_Counter_Type p_arg,int32_t* number)
{
    if(number!= NULL && TinyCmd_buf.arg[p_arg]!= NULL){
        *number = TinyCmd_Str_To_int(TinyCmd_buf.arg[p_arg]);
        return TINYCMD_SUCCESS;
    }
    else{
        return TINYCMD_FAILED;
    }
}

TinyCmd_Status TinyCmd_Arg_To_Int16(TinyCmd_Counter_Type p_arg,int16_t* number)
{
    if(number!= NULL && TinyCmd_buf.arg[p_arg]!= NULL){
        int temp = TinyCmd_Str_To_int(TinyCmd_buf.arg[p_arg]);
        *number = TinyCmd_Str_To_int(TinyCmd_buf.arg[p_arg]); 

        if(temp > CMD_INT16_MAX){
            *number = CMD_INT16_MAX;
            return TINYCMD_SUCCESS;
        }
        else if(temp < CMD_INT16_MIN){
            *number = CMD_INT16_MIN;
            return TINYCMD_SUCCESS;
        }
        else{
            *number = (int16_t)temp;
            return TINYCMD_SUCCESS;
        }
    }
    else{
        return TINYCMD_FAILED;
    }
}

TinyCmd_Status TinyCmd_Arg_To_Int8(TinyCmd_Counter_Type p_arg,int8_t* number)
{
    if(number!= NULL && TinyCmd_buf.arg[p_arg]!= NULL){
        int temp = TinyCmd_Str_To_int(TinyCmd_buf.arg[p_arg]);
        *number = TinyCmd_Str_To_int(TinyCmd_buf.arg[p_arg]); 

        if(temp > CMD_INT8_MAX){
            *number = CMD_INT8_MAX;
            return TINYCMD_SUCCESS;
        }
        else if(temp < CMD_INT8_MIN){
            *number = CMD_INT8_MIN;
            return TINYCMD_SUCCESS;
        }
        else{
            *number = (int16_t)temp;
            return TINYCMD_SUCCESS;
        }
    }
    else{
        return TINYCMD_FAILED;
    }
}

//double TinyCmd_Arg_To_Float(TinyCmd_Counter_Type p_arg):
//Description:Convert the argument at position p_arg to a floating-point number.
//args:
//        p_arg: Position of the argument in the TinyCmd_buf.arg array.
//Returns:
//        Floating-point value of the argument.
TinyCmd_Status TinyCmd_Arg_To_Float(TinyCmd_Counter_Type p_arg,float* number)
{
    if(number!= NULL && TinyCmd_buf.arg[p_arg]!= NULL){
        *number = TinyCmd_Str_To_Float(TinyCmd_buf.arg[p_arg]);
        return TINYCMD_SUCCESS;
    }
    else{
        return TINYCMD_FAILED;
    }
}