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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define TLV320_I2C_DEVICE_ADDRESS (0x18<<1)
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
I2C_HandleTypeDef hi2c2;

I2S_HandleTypeDef hi2s2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C2_Init(void);
static void MX_I2S2_Init(void);
/* USER CODE BEGIN PFP */

void tlv320_Init(I2C_HandleTypeDef *hi2c2);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int16_t buf[256];

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
  MX_I2C2_Init();
  MX_I2S2_Init();
  /* USER CODE BEGIN 2 */
  tlv320_Init(&hi2c2);
  HAL_GPIO_TogglePin(GPIOA, TEST_LED_Pin);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  HAL_I2SEx_TransmitReceive(&hi2s2, buf, buf, 256,100);
    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL14;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C2;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x2000090E;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief I2S2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S2_Init(void)
{

  /* USER CODE BEGIN I2S2_Init 0 */

  /* USER CODE END I2S2_Init 0 */

  /* USER CODE BEGIN I2S2_Init 1 */

  /* USER CODE END I2S2_Init 1 */
  hi2s2.Instance = SPI2;
  hi2s2.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s2.Init.Standard = I2S_STANDARD_MSB;
  hi2s2.Init.DataFormat = I2S_DATAFORMAT_16B_EXTENDED;
  hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
  hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_48K;
  hi2s2.Init.CPOL = I2S_CPOL_HIGH;
  hi2s2.Init.ClockSource = I2S_CLOCK_SYSCLK;
  hi2s2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_ENABLE;
  if (HAL_I2S_Init(&hi2s2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S2_Init 2 */
  /* USER CODE END I2S2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TEST_LED_GPIO_Port, TEST_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CODEC_RESET_GPIO_Port, CODEC_RESET_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : TEST_LED_Pin */
  GPIO_InitStruct.Pin = TEST_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TEST_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CODEC_RESET_Pin */
  GPIO_InitStruct.Pin = CODEC_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CODEC_RESET_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void tlv320_Init(I2C_HandleTypeDef *hi2c2){

	uint16_t I2C_Reg_Address;
	uint8_t I2C_Data;


	/*Performing hardware Reset*/
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(100);


	/*Page select 0 CHECKED*/
	I2C_Reg_Address = 0x00;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Performing software Reset CHECKED*/
	I2C_Reg_Address = 0x01;
	I2C_Data = 0x01;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	HAL_Delay(100);
	/*I2S 24BIT i2s configured with 16bit extended*/
	I2C_Reg_Address = 0x1B;
	I2C_Data = 0x20;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*External master clock is selected and internal clock generator is off by default*/
	/*For MADC, NADC , AOSR, MDAC, NDAC, DOSR check manual at page 79 */
	/*Configuring NADC and MADC registers - AOSR registers are set to 128 by default CHECKED*/
	//NADC
	I2C_Reg_Address = 0x12;
	I2C_Data = 0x81;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	//MADC
	I2C_Reg_Address = 0x13;
	I2C_Data = 0x82;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	//AOSR
	I2C_Reg_Address = 0x14;
	I2C_Data = 0x80;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	//Sampling Freq = 48Khz, extMCLK = 48Mhz
	/*Configuring NDAC and MDAC registers - DOSR registers are set to 128 by default*/
	//NDAC
	I2C_Reg_Address = 0x0B;
	I2C_Data = 0x81;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	//MDAC
	I2C_Reg_Address = 0x0C;
	I2C_Data = 0x82;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	//DOSR 128
	I2C_Reg_Address = 0x0D;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	I2C_Reg_Address = 0x0E;
	I2C_Data = 0x80;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/* ADC PRB_R1, DAC PRB_P1 set by default CHECKED*/

	/*Page select 1 CHECKED*/
	I2C_Reg_Address = 0x00;
	I2C_Data = 0x01;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Power up internal aVDD LDO CHECKED*/
	I2C_Reg_Address = 0x01;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Power enable master analog power control CHECKED*/
	I2C_Reg_Address = 0x02;
	I2C_Data = 0x01;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Setting up common mode to 0.9V CHECKED*/
	I2C_Reg_Address = 0x0a;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/* Selecting ADC PTM_R4 CHECKED*/
	I2C_Reg_Address = 0x3d;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Setting MicPGA startup delay to 3.1ms CHECKED*/
	I2C_Reg_Address = 0x47;
	I2C_Data = 0x32;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Power REF charging time to 40ms CHECKED*/
	I2C_Reg_Address = 0x7b;
	I2C_Data = 0x01;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Routing IN1L to left PGA_Positive with 20k input impedance CHECKED*/
	I2C_Reg_Address = 0x34;
	I2C_Data = 0x80;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Setting up IN1L common mode to the negative terminal CHECKED*/
	I2C_Reg_Address = 0x36;
	I2C_Data = 0x80;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Routing IN1R to right PGA_Positive with 20k input impedance CHECKED*/
	I2C_Reg_Address = 0x37;
	I2C_Data = 0x80;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Setting up IN1R common mode to the negative terminal CHECKED*/
	I2C_Reg_Address = 0x39;
	I2C_Data = 0x80;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Unmute Left MICPGA CHECKED*/
	I2C_Reg_Address = 0x3b;
	I2C_Data = 0x0c;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Unmute Right MICPGA CHECKED*/
	I2C_Reg_Address = 0x3c;
	I2C_Data = 0x0c;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);


	/*Page select 0 CHECKED*/
	I2C_Reg_Address = 0x00;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Powering up left and right ADC CHECKED*/
	I2C_Reg_Address = 0x51;
	I2C_Data = 0xc0;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Unmute Left and Right ADC Digital Volume Control. CHECKED*/
	I2C_Reg_Address = 0x52;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);


	/*Page select 1*/
	I2C_Data = 0x01;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, 0x00, 1, &I2C_Data, 1, 100);

	/*LOL Routing*/
	I2C_Reg_Address = 0x0E;
	I2C_Data = 0x08;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*LOR Routing*/
	I2C_Reg_Address = 0x0F;
	I2C_Data = 0x08;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*LOL Driver Gain unmuted*/
	I2C_Reg_Address = 0x12;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*LOR Driver Gain unmuted*/
	I2C_Reg_Address = 0x13;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);


	/*Page select 0 CHECKED*/
	I2C_Reg_Address = 0x00;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*DAC Channel Setup left - right*/
	I2C_Reg_Address = 0x3F;
	I2C_Data = 0xD4;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);


	/*DAC Channel Setup left - right unmuted*/
	I2C_Reg_Address = 0x40;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);


	/*Page select 1*/
	I2C_Data = 0x01;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, 0x00, 1, &I2C_Data, 1, 100);


	/*Powering up left and right DAC*/
	I2C_Data = 0x08;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, 0x0A, 1, &I2C_Data, 1, 100);


	/*Powering up left and right LOL and LOR Drivers*/
	I2C_Reg_Address = 0x09;
	I2C_Data = 0x0c;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);
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
