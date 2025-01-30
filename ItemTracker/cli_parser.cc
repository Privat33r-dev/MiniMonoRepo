#include "cli_parser.h"

namespace item_tracker {

CliParser::CliParser(const std::string& app_name) : app_name_(app_name) {}

void CliParser::Parse(int argc, const char* argv[]) {
  std::map<std::string, bool> seen_options;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (options_.count(arg)) {
      if (i + 1 < argc) {
        options_[arg](argv[++i]);
        seen_options[arg] = true;
      } else {
        std::cerr << "Error: Missing value for option " << arg << "\n";
        exit(1);
      }
    } else {
      HandleUnknownArgument(arg);
    }
  }

  // Check for missing required options
  for (const auto& [option, is_required] : required_options_) {
    if (is_required && seen_options.find(option) == seen_options.end()) {
      std::cerr << "Error: Missing required option " << option << "\n";
      PrintHelp();
      exit(1);
    }
  }
}

void CliParser::HandleUnknownArgument(const std::string& arg) {
  std::cerr << "Error: Unknown argument '" << arg << "'\n";
  PrintHelp();
  exit(1);
}

void CliParser::PrintHelp() const {
  std::cout << "Usage: " << app_name_ << " [OPTIONS]\n";
  for (const auto& [option, help] : help_text_) {
    std::cout << "  " << option << "  - " << help << "\n";
  }
}

}  // namespace item_tracker
