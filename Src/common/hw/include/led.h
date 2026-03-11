#ifndef SRC_COMMON_HW_INCLUDE_LED_H_
#define SRC_COMMON_HW_INCLUDE_LED_H_

#include "hw_def.h"

#ifdef _USE_HW_LED

#define LED_MAX_CH    HW_LED_MAX_CH
typedef struct
{
  GPIO_TypeDef *port;
  uint16_t      pin;
  GPIO_PinState on_state;
  GPIO_PinState off_state;
} led_info_t;


bool ledInit(void);
void ledOn(uint8_t ch);
void ledOff(uint8_t ch);
void ledToggle(uint8_t ch);

#endif

#endif
