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
  const int minPadding = 2;                      // Borders (e.g., "*TEXT*")
  const int usableWidth = m_width - minPadding;  // Max text size
  const int labelLength = static_cast<int>(label.length());
  return {usableWidth, labelLength};
}

// Truncates the label to fit within a given width, appending "..." if
// necessary.
std::string StringFormatter::TruncateLabel(const std::string& label,
                                           int maxWidth) const {
  if (static_cast<int>(label.length()) > maxWidth) {
    return label.substr(0, maxWidth - 3) + "...";
  }
  return label;
}

// Builds a formatted string with space padding between the borders and the
// label.
std::string StringFormatter::BuildFormattedString(const std::string& label,
                                                  int leftPadding,
                                                  int rightPadding,
                                                  char borderChar) const {
  return std::string(1, borderChar) + std::string(leftPadding, ' ') + label +
         std::string(rightPadding, ' ') + std::string(1, borderChar);
}

// Builds a formatted string with border characters around the label,
// and spaces between the label and the borders.
std::string StringFormatter::BuildFullBorderFormattedString(
    const std::string& label, int leftPadding, int rightPadding,
    char borderChar) const {
  return std::string(leftPadding, borderChar) + " " + label + " " +
         std::string(rightPadding, borderChar);
}

void ClearInput() {
  cin.clear();  // Reset the error flags on std::cin
  cin.ignore(std::numeric_limits<std::streamsize>::max(),
             '\n');  // Discard invalid input in the buffer
}

// Public

StringFormatter::StringFormatter(int width) : m_width(width) {}

string StringFormatter::HorizontalSeparator(char borderChar) {
  return string(m_width, borderChar);
}

string StringFormatter::FormatCentered(const std::string& label,
                                       const char& borderChar) const {
  auto [usableWidth, labelLength] = CalculateStringMetrics(label);
  string truncatedLabel = TruncateLabel(label, usableWidth);

  int totalPadding = max(0, usableWidth - labelLength);
  int leftPadding = totalPadding / 2;
  int rightPadding = totalPadding - leftPadding;
  return BuildFormattedString(truncatedLabel, leftPadding, rightPadding,
                              borderChar);
}

std::string StringFormatter::FormatFullBorder(const std::string& label,
                                              const char& borderChar) const {
  auto [usableWidth, labelLength] = CalculateStringMetrics(label);
  string truncatedLabel = TruncateLabel(label, usableWidth);

  int totalPadding = max(0, usableWidth - labelLength);
  int leftPadding = totalPadding / 2;
  int rightPadding = totalPadding - leftPadding;
  return BuildFullBorderFormattedString(truncatedLabel, leftPadding,
                                        rightPadding, borderChar);
}

string StringFormatter::FormatSideBorder(const string& label,
                                         const char& border_char) {
  auto [usableWidth, labelLength] = CalculateStringMetrics(label);
  string truncatedLabel = TruncateLabel(label, usableWidth);
  int spaces =
      std::max(0, usableWidth - labelLength - 1);  // subtract left padding

  return BuildFormattedString(truncatedLabel, spaces > 0 ? 1 : 0, spaces,
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
