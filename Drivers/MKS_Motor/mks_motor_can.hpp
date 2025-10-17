#pragma once
#include <stdint.h>
#include <drv_can.h>

class MKS_MotorByCan {
public:
    MKS_MotorByCan(const uint16_t can_id,CANHandle *can_handle, const int default_accel, const int max_speed);
    ~MKS_MotorByCan();
    void set_speed(const int target_rpm, int target_accel = -1);
    void set_accel(const int target_accel);
    void go_home();
    void set_can_handle(CANHandle *can_ptr){can_handle_ = can_ptr;};
    CANHandle* get_can_handle(){return can_handle_;};
private:
    uint16_t can_id_;
    CANHandle *can_handle_;
    int default_accel_;
    int max_speed_;
};

