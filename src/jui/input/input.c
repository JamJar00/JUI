#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "input.h"

volatile int8_t delta;

void init_input() {
  PORTE |= SWC | ROTA | ROTB;
  PORTC |= SWW | SWS | SWE | SWN;

  // last_rot = PINE & ROT;

  /* Setup interrupts on rotary encoder pins */

  EICRB |= _BV(ISC40) |     /* Set interrupt on logical change of pin state */
           _BV(ISC50);

  EIMSK |= _BV(INT4) | _BV(INT5);  /* Enable interrupts */
}

int8_t get_scroll_delta() {
  int8_t val;

  cli();
  val = delta;
  delta &= 1;
  sei();

  return -(val >> 1);
}

ISR(INT4_vect) {
  static int8_t last;
  int8_t new, diff;
  uint8_t wheel;

  wheel = PINE;
  new = 0;

  /* Convert gray to binary */

  if( wheel & ROTA ) new = 3;
  if( wheel & ROTB ) new ^= 1;

  /* Calculate delta */

  diff = last - new;

  if( diff & 1 ){
    last = new;
    delta += (diff & 2) - 1;
  }
}

ISR(INT5_vect, ISR_ALIASOF(INT4_vect));
