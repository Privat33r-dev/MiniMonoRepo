/*
 * Clock program that calculates and outputs time in 12- and 24-hours format at
 * the same time.
 */

#include "clock.h"

int main() {
  clock_cli::Clock clock;
  clock.startCli();

  return 0;
}
