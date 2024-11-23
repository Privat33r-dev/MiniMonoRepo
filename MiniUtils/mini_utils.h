#ifndef MINI_UTILS_H
#define MINI_UTILS_H

#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace mini_utils {
using std::string;
using std::vector;

// TODO: formatter standard class
// setWidth, width_, truncate

class StringFormatter {
 public:
  StringFormatter(int width);
  string horizontalSeparator(char borderChar = '*') const;
  string horizontalSeparatorWithSides(char separatorChar = '*',
                                      char sideChar = '|') const;

  // Format a label centered within the width, with customizable border.
  // Example: "*     SOME TEXT     *"
  string formatCentered(const string& label,
                        const char& border_char = '*') const;

  // Format a label with a fixed one-space padding: "***** TEXT *****".
  string formatFullBorder(const string& label,
                          const char& border_char = '*') const;

  // Format the label with a fixed one-space padding on the left: "* TEXT     *"
  string formatSideBorder(const string& label,
                          const char& border_char = '*') const;

  // Format double to string with precision
  string toStringWithPrecision(double value, int precision = 2);

 private:
  // Width within which the text is rendered
  int m_width;

  // Helper to construct a formatted string with padding and border.
  string buildFormattedString(const string& label, int leftPadding,
                                   int rightPadding, char borderChar) const;

  string buildFullBorderFormattedString(const string& label,
                                             int leftPadding, int rightPadding,
                                             char borderChar) const;


  string buildCentered(const string& label, const char& borderChar,
                             string (StringFormatter::*formatBuilder)(
                                 const string&, int, int, char) const) const;

  string truncateLabel(const string& label,
                                        int maxWidth) const;

  struct StringMetrics {
    int usable_width;
    int label_length;
  };

  StringMetrics calculateStringMetrics(const string& label) const;
};

// Clear the input buffer in case of invalid input,
// ensuring that subsequent input operations are not affected.
void clearInput();

// Get validated input from user using provided validator
// The `criteriaDescription` parameter should describe the validation criteria
// (e.g. "positive integer"). It's used in error messages when validation fails.
template <typename T>
T getValidatedInput(const string& prompt, std::function<bool(T)> validator,
                    const string& criteriaDescription = "value") {
  T input;
  while (true) {
    std::cout << prompt;
    std::cin >> input;

    // Check if input is valid
    if (std::cin.fail()) {
      clearInput();
      std::cout << "Invalid input. Please enter a valid " << criteriaDescription
                << "." << std::endl;
      continue;
    }

    // Check if there are extra characters (like "1 2 3")
    if (std::cin.peek() != '\n') {
      clearInput();
      std::cout << "Only one value is allowed. Please enter a valid "
                << criteriaDescription << "." << std::endl;
      continue;
    }

    // Check if input meets custom criteria
    if (!validator(input)) {
      clearInput();
      std::cout << "Input is out of the accepted range or format. Please enter "
                   "a valid "
                << criteriaDescription << "." << std::endl;
      continue;
    }

    break;  // Input is valid and passes the validator function
  }
  return input;
}


class TableFormatter {
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
  int m_width;                    // Total table width
  vector<int> m_col_widths;       // Column widths
  vector<string> m_headers;       // Optional headers
  vector<vector<string>> m_rows;  // Rows of data

  // Helper: format a single row as a string
  string formatRow(const vector<string>& row) const;

  // Helper: truncate a string if it exceeds the width
  string truncateString(const string& str, int width) const;
};

// Checks whether provided value is a positive real number
bool isPositiveRealNum(double number);

// Trims leading and trailing whitespace from a string
string trim(const string& str);

}  // namespace mini_utils
#endif  // MINI_UTILS_H