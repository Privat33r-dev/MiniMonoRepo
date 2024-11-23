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
string trim(const string& str);

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
  string horizontalSeparator(char borderChar = '*') const;
  string horizontalSeparatorWithSides(char separatorChar = '*',
                                      char sideChar = '|') const;

  // Format a label centered within the width, with customizable border.
  // Example: "*     SOME TEXT     *"
  string formatCentered(const string& label,
                        const char& borderChar = '*') const;

  // Format a label with a fixed one-space padding: "***** TEXT *****".
  string formatFullBorder(const string& label,
                          const char& borderChar = '*') const;

  // Format the label with a fixed one-space padding on the left: "* TEXT     *"
  string formatSideBorder(const string& label,
                          const char& borderChar = '*') const;

  // Format double to string with precision
  string toStringWithPrecision(double value, int precision = 2);

 private:
  // Helper to construct a formatted string with padding and border.
  string buildFormattedString(const string& label, int leftPadding,
                              int rightPadding, char borderChar) const;

  string buildFullBorderFormattedString(const string& label, int leftPadding,
                                        int rightPadding,
                                        char borderChar) const;

  string buildCentered(const string& label, const char& borderChar,
                       string (StringFormatter::*formatBuilder)(const string&,
                                                                int, int, char)
                           const) const;

  string truncateLabel(const string& label, int maxWidth) const;

  struct StringMetrics {
    int usableWidth;
    int labelLength;
  };

  StringMetrics calculateStringMetrics(const string& label) const;
};

// Clear the input buffer in case of invalid input,
// ensuring that subsequent input operations are not affected.
void clearInput();

// Prompts the user to input a value, validates it, and ensures it meets
// specified criteria.
//
// T: The expected input type (e.g., int, double, string).
// prompt: Message to display when asking for input.
// validator: A function that checks if the input meets specific conditions.
// criteriaDescription: A short explanation of the validation criteria for error
// messages (default is "value").
// strictMode: If true, disallows extra characters after the expected input.
template <typename T>
T getValidatedInput(const string& prompt, std::function<bool(T)> validator,
                    const string& criteriaDescription = "value",
                    bool strictMode = false) {
  T input;
  bool isInputValid = false;

  do {
    std::cout << prompt;
    string rawInput = "";
    getline(std::cin, rawInput);

    // Trim raw input and attempt to convert to the desired type
    rawInput = trim(rawInput);
    std::stringstream inputStream(rawInput);

    // Attempt to extract the input
    if (!(inputStream >> input)) {
      std::cout << "Invalid input. Please enter a valid " << criteriaDescription
                << "." << std::endl;
      continue;
    }

    // Check if input meets custom criteria
    if (!validator(input)) {
      std::cout << "Input is out of the accepted range or format. Please enter "
                   "a valid "
                << criteriaDescription << "." << std::endl;
      continue;
    }

    // In strict mode, ensure there are no unexpected characters after the input
    char extraChar;
    if (strictMode && inputStream >> extraChar) {
      std::cout << "Unexpected characters found. Please enter a valid "
                << criteriaDescription << "." << std::endl;
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
  bool setColumnWidths(const vector<int>& widths);
  void setHeaders(const vector<string>& headers);

  // Add a row to the table
  void addRow(const vector<string>& row);

  // Clear all rows
  void clearRows();

  // Render the entire table as a formatted string
  string render() const;

 private:
  vector<int> m_col_widths;       // Column widths
  vector<string> m_headers;       // Optional headers
  vector<vector<string>> m_rows;  // Rows of data

  // Helper: format a single row as a string
  string formatRow(const vector<string>& row) const;
};

}  // namespace mini_utils
#endif  // MINI_UTILS_H