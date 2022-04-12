
#include "helper_pwm.h"

#include <stdio.h>

static uint32_t _pwm_set_freq_duty( uint slice_num, uint chan, uint32_t f, int d );

void pwm_init_helper( uint gpio, uint32_t freq, uint duty ) {

   gpio_init( gpio );
   gpio_set_function( gpio, GPIO_FUNC_PWM );
   uint slice_num = pwm_gpio_to_slice_num( gpio );
   uint channel_num = pwm_gpio_to_channel( gpio );
   _pwm_set_freq_duty( slice_num, channel_num, freq, duty );
   pwm_set_enabled( slice_num, true );
}

void pwm_set_freq_duty( uint gpio, uint32_t freq, uint duty ) {
   uint slice_num = pwm_gpio_to_slice_num( gpio );
   uint channel_num = pwm_gpio_to_channel( gpio );
   _pwm_set_freq_duty( slice_num, channel_num, freq, duty );
}

int pwm_measure_rpm( uint gpio ) {

   uint slice_num = pwm_gpio_to_slice_num( gpio );

   pwm_config cfg = pwm_get_default_config();
   pwm_config_set_clkdiv_mode( &cfg, PWM_DIV_B_FALLING );
   pwm_config_set_clkdiv_int( &cfg, 3 );
   pwm_init( slice_num, &cfg, false );
   gpio_init( gpio );
   gpio_set_function( gpio, GPIO_FUNC_PWM );

   printf( "Counter0: %u\n", pwm_get_counter( slice_num ) );

   pwm_set_enabled( slice_num, true );
   sleep_ms( 1000 );
   pwm_set_enabled( slice_num, false );

   printf( "Counter1: %u\n", pwm_get_counter( slice_num ) );

   return pwm_get_counter( slice_num ) * 30;
}

// ----- Private -----

static uint32_t _pwm_set_freq_duty( uint slice_num, uint chan, uint32_t f, int d ) {

   const uint32_t clock16 = clock_get_hz( clk_sys ) << 4;

   uint32_t divider16 = clock16 / ( f * 65536 );
   // If decimal inc 1
   if ( clock16 % ( f * 4096 ) != 0 )
      divider16++;

   // Divider must be >= 1 (16 in 8:4 format)
   if ( divider16 >> 4 == 0 )
      divider16 = 16;

   uint32_t wrap = clock16 / ( divider16 * f ) - 1;

   pwm_set_clkdiv_int_frac( slice_num, divider16 >> 4, divider16 & 0xF );
   pwm_set_wrap( slice_num, wrap );
   pwm_set_chan_level( slice_num, chan, wrap * d / 100 );

   return wrap;
}
