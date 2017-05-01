#include "input/input.h"
#include "lcd/lcd.h"
#include <avr/io.h>

void init_jui() {
    /* 8MHz clock, no prescaling (DS, p. 48) */
  CLKPR = (1 << CLKPCE);
  CLKPR = 0;

  init_input();
  init_lcd();
}