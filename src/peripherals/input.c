#include <stdio.h>
#include "../includes/hal/hal-api.h"
#include "../includes/input.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "../../lib/address_map_arm.h"


static hal_map_t hal_map;
static int hal_initialized = 0;

int button_init(button_handle_t *button){
        if (!button) return -1;
        if(!hal_initialized){
                if(hal_open(&hal_map) != 0){
                        fprintf(stderr, "Failed to initialize hal");
                        return -1;
                }

        hal_initialized =1 ;
        }

        button->reg_addr = hal_get_virtual_addr(&hal_map, KEY_BASE);
        if(!button->reg_addr){
                fprintf(stderr, "failed to get button register addr");
                return -1;
        }
        button -> initialized =1;

        printf("Buttons are initialized");
        return 0;
}


int button_read(button_handle_t *button){
        if(!button || !button -> initialized) return -1;
        volatile uint32_t *reg = (volatile uint32_t*)button->reg_addr;
        return *reg;


}

int button_is_pressed(button_handle_t *button, int id) {
    if (!button || !button->initialized)
        return -1;

    // 0�~@~S3 are valid KEY IDs
    if (id < 0 || id > 3)
        return -1;

    volatile uint32_t *reg = (volatile uint32_t*) button->reg_addr;

    // Check the specific bit
    uint32_t mask = (1 << id);
    return ((*reg) & mask) ? 1 : 0;
}