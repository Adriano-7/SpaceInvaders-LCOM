#include <lcom/lcf.h>
#include "../../state.h"

#include "../keys.h"

#include "model/menu/menu.h"
#include "../../state.h"

extern struct packet pp;

void (menu_handle_keyboard)(enum Keys key);

void (menu_handle_timer)(Menu_t* menu);

void (menu_handle_mouse)(Menu_t* menu);

void selectOption(Menu_t* menu, struct packet pp);

