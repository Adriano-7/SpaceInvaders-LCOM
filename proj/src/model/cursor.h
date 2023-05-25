#pragma once
#include <lcom/lcf.h>
#include "drawableObject.h"
#include "../devices/mouse.h"
#include "../state.h"

typedef struct Cursor {
  DrawableObject_t* drawableObject;
  bool lbPressed;
} Cursor_t;

Cursor_t* createCursor();
void updateCursor(Cursor_t* cursor, struct packet pp);
void destroyCursor(Cursor_t* cursor);

