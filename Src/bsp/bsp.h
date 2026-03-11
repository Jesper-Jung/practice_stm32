#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_

#include "def.h"
#include "bsp_def.h"
#include "stm32h5xx_hal.h"
#include "stm32h5xx_nucleo.h"

void bspInit(void);

void gpio_init(void);
void delay(uint32_t ms);
uint32_t millis(void);
void SystemClock_Config(void);
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/

#endif
