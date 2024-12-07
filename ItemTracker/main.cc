#include <iostream>

#include "item_tracker.h"

int main() {
  // These are set in stone by assignment requirements
  // Normally we can fetch those from arguments/ask user for input
  const std::string INPUT_FILE_NAME = "CS210_Project_Three_Input_File.txt";
  const std::string OUTPUT_FILE_NAME = "frequency.dat";

  const int STANDARD_CONSOLE_WIDTH = 80;
  item_tracker::ItemTrackerCli cli(INPUT_FILE_NAME, OUTPUT_FILE_NAME,
                                   STANDARD_CONSOLE_WIDTH);
  cli.Start();
}
