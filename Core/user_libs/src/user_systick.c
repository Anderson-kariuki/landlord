/*
 * user_systick.c
 *
 *  Created on: Oct 25, 2018
 *      Author: ZBook
 */


#include "user_systick.h"
#include "main.h"

__IO uint32_t ms_tick;
__IO uint32_t lcd_led_ticks;
__IO uint32_t button_press_ticks;
__IO uint32_t button_handler_ticks;


void delay(uint32_t delay_ms){

	ms_tick = 0;
	while(ms_tick < delay_ms){

	}
}
/*
 * This function handles the systic interrupt
 */
void user_systic_handler(){

	ms_tick++;


	if(backlight){
		lcd_led_ticks++;
	}

	if((lcd_led_ticks > 100000)&&(backlight)){
		backlight = 0;
		lcd_led_ticks=0;
	}

	if(button_press_flag){
		button_press_ticks++;
	}

	if(button_handler_flag){
		button_handler_ticks++;
	}


}
