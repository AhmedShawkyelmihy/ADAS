/****************************************/
/* 			     Directives 			*/
/****************************************/
#include "../STD.h"
#include "../BitMath.h"
/******************************************************************/
#include "../MCAL/ADC/ADC_Interface.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/Timer/Timer_Interface.h"
/******************************************************************/
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/LED/LED_Interface.h"
#include "../HAL/Buzzer/Buzzer_Interface.h"
#include "../HAL/Keypad/Keypad_Interface.h"
#include "../HAL/PushButton/PushButton_Interface.h"
/******************************************************************/
#include "util/delay.h"
#include "States_private.h"
#include "States_Interface.h"
/******************************************************************/

u8 	g_Speed_Limit_State = SPD_LIM_OFF ;
u8 	GearBox_State 		= GEARBOX_N  ;
u8 	g_CCS_State     	= CCS_OFF    ;
u8   g_LCD_Update    	= 1 		 ;
u8	g_BAS_State 		= BAS_OFF ;
u8 	g_LCD_Tab			= LCD_TAB_1 ;
u16	g_Speed				= 0 ;
u8	g_Speed_Old			= 0 ;
u8	g_Speed_Limit		= 0 ;
u8  Button              = KEYPAD_RELEASED ;
u8  flag_for_DM          = DRIVER_NOT_SLEEP ;
u32 seconds              = 0 ;
u8 	g_Speed_Range	     = 0 ;
u16 g_KM_Counter		= 0 ;
u8 	g_LCD_Update_Pages	= 1 ;

void A_Void_Exceed_Speed_Limit(void)
{
	static u8 counter = 0 ;
	counter ++ ;
	if ((g_Speed_Limit_State == SPD_LIM_ON) && (g_Speed > g_Speed_Limit))
	{
		if(counter % 2 == 0)
		{
			M_DIO_Void_SetPinValue(RELAY_PIN,HIGH) ;
		}
		else
		{
			M_DIO_Void_SetPinValue(RELAY_PIN,LOW) ;
		}
	}
	/*speed limiter decrement*/
	if (Button == '2')
	{
		if(g_Speed_Limit > 0)
		{
			g_Speed_Limit -= 5 ;
		}
	}
	/*speed limiter increment*/
	if (Button == '3')
	{
		if(g_Speed_Limit < 100)
		{
			g_Speed_Limit += 5 ;
		}
	}
	if (counter == 10)
	{
		if (GearBox_State == GEARBOX_D)
		{
			flag_for_DM = DRIVER_SLEEP ;
		}
		counter = 0 ;
	}

	if (counter %2 == 0)
	{
		g_KM_Counter += g_Speed_Range ;
		seconds ++ ;
		if (seconds == 86400)
		{
			seconds = 0 ;
		}
	}
}

void A_Void_Init_System(void)
{
	M_ADC_Void_ADCInit();

	H_KeyPad_Void_KeyPadInit();

	H_PushButton_Void_PushButtonInit(BRAKE_PEDAL);


	H_LED_Void_LedInit(BRAKE_LED);
	H_LED_Void_LedInit(ALARM_LED);

	H_Buzzer_Void_BuzzerInit();

	H_Lcd_Void_LCDInit();

	M_DIO_Void_SetPinDirection(RELAY_PIN,OUTPUT);

	M_Timer_Void_TimerInit();
	M_Timer_Void_TimerSetTime(500);
	M_Timer_Void_SetCallBack(A_Void_Exceed_Speed_Limit);
	M_Timer_Void_TimerStart(TIMER0_CHANNEL) ;
}

void A_Void_Keypad_Check_State(void)
{
	Button = H_KeyPad_U8_KeyPadRead() ;
	switch(Button)
	{
	case '1' :
		/* Speed Limit ON/OFF */
		flag_for_DM = DRIVER_NOT_SLEEP ;
		A_Void_SpeedLimiter_Switch_State();
		break;
	case '4' :
		/* CCS ON/OFF */
		flag_for_DM = DRIVER_NOT_SLEEP ;
		A_Void_CCS_Check_Task();
		break;
	case '5' :
		/* BAS ON/OFF */
		flag_for_DM = DRIVER_NOT_SLEEP ;
		A_Void_BAS_Check_Task();
		break;
	case '6' :
		/* Changing Gear Box */
		flag_for_DM = DRIVER_NOT_SLEEP ;
		A_Void_GearBox_Check_Task();
		break;
	case '7' :
		/* LCD Left */
		flag_for_DM = DRIVER_NOT_SLEEP ;
		A_Void_LCD_Left();
		break;
	case '8' :
		/* LCD Right */
		flag_for_DM = DRIVER_NOT_SLEEP ;
		A_Void_LCD_Right();
		break;
	case '9' :
		break;
	default :
		H_LED_Void_LedOff(ALARM_LED);
		break;
	}
}

void A_Void_BrakeLED_Check_State(void)
{
	if(H_PushButton_U8_PushButtonRead(BRAKE_PEDAL) == PUSH_BUTTON_PRESSED)
	{
		flag_for_DM = DRIVER_NOT_SLEEP ;
		H_LED_Void_LedOn(BRAKE_LED);
	}
	else
	{
		H_LED_Void_LedOff(BRAKE_LED);
	}
}

void A_Void_LCD_Display(void)
{
	switch(g_LCD_Tab)
	{
	case LCD_TAB_1 :
		A_Void_LCD_Screen1_Display();
		break;
	case LCD_TAB_2 :
		A_Void_LCD_Screen2_Display();
		break;
	case LCD_TAB_3 :
		A_Void_LCD_Screen3_Display();
		break;
	case LCD_TAB_4 :
		A_Void_LCD_Screen4_Display();
		break;
	}
}

void A_Void_Speed_Check(void)
{
	g_Speed = ((M_ADC_U16_ADCRead(ADC_CHANNEL_0) / 1023.0) * 200) ;

	if((g_Speed == g_Speed_Old + 1) || (g_Speed == g_Speed_Old - 1))
	{
		/* Do Nothing */
	}
	else if(g_Speed_Old != g_Speed)
	{
		flag_for_DM = DRIVER_NOT_SLEEP ;

		g_CCS_State     	= CCS_OFF    ;
		if(g_LCD_Tab == LCD_TAB_2)
		{
			H_Lcd_Void_LCDGoTo(1, 5);
			H_Lcd_Void_LCDWriteString((u8*)"OFF");
		}

		g_Speed_Old = g_Speed ;
	}
	if((g_Speed > 0) && (g_Speed <= 40))
	{
		g_Speed_Range = RANGE_0_40 ;
	}
	else if((g_Speed > 40) && (g_Speed <= 80))
	{
		g_Speed_Range = RANGE_40_80 ;
	}
	else if((g_Speed > 80) && (g_Speed <= 120))
	{
		g_Speed_Range = RANGE_80_120 ;
	}
	else if((g_Speed > 120) && (g_Speed <= 160))
	{
		g_Speed_Range = RANGE_120_160 ;
	}
	else if((g_Speed > 160) && (g_Speed <= 200))
	{
		g_Speed_Range = RANGE_160_200 ;
	}
	else
	{
		g_Speed_Range = 0 ;
	}

	if(g_LCD_Tab == LCD_TAB_1)
	{
		H_Lcd_Void_LCDGoTo(0, 7);
		H_Lcd_Void_LCDWriteNumber(g_Speed/100);
		H_Lcd_Void_LCDWriteNumber((g_Speed%100)/10);
		H_Lcd_Void_LCDWriteNumber(((g_Speed%100)%10));
	}

	if(g_LCD_Tab == LCD_TAB_1)
	{
		H_Lcd_Void_LCDGoTo(1, 7);
		H_Lcd_Void_LCDWriteNumber(g_Speed_Limit/100);
		H_Lcd_Void_LCDWriteNumber((g_Speed_Limit%100)/10);
		H_Lcd_Void_LCDWriteNumber(((g_Speed_Limit%100)%10));
	}

}

void A_Void_Drive_Monitor (void)
{
	if (flag_for_DM == DRIVER_NOT_SLEEP)
	{
		H_Lcd_Void_LCDGoTo(2, 0) ;
		H_Lcd_Void_LCDWriteString((u8*)"                ") ;
	}
	else if (flag_for_DM == DRIVER_SLEEP)
	{
		H_Lcd_Void_LCDGoTo(2, 0) ;
		H_Lcd_Void_LCDWriteString((u8*)"You are sleeping") ;
	}
}
void A_Void_Display_Time (void)
{
	if (g_LCD_Tab == LCD_TAB_4)
	{
		/*Second Row*/
		H_Lcd_Void_LCDGoTo(1,0);
		H_Lcd_Void_LCDWriteString((u8*)"Time : ");
		H_Lcd_Void_LCDWriteNumber((seconds/3600)/10) ;
		H_Lcd_Void_LCDWriteNumber((seconds/3600)%10) ;
		H_Lcd_Void_LCDWriteString((u8*)":");
		H_Lcd_Void_LCDWriteNumber(((seconds%3600)/60)/10) ;
		H_Lcd_Void_LCDWriteNumber(((seconds%3600)/60)%10) ;
		H_Lcd_Void_LCDWriteString((u8*)":");
		H_Lcd_Void_LCDWriteNumber(((seconds%3600)%60)/10) ;
		H_Lcd_Void_LCDWriteNumber(((seconds%3600)%60)%10) ;
	}
}

void A_Void_Display_KMG (void)
{
	if (g_LCD_Tab == LCD_TAB_3)
	{
		H_Lcd_Void_LCDGoTo(0,13);
		H_Lcd_Void_LCDWriteNumber(g_KM_Counter/100);
		H_Lcd_Void_LCDWriteNumber((g_KM_Counter%100)/10);
		H_Lcd_Void_LCDWriteNumber(((g_KM_Counter%100)%10));
	}
}
