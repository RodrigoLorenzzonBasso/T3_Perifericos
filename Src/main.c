/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma2d.h"
#include "i2c.h"
#include "ltdc.h"
#include "rtc.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_sdram.h"
#include "stm32f429i_discovery_ts.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

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
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void renderiza_RTC(void);
void inicializa_vetor_uint8(uint8_t vetor[], int tam);
void inicializa_display(void);
void configura_hora(void);
void confere_estado(void);

struct Control{
	
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;

  uint8_t dadoRX[30];
	uint8_t str[30];
	
	uint8_t config;
	
}c;

typedef struct
{
	
	char nome[30];
	char cargo[30];
	char matricula[10];
	char hora_entrada[17];
	char data_entrada[17];
	char hora_saida[17];
	char data_saida[17];

} form;

form usuario;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	c.sTime.Hours = 18;
	c.sTime.Minutes = 30;
	c.sTime.Seconds = 0;
		
	c.sDate.Year = 70;
	c.sDate.Month = 01;
	c.sDate.Date = 01;
	
	inicializa_vetor_uint8(c.str,30);
	inicializa_vetor_uint8(c.dadoRX,30);

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
  MX_DMA2D_Init();
  MX_I2C3_Init();
  MX_LTDC_Init();
  MX_SPI5_Init();
  MX_FMC_Init();
  MX_RTC_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	
	inicializa_display();

	HAL_RTC_SetDate(&hrtc, &c.sDate, FORMAT_BIN);
	HAL_RTC_SetTime(&hrtc, &c.sTime, FORMAT_BIN);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		HAL_UART_Receive(&huart1, &c.config, 1, 1000);
		BSP_LCD_DisplayStringAtLine(9,&c.config);
		
		if(c.config == 'h')
		{
			HAL_UART_Receive(&huart1, c.dadoRX, 17, 5000);
			c.config = 0;
			BSP_LCD_DisplayStringAtLine(10,c.dadoRX);
			configura_hora();
		}
		else if(c.config == 'f')
		{
			HAL_UART_Receive(&huart1, (uint8_t*)&usuario, sizeof(usuario), 5000);
			c.config = 0;
			
			sprintf((char*)c.str,"%s",usuario.nome);
			BSP_LCD_DisplayStringAtLine(4,c.str);
			
			HAL_UART_Transmit(&huart1, (uint8_t*)&usuario, sizeof(usuario), 5000);
		}
		
		renderiza_RTC();
		
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC|RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 216;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void renderiza_RTC(void)
{
  HAL_RTC_GetTime(&hrtc, &c.sTime, FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &c.sDate, FORMAT_BIN);
  
  BSP_LCD_SetFont(&Font16);
  sprintf((char*)c.str,"%02d:%02d:%02d",c.sTime.Hours,c.sTime.Minutes,c.sTime.Seconds);
  BSP_LCD_DisplayStringAtLine(1,c.str);
	
	sprintf((char*)c.str,"%02d/%02d/%02d",c.sDate.Date,c.sDate.Month,c.sDate.Year);
  BSP_LCD_DisplayStringAtLine(2,c.str);
}
/*void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	BSP_LCD_DisplayStringAtLine(8,(uint8_t*)"MEUDEUS");
	
	if(c.estado == -1)
	{
		confere_estado();
	}
	else if(c.estado == 0)
	{
		configura_hora();
		c.estado = -1;
		HAL_UART_Receive_IT(&huart1, c.config , 2);
	}
	else if(c.estado == 1)
	{
		c.estado = -1;
		HAL_UART_Receive_IT(&huart1, c.config , 2);
	}

	configura_hora();
	HAL_UART_Receive_IT(&huart1, c.dadoRX , 17);
}*/
void inicializa_vetor_uint8(uint8_t vetor[], int tam)
{
  for(int i = 0; i < tam; i++)
  {
    vetor[i] = 0;
  }
}
void inicializa_display(void)
{
  BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(LCD_BACKGROUND_LAYER,LCD_FRAME_BUFFER);
	BSP_LCD_LayerDefaultInit(LCD_FOREGROUND_LAYER,LCD_FRAME_BUFFER);
	BSP_LCD_SelectLayer(LCD_FOREGROUND_LAYER);
	BSP_LCD_DisplayOn();
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_SetFont(&Font16);
	BSP_TS_Init(240, 320);
}

void configura_hora(void)
{	
	c.sTime.Hours = (c.dadoRX[0] - 0x30)*10 + (c.dadoRX[1] - 0x30);
	c.sTime.Minutes = (c.dadoRX[3] - 0x30)*10 + (c.dadoRX[4] - 0x30);
	c.sTime.Seconds = (c.dadoRX[6] - 0x30)*10 + (c.dadoRX[7] - 0x30);
	
	c.sDate.Date = (c.dadoRX[9] - 0x30)*10 + (c.dadoRX[10] - 0x30);
	c.sDate.Month = (c.dadoRX[12] - 0x30)*10 + (c.dadoRX[13] - 0x30);
	c.sDate.Year = (c.dadoRX[15] - 0x30)*10 + (c.dadoRX[16] - 0x30);
	
	HAL_RTC_SetDate(&hrtc, &c.sDate, FORMAT_BIN);
  HAL_RTC_SetTime(&hrtc, &c.sTime, FORMAT_BIN);
}
/*void confere_estado(void)
{
	if(c.config[0] == 'h')
	{
		HAL_UART_Receive_IT(&huart1, c.dadoRX , 17);
		c.estado = 0;
	}
	else if(c.config[0] == 'f')
	{
		//HAL_UART_Receive_IT(&huart1,(uint8_t *)&usuario, sizeof(estrutura));
		//c.estado = 1;
	}
	
	sprintf((char*)c.str,"aaaa %d",c.estado);
	BSP_LCD_DisplayStringAtLine(10,c.str);
	
}*/
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
