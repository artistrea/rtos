// https://developer.arm.com/documentation/dui0662/b/The-Cortex-M0--Processor/Programmers-model/Core-registers
#include "pico/stdlib.h"

int task_next_id=0;

struct task {
  int id;
  void (*exec)(void);
};

#define BUF_SIZE 10

struct task tasks_buf[BUF_SIZE];
int start=0, end=0, is_full=0;

void add_task(void (*func)(void)) {
  if (is_full) return;

  tasks_buf[end].id = task_next_id++;
  tasks_buf[end++].exec = func;
  if (end >= BUF_SIZE) end=0;
  if (end == start) is_full=1;
}

void run_task() {
  if (start == end && !is_full) {
    return;
  }

  tasks_buf[start++].exec();

  if (start >= BUF_SIZE) start=0;
  is_full=0;
}

int main() {
  // setup

  // run stuff
  while (1) {
    run_task();
  }

  return 0;
}
