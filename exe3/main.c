#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

volatile int bnt_red = 0;
volatile int bnt_green = 0;
const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    if (gpio == BTN_PIN_R){
      bnt_red = 1;
    }
      
    else if (gpio == BTN_PIN_G){
      bnt_green = 1;
    }
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true,
                                     &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true);

  while (true) {
    if (bnt_red == 1) {
      printf("fall red\n");
      bnt_red = 0;
    }

    if (bnt_green == 1) {
      printf("fall green\n");
      bnt_green = 0;
    }
  }
}