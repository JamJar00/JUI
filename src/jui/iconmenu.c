#include "lcd/lcd.h"
#include "iconmenu.h"
#include "jui.h"
#include "util.h"
#include "input/input.h"
#include <stdbool.h>
#include <util/delay.h>

typedef struct {
  uint16_t x;
  uint16_t y;
} position_t;

static position_t get_icon_position(iconmenu_t* menu, uint8_t index);
static uint8_t get_icons_on_row(iconmenu_t* menu, uint8_t row);
static void draw_select_line(iconmenu_t* menu, uint16_t color);

iconmenu_t iconmenu_create(uint8_t count, component_t* components, uint16_t icon_width, uint16_t icon_height) {
  uint8_t icons_per_row = display.width / (icon_width * 2) - 1;
  uint8_t row_count = (count + icons_per_row - 1) / icons_per_row;  /* Ceil division */

  uint16_t y_offset = (display.height - row_count * icon_height * 2) / 2 + icon_height / 2;;

  return (iconmenu_t){count, components, icon_width, icon_height, icons_per_row, row_count, y_offset, count};
}

void iconmenu_draw(iconmenu_t* menu) {
  clear_screen();

  uint8_t i;
  for (i=0; i<menu->count; i++) {
    position_t pos = get_icon_position(menu, i);

    rectangle_t rect = {
      pos.x,
      pos.x + menu->icon_width - 1,
      pos.y,
      pos.y + menu->icon_height - 1
    };

    uint16_t old_bg = display.background;
    if (menu->components[i].style.flags & STYLE_BACKGROUND)
        display.background = menu->components[i].style.background_color;

    style_draw(rect, menu->components[i].style);
    menu->components[i].draw_func(menu->components + i, rect);

    display.background = old_bg;
  }
}

void iconmenu_select(iconmenu_t* menu, uint8_t index) {
  if (menu->selected != index) {
    draw_select_line(menu, display.background);

    menu->selected = index;

    draw_select_line(menu, SELECT_LINE_COLOUR);
  }
}

void iconmenu_scroll(iconmenu_t* menu, int8_t delta) {
  iconmenu_select(menu, mod(menu->selected + delta, menu->count));
}

void iconmenu_up(iconmenu_t* menu) {
  uint8_t row = menu->selected / menu->icons_per_row;
  uint8_t icons_this_row = get_icons_on_row(menu, row);
  uint8_t icons_last_row = get_icons_on_row(menu, mod(row - 1, menu->row_count));
  iconmenu_select(menu, mod(menu->selected - (icons_this_row + icons_last_row) / 2, menu->count));
}

void iconmenu_down(iconmenu_t* menu) {
  uint8_t row = menu->selected / menu->icons_per_row;
  uint8_t icons_this_row = get_icons_on_row(menu, row);
  uint8_t icons_next_row = get_icons_on_row(menu, mod(row + 1, menu->row_count));
  iconmenu_select(menu, mod(menu->selected + (icons_this_row + icons_next_row) / 2, menu->count));
}

void iconmenu_left(iconmenu_t* menu) {
  iconmenu_scroll(menu, -1);
}

void iconmenu_right(iconmenu_t* menu) {
  iconmenu_scroll(menu, 1);
}

void iconmenu_run(iconmenu_t* menu) {
  bool is_up_pressed = UP_PRESSED, is_down_pressed = DOWN_PRESSED, is_left_pressed = LEFT_PRESSED,
        is_right_pressed = RIGHT_PRESSED, is_center_pressed = CENTER_PRESSED;
  int8_t delta;

  while (1) {
    delta = get_scroll_delta();
    if (delta != 0)
      iconmenu_scroll(menu, delta);

    if (UP_PRESSED && !is_up_pressed)
      iconmenu_up(menu);
    else if (DOWN_PRESSED && !is_down_pressed)
      iconmenu_down(menu);
    else if (LEFT_PRESSED && !is_left_pressed)
      iconmenu_left(menu);
    else if (RIGHT_PRESSED && !is_right_pressed)
      iconmenu_right(menu);
    else if (CENTER_PRESSED && !is_center_pressed)
      menu->components[menu->selected].selected_func(menu->components + menu->selected);

    is_up_pressed = UP_PRESSED;
    is_down_pressed = DOWN_PRESSED;
    is_left_pressed = LEFT_PRESSED;
    is_right_pressed = RIGHT_PRESSED;
    is_center_pressed = CENTER_PRESSED;

    _delay_ms (10);     //Improve responsiveness by slowing down the loop 
  }
}

static uint8_t get_icons_on_row(iconmenu_t* menu, uint8_t row) {
  if (row == menu->row_count - 1)
    return menu->count - row * menu->icons_per_row;
  else
    return menu->icons_per_row;
}

static position_t get_icon_position(iconmenu_t* menu, uint8_t index) {
  uint8_t column = index % menu->icons_per_row;
  uint8_t row = index / menu->icons_per_row;
  uint16_t x = column * menu->icon_width * 2;
  uint16_t y = row * menu->icon_height * 2;

  uint16_t x_offset = (display.width - get_icons_on_row(menu, row) * menu->icon_width * 2) / 2 + menu->icon_width / 2;

  return (position_t){x + x_offset, y + menu->y_offset};
}

static void draw_select_line(iconmenu_t* menu, uint16_t color) {
  position_t pos = get_icon_position(menu, menu->selected);

  fill_rectangle(
    (rectangle_t) {
      pos.x,
      pos.x + menu->icon_width,
      pos.y + menu->icon_height + SELECT_LINE_OFFSET,
      pos.y + menu->icon_height + SELECT_LINE_OFFSET + SELECT_LINE_THICKNESS,
    },
    color
  );
}