#include <iostream>
#include "item_tracker.h"

int main() {
  const std::string kInputFileName = "CS210_Project_Three_Input_File.txt";
  const int kStandardConsoleWidth = 80;
  item_tracker::ItemTrackerCli cli(kInputFileName, kStandardConsoleWidth);
  cli.Start();
}
