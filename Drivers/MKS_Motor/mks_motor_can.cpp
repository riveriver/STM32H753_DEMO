
#include <MKS_MotorByCan_can.hpp>

MKS_MotorByCan::MKS_MotorByCan(const uint16_t can_id,CANHandle *can_handle, const int default_accel, const int max_speed)
	:can_id_(can_id),can_handle_(can_handle),default_accel_(default_accel),max_speed_(max_speed){
}

MKS_MotorByCan::~MKS_MotorByCan() {
}

// HACK
CANSendHeader motor_header;
uint8_t motor_data[5];
void MKS_MotorByCan::set_speed(const int target_rpm, int target_accel){
    if (target_rpm < -abs(max_speed_) || target_rpm > abs(max_speed_)) {
        usb_printf("[CRANE SERVER] Error: Speed out of range (%d to %d RPM) for id=%d.\r\n", -abs(max_speed_), abs(max_speed_), can_id_);
        return;
    }

    if (target_accel == -1){
        target_accel = default_accel_;
    }else if (target_accel < 0 || target_accel > 255){
        usb_printf("[CRANE SERVER] Error: Accel out of range (0 to 255) for id=%d.\r\n", can_id_);
        return;
    }

    // Prepare the CAN frame
    motor_header.IdType = FDCAN_STANDARD_ID;
    motor_header.TxFrameType = FDCAN_DATA_FRAME;
    motor_header.BitRateSwitch = FDCAN_BRS_OFF;
    motor_header.FDFormat =  FDCAN_CLASSIC_CAN;
    motor_header.TxEventFifoControl =  FDCAN_NO_TX_EVENTS;
    motor_header.MessageMarker = 0;
    motor_header.Identifier = can_id_; // Set the CAN ID
    motor_header.DataLength = 5; // Set Data length
    
    // Byte 1: Function Code (0xF6)
    motor_data[0] = 0xF6;
    // Byte 2: Direction (bit 7) + Speed lower 4 bits (bits 3-0)
    uint8_t direction = (target_rpm < 0) ? 0x80 : 0x00;  // 0x80 for CCW, 0x00 for CW
    uint16_t abs_speed = static_cast<uint16_t>(std::abs(target_rpm));  // Absolute value
    motor_data[1] = direction | ((abs_speed >> 8) & 0x0F);  // High byte (dir + 4 speed bits)
    // Byte 3: Lower 8 bits of speed
    motor_data[2] = abs_speed & 0xFF;
    // Byte 4: Acceleration
    motor_data[3] = target_accel;
    // Byte 5: Checksum
    motor_data[4] = motor_data[0] + motor_data[1] + motor_data[2] + motor_data[3] + can_id_;

    // Send the CAN frame
    if(HAL_FDCAN_AddMessageToTxFifoQ(can_handle_,&motor_header,motor_data)){
        usb_printf("[CRANE SERVER] Error sending CAN request for id=%d.\r\n", can_id_);
    }
}

void MKS_MotorByCan::set_accel(const int target_accel){
    default_accel_ = target_accel;
}

void MKS_MotorByCan::go_home(){
    
    // Prepare the CAN frame
    CANSendHeader header;
    header.IdType = FDCAN_STANDARD_ID;
    header.TxFrameType = FDCAN_DATA_FRAME;
    header.BitRateSwitch = FDCAN_BRS_OFF;
    header.FDFormat =  FDCAN_CLASSIC_CAN;
    header.TxEventFifoControl =  FDCAN_NO_TX_EVENTS;
    header.MessageMarker = 0;
    header.Identifier = can_id_; // Set the CAN ID
    header.DataLength = 2; // Set Data length

    uint8_t data[header.DataLength];
    // Byte 1: Function Code (0x91)
    data[0] = 0x91;
    // Byte 2: Checksum
    data[1] = data[0] + can_id_;

    // Send the CAN frame
    if(HAL_FDCAN_AddMessageToTxFifoQ(can_handle_,&header,data)){
        usb_printf("[CRANE SERVER] Error sending CAN request for id=%d.\r\n", can_id_);
    }
}
