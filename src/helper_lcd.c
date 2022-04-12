#include "helper_lcd.h"

extern int LCDpins[ 14 ];

static inline float _contrast_duty(float pot_lcd) {
   return ( pot_lcd / 2 ) + 50;
}

void lcd_init( float pot_lcd ) {

   for ( int gpio = 0; gpio < 11; gpio++ ) {
      gpio_init( LCDpins[ gpio ] );
      gpio_set_dir( LCDpins[ gpio ], true );
      gpio_put( LCDpins[ gpio ], false );
   }

   float contrast_duty = _contrast_duty(pot_lcd);
   pwm_init_helper( GPIO_CONTRAST_LCD, CONTRAST_FREQ, contrast_duty );

   LCDclear();
   LCDinit();
}

void lcd_update( float pot_temp, float temp, float pot_lcd ) {
   char str[ 33 ];
   LCDgoto( "00" );
   LCDsendRawInstruction( 0, 0, "00001100" );
   sprintf( str, "Cur: %2.1f C", temp );
   LCDwriteRawMessage( str );
   LCDgoto( "40" );
   sprintf( str, "Obj: %2.1f C", pot_temp );
   LCDwriteRawMessage( str );

   float contrast_duty = _contrast_duty(pot_lcd);
   pwm_set_freq_duty( GPIO_CONTRAST_LCD, CONTRAST_FREQ, contrast_duty );
}
