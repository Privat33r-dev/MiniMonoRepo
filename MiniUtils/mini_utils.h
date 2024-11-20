#ifndef MINI_UTILS_H
#define MINI_UTILS_H

#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace mini_utils {
using std::string;
using std::vector;

class StringFormatter {
 public:
  StringFormatter();
  StringFormatter(int width);

  // Format a label centered within the width, with customizable border.
  // Example: "*     SOME TEXT     *"
  string FormatCentered(const string& label,
                        const char& border_char = '*') const;

  // Format a label with a fixed one-space padding: "***** TEXT *****".
  string FormatFullBorder(const string& label,
                          const char& border_char = '*') const;

  // Format the label with a fixed one-space padding on the left: "* TEXT     *"
  string FormatSideBorder(const string& label, const char& border_char = '*');

 private:
  // Width within which the text is rendered
  int m_width;

  // Helper to construct a formatted string with padding and border.
  string BuildFormattedString(const string& label, int left_padding,
                              int right_padding, char border_char) const;

  // Recursive function to handle truncation and printing.
  string ProcessLabelWithTruncation(const string& label, int left_padding,
                                   int right_padding, char border_char) const;

  struct StringMetrics {
    int usable_width;
    int label_length;
  };

  StringMetrics CalculateStringMetrics(const std::string& label) const;
};

// Clear the input buffer in case of invalid input,
// ensuring that subsequent input operations are not affected.
void ClearInput();

// Get validated input from user using provided validator
template <typename T>
T GetValidatedInput(const string& prompt, std::function<bool(T)> validator) {
  T input;
  while (true) {
    std::cout << prompt;
    std::cin >> input;

    // Check if input is valid
    if (std::cin.fail()) {
      ClearInput();
      std::cout << "Invalid input. Please try again." << std::endl;
    } else if (validator(input)) {
      break;  // Input is valid and passes the validator function
    } else {
      std::cout << "Input does not meet the criteria. Please try again."
                << std::endl;
    }
  }
  return input;
}


class TableFormatter {
 public:
  TableFormatter(int width);
  // Mind that minimal terminal size in columns: 80
  void SetColumnWidths(const vector<int>& widths);
  void SetHeaders(const vector<string>& headers);

  // Add a row to the table
  void AddRow(const vector<string>& row);

  // Render the entire table as a formatted string
  string Render() const;

 private:
  int m_width;                    // Total table width
  vector<int> m_col_widths;       // Column widths
  vector<string> m_headers;       // Optional headers
  vector<vector<string>> m_rows;  // Rows of data

  // Helper: format a single row as a string
  string FormatRow(const vector<string>& row) const;

  // Helper: truncate a string if it exceeds the width
  string TruncateString(const string& str, int width) const;
};

}  // namespace mini_utils
#endif  // MINI_UTILS_H