#ifndef ICONMENU_H
#define ICONMENU_H

#include <stdlib.h>
#include "jui.h"

typedef struct {
  uint8_t count;
  component_t* components;
  uint16_t icon_width;
  uint16_t icon_height;
  uint8_t icons_per_row;
  uint8_t row_count;
  uint16_t y_offset;
  uint8_t selected;
} iconmenu_t;

iconmenu_t iconmenu_create(uint8_t count, component_t* components, uint16_t icon_width, uint16_t icon_height);
void iconmenu_draw(iconmenu_t* menu);
void iconmenu_select(iconmenu_t* menu, uint8_t index);
void iconmenu_scroll(iconmenu_t* menu, int8_t delta);
void iconmenu_up(iconmenu_t* menu);
void iconmenu_down(iconmenu_t* menu);
void iconmenu_right(iconmenu_t* menu);
void iconmenu_left(iconmenu_t* menu);
void iconmenu_run(iconmenu_t* menu);

#endif
