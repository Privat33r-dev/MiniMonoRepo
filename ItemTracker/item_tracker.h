#ifndef ITEM_TRACKER_H
#define ITEM_TRACKER_H
#include <string>
#include <unordered_map>

#include "mini_utils.h"

namespace item_tracker {

class ItemTracker {
 public:
  // Import item data from a file, counting occurrences of each line
  bool LoadItemsFromFile(const std::string& file_name);

  // Import item data from a stream, counting occurrences of each line
  bool ImportFromStream(std::istream& input_stream);

  // Get frequency of the word in the internal items list
  int GetWordFrequency(const std::string& word) const;

  // Export item data to a file
  bool ExportItemsToFile(const std::string& file_name) const;

  // Export item data to a stream
  bool ExportToStream(std::ostream& output_stream) const;

  // Get list of stored items
  std::unordered_map<std::string, int> GetItems() const;

 private:
  std::unordered_map<std::string, int> m_items;
};

class ItemTrackerCli {
 public:
  ItemTrackerCli(const std::string& input_file_name,
                 const std::string& output_file_name, int max_console_width);

  // Start the CLI, loading items from the file and displaying the menu.
  void Start();

 private:
  void DisplayMenu() const;
  void HandleMenuChoice(int user_choice) const;
  void FindItemFrequency() const;
  void ListItemsWithFrequencies() const;
  void ListItemHistogram() const;

  std::string m_inputFileName;
  std::string m_outputFileName;
  ItemTracker m_itemTracker;
  mini_utils::StringFormatter m_formatter;
};

}  // namespace item_tracker
#endif  // ITEM_TRACKER_H