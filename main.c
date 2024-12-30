#include "pico/stdlib.h"

int count = 0;

void __isr on_clock_tick() {
  count++;
}

int main() {
  while (1) {
    
  }
}

