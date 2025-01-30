#include "mini_utils.h"
#include <gtest/gtest.h>
#include <sstream>

using namespace mini_utils;

/**
 * @brief Tests for `isPositiveRealNum`
 */
TEST(IsPositiveRealNumTest, ValidPositiveNumbers) {
    EXPECT_TRUE(isPositiveRealNum(3.14));
    EXPECT_TRUE(isPositiveRealNum(0.00001));
}

TEST(IsPositiveRealNumTest, InvalidNumbers) {
    EXPECT_TRUE(isPositiveRealNum(0.000001));
    EXPECT_FALSE(isPositiveRealNum(0));
    EXPECT_FALSE(isPositiveRealNum(-5.5));
}

/**
 * @brief Tests for `trim`
 */
TEST(TrimTest, LeadingAndTrailingWhitespace) {
    EXPECT_EQ(trim("  hello  "), "hello");
    EXPECT_EQ(trim("\ttrim\t"), "trim");
}

TEST(TrimTest, NoWhitespace) {
    EXPECT_EQ(trim("text"), "text");
}

TEST(TrimTest, OnlyWhitespace) {
    EXPECT_EQ(trim("   "), "");
}

/**
 * @brief Tests for `StringFormatter`
 */
class StringFormatterTest : public ::testing::Test {
protected:
    StringFormatter formatter{20};
};

TEST_F(StringFormatterTest, HorizontalSeparator) {
    EXPECT_EQ(formatter.horizontalSeparator('-'), "--------------------");
}

TEST_F(StringFormatterTest, HorizontalSeparatorWithSides) {
    EXPECT_EQ(formatter.horizontalSeparatorWithSides('-', '|'), "|------------------|");
}

TEST_F(StringFormatterTest, FormatCentered) {
    EXPECT_EQ(formatter.formatCentered("Title", '*'), "*      Title       *");
}

TEST_F(StringFormatterTest, FormatFullBorder) {
    EXPECT_EQ(formatter.formatFullBorder("Header", '*'), "****** Header ******");
}

TEST_F(StringFormatterTest, FormatSideBorder) {
    EXPECT_EQ(formatter.formatSideBorder("Side", '|'), "| Side             |");
}

TEST_F(StringFormatterTest, ToStringWithPrecision) {
    EXPECT_EQ(formatter.toStringWithPrecision(3.14159, 2), "3.14");
    EXPECT_EQ(formatter.toStringWithPrecision(1234.5678, 4), "1234.5678");
}

/**
 * @brief Tests for `TableFormatter`
 */
class TableFormatterTest : public ::testing::Test {
protected:
    TableFormatter tableFormatter{30};
};

TEST_F(TableFormatterTest, SetColumnWidths_Valid) {
    EXPECT_TRUE(tableFormatter.setColumnWidths({10, 10, 10}));
}

TEST_F(TableFormatterTest, SetColumnWidths_TooWide) {
    EXPECT_FALSE(tableFormatter.setColumnWidths({15, 15, 10}));
}

TEST_F(TableFormatterTest, RenderTable_WithHeaders) {
    tableFormatter.setColumnWidths({10, 10, 10});
    tableFormatter.setHeaders({"Name", "Age", "City"});
    tableFormatter.addRow({"Alice", "30", "New York"});
    tableFormatter.addRow({"Bob", "25", "LA"});

    std::string expected_output =
        "+----------+--------+--------+\n"
        "| Name     | Age    | City   |\n"
        "+----------+--------+--------+\n"
        "| Alice    | 30     | New... |\n"
        "| Bob      | 25     | LA     |\n"
        "+----------+--------+--------+\n";

    EXPECT_EQ(tableFormatter.render(), expected_output);
}

TEST_F(TableFormatterTest, ClearRows) {
    tableFormatter.addRow({"Alice", "30", "New York"});
    tableFormatter.clearRows();
    EXPECT_EQ(tableFormatter.render(), "+\n+\n");
}

/**
 * @brief Tests for `clearInput`
 */
TEST(ClearInputTest, ClearBuffer) {
    std::istringstream input("123\n");
    std::cin.rdbuf(input.rdbuf());
    clearInput();
    EXPECT_FALSE(std::cin.fail());
}

/**
 * @brief Tests for `getValidatedInput`
 */
TEST(GetValidatedInputTest, ValidIntegerInput) {
    std::istringstream input("42\n");
    std::cin.rdbuf(input.rdbuf());

    int result = getValidatedInput<int>("Enter a number: ", [](int value) { return value > 0; });

    EXPECT_EQ(result, 42);
}

TEST(GetValidatedInputTest, InvalidIntegerInput) {
    std::istringstream input("abc\n42\n");
    std::cin.rdbuf(input.rdbuf());

    int result = getValidatedInput<int>("Enter a number: ", [](int value) { return value > 0; });

    EXPECT_EQ(result, 42);
}
