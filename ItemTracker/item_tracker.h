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

  // Get list of stored items
  std::unordered_map<std::string, int> GetItems() const;

 private:
  std::unordered_map<std::string, int> items_;
};

class ItemTrackerCli {
 public:
  ItemTrackerCli(const std::string& file_name, int max_console_width);

  // Start the CLI, loading items from the file and displaying the menu.
  void Start();

 private:
  void DisplayMenu() const;
  void HandleMenuChoice(int user_choice) const;
  void FindItemFrequency() const;
  void ListItemsWithFrequencies() const;
  void ListItemHistogram() const;

  std::string file_name_;
  ItemTracker item_tracker_;
  mini_utils::StringFormatter formatter_;
};

}  // namespace item_tracker
#endif  // ITEM_TRACKER_H