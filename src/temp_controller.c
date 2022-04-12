#include "pico/stdlib.h"
#include <stdio.h>

#include "helper_adc.h"
#include "helper_lcd.h"
#include "helper_pwm.h"

#include "temp_controller.h"

// D0,D1,D2,D3,D4,D5,D6,D7,EN,RS,RW,Col,Row
int LCDpins[ 14 ] = { 6, 7, 8, 9, 13, 10, 11, 12, 2, 4, 5, 16, 2 };

void setup() {
   stdio_init_all();

   adc_init_helper();

   float pot_temp = adc_read_pot_percent( GPIO_POT_TEMP );
   float pot_lcd = adc_read_pot_percent( GPIO_POT_LCD );

   pwm_init_helper( GPIO_FAN_PWM, 25000, 0 );

   lcd_init( pot_lcd );
}

int main() {

   setup();

   while ( 1 ) {

      float pot_temp = adc_read_pot_percent( GPIO_POT_TEMP );
      float pot_lcd = adc_read_pot_percent( GPIO_POT_LCD );
      float cur_temp = adc_read_temp();
      int fan_rpm = pwm_measure_rpm( GPIO_FAN_TACH );

      lcd_update( pot_temp, cur_temp, pot_lcd );
      pwm_set_freq_duty( GPIO_FAN_PWM, 25000, pot_temp );

      printf( "Fan RPM: %d\n", fan_rpm );
      sleep_ms( 500 );
   }
}
