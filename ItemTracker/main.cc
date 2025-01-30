#include <iostream>

#include "cli_parser.h"
#include "item_tracker.h"

// Default values for CLI arguments
namespace item_tracker {
const std::string kDefaultInputFile = "input.txt";
const std::string kDefaultOutputFile = "frequency.dat";
const int kDefaultConsoleWidth = 80;
}  // namespace item_tracker

int main(int argc, const char* argv[]) {
    // Initialize CLI argument variables with defaults
    std::string input_file = item_tracker::kDefaultInputFile;
    std::string output_file = item_tracker::kDefaultOutputFile;
    int console_width = item_tracker::kDefaultConsoleWidth;

    // Setup CLI parser
    item_tracker::CliParser parser("ItemTracker");
    parser.AddOption<std::string>("-i", input_file, "Input file name (default: input.txt)", false);
    parser.AddOption<std::string>("-o", output_file, "Output file name (default: frequency.dat)", false);
    parser.AddOption<int>("--width", console_width, "Console width (default: 80)", false);

    // Parse CLI arguments
    if (parser.Parse(argc, argv) != EXIT_SUCCESS) {
      return EXIT_FAILURE;
    }

    // Initialize and start CLI application
    item_tracker::ItemTrackerCli cli(input_file, output_file, console_width);
    cli.Start();

    return EXIT_SUCCESS;
}