#include "bsp.h"

static void gpio_clk_enable(void);
static void gpio_conf_write_pin(void);
static void gpio_conf_pins(GPIO_InitTypeDef *GPIO_InitStruct);

void bspInit(void)
{
  HAL_Init();
  SystemClock_Config();

  gpio_init();
}

void gpio_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  gpio_clk_enable();

  /*Configure GPIO pin Output Level */
  gpio_conf_write_pin();
  
  gpio_conf_pins(&GPIO_InitStruct);
}

void gpio_clk_enable(void)
{
  #if defined(NUCLEO_H563ZI) || defined(NUCLEO_H503RB)
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
  #endif

  #if defined(NUCLEO_H563ZI)
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
  #endif    
}

void gpio_conf_write_pin(void)
{
  #if defined(NUCLEO_H563ZI)
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
  #endif
}

void gpio_conf_pins(GPIO_InitTypeDef *GPIO_InitStruct)
{
  #if defined(NUCLEO_H563ZI)
  /*Configure GPIO pins : RMII_MDC_Pin RMII_RXD0_Pin RMII_RXD1_Pin */
  GPIO_InitStruct->Pin = RMII_MDC_Pin|RMII_RXD0_Pin|RMII_RXD1_Pin;
  GPIO_InitStruct->Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct->Pull = GPIO_NOPULL;
  GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct->Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOC, GPIO_InitStruct);

  /*Configure GPIO pins : RMII_REF_CLK_Pin RMII_MDIO_Pin RMII_CRS_DV_Pin */
  GPIO_InitStruct->Pin = RMII_REF_CLK_Pin|RMII_MDIO_Pin|RMII_CRS_DV_Pin;
  GPIO_InitStruct->Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct->Pull = GPIO_NOPULL;
  GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct->Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOA, GPIO_InitStruct);

  /*Configure GPIO pin : VBUS_SENSE_Pin */
  GPIO_InitStruct->Pin = VBUS_SENSE_Pin;
  GPIO_InitStruct->Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct->Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VBUS_SENSE_GPIO_Port, GPIO_InitStruct);

  /*Configure GPIO pin : PB12 */
  GPIO_InitStruct->Pin = GPIO_PIN_12;
  GPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct->Pull = GPIO_NOPULL;
  GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, GPIO_InitStruct);

  /*Configure GPIO pins : UCPD_CC1_Pin UCPD_CC2_Pin */
  GPIO_InitStruct->Pin = UCPD_CC1_Pin|UCPD_CC2_Pin;
  GPIO_InitStruct->Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct->Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, GPIO_InitStruct);

  /*Configure GPIO pin : RMII_TXD1_Pin */
  GPIO_InitStruct->Pin = RMII_TXD1_Pin;
  GPIO_InitStruct->Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct->Pull = GPIO_NOPULL;
  GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct->Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(RMII_TXD1_GPIO_Port, GPIO_InitStruct);

  /*Configure GPIO pin : UCPD_FLT_Pin */
  GPIO_InitStruct->Pin = UCPD_FLT_Pin;
  GPIO_InitStruct->Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct->Pull = GPIO_NOPULL;
  HAL_GPIO_Init(UCPD_FLT_GPIO_Port, GPIO_InitStruct);

  /*Configure GPIO pins : USB_FS_N_Pin USB_FS_P_Pin */
  GPIO_InitStruct->Pin = USB_FS_N_Pin|USB_FS_P_Pin;
  GPIO_InitStruct->Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct->Pull = GPIO_NOPULL;
  GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct->Alternate = GPIO_AF10_USB;
  HAL_GPIO_Init(GPIOA, GPIO_InitStruct);

  /*Configure GPIO pins : RMII_TXT_EN_Pin RMI_TXD0_Pin */
  GPIO_InitStruct->Pin = RMII_TXT_EN_Pin|RMI_TXD0_Pin;
  GPIO_InitStruct->Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct->Pull = GPIO_NOPULL;
  GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct->Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOG, GPIO_InitStruct);

  /*Configure GPIO pins : ARD_D1_TX_Pin ARD_D0_RX_Pin */
  GPIO_InitStruct->Pin = ARD_D1_TX_Pin|ARD_D0_RX_Pin;
  GPIO_InitStruct->Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct->Pull = GPIO_NOPULL;
  GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct->Alternate = GPIO_AF8_LPUART1;
  HAL_GPIO_Init(GPIOB, GPIO_InitStruct);

  #elif defined(NUCLEO_H503RB)
  /*Configure GPIO pins : ARD_D1_TX_Pin ARD_D0_RX_Pin */
  GPIO_InitStruct->Pin = ARD_D1_TX_Pin|ARD_D0_RX_Pin;
  GPIO_InitStruct->Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct->Pull = GPIO_NOPULL;
  GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct->Alternate = GPIO_AF4_USART1;
  HAL_GPIO_Init(GPIOB, GPIO_InitStruct);
  #endif
}

void delay(uint32_t ms)
{
  HAL_Delay(ms);
}

uint32_t millis(void)
{
  return HAL_GetTick();
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 12;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the programming delay
  */
  __HAL_FLASH_SET_PROGRAM_DELAY(FLASH_PROGRAMMING_DELAY_1);
}

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
