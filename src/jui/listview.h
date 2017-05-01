#ifndef JUI_LISTVIEW_H
#define JUI_LISTVIEW_H

#define COMPONENT_HEIGHT 15
#define COMPONENT_X_OFFSET 8

#define SEPERATOR_COLOUR LIGHT_GREY

#include <stdint.h>
#include "jui.h"

typedef struct {
  uint8_t count;
  component_t* components;
  uint8_t selected;
} listview_t;

listview_t listview_create(uint8_t count, component_t* components);
void listview_draw(listview_t* view);
void listview_select(listview_t* menu, uint8_t index);
void listview_scroll(listview_t* menu, int8_t delta);
void listview_up(listview_t* menu);
void listview_down(listview_t* menu);
void listview_run(listview_t* view);

#endif
