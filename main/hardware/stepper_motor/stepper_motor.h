#ifndef _STEPPER_MOTOR_H_
#define _STEPPER_MOTOR_H_

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//设置motor四相的引脚
#define MOTOR_A 11
#define MOTOR_B 12
#define MOTOR_C 13
#define MOTOR_D 14

/*电机初始化*/
void motor_init(void);

/*电机正转*/
void motor_forward(void);

/*电机反转*/
void motor_backward(void);

/*电机停止*/
void motor_stop(void);

#endif