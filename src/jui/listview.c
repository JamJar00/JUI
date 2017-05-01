#include <stdbool.h>
#include <util/delay.h>
#include "lcd/lcd.h"
#include "input/input.h"
#include "listview.h"
#include "jui.h"
#include "util.h"

static void draw_select_line(listview_t* view, uint16_t color);

listview_t listview_create(uint8_t count, component_t* components) {
  return (listview_t){count, components, 0};
}

void listview_draw(listview_t* view) {
  clear_screen();

  uint8_t i;
  uint16_t top = 0;
  for (i = 0; i < view->count; i++) {
    rectangle_t comp_rect = {COMPONENT_X_OFFSET, display.width - COMPONENT_X_OFFSET * 2, top, top + COMPONENT_HEIGHT - 1};

    view->components[i].draw_func(view->components + i, comp_rect);

    top += COMPONENT_HEIGHT + 1;
  }
}

void listview_select(listview_t* view, uint8_t index) {
  if (view->selected != index) {
    draw_select_line(view, display.background);

    view->selected = index;

    draw_select_line(view, SELECT_LINE_COLOUR);
  }
}

void listview_scroll(listview_t* view, int8_t delta) {
  listview_select(view, mod(view->selected + delta, view->count));
}

void listview_up(listview_t* view) {
  listview_scroll(view, -1);
}

void listview_down(listview_t* view) {
  listview_scroll(view, 1);
}

void listview_run(listview_t* view) {
  bool is_up_pressed = UP_PRESSED, is_down_pressed = DOWN_PRESSED, is_left_pressed = LEFT_PRESSED,
        is_right_pressed = RIGHT_PRESSED, is_center_pressed = CENTER_PRESSED;
  int8_t delta;

  while (1) {
    delta = get_scroll_delta();
    if (delta != 0)
      listview_scroll(view, delta);

    if (UP_PRESSED && !is_up_pressed)
      listview_up(view);
    else if (DOWN_PRESSED && !is_down_pressed)
      listview_down(view);
    else if (LEFT_PRESSED && !is_left_pressed)
      return;
    else if ((RIGHT_PRESSED && !is_right_pressed) || (CENTER_PRESSED && !is_center_pressed))
      view->components[view->selected].selected_func(view->components + view->selected);

    is_up_pressed = UP_PRESSED;
    is_down_pressed = DOWN_PRESSED;
    is_left_pressed = LEFT_PRESSED;
    is_right_pressed = RIGHT_PRESSED;
    is_center_pressed = CENTER_PRESSED;

    _delay_ms (10);     //Improve responsiveness by slowing down the loop 
  }
}

static void draw_select_line(listview_t* view, uint16_t color) {
  uint16_t selected_y = view->selected * (COMPONENT_HEIGHT + 1);

  rectangle_t rect =
  {
    SELECT_LINE_OFFSET,
    SELECT_LINE_OFFSET + SELECT_LINE_THICKNESS,
    selected_y + 2,
    selected_y + COMPONENT_HEIGHT - 2
  };

  fill_rectangle(rect, color);
}