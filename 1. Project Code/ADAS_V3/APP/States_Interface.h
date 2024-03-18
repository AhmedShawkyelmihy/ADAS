/****************************************************************************************
* ! Title : States_Interface
* ! File Name : States_Interface.c
* ! Description : This file has the declaration of the system functions and
* the usage of the static global variables.
* ! Compiler : GNU AVR Cross Compiler
* ! Target : ATMEGA32 Micro-controller
****************************************************************************************/
/****************************************************************************************
* LOG :
* VERSION    AUTHOR             DATE              DESCRIPTION
* v1.0       Mohammed Ramadan   4 March,2024       - Initial creation, Adding APIs
* v2.0       Ahmed Shawky       5 March,2024       - Modifying the change of requirements and developing them
****************************************************************************************/


#ifndef APP_STATES_INTERFACE_H_
#define APP_STATES_INTERFACE_H_
/******************************************************************************/
#define DISABLE 			   	0
#define ENABLE 				   	1
/******************************************************************************/
#define BRAKE_PEDAL			   	PUSH_BUTTON_3
#define BRAKE_LED			   	LED_RED
/******************************************************************************/
#define GEARBOX_SWITCH		   	'6'
/******************************************************************************/
#define CCS_SWITCH			   	'4'
/******************************************************************************/
#define BAS_SWITCH		   		'5'
/******************************************************************************/
#define ALARM_LED			   	LED_YEL
/******************************************************************************/
#define POTENTIOMETER_CHANNEL  	ADC_CHANNEL_0
/******************************************************************************/
#define RELAY_PIN				PC7_PIN
/******************************************************************************/


void A_Void_Init_System(void) ;
void A_Void_BrakeLED_Check_State(void) ;
void A_Void_LCD_Display(void);
void A_Void_Keypad_Check_State(void);
void A_Void_Speed_Check(void) ;
void A_Void_Drive_Monitor (void) ;
void A_Void_Display_Time (void) ;
void A_Void_Display_KMG (void) ;
#endif /* APP_STATES_INTERFACE_H_ */
