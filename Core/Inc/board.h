#include "main.h"
#include "usart.h"
#include "gpio.h"

#define DEBUG_UART huart3
#define LED_RED_PORT GPIOB
#define LED_RED_PIN GPIO_PIN_14
#define LED_GREEN_PORT GPIOB
#define LED_GREEN_PIN GPIO_PIN_0
#define LED_YELLOW_PORT GPIOE
#define LED_YELLOW_PIN GPIO_PIN_1

void report_board_version(void);
void flash_heartbeat(void);
