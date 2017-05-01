#ifndef jui_style_h
#define jui_style_h

#include "jui.h"
#include "lcd/lcd.h"
#include "lcd/svgrgb565.h"
#include <stdint.h>

typedef struct {
    uint8_t flags;
    uint16_t background_color;
    uint16_t border_color;
} style_t;

#define STYLE_NONE 0
#define STYLE_BACKGROUND 1
#define STYLE_TOP_BORDER 2
#define STYLE_BOTTOM_BORDER 4
#define STYLE_LEFT_BORDER 8
#define STYLE_RIGHT_BORDER 16

#define STYLE_FULL_BORDER (STYLE_TOP_BORDER | STYLE_BOTTOM_BORDER | STYLE_LEFT_BORDER | STYLE_RIGHT_BORDER)

#define NO_STYLE (style_t){ STYLE_NONE, BLACK, BLACK }
#define ICONMENU_BUTTON_STYLE (style_t){ STYLE_FULL_BORDER, BLACK, DARK_GREY }
#define LISTVIEW_BUTTON_STYLE (style_t){ STYLE_BOTTOM_BORDER, BLACK, DARK_GREY }
#define GRIDVIEW_BUTTON_STYLE (style_t){ STYLE_FULL_BORDER, BLACK, DARK_GREY }

void style_draw(rectangle_t rect, style_t style);

#endif