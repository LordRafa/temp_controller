#include "helper_adc.h"

// 12 bits. Vref=3.3V
static const float adc_factor = VREF / ( 1 << 12 );

void adc_init_helper() {

   adc_init();
   adc_gpio_init( GPIO_POT_TEMP );
   adc_gpio_init( GPIO_POT_LCD );
   adc_set_temp_sensor_enabled( true );
}

float adc_read_temp() {

   float temp_conv;

   adc_select_input( ADC_TEMP );
   temp_conv = adc_read() * adc_factor;

   return 27 - ( temp_conv - 0.706 ) / 0.001721;
}

float adc_read_pot_percent( uint pot_gpio ) {

   const uint adc_ch = pot_gpio - 26;

   adc_select_input( adc_ch );
   float pot_conv = adc_read() * adc_factor;

   return pot_conv * 100 / VREF;
}
