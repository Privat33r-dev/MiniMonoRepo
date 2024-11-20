// MiniUtils.cpp : Defines the functions for the static library.
#include "framework.h"
#include "pch.h"

#include "mini_utils.h"

#include <string>
#include <functional>
#include <iostream>


namespace mini_utils {
using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::string;

// StringFormatter

// Private

StringFormatter::StringMetrics StringFormatter::CalculateStringMetrics(
    const std::string& label) const {
  const int min_padding = 2;                       // Borders (e.g., "*TEXT*")
  const int usable_width = m_width - min_padding;  // Max text size
  const int label_length = static_cast<int>(label.length());
  return {usable_width, label_length};
}

std::string StringFormatter::BuildFormattedString(const std::string& label,
                                                  int left_padding,
                                                  int right_padding,
                                                  char border_char) const {
  return std::string(1, border_char) + std::string(left_padding, ' ') + label +
         std::string(right_padding, ' ') + std::string(1, border_char);
}

std::string StringFormatter::ProcessLabelWithTruncation(
    const std::string& label, int left_padding, int right_padding,
    char border_char) const {
  const int usable_width = m_width - 2;  // Space for the label minus borders
  std::string truncated_label = label;

  // If the label is too long, truncate it and append "..."
  if (static_cast<int>(label.length()) > usable_width) {
    truncated_label = label.substr(0, usable_width - 3) + "...";
  }

  // Build the formatted string with the truncated label
  return BuildFormattedString(truncated_label, left_padding, right_padding,
                              border_char);
}

void ClearInput() {
  cin.clear();  // Reset the error flags on std::cin
  cin.ignore(std::numeric_limits<std::streamsize>::max(),
             '\n');  // Discard invalid input in the buffer
}

// Public

StringFormatter::StringFormatter() : m_width(0) {}
StringFormatter::StringFormatter(int width) : m_width(width) {}

string StringFormatter::FormatCentered(const std::string& label,
                                       const char& border_char) const {
  auto [usable_width, label_length] = CalculateStringMetrics(label);

  int total_padding = max(0, usable_width - label_length);
  int left_padding = total_padding / 2;
  int right_padding = total_padding - left_padding;

  return ProcessLabelWithTruncation(label, left_padding, right_padding,
                                    border_char);
}

std::string StringFormatter::FormatFullBorder(const std::string& label,
                                              const char& border_char) const {
  return ProcessLabelWithTruncation(label, 1, 1, border_char);
}

string StringFormatter::FormatSideBorder(const string& label,
                                         const char& border_char) {
  const int min_padding = 2;                       // borders, e.g. "*TEXT*"
  const int usable_width = m_width - min_padding;  // Max text size
  const int label_length = static_cast<int>(label.length());

  int labelLength = static_cast<int>(label.length());
  int spaces = std::max(0, usable_width - labelLength);

  // Construct the label with a left border, label, spaces, and a right border
  return ProcessLabelWithTruncation(label, spaces > 0 ? 1 : 0, spaces,
                                    border_char);
}


// Table Formatter
// Public

TableFormatter::TableFormatter(int width) : m_width(width) {}

void TableFormatter::SetColumnWidths(const vector<int>& widths) {
  m_col_widths = widths;
}

void TableFormatter::SetHeaders(const vector<string>& headers) {
  m_headers = headers;
}

void TableFormatter::AddRow(const vector<string>& row) {
  m_rows.push_back(row);
}

string TableFormatter::Render() const {
  string result;
  string border = "+";
  for (int width : m_col_widths) {
    border += string(width + 2, '-') + "+";
  }
  border += "\n";

  // Add headers
  result += border;
  if (!m_headers.empty()) {
    result += FormatRow(m_headers) + "\n";
    result += border;
  }

  // Add rows
  for (const auto& row : m_rows) {
    result += FormatRow(row) + "\n";
  }
  result += border;

  return result;
}

// Private

string TableFormatter::TruncateString(const string& str, int width) const {
  if (static_cast<int>(str.length()) > width) {
    return str.substr(0, width - 3) + "...";
  }
  return str;
}

string TableFormatter::FormatRow(const vector<string>& row) const {
  string result = "|";
  for (size_t i = 0; i < row.size(); ++i) {
    int col_width = m_col_widths[i];
    string cell = TruncateString(row[i], col_width);
    result += " " + cell + string(col_width - cell.length(), ' ') + " |";
  }
  return result;
}

}  // namespace mini_utils