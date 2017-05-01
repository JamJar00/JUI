#ifndef JUI_GRIDVIEW_H
#define JUI_GRIDVIEW_H

#include <stdint.h>
#include "jui.h"

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
    component_t* component;
} gridview_component_t;

typedef struct {
  uint8_t xCount;
  uint8_t yCount;
  uint8_t count;
  gridview_component_t* components;
  uint8_t selected;
} gridview_t;

gridview_t gridview_create(uint8_t xCount, uint8_t yCount, uint8_t count, gridview_component_t* components);
void gridview_draw(gridview_t* view);
gridview_component_t gridview_place(uint8_t x, uint8_t y, uint8_t width, uint8_t height, component_t* component);
void gridview_select(gridview_t* menu, uint8_t index);
void gridview_scroll(gridview_t* menu, int8_t delta);
void gridview_left(gridview_t* menu);
void gridview_right(gridview_t* menu);
void gridview_up(gridview_t* menu);
void gridview_down(gridview_t* menu);
void gridview_run(gridview_t* view);

#endif