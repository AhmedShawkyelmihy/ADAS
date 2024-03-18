/****************************************************************************************
* ! Title : main 
* ! File Name : main.c
* ! Description : This file has the calling of APIs
* ! Compiler : GNU AVR Cross Compiler
* ! Target : ATMEGA32 Micro-controller
****************************************************************************************/
/****************************************************************************************
* LOG :
* VERSION    AUTHOR             DATE         
* v1.0       Mohammed Ramadan   4  March,2024
* v2.0       Ahmed Shawky       5  March,2024
* v3.0       Mohammed Ramadan   16 March,2024
****************************************************************************************/

/****************************************/
/* 			     Directives 			*/
/****************************************/
#include "../STD.h"
#include "../BitMath.h"
/*********************************************************************/
#include "States_Interface.h"
/*********************************************************************/

int main()
{
	A_Void_Init_System();

 	while (1)
	{
 		A_Void_BrakeLED_Check_State();
 		A_Void_Keypad_Check_State();
 		A_Void_LCD_Display();
 		A_Void_Speed_Check();
 		A_Void_Drive_Monitor () ;
 		A_Void_Display_Time () ;
 		A_Void_Display_KMG () ;
	}
	return 0;
}
