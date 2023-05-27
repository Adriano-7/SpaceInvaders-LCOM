#pragma once
#include <lcom/lcf.h>
#include "drawableObject.h"
#include "../devices/mouse.h"
#include "../state.h"

extern struct packet pkt;

typedef struct Cursor {
  DrawableObject_t* drawableObject;
  bool lbPressed;
} Cursor_t;

Cursor_t* createCursor();
void updateCursor(Cursor_t* cursor);
void destroyCursor(Cursor_t* cursor);

