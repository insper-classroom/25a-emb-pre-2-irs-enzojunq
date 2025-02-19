#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int LED_PIN = 4;
const int BTN_PIN = 28;
volatile int flag_bnt = 0;

void btn_callback(uint gpio, uint32_t events) {
    flag_bnt = 1;
}

int main() {

    bool led = false;

    stdio_init_all();
    gpio_init(BTN_PIN);
    gpio_set_dir(BTN_PIN, GPIO_IN);
    gpio_pull_up(BTN_PIN);
    gpio_set_irq_enabled_with_callback(
        BTN_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        if (flag_bnt == 1) {
            flag_bnt = 0;
            led = !led;
            gpio_put(LED_PIN, led);
        }
    }
}