#include "item_tracker.h"

#include <fstream>

namespace item_tracker {

// ItemTracker:Public
bool ItemTracker::LoadItemsFromFile(const std::string& file_name) {
  std::ifstream input_file(file_name);
  if (!input_file.is_open() || input_file.fail()) {
    return false;
  }
  return ImportFromStream(input_file);
}

bool ItemTracker::ImportFromStream(std::istream& input_stream) {
  std::string line;
  while (getline(input_stream, line)) {
    std::string trimmed_line = mini_utils::trim(line);
    if (!trimmed_line.empty()) ++items_[trimmed_line];
  }
  return true;
}

int ItemTracker::GetWordFrequency(const std::string& word) const {
  auto found_item = items_.find(word);
  return found_item == items_.end() ? 0 : found_item->second;
}

bool ItemTracker::ExportItemsToFile(const std::string& file_name) const {
  std::ofstream output_file(file_name);
  if (!output_file.is_open() || output_file.fail()) {
    return false;
  }
  return ExportToStream(output_file);
}

bool ItemTracker::ExportToStream(std::ostream& output_stream) const {
  for (const auto& item : items_) {
    output_stream << item.first << " " << item.second << "\n";
  }
  return true;
}

std::unordered_map<std::string, int> ItemTracker::GetItems() const {
  return items_;
}
// /ItemTracker

// ItemTrackerCli:Public
ItemTrackerCli::ItemTrackerCli(const std::string& input_file_name,
                               const std::string& output_file_name,
                               int max_console_width)
    : input_file_name_(input_file_name),
      output_file_name_(output_file_name),
      formatter_(max_console_width) {}

void ItemTrackerCli::Start() {
  if (!item_tracker_.LoadItemsFromFile(input_file_name_)) {
    std::cerr << "Error: Unable to import items from file: " << input_file_name_
              << std::endl;
    return;
  }

  if (!item_tracker_.ExportItemsToFile(output_file_name_)) {
    std::cerr << "Error: Unable to export items to a file: "
              << output_file_name_ << std::endl;
    return;
  }

  int user_choice = 0;
  while (user_choice != 4) {
    DisplayMenu();
    user_choice = mini_utils::getValidatedInput<int>(
        "State your choice: ",
        [](int input) { return input >= 1 && input <= 4; },
        "integer 1 through 4");
    mini_utils::clearInput();
    HandleMenuChoice(user_choice);
    std::cout << std::endl;
  }
}

// ItemTrackerCli:Private

void ItemTrackerCli::DisplayMenu() const {
  const char FORMAT_CHARACTER = '*';
  std::cout << formatter_.horizontalSeparator(FORMAT_CHARACTER) << "\n"
            << formatter_.formatFullBorder("Item Tracker Menu",
                                           FORMAT_CHARACTER)
            << "\n"
            << formatter_.formatSideBorder("Options:") << "\n";

  const std::vector<std::string> kMenuItems = {
      "1. Find item frequency", "2. List items with frequencies",
      "3. List item histogram with frequencies", "4. Exit"};

  for (const auto& item : kMenuItems) {
    std::cout << formatter_.formatSideBorder(item) << "\n";
  }
  std::cout << formatter_.horizontalSeparator(FORMAT_CHARACTER) << std::endl;
}

void ItemTrackerCli::HandleMenuChoice(int user_choice) const {
  switch (user_choice) {
    case 1:
      FindItemFrequency();
      break;
    case 2:
      ListItemsWithFrequencies();
      break;
    case 3:
      ListItemHistogram();
      break;
    case 4:
      std::cout << "Goodbye!" << std::endl;
      break;
    default:
      std::cerr << "Invalid choice. Please, select a valid menu item."
                << std::endl;
  }
}

// Prompts the user for an item and displays its frequency
void ItemTrackerCli::FindItemFrequency() const {
  std::string user_input = "";
  std::cout << "Please, enter item to search for: ";
  while (user_input.empty()) getline(std::cin, user_input);

  int frequency = item_tracker_.GetWordFrequency(user_input);
  const std::string s_suffix = frequency != 1 ? "s" : "";

  if (frequency == 0) {
    std::cout << "Item \"" << user_input << "\" is not present in the list."
              << std::endl;
  } else {
    std::cout << "Item \"" << user_input << "\" encountered " << frequency
              << " time" << s_suffix << "." << std::endl;
  }
}

// Displays all items with their corresponding frequencies
void ItemTrackerCli::ListItemsWithFrequencies() const {
  const auto& items = item_tracker_.GetItems();
  for (const auto& item : items) {
    std::cout << item.first << " " << item.second << std::endl;
  }
}

// Displays all items as a histogram (bars made of '#' characters) based on
// their frequencies
void ItemTrackerCli::ListItemHistogram() const {
  const auto& items = item_tracker_.GetItems();
  for (const auto& item : items) {
    std::cout << item.first << " " << std::string(item.second, '#')
              << std::endl;
  }
}
// /ItemTrackerCli

}  // namespace item_tracker