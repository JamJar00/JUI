#include <stdlib.h>
#include "textcomponent.h"
#include "style.h"
#include "lcd/lcd.h"

void text_draw_callback(component_t* component, rectangle_t rect);
int strlen(char* string);

void text_create(component_t* component, style_t style, char* text) {
    component->flags = 0;
    component->draw_func = text_draw_callback;
    component->selected_func = NULL;
    component->style = style;
    component->contents = text;
}

void text_draw_callback(component_t* component, rectangle_t rect) {
    int width = strlen((char*)component->contents) * 6;
    int x_offset = (rect.right - rect.left - width) / 2;
    int y_offset = (rect.bottom - rect.top - 7) / 2;

    display_string_xy((char*)component->contents, rect.left + x_offset, rect.top + y_offset);
}

int strlen(char* string) {
    int c = 0;
    while (string[c] != '\0')
        c++;
    return c;
}