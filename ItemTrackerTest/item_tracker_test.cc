#include "pch.h"
#include <gtest/gtest.h>

#include <sstream>

#include "item_tracker.h"

// Test suite for ItemTracker class
class ItemTrackerTest : public testing::Test {
 protected:
  item_tracker::ItemTracker tracker_;

  void PopulateTracker(std::istream& stream) {
    ASSERT_TRUE(tracker_.ImportFromStream(stream));
  }
};

// Tests successful import of a stream containing valid entries
TEST_F(ItemTrackerTest, ImportFromStream_ValidEntries) {
  std::istringstream test_stream("onions\npotatoes\ntomatoes\npotatoes\n");
  PopulateTracker(test_stream);

  EXPECT_EQ(tracker_.GetWordFrequency("onions"), 1);
  EXPECT_EQ(tracker_.GetWordFrequency("potatoes"), 2);
  EXPECT_EQ(tracker_.GetWordFrequency("tomatoes"), 1);
}

// Tests the handling of empty input streams
TEST_F(ItemTrackerTest, ImportFromStream_EmptyInput) {
  std::istringstream test_stream("");
  PopulateTracker(test_stream);

  EXPECT_EQ(tracker_.GetWordFrequency("anything"), 0);
  EXPECT_TRUE(tracker_.GetItems().empty());
}

// Tests the handling of input with only whitespace
TEST_F(ItemTrackerTest, ImportFromStream_WhitespaceOnly) {
  std::istringstream test_stream("   \n   \n");
  PopulateTracker(test_stream);

  EXPECT_TRUE(tracker_.GetItems().empty());
}

// Tests multi-word entries in the stream
TEST_F(ItemTrackerTest, ImportFromStream_MultiWordEntries) {
  std::istringstream test_stream("red apple\ngreen apple\nred apple\n");
  PopulateTracker(test_stream);

  EXPECT_EQ(tracker_.GetWordFrequency("red apple"), 2);
  EXPECT_EQ(tracker_.GetWordFrequency("green apple"), 1);
  EXPECT_EQ(tracker_.GetWordFrequency("blue apple"), 0);
}

// Tests case sensitivity when importing and querying entries
TEST_F(ItemTrackerTest, ImportFromStream_CaseSensitiveEntries) {
  std::istringstream test_stream("apple\nApple\nAPPLE\n");
  PopulateTracker(test_stream);

  EXPECT_EQ(tracker_.GetWordFrequency("apple"), 1);
  EXPECT_EQ(tracker_.GetWordFrequency("Apple"), 1);
  EXPECT_EQ(tracker_.GetWordFrequency("APPLE"), 1);
}

// Tests the retrieval of all items and their frequencies
TEST_F(ItemTrackerTest, GetItems_RetrievesCorrectMap) {
  std::istringstream test_stream("apple\nbanana\napple\n");
  PopulateTracker(test_stream);

  auto items = tracker_.GetItems();
  ASSERT_EQ(items.size(), 2);
  EXPECT_EQ(items["apple"], 2);
  EXPECT_EQ(items["banana"], 1);
  EXPECT_EQ(items.count("orange"), 0);  // Ensure "orange" is not present
}

// Tests behavior when querying the frequency of non-existent items
TEST_F(ItemTrackerTest, GetWordFrequency_NonExistentItem) {
  std::istringstream test_stream("apple\nbanana\napple\n");
  PopulateTracker(test_stream);

  EXPECT_EQ(tracker_.GetWordFrequency("orange"), 0);
}

// Tests handling of entries with leading and trailing spaces
TEST_F(ItemTrackerTest, ImportFromStream_EntriesWithSpaces) {
  std::istringstream test_stream(" apple\nbanana \n apple \n");
  PopulateTracker(test_stream);

  EXPECT_EQ(tracker_.GetWordFrequency("apple"),
            0);  // "apple" without spaces not found
  EXPECT_EQ(tracker_.GetWordFrequency(" apple"), 1);   // Leading space
  EXPECT_EQ(tracker_.GetWordFrequency("banana "), 1);  // Trailing space
  EXPECT_EQ(tracker_.GetWordFrequency(" apple "),
            1);  // Both leading and trailing spaces
}

// Tests behavior when attempting to load items from a non-existent file
TEST_F(ItemTrackerTest, LoadItemsFromFile_FileDoesNotExist) {
  EXPECT_FALSE(tracker_.LoadItemsFromFile("non_existent_file.txt"));
}
