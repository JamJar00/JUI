#include <stdlib.h>
#include "jui.h"
#include "lcd/lcd.h"
#include "style.h"

void style_draw(rectangle_t rect, style_t style) {
    //Fill
    if (style.flags & STYLE_BACKGROUND)
        fill_rectangle(rect, style.background_color);

    //Draw borders
    if (style.flags & STYLE_TOP_BORDER)
        fill_rectangle((rectangle_t){rect.left, rect.right, rect.top, rect.top}, style.border_color);
    if (style.flags & STYLE_BOTTOM_BORDER)
    fill_rectangle((rectangle_t){rect.left, rect.right, rect.bottom, rect.bottom}, style.border_color);
    if (style.flags & STYLE_LEFT_BORDER)
        fill_rectangle((rectangle_t){rect.left, rect.left, rect.top, rect.bottom}, style.border_color);
    if (style.flags & STYLE_RIGHT_BORDER)
        fill_rectangle((rectangle_t){rect.right, rect.right, rect.top, rect.bottom}, style.border_color);
}