#include <iostream>

#include "item_tracker.h"

int main() {
  // These are set in stone by assignment requirements
  // Normally we can fetch those from arguments/ask user for input
  const std::string kInputFileName = "CS210_Project_Three_Input_File.txt";
  const std::string kOutputFileName = "frequency.dat";

  const int kStandardConsoleWidth = 80;
  item_tracker::ItemTrackerCli cli(kInputFileName, kOutputFileName,
                                   kStandardConsoleWidth);
  cli.Start();
}
