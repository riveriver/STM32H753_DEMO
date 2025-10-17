#include "main.h"

#include "drv_can.h"

FDCAN_frame_TypeDef can_tx_frame;
FDCAN_RxFrame_TypeDef can_rx_frame;

void config_can_filter(CANHandle *p_can)
{
  FDCAN_FilterTypeDef FDCAN1_FilterConfig;
  FDCAN1_FilterConfig.IdType = FDCAN_STANDARD_ID;
  FDCAN1_FilterConfig.FilterIndex = 0;
  FDCAN1_FilterConfig.FilterType = FDCAN_FILTER_MASK;
  FDCAN1_FilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  FDCAN1_FilterConfig.FilterID1 = 0x00000000;
  FDCAN1_FilterConfig.FilterID2 = 0x00000000;
  if(HAL_FDCAN_ConfigFilter(p_can, &FDCAN1_FilterConfig) != HAL_OK){
      Error_Handler();
  }
  if (HAL_FDCAN_ConfigGlobalFilter(p_can, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK){
      Error_Handler();
  }
  if (HAL_FDCAN_ActivateNotification(p_can, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK){
      Error_Handler();
  }
  if (HAL_FDCAN_Start(p_can) != HAL_OK){
      Error_Handler();
  }
}

void test_can_tx(FDCAN_HandleTypeDef *hfdcan, FDCAN_frame_TypeDef *frame)
{
 frame->hcan = hfdcan;
 frame->Header.IdType = FDCAN_STANDARD_ID;
 frame->Header.TxFrameType = FDCAN_DATA_FRAME;
 frame->Header.DataLength = 8;
 frame->Header.BitRateSwitch = FDCAN_BRS_OFF;
 frame->Header.FDFormat =  FDCAN_CLASSIC_CAN;
 frame->Header.TxEventFifoControl =  FDCAN_NO_TX_EVENTS;
 frame->Header.MessageMarker = 0;
 frame->Header.Identifier = 0x12;
 frame->Data[0] = 0xF1;
 frame->Data[1] = 0xF2;
 frame->Data[2] = 0xF3;
 frame->Data[3] = 0xF4;
 frame->Data[4] = 0xF5;
 frame->Data[5] = 0xF6;
 frame->Data[6] = 0xF7;
 frame->Data[7] = 0xF8;
 HAL_FDCAN_AddMessageToTxFifoQ(frame->hcan,&frame->Header,frame->Data);
}
