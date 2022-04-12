#ifndef HELPER_ADC_H
#define HELPER_ADC_H

#include "hardware/adc.h"
#include "pico/stdlib.h"

#include "temp_controller.h"

#define ADC_TEMP 4

void adc_init_helper();
float adc_read_temp();
float adc_read_pot_percent( uint pot_gpio );

#endif
