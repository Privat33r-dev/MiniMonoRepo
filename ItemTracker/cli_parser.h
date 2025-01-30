#ifndef ITEM_TRACKER_CLI_PARSER_H_
#define ITEM_TRACKER_CLI_PARSER_H_

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace item_tracker {

/**
 * @brief CLI Parser for handling command-line arguments dynamically.
 */
class CliParser {
 private:
  std::string app_name_;
  std::map<std::string, std::function<void(const std::string&)>> options_;
  std::map<std::string, bool> required_options_;
  std::map<std::string, std::string> help_text_;

  void HandleUnknownArgument(const std::string& arg);

 public:
  /**
   * @brief Constructs a CLI Parser with the application name.
   * @param app_name The name of the application.
   */
  explicit CliParser(const std::string& app_name);

  /**
   * @brief Adds a standard option (e.g., --output filename).
   * @tparam T Type of the value to store.
   * @param option_name Name of the CLI option (e.g., "--output").
   * @param output Reference to store the parsed value.
   * @param help_string Help message for the option.
   * @param required Whether the option is required (program exits if missing).
   */
  template <typename T>
  void AddOption(const std::string& option_name, T& output, const std::string& help_string, bool required) {
    options_[option_name] = [&output](const std::string& value) {
      if constexpr (std::is_same_v<T, std::string>) {
        output = value;
      } else if constexpr (std::is_same_v<T, int>) {
        output = std::stoi(value);
      } else if constexpr (std::is_same_v<T, double>) {
        output = std::stod(value);
      } else if constexpr (std::is_same_v<T, bool>) {
        output = (value == "true" || value == "1");
      } else {
        std::cerr << "Error: Unsupported type for option parsing.\n";
        exit(1);
      }
    };
    help_text_[option_name] = help_string;
    required_options_[option_name] = required;
  }

  /**
   * @brief Parses command-line arguments and sets values.
   * @param argc Argument count from main.
   * @param argv Argument values from main.
   * @returns EXIT_SUCCESS if arguments are valid or EXIT_FAILURE
   */
  int Parse(int argc, const char* argv[]);

  /**
   * @brief Prints usage instructions.
   */
  void PrintHelp() const;

};

}  // namespace item_tracker

#endif  // ITEM_TRACKER_CLI_PARSER_H_
