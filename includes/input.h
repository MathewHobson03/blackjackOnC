#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

typedef struct{
        void* reg_addr;
        int initialized;
}button_handle_t;

int button_init(button_handle_t *button);
int button_is_pressed(button_handle_t *button, int id);
int button_read(button_handle_t *button);

#endif
