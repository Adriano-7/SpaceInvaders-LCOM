#include <lcom/lcf.h>
#include "../../state.h"

#include "../keys.h"

#include "model/menu/over.h"
#include "../../state.h"

extern struct packet pp;

void (over_handle_keyboard)(enum Keys key);

void (over_handle_timer)(Over_t* over);

void (over_handle_mouse)(Over_t* over);

void sOption(Over_t* over, struct packet pp);
