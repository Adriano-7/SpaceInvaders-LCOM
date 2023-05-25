#include <lcom/lcf.h>
#include "../../state.h"

#include "../keys.h"

#include "model/menu/menu.h"
#include "../../state.h"

extern struct packet pp;

void (menu_handle_keyboard)(enum Keys key, Menu_t* menu, enum State* state);

void (menu_handle_timer)(Menu_t* menu);

void (menu_handle_mouse)(Menu_t* menu);
