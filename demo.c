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
 * File: demo.c
 * Author: Civic_Crab
 * Version: 1.1.0
 * Created on: 2024-10-24
 *
 * Description:
 * This file is a demo shows how to use TinyCmd to handle command line input.
 */

#include <stdio.h>
#include "TinyCmd.h"

TinyCmd_CallBack_Ret Cmd1_Callback(void)
{
    printf("Command1 is called!\n");

    //Check 1st aurgument and do something
    if(TinyCmd_Arg_Check("check",0) == TINYCMD_SUCCESS)
    {
        //Do something here when the command with argument "check" is called
        //Your code here......
        printf("Position 0 has parameter: check\n");
    }
    else if(TinyCmd_Arg_Check("check2",0) == TINYCMD_SUCCESS)
    {
        //Do something here when the command with argument "check2" is called
        //Your code here......
        printf("Position 0 has parameter: check2\n");
    }

    
    //Get integer number from 2nd aurgument and do something
    int ArgInt = TinyCmd_Arg_To_Int(1);
    if(ArgInt)
    {
        //Do something here when the command with argument "check" is called
        //Your code here......
        printf("Position 1 has parameter: %d\n",ArgInt);
    }

    //Get float number from 3rd aurgument and do something
    float ArgFloat = TinyCmd_Arg_To_Float(2);
    if(ArgFloat)
    {
        //Do something here when the command with argument "check" is called
        //Your code here......
        printf("Position 2 has parameter: %f\n",ArgFloat);
    }


}

TinyCmd_CallBack_Ret Cmd2_Callback(void)
{
    printf("Command1 is called!\n");
}

//Create a new command 
TinyCmd_Command Cmd1 = {.command = "cmd1",.callback = &Cmd1_Callback};
TinyCmd_Command Cmd2 = {.command = "cmd2",.callback = &Cmd2_Callback};

//Create a buffer to store the input string
char buffer[CMD_BUF_SIZE];

int main(void) 
{
    //Add command to the list,
    TinyCmd_Add_Cmd(&Cmd1);
    TinyCmd_Add_Cmd(&Cmd2);

    while(1)
    {
        //Print the prompt to the user
        printf("Input: ");

        //Get the input string from the user
        //You also can do it in another way
        //For instance in microcontroller,you can use UART or other serial port to get the input string
        fgets(buffer,CMD_BUF_SIZE,stdin);

        //Put the input string to the TinyCmd,TinyCmd_PutString 
        //function will trim the string and remove the '\n' character for you
        //so you don't need to do it manually.
        TinyCmd_PutString(buffer);

        //After you put the input string to the TinyCmd,
        //Call Tiny_Command_Handler function to handle the input string
        //If the input string is a valid command,
        //The corresponding callback function will be called.
        TinyCmd_Handler();
    }


    return 0;
}