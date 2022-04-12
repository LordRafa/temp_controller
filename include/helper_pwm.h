#ifndef HELPER_PWM_H
#define HELPER_PWM_H

#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

#include "temp_controller.h"

void pwm_init_helper( uint gpio, uint32_t freq, uint duty );
void pwm_set_freq_duty( uint gpio, uint32_t freq, uint duty );
int pwm_measure_rpm( uint gpio );

#endif
