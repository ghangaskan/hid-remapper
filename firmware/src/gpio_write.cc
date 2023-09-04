#include "gpio_write.h"

#include <bsp/board.h>

#include <hardware/timer.h>
#include <hardware/gpio.h>

static uint32_t relay_state = 0;
static uint64_t turn_relay_off_after[32] = { 0 };

void gpio_write_on_mask(int PinMask) {
    If (relay_state & PinMask == 0) {
        for(uint i=0;i<NUM_BANK0_GPIOS;i++) {
            if (PinMask & 1) {
                turn_relay_off_after[i] = time_us_64() + 5000; 
                gpio_put(i, true);
            }
            PinMask >>= 1;
        }
    }   
}

void gpio_write_off_mask_maybe(int PinMask) {
    If (relay_state & PinMask > 0) {
        for(uint i=0;i<NUM_BANK0_GPIOS;i++) {
            if (PinMask & 1) {
                if (time_us_64() > turn_relay_off_after[i]) {
                    relay_state = relay_state & (~PinMask);
                    gpio_put(i, false);
                }
            }
            PinMask >>= 1;
        }
    }
}

void gpio_init_read_mask(int gpio_mask) {
    for(uint i=0;i<NUM_BANK0_GPIOS;i++) {
        if (gpio_mask & 1) {
            gpio_init(i);
            gpio_pull_up(i);
        }
        gpio_mask >>= 1;
    }
}

void gpio_init_write_mask(int gpio_mask) {
    for(uint i=0;i<NUM_BANK0_GPIOS;i++) {
        if (gpio_mask & 1) {
            gpio_init(i);
            gpio_set_dir(i, GPIO_OUT);      // Configure the onboard relay
            gpio_pull_down(i);    // 
        }
        gpio_mask >>= 1;
    }
}
