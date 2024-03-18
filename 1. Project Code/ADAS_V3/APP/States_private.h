/*
 * States_private.h
 *
 *  Created on: Mar 17, 2024
 *      Author: Mohammed Ramadan
 */

#ifndef APP_STATES_PRIVATE_H_
#define APP_STATES_PRIVATE_H_

#define LCD_LEFT				'7'
#define LCD_RIGHT				'8'

typedef enum
{
	CCS_OFF,
	CCS_ON
}CCS_State_t;
/*******************************************************************************/
typedef enum
{
	BAS_OFF,
	BAS_ON
}BAS_State_t;
/********************************************************************************/
typedef enum
{
	GEARBOX_N,
	GEARBOX_D,
	GEARBOX_R
}GearBox_State_t;
/********************************************************************************/
typedef enum
{
	BRAKE_LED_OFF,
	BRAKE_LED_ON
}BrakeLED_State_t;
/********************************************************************************/
typedef enum
{
	ALARM_LED_OFF,
	ALARM_LED_ON
}AlarmLED_State_t;

/********************************************************************************/
typedef enum
{
	LCD_TAB_1,
	LCD_TAB_2,
	LCD_TAB_3,
	LCD_TAB_4
}LCD_TAB_State_t;

typedef enum
{
	SPD_LIM_OFF,
	SPD_LIM_ON
}SPD_Limiter_State_t;

typedef enum
{
	DRIVER_SLEEP ,
	DRIVER_NOT_SLEEP
}Drive_Monitor_State_t;

typedef enum
{
	RANGE_0_40 = 1,
	RANGE_40_80,
	RANGE_80_120,
	RANGE_120_160,
	RANGE_160_200,

}Speed_Ranges_t;

extern u8 	g_Speed_Limit_State  ;
extern u8 	GearBox_State 		 ;
extern u8 	g_CCS_State     	 ;
extern u8   g_LCD_Update    	 ;
extern u8	g_BAS_State 		 ;
extern u8 	g_LCD_Tab			 ;
extern u16	g_Speed				 ;
extern u8	g_Speed_Limit		 ;
extern u8   Driver_monitor ;
extern u8   flag_for_DM ;
extern u32   seconds ;
extern u16	g_KM_Counter ;
extern u8	g_LCD_Update_Pages ;

void A_Void_LCD_Screen1_Display(void);
void A_Void_LCD_Screen2_Display(void);
void A_Void_LCD_Screen3_Display(void);
void A_Void_LCD_Screen4_Display(void) ;
void A_Void_SpeedLimiter_Switch_State(void) ;
void A_Void_CCS_Check_Task(void) ;
void A_Void_BAS_Check_Task(void) ;
void A_Void_GearBox_Check_Task(void);
void A_Void_LCD_Left(void) ;
void A_Void_LCD_Right(void) ;


#endif /* APP_STATES_PRIVATE_H_ */
