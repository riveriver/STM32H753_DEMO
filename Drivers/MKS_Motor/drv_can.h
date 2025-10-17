#ifndef DRV_CAN_H_
#define DRV_CAN_H_

#include "stm32h7xx_hal.h"



typedef FDCAN_HandleTypeDef CANHandle;
typedef FDCAN_TxHeaderTypeDef CANSendHeader;
typedef FDCAN_RxHeaderTypeDef CANRecvHeader;

typedef struct {
    FDCAN_HandleTypeDef *hcan;
    FDCAN_TxHeaderTypeDef Header;
    uint8_t             Data[8];
}FDCAN_frame_TypeDef;

typedef struct {
    FDCAN_HandleTypeDef *hcan;
    FDCAN_RxHeaderTypeDef Header;
    uint8_t Data[8];
} FDCAN_RxFrame_TypeDef;

void config_can_filter(CANHandle *p_can);
void test_can_tx(CANHandle *hfdcan, FDCAN_frame_TypeDef *frame);

#endif /* DRV_CAN_H_ */

