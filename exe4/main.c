#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_RED = 28;
const int BTN_PIN_GREEN = 26;

const int LED_PIN_R = 4;
const int LED_PIN_G = 6;

volatile int btn_green = -1;
volatile int btn_red = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    if (gpio == BTN_PIN_RED) {
      btn_red = 1;
    }
  }

  else if (events == 0x8) { // rise edge
    if (gpio == BTN_PIN_GREEN) {
      btn_green = 0;
    }
  }

}

void init(){
  gpio_init(BTN_PIN_RED);
  gpio_set_dir(BTN_PIN_RED, GPIO_IN);
  gpio_pull_up(BTN_PIN_RED);

  gpio_init(BTN_PIN_GREEN);
  gpio_set_dir(BTN_PIN_GREEN, GPIO_IN);
  gpio_pull_up(BTN_PIN_GREEN);

  gpio_set_irq_enabled_with_callback(BTN_PIN_RED, GPIO_IRQ_EDGE_FALL, true,
                                     &btn_callback);
  
  gpio_set_irq_enabled_with_callback(BTN_PIN_GREEN, GPIO_IRQ_EDGE_RISE, true,
                                      &btn_callback);

  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);

  gpio_init(LED_PIN_G);
  gpio_set_dir(LED_PIN_G, GPIO_OUT);
}

int main() {
  stdio_init_all();  
  init();

  bool led_state_r = false;
  bool led_state_g = false;

  while (true) {
    if (btn_red == 1) {
      led_state_r = !led_state_r;
      gpio_put(LED_PIN_R, led_state_r);
      btn_red = 0;
    }

    else if (!btn_green) {
      led_state_g = !led_state_g;
      gpio_put(LED_PIN_G, led_state_g);
      btn_green = -1;
    }
   
  }
}