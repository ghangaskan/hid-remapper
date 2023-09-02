#include "activity_led.h"

#include <bsp/board.h>

#include <hardware/timer.h>
#include <hardware/gpio.h>

#define GPIO_PIN_Relay1 10

static bool led_state = false;
static bool relay_state = false;
static uint64_t turn_led_off_after = 0;
static uint64_t turn_relay_off_after = 0;

void activity_led_on() {
    led_state = true;
    board_led_write(true);
    turn_led_off_after = time_us_64() + 50000;
}

void activity_relay1_on() {
    relay_state = true;
    gpio_put(GPIO_PIN_Relay1, true);
    turn_relay_off_after = time_us_64() + 5000;
}

void activity_led_off_maybe() {
    if (led_state && (time_us_64() > turn_led_off_after)) {
        led_state = false;
        board_led_write(false);
    }

}

void activity_relay1_off_maybe() {
    if (relay_state && (time_us_64() > turn_relay_off_after)) {
        relay_state = false;
        gpio_put(GPIO_PIN_Relay1, false);
    }

}