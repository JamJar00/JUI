#include <stdlib.h>
#include "jui.h"
#include "style.h"
#include "lcd/lcd.h"
#include "buttoncomponent.h"

static void button_draw_callback(component_t* component, rectangle_t rect);

void button_create(component_t* button, style_t style, component_t* contents, void (*selected_callback) (component_t* component)) {
    button->flags = COMPONENT_SELECTABLE;
    button->draw_func = button_draw_callback;
    button->selected_func = selected_callback;
    button->style = style;
    button->contents = (void*)contents;
}

static void button_draw_callback(component_t* component, rectangle_t rect) {
    style_draw(rect, component->style);

    rectangle_t r = (rectangle_t){rect.left + 2, rect.right - 2, rect.top + 2, rect.bottom - 2};
    component_t* child = (component_t*)component->contents;

    uint16_t old_bg = display.background;
    if (component->style.flags & STYLE_BACKGROUND)
        display.background = component->style.background_color;

    child->draw_func(child, r);

    display.background = old_bg;
}