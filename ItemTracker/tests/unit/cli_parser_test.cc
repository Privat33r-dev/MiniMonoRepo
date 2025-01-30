#include "cli_parser.h"
#include <gtest/gtest.h>
#include <cstdlib>  // For EXIT_SUCCESS and EXIT_FAILURE

/**
 * @brief Tests that the CLI parser correctly assigns default values
 *        when no arguments are provided.
 */
TEST(CliParserTest, DefaultValues) {
    const char* argv[] = { "ItemTrackerExe" };  // No CLI arguments provided

    std::string input_file = "input.txt";  // Default values
    std::string output_file = "frequency.dat";
    int console_width = 80;

    item_tracker::CliParser parser("ItemTracker");
    parser.AddOption<std::string>("-i", input_file, "Input file", false);
    parser.AddOption<std::string>("-o", output_file, "Output file", false);
    parser.AddOption<int>("--width", console_width, "Console width", false);

    EXPECT_EQ(parser.Parse(1, argv), EXIT_SUCCESS);

    // Ensure default values remain unchanged
    EXPECT_EQ(input_file, "input.txt");
    EXPECT_EQ(output_file, "frequency.dat");
    EXPECT_EQ(console_width, 80);
}

/**
 * @brief Tests whether the CLI parser correctly updates string
 *        when a custom input file argument is provided.
 */
TEST(CliParserTest, ParseCustomInput) {
    const char* argv[] = { "ItemTrackerExe", "-i", "data.txt" };

    std::string input_file = "input.txt";  // Default value
    item_tracker::CliParser parser("ItemTracker");
    parser.AddOption<std::string>("-i", input_file, "Input file", false);

    EXPECT_EQ(parser.Parse(3, argv), EXIT_SUCCESS);

    // Ensure input file is updated
    EXPECT_EQ(input_file, "data.txt");
}

/**
 * @brief Tests whether the CLI parser correctly updates int value
 *        when the custom argument is provided.
 */
TEST(CliParserTest, ParseConsoleWidth) {
    const char* argv[] = { "ItemTrackerExe", "--width", "100" };

    int console_width = 80;  // Default value
    item_tracker::CliParser parser("ItemTracker");
    parser.AddOption<int>("--width", console_width, "Console width", false);

    EXPECT_EQ(parser.Parse(3, argv), EXIT_SUCCESS);

    // Ensure console width is updated
    EXPECT_EQ(console_width, 100);
}

/**
 * @brief Tests that the CLI parser returns `EXIT_FAILURE` when an option is missing
 *        its required value.
 */
TEST(CliParserTest, MissingOptionValue) {
    const char* argv[] = { "ItemTrackerExe", "--width" };  // '--width' requires a value

    int console_width = 80;
    item_tracker::CliParser parser("ItemTracker");
    parser.AddOption<int>("--width", console_width, "Console width", false);

    // Expect function to return EXIT_FAILURE
    EXPECT_EQ(parser.Parse(2, argv), EXIT_FAILURE);
}

/**
 * @brief Tests that the CLI parser returns `EXIT_FAILURE` when a required option is missing.
 */
TEST(CliParserTest, MissingRequiredOption) {
    const char* argv[] = { "ItemTrackerExe" };  // No arguments provided

    std::string input_file;
    item_tracker::CliParser parser("ItemTracker");
    parser.AddOption<std::string>("-i", input_file, "Input file", true);

    // Expect function to return EXIT_FAILURE
    EXPECT_EQ(parser.Parse(1, argv), EXIT_FAILURE);
}

/**
 * @brief Tests that the CLI parser returns `EXIT_FAILURE` when an unknown argument is provided.
 */
TEST(CliParserTest, UnknownArgument) {
    const char* argv[] = { "ItemTrackerExe", "--unknown" };  // Unsupported argument

    item_tracker::CliParser parser("ItemTracker");

    // Expect function to return EXIT_FAILURE
    EXPECT_EQ(parser.Parse(2, argv), EXIT_FAILURE);
}
