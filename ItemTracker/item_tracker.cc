#include "item_tracker.h"

#include <fstream>

namespace item_tracker {

// ItemTracker:Public
bool ItemTracker::LoadItemsFromFile(const std::string& FILE_NAME) {
  std::ifstream inputFile(FILE_NAME);
  if (!inputFile.is_open() || inputFile.fail()) {
    return false;
  }
  return ImportFromStream(inputFile);
}

bool ItemTracker::ImportFromStream(std::istream& inputStream) {
  std::string line;
  while (getline(inputStream, line)) {
    std::string trimmedLine = mini_utils::trim(line);
    if (!trimmedLine.empty()) ++m_items[trimmedLine];
  }
  return true;
}

int ItemTracker::GetWordFrequency(const std::string& word) const {
  auto foundItem = m_items.find(word);
  return foundItem == m_items.end() ? 0 : foundItem->second;
}

bool ItemTracker::ExportItemsToFile(const std::string& fileName) const {
  std::ofstream outputFile(fileName);
  if (!outputFile.is_open() || outputFile.fail()) {
    return false;
  }
  return ExportToStream(outputFile);
}

bool ItemTracker::ExportToStream(std::ostream& outputStream) const {
  for (const auto& ITEM : m_items) {
    outputStream << ITEM.first << " " << ITEM.second << "\n";
  }
  return true;
}

std::unordered_map<std::string, int> ItemTracker::GetItems() const {
  return m_items;
}
// /ItemTracker

// ItemTrackerCli:Public
ItemTrackerCli::ItemTrackerCli(const std::string& INPUT_FILE_NAME,
                               const std::string& OUTPUT_FILE_NAME,
                               int maxConsoleWidth)
    : m_inputFileName(INPUT_FILE_NAME),
      m_outputFileName(OUTPUT_FILE_NAME),
      m_formatter(maxConsoleWidth) {}

void ItemTrackerCli::Start() {
  if (!m_itemTracker.LoadItemsFromFile(m_inputFileName)) {
    std::cerr << "Error: Unable to import items from file: " << m_inputFileName
              << std::endl;
    return;
  }

  if (!m_itemTracker.ExportItemsToFile(m_outputFileName)) {
    std::cerr << "Error: Unable to export items to a file: " << m_outputFileName
              << std::endl;
    return;
  }

  int userChoice = 0;
  while (userChoice != 4) {
    DisplayMenu();
    userChoice = mini_utils::getValidatedInput<int>(
        "State your choice: ",
        [](int input) { return input >= 1 && input <= 4; },
        "integer 1 through 4");
    HandleMenuChoice(userChoice);
    std::cout << std::endl;
  }
}

// ItemTrackerCli:Private

void ItemTrackerCli::DisplayMenu() const {
  const char FORMAT_CHARACTER = '*';
  std::cout << m_formatter.horizontalSeparator(FORMAT_CHARACTER) << "\n"
            << m_formatter.formatFullBorder("Item Tracker Menu",
                                            FORMAT_CHARACTER)
            << "\n"
            << m_formatter.formatSideBorder("Options:") << "\n";

  const std::vector<std::string> MENU_ITEMS = {
      "1. Find item frequency", "2. List items with frequencies",
      "3. List item histogram with frequencies", "4. Exit"};

  for (const auto& ITEM : MENU_ITEMS) {
    std::cout << m_formatter.formatSideBorder(ITEM) << "\n";
  }
  std::cout << m_formatter.horizontalSeparator(FORMAT_CHARACTER) << std::endl;
}

void ItemTrackerCli::HandleMenuChoice(int userChoice) const {
  switch (userChoice) {
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
  std::string userInput = "";
  std::cout << "Please, enter item to search for: ";
  while (userInput.empty()) getline(std::cin, userInput);

  int frequency = m_itemTracker.GetWordFrequency(userInput);
  const std::string S_SUFFIX = frequency != 1 ? "s" : "";

  if (frequency == 0) {
    std::cout << "Item \"" << userInput << "\" is not present in the list."
              << std::endl;
  } else {
    std::cout << "Item \"" << userInput << "\" encountered " << frequency
              << " time" << S_SUFFIX << "." << std::endl;
  }
}

// Displays all items with their corresponding frequencies
void ItemTrackerCli::ListItemsWithFrequencies() const {
  const auto& ITEMS = m_itemTracker.GetItems();
  for (const auto& ITEM : ITEMS) {
    std::cout << ITEM.first << " " << ITEM.second << std::endl;
  }
}

// Displays all items as a histogram (bars made of '#' characters) based on
// their frequencies
void ItemTrackerCli::ListItemHistogram() const {
  const auto& ITEMS = m_itemTracker.GetItems();
  for (const auto& ITEM : ITEMS) {
    std::cout << ITEM.first << " " << std::string(ITEM.second, '#')
              << std::endl;
  }
}
// /ItemTrackerCli

}  // namespace item_tracker