#ifndef MINI_UTILS_H
#define MINI_UTILS_H

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace mini_utils {
using std::string;
using std::vector;

// Checks whether provided value is a positive real number
bool isPositiveRealNum(double number);

// Trims leading and trailing whitespace from a string
string trim(const string& STR);

class Formatter {
 public:
  Formatter(int width);
  void setWidth(int newWidth);

 protected:
  // Helper: truncate a string if it exceeds the width
  string truncateString(const string& STR, int width) const;

  // Width within which the text is rendered
  int m_width = 0;
};

class StringFormatter : public Formatter {
 public:
  StringFormatter(int width);
  string horizontalSeparator(const char BORDER_CHAR = '*') const;
  string horizontalSeparatorWithSides(const char SEPARATOR_CHAR = '*',
                                      const char SIDE_CHAR = '|') const;

  // Format a label centered within the width, with customizable border.
  // Example: "*     SOME TEXT     *"
  string formatCentered(const string& LABEL,
                        const char BORDER_CHAR = '*') const;

  // Format a label with a fixed one-space padding: "***** TEXT *****".
  string formatFullBorder(const string& LABEL,
                          const char BORDER_CHAR = '*') const;

  // Format the label with a fixed one-space padding on the left: "* TEXT     *"
  string formatSideBorder(const string& LABEL,
                          const char BORDER_CHAR = '*') const;

  // Format double to string with precision
  string toStringWithPrecision(double value, int precision = 2) const;

 private:
  // Helper to construct a formatted string with padding and border.
  string buildFormattedString(const string& LABEL, int leftPadding,
                              int rightPadding, char borderChar) const;

  string buildFullBorderFormattedString(const string& LABEL, int leftPadding,
                                        int rightPadding,
                                        char borderChar) const;

  string buildCentered(const string& LABEL, const char BORDER_CHAR,
                       string (StringFormatter::*formatBuilder)(const string&,
                                                                int, int, char)
                           const) const;

  struct StringMetrics {
    int usableWidth;
    int labelLength;
  };

  StringMetrics calculateStringMetrics(const string& LABEL) const;
};

// Clear the input buffer in case of invalid input,
// ensuring that subsequent input operations are not affected.
void clearInput();

// Prompts the user to input a value, validates it, and ensures it meets
// specified criteria.
//
// T:
//   The expected input type (e.g., int, double, string).
// PROMPT:
//   Message to display when asking for input.
// validator:
//   A function that checks if the input meets specific conditions.
// criteriaDescription:
//   A short explanation of the validation criteria for error messages.
// strictMode:
//   If true, disallows extra characters after the expected input. Defaults to
//   false.
// preprocess:
//   A function that preprocesses the input string before parsing. Defaults to
//   trim.
template <typename T>
T getValidatedInput(
    const string& PROMPT, std::function<bool(T)> validator,
    const string& CRITERIA_DESCRIPTION = "value", bool strictMode = false,
    std::function<std::string(const std::string&)> preprocess = trim) {
  T input;
  bool isInputValid = false;

  do {
    std::cout << PROMPT;
    string rawInput = "";
    getline(std::cin, rawInput);

    // Preprocess input, e.g. trim spaces
    rawInput = preprocess(rawInput);

    // Attempt to convert input to the desired type
    std::stringstream inputStream(rawInput);

    // Attempt to extract the input
    if (!(inputStream >> input)) {
      std::cout << "Invalid input. Please enter a valid "
                << CRITERIA_DESCRIPTION
                << "." << std::endl;
      continue;
    }

    // Check if input meets custom criteria
    if (!validator(input)) {
      std::cout << "Input is out of the accepted range or format. Please enter "
                   "a valid "
                << CRITERIA_DESCRIPTION << "." << std::endl;
      continue;
    }

    // In strict mode, ensure there are no unexpected characters after the input
    char extraChar;
    if (strictMode && inputStream >> extraChar) {
      std::cout << "Unexpected characters found. Please enter a valid "
                << CRITERIA_DESCRIPTION << "." << std::endl;
      continue;
    }

    isInputValid = true;  // Input is valid and passes the validator function
  } while (!isInputValid);

  return input;
}

class TableFormatter : public Formatter {
 public:
  TableFormatter(int width);
  // Mind that minimal terminal size in columns: 80
  bool setColumnWidths(const vector<int>& WIDTHS);
  void setHeaders(const vector<string>& HEADERS);

  // Add a row to the table
  void addRow(const vector<string>& ROW);

  // Clear all rows
  void clearRows();

  // Render the entire table as a formatted string
  string render() const;

 private:
  vector<int> m_col_widths;       // Column widths
  vector<string> m_headers;       // Optional headers
  vector<vector<string>> m_rows;  // Rows of data

  // Helper: format a single row as a string
  string formatRow(const vector<string>& ROW) const;
};

}  // namespace mini_utils
#endif  // MINI_UTILS_H