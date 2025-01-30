#include <gtest/gtest.h>
#include <fstream>
#include "cli_parser.h"
#include "item_tracker.h"

namespace item_tracker {

// Helper function to create a temporary test file
void CreateTestFile(const std::string& filename, const std::vector<std::string>& lines) {
    std::ofstream file(filename);
    for (const auto& line : lines) {
        file << line << "\n";
    }
    file.close();
}

// Integration test for ItemTracker file loading & frequency tracking
TEST(ItemTrackerIntegrationTest, LoadAndTrackItems) {
    const std::string test_file = "test_input.txt";
    const std::vector<std::string> test_data = {"apple", "banana", "apple", "orange", "banana", "apple"};
    CreateTestFile(test_file, test_data);

    ItemTracker tracker;
    EXPECT_TRUE(tracker.LoadItemsFromFile(test_file));

    EXPECT_EQ(tracker.GetWordFrequency("apple"), 3);
    EXPECT_EQ(tracker.GetWordFrequency("banana"), 2);
    EXPECT_EQ(tracker.GetWordFrequency("orange"), 1);
    EXPECT_EQ(tracker.GetWordFrequency("grape"), 0);
}

// Integration test for exporting item frequency
TEST(ItemTrackerIntegrationTest, ExportItemsToFile) {
    const std::string output_file = "test_output.txt";
    ItemTracker tracker;

    std::stringstream test_stream("apple\nbanana\napple\norange\n");
    EXPECT_TRUE(tracker.ImportFromStream(test_stream));
    EXPECT_TRUE(tracker.ExportItemsToFile(output_file));

    std::ifstream file(output_file);
    std::string line;
    std::vector<std::string> output_lines;
    while (std::getline(file, line)) {
        output_lines.push_back(line);
    }

    ASSERT_EQ(output_lines.size(), 3);
    EXPECT_EQ(output_lines[0], "apple 2");
    EXPECT_EQ(output_lines[1], "banana 1");
    EXPECT_EQ(output_lines[2], "orange 1");
}

// Integration test for CLI parsing and ItemTracker
TEST(ItemTrackerIntegrationTest, CliParserIntegration) {
    char* argv[] = { (char*)"ItemTrackerExe", "-i", "custom_input.txt", "-o", "custom_output.dat", "--width", "120" };
    int argc = 6;

    std::string input_file = "input.txt";
    std::string output_file = "frequency.dat";
    int console_width = 80;

    CliParser parser("ItemTracker");
    parser.AddOption<std::string>("-i", input_file, "Input file name");
    parser.AddOption<std::string>("-o", output_file, "Output file name");
    parser.AddOption<int>("--width", console_width, "Console width");

    parser.Parse(argc, argv);

    EXPECT_EQ(input_file, "custom_input.txt");
    EXPECT_EQ(output_file, "custom_output.dat");
    EXPECT_EQ(console_width, 120);
}

}  // namespace item_tracker
