/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "rtc.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "i2c_lcd.h"
#include "user_systick.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t backlight = 1;

//button operation variables
uint8_t button_press_flag;
uint8_t button_handler_flag;
uint8_t up_flag = 0;
uint8_t down_flag = 0;
uint8_t ok_flag = 0;
uint8_t back_flag = 0;

uint8_t admin_screen = 0;
uint8_t menu_screen = 1;
uint8_t mpesa_mode = 0;
uint8_t mpesa_case = 0;
uint8_t payment_flag = 0;
uint8_t menu = 0;
uint8_t admin = 0;
uint8_t a = 0;
uint8_t sub_mode_flag = 0;
uint8_t check_balance_flag = 0;
uint8_t sub = 0;
uint8_t adm = 0;
uint8_t mpesa_flag = 0;
uint8_t mpesa_menu_flag = 0;
uint8_t till_flag = 0;
uint8_t till_menu = 0;
uint8_t paybill = 0;
uint8_t pin = 0;
uint8_t amount = 0;
uint8_t adm_menu = 0;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  //lcd init
  lcd16x2_i2c_init(&hi2c1); //Initialize LCD
  lcd16x2_i2c_1stLine();
  lcd16x2_i2c_printf("WELCOME");
  lcd16x2_i2c_2ndLine();
  lcd16x2_i2c_printf("VIEW MENU");
  delay(2000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  button_hundler();
	  homeScreen();
	  sleep_mode() ;
	  resetButtons();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
unsigned char key_press(void){
	unsigned char clm_var;
	unsigned char key_arr[] = {7, 8, 9, 15, 4, 5, 6, 14, 1, 2, 3, 13, 10, 0, 11, 12};
	HAL_GPIO_WritePin(C1_GPIO_PORT, C1_Pin | C2_GPIO_PORT, C2_Pin | C3_GPIO_PORT, C3_Pin | C4_GPIO_PORT, C4_Pin, GPIO_PIN_RESET);

	if (HAL_GPIO_ReadPin(R1_GPIO_Port, R1_Pin)==0){
		clm_var = check_clm(R1_Pin);
		return key_arr[clm_var-1];
	}
	else if (HAL_GPIO_ReadPin(R2_GPIO_Port, R2_Pin)==0){
		clm_var = check_clm(R2_Pin);
		return key_arr[clm_var+3];
	}
	else if (HAL_GPIO_ReadPin(R3_GPIO_Port, R3_Pin)==0){
		clm_var = check_clm(R3_Pin);
		return key_arr[clm_var+7];
	}
	else if (HAL_GPIO_ReadPin(R4_GPIO_Port, R4_Pin)==0){
		clm_var = check_clm(R4_Pin);
		return key_arr[clm_var+11];
	}
	else
		return 16;
}

unsigned char check_clm(unsigned char pin_var){
	unsigned char clm;
	HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin | C2_GPIO_Port, C2_Pin | C3_GPIO_Port, C3_Pin | C4_GPIO_Port, C4_Pin, GPIO_PIN_SET); //Set all colunms to logic 1

	HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);  //Set first column to GND
	if(HAL_GPIO_ReadPin(R1_GPIO_Port, R1_Pin | R2_GPIO_Port, R2_Pin | R3_GPIO_Port, R3_Pin | R4_GPIO_Port, R4_Pin) == 0){
		clm = 1;
	}

	HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(C2_GPIO_Port, C2_Pin, GPIO_PIN_RESET);  //Set second column to GND
	if(HAL_GPIO_ReadPin(R1_GPIO_Port, R1_Pin | R2_GPIO_Port, R2_Pin | R3_GPIO_Port, R3_Pin | R4_GPIO_Port, R4_Pin) == 0){
		clm = 2;
	}

	HAL_GPIO_WritePin(C2_GPIO_Port, C2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(C3_GPIO_Port, C3_Pin, GPIO_PIN_RESET);  //Set third column to GND
	if(HAL_GPIO_ReadPin(R1_GPIO_Port, R1_Pin | R2_GPIO_Port, R2_Pin | R3_GPIO_Port, R3_Pin | R4_GPIO_Port, R4_Pin) == 0){
		clm = 3;
	}
	HAL_GPIO_WritePin(C3_GPIO_Port, C3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(C4_GPIO_Port, C4_Pin, GPIO_PIN_RESET);  //Set second column to GND
	if(HAL_GPIO_ReadPin(R1_GPIO_Port, R1_Pin | R2_GPIO_Port, R2_Pin | R3_GPIO_Port, R3_Pin | R4_GPIO_Port, R4_Pin) == 0){
		clm = 4;
	}

	HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin | C2_GPIO_Port, C2_Pin | C3_GPIO_Port, C3_Pin | C4_GPIO_Port, C4_Pin, GPIO_PIN_RESET);  // Set all columns to logic0 ie connected
	return clm;
}

void button_hundler(){

	  if (HAL_GPIO_ReadPin(UP_GPIO_Port, UP_Pin)==0){
		  //raise up menu movement flag
		  up_flag = 1;
		  backlight = 1;
		  button_handler_flag = 1;
		  button_handler_ticks=0;

	  }

	  if (HAL_GPIO_ReadPin(DOWN_GPIO_Port, DOWN_Pin)==0){
		  //raise down menu movement flag
		  down_flag = 1;
		  backlight = 1;
		  button_handler_flag = 1;
		  button_handler_ticks=0;
	  }

	  if (HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin)==0){
		  //raise okey flag
		  ok_flag = 1;
		  backlight = 1;
		  button_handler_flag = 1;
		  button_handler_ticks=0;
	  }

	  if (HAL_GPIO_ReadPin(BACK_GPIO_Port, BACK_Pin)==0){
		  //raise back menu movement flag
		  back_flag = 1;
		  backlight = 1;
		  button_handler_flag = 1;
		  button_handler_ticks=0;
	  }
	  delay(50);
}

void homeScreen() {
	//	main menu screen select
	while (menu_screen) {
		button_hundler();

		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("MENU");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("ADMIN");
		lcd16x2_i2c_setCursor(0, 6);
		lcd16x2_i2c_printf(">");
		delay(100);

		if (ok_flag) {
			resetButtons();
			menu = 1;
		}

		while (menu) {
			button_hundler();
			if (up_flag || down_flag){
				resetButtons();
				a++;
			 }
			if(a>1){
				a=0;
			}
			if (!a){
//				PROMPTING FOR PAYMENT SUBSCRIPTION MODE SELECTING
				lcd16x2_i2c_clear();
				lcd16x2_i2c_1stLine();
				lcd16x2_i2c_printf("SUBSCRIPTION");
				lcd16x2_i2c_2ndLine();
				lcd16x2_i2c_printf("MODE");
				delay(100);

				if (ok_flag){
					resetButtons();
					sub_mode_flag =1;
				}
			}

			while (sub_mode_flag) {
				button_hundler();
				sub_mode();

				if (back_flag){
					resetButtons();
					sub_mode_flag =0;
				}
			}

			if (a) {
//				prompt for your tocken balance but ideally it should be desplayed at the home screen
				lcd16x2_i2c_clear();
				lcd16x2_i2c_1stLine();
				lcd16x2_i2c_printf("CHECK TOCKEN");
				lcd16x2_i2c_2ndLine();
				lcd16x2_i2c_printf("BALANCE");
				lcd16x2_i2c_setCursor(1, 7);
				delay(100);

				if (ok_flag){
					resetButtons();
					check_balance_flag =1;
				}
			}

			while (check_balance_flag){
//				the display for tocken balance after prompting
				button_hundler();
				if (backlight){
					lcd16x2_i2c_clear();
					lcd16x2_i2c_1stLine();
					lcd16x2_i2c_printf("TOCKEN");
					lcd16x2_i2c_2ndLine();
					lcd16x2_i2c_printf("BALANCE");
					lcd16x2_i2c_setCursor(1, 7);
					delay(100);
				}

				if (back_flag) {
					resetButtons();
					check_balance_flag =0;
				}
			}

			if (back_flag){
				resetButtons();
				menu =0;
			}

		}

		if (up_flag || down_flag) {
			resetButtons();
			admin_screen = 1;
			menu_screen = 0;
		}

	}

//	main admin screen select
	while (admin_screen ) {
		button_hundler();

		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("ADMIN");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("MENU");
		lcd16x2_i2c_setCursor(0, 6);
		lcd16x2_i2c_printf(">");
		delay(100);

		if (ok_flag) {
			resetButtons();
			admin = 1;
		}

		while (admin) {
//			to continue in admin mode you must enter authorisation pin and verification maybe done to the owners registered simcard
			button_hundler();

			lcd16x2_i2c_clear();
			lcd16x2_i2c_1stLine();
			lcd16x2_i2c_printf(" ENTER");
			lcd16x2_i2c_2ndLine();
			lcd16x2_i2c_printf("  PIN");
			delay(100);

			//		TO CONTINUE IT SHOULD DO SO WITH SIMCARD INSERTED SO AS TO NOTIFY THE OWNER VIA SMS ELSE DISPLAY ERROR
			if (ok_flag){
				adm_menu = 1;
				resetButtons();
				admin =0;
			}

			if (back_flag){
				resetButtons();
				admin =0;
			}
			while (adm_menu){
				button_hundler();
				adm_mode();
			}
		}

		if (up_flag || down_flag){
			resetButtons();
			admin_screen = 0;
			menu_screen = 1;
		}
	}
}

//this function has a case statement to iterate through various functions an admin can do
void adm_mode() {
	if (up_flag){
		if (adm >4){
			adm = 0;
		}
		adm++;
		resetButtons();
	}
	if (down_flag){
		if (adm == 0) {
			adm = 5;
			delay(10);
		}
		adm--;
		resetButtons();
	}

//	if (ok_flag){
//		resetButtons();
//		mpesa_flag = 1;
//	}
//
//	mpesa();

	switch (adm){
	case 0:
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("CHANGE");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("PIN");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);
		break;

	case 1:
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("CHANGE");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("RATES");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);
		break;

	case 2:
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("DEACTIVATE");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("LOCK");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);
		break;

	case 3:
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("ADD EXTRA DAYS ");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("WITH LOCK DEACTIVATED");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);
		break;

	case 4:
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("ACTIVATE ");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("LOCK");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);
		break;
	}
}


//this function has a switch statement to iterate through various subscription modes available for the client
void sub_mode() {
	if (up_flag){
		if (sub >3){
			sub = 0;
		}
		sub++;
		resetButtons();
	}
	if (down_flag){
		if (sub == 0) {
			sub = 4;
			delay(10);
		}
		sub--;
		resetButtons();
	}

	if (ok_flag){
		resetButtons();
		mpesa_flag = 1;
	}

	mpesa();

	switch (sub){
	case 0:
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("WEEKLY");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("SUBSCRIPTION");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);
		break;

	case 1:
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("HALF MONTHLY");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("SUBSCRIPTION");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);
		break;

	case 2:
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("MONTHLY");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("SUBSCRIPTION");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);
		break;

	case 3:
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("HALF ANNUALLY");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("SUBSCRIPTION");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);
		break;
	}
}

void mpesa(){
	while(mpesa_flag){
//		this is where at commands for simcard mpesa payment will be initiated
		button_hundler();

		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("INSERT");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("SIMCARD");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);

		if (ok_flag){
			resetButtons();
			mpesa_menu_flag =1 ;
		}

		while (mpesa_menu_flag){
//			this part is a guide to send command to initiate mpesa menu for payments
			button_hundler();
			lcd16x2_i2c_clear();
			lcd16x2_i2c_1stLine();
			lcd16x2_i2c_printf("MPESA");
			lcd16x2_i2c_2ndLine();
			lcd16x2_i2c_printf("MENU");
			lcd16x2_i2c_setCursor(1, 12);
			delay(100);
			if (ok_flag) {
				resetButtons();
				mpesa_mode =1 ;
			}

			while(mpesa_mode){
				button_hundler();
				mpesaPaymentMenu();
				if (back_flag){
					resetButtons();
					mpesa_mode =0;
				}
			}

			if (back_flag){
				resetButtons();
				mpesa_menu_flag =0;
			}
		}

		if (back_flag){
			resetButtons();
			mpesa_flag =0;
		}
	}
}

//this function contains switch statement to showcase menu navigation for mpesa payment
void mpesaPaymentMenu(){
	if (up_flag){
		if (mpesa_case >5){
			mpesa_case = 0;
		}
		mpesa_case ++;
		resetButtons();
	}
	if (down_flag){
		if (mpesa_case == 0) {
			mpesa_case = 6;
			delay(10);
		}
		mpesa_case --;
		resetButtons();
	}

	if (ok_flag && mpesa_case == 4){
		resetButtons();
		payment_flag = 1;
	}

	payment();

	switch (mpesa_case){
	case 0:
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("SEND");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("MONEY");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);
		break;

	case 1:
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("WITHDRAW");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("CASH");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);
		break;

	case 2:
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("BUY");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("AIRTIME");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);
		break;

	case 3:
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("LOAN AND");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("SAVINGS");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);
		break;

	case 4:
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("LIPA NA");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("MPESA");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);
		break;

	case 5:
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf(" MY ");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("ACCOUNT");
		lcd16x2_i2c_setCursor(1, 12);
		delay(100);
		break;
	}
}

//this function assumes that payments shall be made via paybill number and guides on how the payment process shall continue
void payment(){
	while (payment_flag){
		button_hundler();

		if (up_flag){
			if (till_menu >2){
				till_menu = 0;
			}
			till_menu ++;
			resetButtons();
		}
		if (down_flag){
			if (till_menu == 0) {
				till_menu = 3;
				delay(10);
			}
			till_menu --;
			resetButtons();
		}

		if (ok_flag && till_menu == 0){
			resetButtons();
			till_flag = 1;
		}

		while(till_flag){
			button_hundler();
			lcd16x2_i2c_clear();
			lcd16x2_i2c_1stLine();
			lcd16x2_i2c_printf("Enter Business");
			lcd16x2_i2c_2ndLine();
			lcd16x2_i2c_printf("    Number");
			delay(100);

			if (ok_flag) {
				resetButtons();
				paybill = 1 ;
			}

			while (paybill){
				button_hundler();
				lcd16x2_i2c_clear();
				lcd16x2_i2c_1stLine();
				lcd16x2_i2c_printf("Enter account");
				lcd16x2_i2c_2ndLine();
				lcd16x2_i2c_printf("    Number");
				delay(100);

				if (ok_flag) {
					resetButtons();
					amount = 1 ;
				}

				while (amount){
					button_hundler();
					lcd16x2_i2c_clear();
					lcd16x2_i2c_1stLine();
					lcd16x2_i2c_printf("  Enter");
					lcd16x2_i2c_2ndLine();
					lcd16x2_i2c_printf(" Amount");
					delay(100);

					if (ok_flag) {
						resetButtons();
						pin = 1 ;
					}

					while (pin){
						button_hundler();
						lcd16x2_i2c_clear();
						lcd16x2_i2c_1stLine();
						lcd16x2_i2c_printf("  Enter");
						lcd16x2_i2c_2ndLine();
						lcd16x2_i2c_printf("  PIN");
						delay(100);

						if (ok_flag) {
							resetButtons();
//							amount = 1 ;
						}

						if (back_flag){
							resetButtons();
							pin =0;
						}
					}

					if (back_flag){
						resetButtons();
						amount =0;
					}
				}

				if (back_flag){
					resetButtons();
					paybill =0;
				}
			}

			if (back_flag){
				resetButtons();
				till_flag =0;
			}
		}

		switch (till_menu){
		case 0:
			lcd16x2_i2c_clear();
			lcd16x2_i2c_1stLine();
			lcd16x2_i2c_printf("PAY BILL");
			lcd16x2_i2c_2ndLine();
			lcd16x2_i2c_printf("");
			delay(100);
			break;

		case 1:
			lcd16x2_i2c_clear();
			lcd16x2_i2c_1stLine();
			lcd16x2_i2c_printf("BUY GOODS");
			lcd16x2_i2c_2ndLine();
			lcd16x2_i2c_printf("AND SERVICES");
			delay(100);
			break;

		case 2:
			lcd16x2_i2c_clear();
			lcd16x2_i2c_1stLine();
			lcd16x2_i2c_printf("POCHI LA");
			lcd16x2_i2c_2ndLine();
			lcd16x2_i2c_printf("BIASHARA");
			delay(100);
			break;
		}

		if (back_flag){
			resetButtons();
			payment_flag =0;
		}
	}
}

void resetButtons(){
	up_flag = 0;
	down_flag = 0;
	ok_flag = 0;
	back_flag = 0;
}

//what to display on sleep mode
void sleep_mode() {
	if(!backlight) {
		lcd16x2_i2c_clear();
		lcd16x2_i2c_1stLine();
		lcd16x2_i2c_printf("DISPLAY");
		lcd16x2_i2c_2ndLine();
		lcd16x2_i2c_printf("BALANCE");
		delay(100);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
