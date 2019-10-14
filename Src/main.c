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
#include "stdio.h"
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

typedef struct
{
	char cadastrado;
	char config;
	char nome[20];
	char cargo[20];
	char matricula[10];
	char hora_entrada[9];
	char data_entrada[9];
	char hora_saida[9];
	char data_saida[9];

} estrutura;

estrutura usuario;

struct Control{
	
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;

	uint8_t str[30];
	
  int escreve;
  int entrandoSaindo;

}c;

void renderiza_RTC(void);
void inicializa_vetor_uint8(uint8_t vetor[], int tam);
void inicializa_display(void);
void configura_hora(void);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);


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

	usuario.config = 'x';
	usuario.cadastrado = 'x';

  c.escreve = 0;
  c.entrandoSaindo = -1;
	
	inicializa_vetor_uint8(c.str,30);

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

  HAL_UART_Receive_IT(&huart1,(uint8_t *)&usuario,sizeof(estrutura));


  int testaCartao = 1;

  if(testaCartao == 1)
  {
    char aa = 'T';
    char x;
    
    HAL_I2C_Mem_Write(&hi2c3,0xa0,0,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&aa,1,1000);
    HAL_Delay(10);
    
    HAL_I2C_Mem_Read(&hi2c3,0xa1,0,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&x,1,1000);
    
    sprintf((char*)c.str,"%c",x);
    BSP_LCD_DisplayStringAtLine(6,(uint8_t*)&x);
  }
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    renderiza_RTC();

    if(c.escreve == 1)
    {
      uint8_t dado[sizeof(usuario)];
			memcpy(dado,(uint8_t*)&usuario,sizeof(estrutura));
			int endereco = 0;

			for(int i = 0; i<sizeof(dado); i++)
			{
				endereco = i;
				HAL_I2C_Mem_Write(&hi2c3,0xa0,endereco,I2C_MEMADD_SIZE_8BIT,&dado[i],1,500);
				HAL_Delay(10);
				
			}

      if(c.entrandoSaindo == 1)
      {
        BSP_LCD_DisplayStringAtLine(10,(uint8_t*)"Entrada Liberada");
        c.entrandoSaindo = -1;
      }
      else if(c.entrandoSaindo == 2)
      {
        // escreve saida liberada
        BSP_LCD_DisplayStringAtLine(10,(uint8_t*)"Saida Liberada");
        c.entrandoSaindo = -1;
      }

			c.escreve = 0;
    }
		
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
	c.sTime.Hours = (usuario.hora_entrada[0] - 0x30)*10 + (usuario.hora_entrada[1] - 0x30);
	c.sTime.Minutes = (usuario.hora_entrada[3] - 0x30)*10 + (usuario.hora_entrada[4] - 0x30);
	c.sTime.Seconds = (usuario.hora_entrada[6] - 0x30)*10 + (usuario.hora_entrada[7] - 0x30);
	
	c.sDate.Date = (usuario.data_entrada[0] - 0x30)*10 + (usuario.data_entrada[1] - 0x30);
	c.sDate.Month = (usuario.data_entrada[3] - 0x30)*10 + (usuario.data_entrada[4] - 0x30);
	c.sDate.Year = (usuario.data_entrada[6] - 0x30)*10 + (usuario.data_entrada[7] - 0x30);
	
	
	HAL_RTC_SetDate(&hrtc, &c.sDate, FORMAT_BIN);
  HAL_RTC_SetTime(&hrtc, &c.sTime, FORMAT_BIN);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(usuario.config == 'h')
  {
    usuario.config = 'x';
    configura_hora();
  }
  else if(usuario.config == 'l')
  {
    usuario.config = 'x';
    HAL_I2C_Mem_Read(&hi2c3,0xa1,0,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&usuario,sizeof(usuario),1000);
    HAL_UART_Transmit_IT(&huart1,(uint8_t *)&usuario,sizeof(estrutura));
  }
  else if(usuario.config == 'c' || usuario.config == 'a' || usuario.config == 'o' || usuario.config == 'u')
  {
    if(usuario.config == 'o')
    {
      estrutura temp;
      HAL_I2C_Mem_Read(&hi2c3,0xa1,0,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&temp,sizeof(temp),1000);
      strcpy(usuario.nome,temp.nome);
      strcpy(usuario.cargo,temp.cargo);
      strcpy(usuario.matricula,temp.matricula);
      strcpy(usuario.cadastrado,temp.cadastrado);
      strcpy(usuario.hora_saida,temp.hora_saida);
      strcpy(usuario.data_saida,temp.data_saida);
      c.entrandoSaindo = 1;
    }
    else if(usuario.config == 'u')
    {
      estrutura temp;
      HAL_I2C_Mem_Read(&hi2c3,0xa1,0,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&temp,sizeof(temp),1000);
      strcpy(usuario.nome,temp.nome);
      strcpy(usuario.cargo,temp.cargo);
      strcpy(usuario.matricula,temp.matricula);
      strcpy(usuario.cadastrado,temp.cadastrado);
      strcpy(usuario.hora_entrada,temp.hora_entrada);
      strcpy(usuario.data_entrada,temp.data_entrada);
      c.entrandoSaindo = 2;
    }

    usuario.config = 'x';
    c.escreve = 1;
  }
  HAL_UART_Receive_IT(&huart1,(uint8_t *)&usuario,sizeof(estrutura));
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
