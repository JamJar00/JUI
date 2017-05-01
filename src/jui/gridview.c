#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>
#include "lcd/lcd.h"
#include "input/input.h"
#include "jui.h"
#include "gridview.h"
#include "util.h"

static void draw_select_line(gridview_t* view, uint16_t color);
static uint8_t find_component(gridview_t* view, uint8_t x, uint8_t y);

gridview_t gridview_create(uint8_t xCount, uint8_t yCount, uint8_t count, gridview_component_t* components) {
    return (gridview_t){xCount, yCount, count, components, 0};
}

void gridview_draw(gridview_t* view) {
    clear_screen();
    
    int i;
    uint16_t unitWidth = display.width / view->xCount;
    uint16_t unitHeight = display.height / view->yCount;

    for (i = 0; i < view->count; i++) {        
        rectangle_t rect = {
            unitWidth * view->components[i].x,
            unitWidth * view->components[i].x + unitWidth * view->components[i].width,
            unitHeight * view->components[i].y,
            unitHeight * view->components[i].y + unitHeight * view->components[i].height
        };

        uint16_t old_bg = display.background;
        if (view->components[i].component->style.flags & STYLE_BACKGROUND)
            display.background = view->components[i].component->style.background_color;

        style_draw(rect, view->components[i].component->style);
        view->components[i].component->draw_func(view->components[i].component, rect);

        display.background = old_bg;
    }
}

gridview_component_t gridview_place(uint8_t x, uint8_t y, uint8_t width, uint8_t height, component_t* component) {
    return (gridview_component_t){x, y, width, height, component};
}

void gridview_select(gridview_t* view, uint8_t index) {
    if (view->selected != index) {
        draw_select_line(view, display.background);

        view->selected = index;

        draw_select_line(view, SELECT_LINE_COLOUR);
    }
}

void gridview_scroll(gridview_t* view, int8_t delta) {
    gridview_select(view, mod(view->selected + delta, view->count));
}

void gridview_left(gridview_t* view) {
    uint8_t s = find_component(view, view->components[view->selected].x - 1, view->components[view->selected].y);
    gridview_select(view, s);
}

void gridview_right(gridview_t* view) {
    uint8_t s = find_component(view, view->components[view->selected].x + view->components[view->selected].width, view->components[view->selected].y);
    gridview_select(view, s);
}

void gridview_up(gridview_t* view) {
    uint8_t s = find_component(view, view->components[view->selected].x, view->components[view->selected].y - 1);
    gridview_select(view, s);
}

void gridview_down(gridview_t* view) {
    uint8_t s = find_component(view, view->components[view->selected].x, view->components[view->selected].y + view->components[view->selected].height);
    gridview_select(view, s);
}

void gridview_run(gridview_t* view) {
    bool is_up_pressed = UP_PRESSED, is_down_pressed = DOWN_PRESSED, is_left_pressed = LEFT_PRESSED,
            is_right_pressed = RIGHT_PRESSED, is_center_pressed = CENTER_PRESSED;
    int8_t delta;

    while (1) {
        delta = get_scroll_delta();
        if (delta != 0)
        gridview_scroll(view, delta);

        if (UP_PRESSED && !is_up_pressed)
            gridview_up(view);
        else if (DOWN_PRESSED && !is_down_pressed)
            gridview_down(view);
        else if (LEFT_PRESSED && !is_left_pressed)
            gridview_left(view);
        else if (RIGHT_PRESSED && !is_right_pressed)
            gridview_right(view);
        else if (CENTER_PRESSED && !is_center_pressed)
        {}

        is_up_pressed = UP_PRESSED;
        is_down_pressed = DOWN_PRESSED;
        is_left_pressed = LEFT_PRESSED;
        is_right_pressed = RIGHT_PRESSED;
        is_center_pressed = CENTER_PRESSED;

        _delay_ms (10);     //Improve responsiveness by slowing down the loop 
    }
}

static void draw_select_line(gridview_t* view, uint16_t color) {
    gridview_component_t* selected = view->components + view->selected;

    uint16_t unitWidth = display.width / view->xCount;
    uint16_t unitHeight = display.height / view->yCount;

    rectangle_t rect =
    {
        selected->x * unitWidth + 2,
        selected->x * unitWidth - 2 + selected->width * unitWidth,
        (selected->y + selected->height) * unitHeight - SELECT_LINE_OFFSET - SELECT_LINE_THICKNESS,
        (selected->y + selected->height) * unitHeight - SELECT_LINE_OFFSET
    };

    fill_rectangle(rect, color);
}

static uint8_t find_component(gridview_t* view, uint8_t x, uint8_t y) {
    uint8_t i;
    
    /* Normalise */
    x = mod(x, view->xCount);
    y = mod(y, view->yCount);

    /* Search */
    for (i = 0; i < view->count; i++) {
        gridview_component_t* component = (view->components + i);
        if (component->x <= x && x < component->x + component->width
         && component->y <= y && y < component->y + component->height)
            return i;
    }

    return 0;
}