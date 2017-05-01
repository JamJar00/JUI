#ifndef jui_input_input_h
#define jui_input_input_h

#include <stdint.h>

#define SWC _BV(PE7)
#define SWW _BV(PC5)
#define SWS _BV(PC4)
#define SWE _BV(PC3)
#define SWN _BV(PC2)

#define ROTA _BV(PE4)
#define ROTB _BV(PE5)

#define ROTA_INT _BV(INT4)
#define ROTB_INT _BV(INT5)

#define CENTER_PRESSED ((PINE & SWC) == 0)
#define LEFT_PRESSED   ((PINC & SWW) == 0)
#define DOWN_PRESSED   ((PINC & SWS) == 0)
#define RIGHT_PRESSED  ((PINC & SWE) == 0)
#define UP_PRESSED     ((PINC & SWN) == 0)

void init_input();
int8_t get_scroll_delta();

#endif
