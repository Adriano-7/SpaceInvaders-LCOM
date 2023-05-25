#pragma once
#include <lcom/lcf.h>
#include "../drawableObject.h"
#include "../../state.h"

typedef struct Option {
  DrawableObject_t* drawableObject;
  enum State state;
} Option_t;

Option_t* createOption(enum State state, DrawableObject_t* drawableObject);
void destroyOption(Option_t* option);
