#include "option.h"

Option_t* createOption(enum State state, DrawableObject_t* drawableObject){
    Option_t* option = malloc(sizeof(Option_t));
    if (option == NULL) {
        printf("Error: malloc failed in createOption\n");
        exit(EXIT_FAILURE);
    }

    option->state = state;
    option->drawableObject = drawableObject;

    return option;
}

void destroyOption(Option_t* option){
    free(option->drawableObject);
    free(option);
}
