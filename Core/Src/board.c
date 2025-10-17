#include "board.h"

#include <stdio.h>

void report_board_version(void)
{
    char send_str[64];
    int len = snprintf(send_str, sizeof(send_str), "Board: %s\r\n", BOARD_NAME);
    if(HAL_UART_Transmit(&DEBUG_UART, (uint8_t *)send_str, len, HAL_MAX_DELAY) != HAL_OK)
    {
        while (1);  
    }
}