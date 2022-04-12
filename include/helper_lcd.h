#ifndef HELPER_LCD_H
#define HELPER_LCD_H

#include "pico/stdlib.h"
#include <stdio.h>

#include "LCDops.h"
#include "generalOps.h"

#include "helper_pwm.h"
#include "temp_controller.h"

#define CONTRAST_FREQ 1000

void lcd_init( float pot_lcd );
void lcd_update( float pot_temp, float temp, float pot_lcd );

#endif
