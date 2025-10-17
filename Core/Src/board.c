#include "board.h"

#include <stdio.h>

void report_board_version(void)
{
    char send_str[64];
    int len = snprintf(send_str, sizeof(send_str), "Board: %s\r\n", HAL_GetDEVID());
    if(HAL_UART_Transmit(&DEBUG_UART, (uint8_t *)send_str, len, HAL_MAX_DELAY) != HAL_OK)
    {
        while (1);  
    }
}

void flash_heartbeat(void)
{
	HAL_GPIO_TogglePin(LED_GREEN_PORT, LED_GREEN_PIN);
	HAL_GPIO_TogglePin(LED_RED_PORT, LED_RED_PIN);
    HAL_GPIO_TogglePin(LED_YELLOW_PORT, LED_YELLOW_PIN);
}


uint32_t get_time_ms(void)
{
#if defined(FREERTOS) || defined(USE_FREERTOS) || defined(configUSE_PREEMPTION)
    // 判断是否在中断中
    if (__get_IPSR() != 0) {
        // 在中断
        return (uint32_t)(xTaskGetTickCountFromISR() * portTICK_PERIOD_MS);
    } else {
        // 任务上下文
        return (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);
    }
#else
    // 非FreeRTOS环境,HAL_GetTick()本身就是线程安全的，可以在中断服务函数（ISR）中直接调用
    return HAL_GetTick();
#endif
}
