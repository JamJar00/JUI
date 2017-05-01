#ifndef jui_buttoncomponent_h
#define jui_buttoncomponent_h

#include "jui.h"

void button_create(component_t* button, style_t style, component_t* contents, void (*selected_callback) (component_t* component));

#endif