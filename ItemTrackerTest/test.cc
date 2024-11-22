#include "pch.h"

#include <sstream>
#include <gtest/gtest.h>

#include "../ItemTracker/item_tracker.h"

TEST(ItemTrackerTest, ImportFromStream) {
  std::istringstream test_stream("onions\npotatoes\ntomatoes\npotatoes\n");
  item_tracker::ItemTracker tracker;
  ASSERT_TRUE(tracker.ImportFromStream(test_stream));

  ASSERT_EQ(tracker.GetWordFrequency("onions"), 1);
  ASSERT_EQ(tracker.GetWordFrequency("potatoes"), 2);
  ASSERT_EQ(tracker.GetWordFrequency("tomatoes"), 1);
}

TEST(ItemTracker, LoadItemsFromFileTest) {
  std::stringstream test_stream("apple\nbanana\napple\n");
  item_tracker::ItemTracker tracker;
  tracker.ImportFromStream(test_stream);

  EXPECT_EQ(tracker.GetWordFrequency("apple"), 2);
  EXPECT_EQ(tracker.GetWordFrequency("banana"), 1);
  EXPECT_EQ(tracker.GetWordFrequency("orange"), 0);
}

TEST(ItemTracker, GetItemsTest) {
  item_tracker::ItemTracker tracker;
  std::stringstream test_stream("apple\nbanana\napple\n");
  tracker.ImportFromStream(test_stream);

  auto items = tracker.GetItems();
  EXPECT_EQ(items["apple"], 2);
  EXPECT_EQ(items["banana"], 1);
}
