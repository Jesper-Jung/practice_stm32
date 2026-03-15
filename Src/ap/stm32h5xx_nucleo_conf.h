#ifndef BSP_CONF_H_
#define BSP_CONF_H_

#include "stm32h5xx_hal.h"

#if defined(NUCLEO_H563ZI)
#define USE_NUCLEO_144
#define STM32H563xx
#define STM32H5

#elif defined(NUCLEO_H503RB)
#define USE_NUCLEO_64
#define STM32H503xx
#define STM32H5

#endif

/* COM define */
#define USE_COM_LOG                         1U
#define USE_BSP_COM_FEATURE                 1U

/* IRQ priorities */
#define BSP_BUTTON_USER_IT_PRIORITY         15U

#endif
