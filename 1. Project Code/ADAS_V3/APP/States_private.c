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


void A_Void_LCD_Screen1_Display(void)
{
	if(g_LCD_Update_Pages == 1)
	{
		g_LCD_Update_Pages = 0 ;

		H_Lcd_Void_LCDClear() ;

		/* First Row */
		H_Lcd_Void_LCDWriteString((u8*)"Speed: ");
		H_Lcd_Void_LCDWriteNumber(g_Speed/100);
		H_Lcd_Void_LCDWriteNumber((g_Speed%100)/10);
		H_Lcd_Void_LCDWriteNumber(((g_Speed%100)%10));
		H_Lcd_Void_LCDWriteString((u8*)" Kmh");

		/* Second Row */
		H_Lcd_Void_LCDGoTo(1,0);
		H_Lcd_Void_LCDWriteString((u8*)"Limit: ");
		H_Lcd_Void_LCDWriteNumber(g_Speed_Limit/100);
		H_Lcd_Void_LCDWriteNumber((g_Speed_Limit%100)/10);
		H_Lcd_Void_LCDWriteNumber(((g_Speed_Limit%100)%10));
		H_Lcd_Void_LCDWriteString((u8*)" Kmh");
		switch(g_Speed_Limit_State)
		{
		case SPD_LIM_OFF :
			H_Lcd_Void_LCDWriteString((u8*)"(OFF)");
			break;
		case SPD_LIM_ON :
			H_Lcd_Void_LCDWriteString((u8*)"(ON)");
			break;
		}

		/* Fourth Row */
		H_Lcd_Void_LCDGoTo(3,8);
		H_Lcd_Void_LCDWriteCharacter(223);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(161);
	}
}

void A_Void_LCD_Screen2_Display(void)
{
	if(g_LCD_Update_Pages == 1)
	{
		g_LCD_Update_Pages = 0 ;

		H_Lcd_Void_LCDClear() ;

		/* First Row */
		H_Lcd_Void_LCDWriteString((u8*)"PNDR: ");
		switch(GearBox_State)
		{
		case GEARBOX_N :
			H_Lcd_Void_LCDWriteCharacter('N');
			break;
		case GEARBOX_D :
			H_Lcd_Void_LCDWriteCharacter('D');
			break;
		case GEARBOX_R :
			H_Lcd_Void_LCDWriteCharacter('R');
			break;
		}

		/* Second Row */
		H_Lcd_Void_LCDGoTo(1,0);
		H_Lcd_Void_LCDWriteString((u8*)"CCS: ");
		switch(g_CCS_State)
		{
		case CCS_OFF :
			H_Lcd_Void_LCDWriteString((u8*)"OFF");
			break;
		case CCS_ON :
			H_Lcd_Void_LCDWriteString((u8*)"ON");
			break;
		}

		/* Second Row */
		H_Lcd_Void_LCDGoTo(1,11);
		H_Lcd_Void_LCDWriteString((u8*)"BAS: ");
		switch(g_BAS_State)
		{
		case BAS_OFF :
			H_Lcd_Void_LCDWriteString((u8*)"OFF");
			break;
		case BAS_ON :
			H_Lcd_Void_LCDWriteString((u8*)"ON");
			break;
		}

		/* Fourth Row */
		H_Lcd_Void_LCDGoTo(3,8);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(223);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(161);
	}
}

void A_Void_LCD_Screen3_Display(void)
{
	if(g_LCD_Update_Pages == 1)
	{
		g_LCD_Update_Pages = 0 ;

		H_Lcd_Void_LCDClear() ;

		H_Lcd_Void_LCDWriteString((u8*)"KM Counter : ") ;
		H_Lcd_Void_LCDWriteNumber(g_KM_Counter/100);
		H_Lcd_Void_LCDWriteNumber((g_KM_Counter%100)/10);
		H_Lcd_Void_LCDWriteNumber(((g_KM_Counter%100)%10));
		H_Lcd_Void_LCDWriteString((u8*)" KM") ;

		/* Fourth Row */
		H_Lcd_Void_LCDGoTo(1,5);
		H_Lcd_Void_LCDWriteString((u8*)"E") ;
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteString((u8*)"F") ;

		/* Fourth Row */
		H_Lcd_Void_LCDGoTo(3,8);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(223);
		H_Lcd_Void_LCDWriteCharacter(161);
	}
}

void A_Void_LCD_Screen4_Display(void)
{
	if(g_LCD_Update_Pages == 1)
	{
		g_LCD_Update_Pages = 0 ;

		H_Lcd_Void_LCDClear() ;

		/*First Row*/
		H_Lcd_Void_LCDWriteString((u8*)"Date : 18/3/2024");

		/* Fourth Row */
		H_Lcd_Void_LCDGoTo(3,8);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(161);
		H_Lcd_Void_LCDWriteCharacter(223);
	}
}

void A_Void_LCD_Left(void)
{
	if(g_LCD_Tab > LCD_TAB_1)
	{
		--g_LCD_Tab ;
		g_LCD_Update_Pages = 1 ;
	}
}

void A_Void_LCD_Right(void)
{
	if(g_LCD_Tab < LCD_TAB_4)
	{
		++g_LCD_Tab ;
		g_LCD_Update_Pages = 1 ;
	}
}

void A_Void_GearBox_Check_Task(void)
{
	H_Buzzer_Void_BuzzerOn();
	_delay_ms(50);
	H_Buzzer_Void_BuzzerOff();

	if(H_PushButton_U8_PushButtonRead(BRAKE_PEDAL) == PUSH_BUTTON_PRESSED)
	{
		flag_for_DM = DRIVER_NOT_SLEEP ;
		g_LCD_Update = 1 ;
		g_CCS_State = CCS_OFF ;

		switch(GearBox_State)
		{
		case GEARBOX_R :
			if(g_LCD_Tab == LCD_TAB_2)
			{
				H_Lcd_Void_LCDGoTo(0, 6);
				H_Lcd_Void_LCDWriteCharacter('N');
				H_Lcd_Void_LCDGoTo(1, 5) ;
				H_Lcd_Void_LCDWriteString((u8*)"OFF") ;
				H_Lcd_Void_LCDGoTo(1, 16) ;
				H_Lcd_Void_LCDWriteString((u8*)"OFF") ;
			}
			g_Speed_Limit_State = SPD_LIM_OFF ;
			GearBox_State = GEARBOX_N ;
			g_BAS_State = BAS_OFF ;
			break;
		case GEARBOX_N :
			if(g_LCD_Tab == LCD_TAB_2)
			{
				H_Lcd_Void_LCDGoTo(0, 6);
				H_Lcd_Void_LCDWriteCharacter('D');
			}
			GearBox_State = GEARBOX_D ;
			g_BAS_State = BAS_ON ;
			break;
		case GEARBOX_D :
			if(g_LCD_Tab == LCD_TAB_2)
			{
				H_Lcd_Void_LCDGoTo(0, 6);
				H_Lcd_Void_LCDWriteCharacter('R');
				H_Lcd_Void_LCDGoTo(1, 5) ;
				H_Lcd_Void_LCDWriteString((u8*)"OFF") ;
				H_Lcd_Void_LCDGoTo(1, 16) ;
				H_Lcd_Void_LCDWriteString((u8*)"OFF") ;
			}
			g_Speed_Limit_State = SPD_LIM_OFF ;
			GearBox_State = GEARBOX_R ;
			g_BAS_State = BAS_OFF ;
			break;
		}

	}
	else
	{
		H_LED_Void_LedOn(ALARM_LED);
	}
}

void A_Void_CCS_Check_Task(void)
{
	H_Buzzer_Void_BuzzerOn();
	_delay_ms(50);
	H_Buzzer_Void_BuzzerOff();

	if(GearBox_State == GEARBOX_D)
	{
		switch(g_CCS_State)
		{
		case CCS_OFF :
			if(g_LCD_Tab == LCD_TAB_2)
			{
				H_Lcd_Void_LCDGoTo(1, 5);
				H_Lcd_Void_LCDWriteString((u8*)"ON ");
			}
			g_CCS_State = CCS_ON ;
			break;
		case CCS_ON :
			if(g_LCD_Tab == LCD_TAB_2)
			{
				H_Lcd_Void_LCDGoTo(1, 5);
				H_Lcd_Void_LCDWriteString((u8*)"OFF");
			}
			g_CCS_State = CCS_OFF ;
			break;
		}
	}
	else
	{
		H_LED_Void_LedOn(ALARM_LED);
	}
}

void A_Void_BAS_Check_Task(void)
{
	H_Buzzer_Void_BuzzerOn();
	_delay_ms(50);
	H_Buzzer_Void_BuzzerOff();

	if(GearBox_State == GEARBOX_D)
	{
		flag_for_DM = DRIVER_NOT_SLEEP ;
		switch(g_BAS_State)
		{
		case BAS_OFF :
			if(g_LCD_Tab == LCD_TAB_2)
			{
				H_Lcd_Void_LCDGoTo(1, 16);
				H_Lcd_Void_LCDWriteString((u8*)"ON ");
			}
			g_BAS_State = BAS_ON ;
			break;
		case BAS_ON :
			if(g_LCD_Tab == LCD_TAB_2)
			{
				H_Lcd_Void_LCDGoTo(1,16);
				H_Lcd_Void_LCDWriteString((u8*)"OFF");
			}
			g_BAS_State = BAS_OFF ;
			break;
		}
	}
	else
	{
		H_LED_Void_LedOn(ALARM_LED);
	}
}

void A_Void_SpeedLimiter_Switch_State(void)
{
	if(GearBox_State == GEARBOX_D)
	{
		flag_for_DM = DRIVER_NOT_SLEEP ;
		switch(g_Speed_Limit_State)
		{
		case SPD_LIM_OFF :
			g_Speed_Limit_State = SPD_LIM_ON ;
			if(g_LCD_Tab == LCD_TAB_1)
			{
				H_Lcd_Void_LCDGoTo(1, 15);
				H_Lcd_Void_LCDWriteString((u8*)"ON) ");
			}
			break;
		case SPD_LIM_ON :
			g_Speed_Limit_State = SPD_LIM_OFF ;
			if(g_LCD_Tab == LCD_TAB_1)
			{
				H_Lcd_Void_LCDGoTo(1, 15);
				H_Lcd_Void_LCDWriteString((u8*)"OFF)");
			}
			break;
		}
	}
	else
	{
		H_LED_Void_LedOn(ALARM_LED);
	}
}
