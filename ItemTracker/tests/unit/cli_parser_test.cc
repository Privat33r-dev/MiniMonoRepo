#include "cli_parser.h"
#include <gtest/gtest.h>

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
    parser.Parse(1, argv);

    // Ensure default values remain unchanged
    EXPECT_EQ(input_file, "input.txt");
    EXPECT_EQ(output_file, "frequency.dat");
    EXPECT_EQ(console_width, 80);
}

/**
 * @brief Tests whether the CLI parser correctly updates the input file
 *        when a custom input file argument is provided.
 */
TEST(CliParserTest, ParseCustomInput) {
    const char* argv[] = { "ItemTrackerExe", "-i", "data.txt" };

    std::string input_file = "input.txt";  // Default value
    item_tracker::CliParser parser("ItemTracker");
    parser.AddOption<std::string>("-i", input_file, "Input file", false);
    parser.Parse(3, argv);

    // Ensure input file is updated
    EXPECT_EQ(input_file, "data.txt");
}

/**
 * @brief Tests whether the CLI parser correctly updates the output file
 *        when the '-o' argument is provided.
 */
TEST(CliParserTest, ParseOutputFile) {
    const char* argv[] = { "ItemTrackerExe", "-o", "results.dat" };

    std::string output_file = "frequency.dat";  // Default value
    item_tracker::CliParser parser("ItemTracker");
    parser.AddOption<std::string>("-o", output_file, "Output file", false);
    parser.Parse(3, argv);

    // Ensure output file is updated
    EXPECT_EQ(output_file, "results.dat");
}

/**
 * @brief Tests whether the CLI parser correctly updates the console width
 *        when the '--width' argument is provided.
 */
TEST(CliParserTest, ParseConsoleWidth) {
    const char* argv[] = { "ItemTrackerExe", "--width", "100" };

    int console_width = 80;  // Default value
    item_tracker::CliParser parser("ItemTracker");
    parser.AddOption<int>("--width", console_width, "Console width", false);
    parser.Parse(3, argv);

    // Ensure console width is updated
    EXPECT_EQ(console_width, 100);
}

/**
 * @brief Tests that the CLI parser exits with an error when an option is missing
 *        its required value.
 */
TEST(CliParserTest, MissingOptionValue) {
    const char* argv[] = { "ItemTrackerExe", "--width" };  // '--width' requires a value

    int console_width = 80;
    item_tracker::CliParser parser("ItemTracker");
    parser.AddOption<int>("--width", console_width, "Console width", false);

    // Expect the program to exit with code 1 due to missing value
    EXPECT_EXIT(parser.Parse(2, argv), ::testing::ExitedWithCode(1), "Error: Missing value for option --width");
}

/**
 * @brief Tests that the CLI parser exits with an error when a required option is missing.
 */
TEST(CliParserTest, MissingRequiredOption) {
    const char* argv[] = { "ItemTrackerExe" };  // No arguments provided

    std::string input_file;
    item_tracker::CliParser parser("ItemTracker");
    parser.AddOption<std::string>("-i", input_file, "Input file", true);

    // Expect exit due to missing required option
    EXPECT_EXIT(parser.Parse(1, argv), ::testing::ExitedWithCode(1), "Error: Missing required option -i");
}

/**
 * @brief Tests that the CLI parser exits with an error when an unknown argument is provided.
 */
TEST(CliParserTest, UnknownArgument) {
    const char* argv[] = { "ItemTrackerExe", "--unknown" };  // Unsupported argument

    item_tracker::CliParser parser("ItemTracker");

    // Expect the program to exit with code 1 due to unrecognized argument
    EXPECT_EXIT(parser.Parse(2, argv), ::testing::ExitedWithCode(1), "Error: Unknown argument '--unknown'");
}
