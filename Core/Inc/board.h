#include "main.h"
#include "usart.h"
#include "gpio.h"

#define BOARD_NAME "STM32H753-DEV"
#define DEBUG_UART huart3

void report_board_version(void);
