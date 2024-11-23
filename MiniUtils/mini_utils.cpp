// MiniUtils.cpp : Defines the functions for the static library.
#include "framework.h"
#include "pch.h"

#include "mini_utils.h"

#include <string>
#include <functional>
#include <iostream>
#include <iomanip>
#include <sstream>


namespace mini_utils {
using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::string;

// StringFormatter

// Private

StringFormatter::StringMetrics StringFormatter::calculateStringMetrics(
    const string& label) const {
  const int minPadding = 2;                      // Borders (e.g., "*TEXT*")
  const int usableWidth = m_width - minPadding;  // Max text size
  const int labelLength = static_cast<int>(label.length());
  return {usableWidth, labelLength};
}

// Truncates the label to fit within a given width, appending "..." if
// necessary.
string StringFormatter::truncateLabel(const string& label,
                                           int maxWidth) const {
  if (static_cast<int>(label.length()) > maxWidth) {
    return label.substr(0, maxWidth - 3) + "...";
  }
  return label;
}

// Builds a formatted string with space padding between the borders and the
// label.
string StringFormatter::buildFormattedString(const string& label,
                                                  int leftPadding,
                                                  int rightPadding,
                                                  char borderChar) const {
  return string(1, borderChar) + string(leftPadding, ' ') + label +
         string(rightPadding, ' ') + string(1, borderChar);
}

// Builds a formatted string with border characters around the label,
// and spaces between the label and the borders.
string StringFormatter::buildFullBorderFormattedString(
    const string& label, int leftPadding, int rightPadding,
    char borderChar) const {
  return string(leftPadding, borderChar) + " " + label + " " +
         string(rightPadding, borderChar);
}

void clearInput() {
  cin.clear();  // Reset the error flags on std::cin
  cin.ignore(std::numeric_limits<std::streamsize>::max(),
             '\n');  // Discard invalid input in the buffer
}

// Public

StringFormatter::StringFormatter(int width) : m_width(width) {}

string StringFormatter::horizontalSeparator(char borderChar) const {
  return string(m_width, borderChar);
}

string StringFormatter::horizontalSeparatorWithSides(char separatorChar,
                                                     char sideChar) const {
  return sideChar + string(m_width - 2, separatorChar) + sideChar;
}

string StringFormatter::buildCentered(
    const string& label, const char& borderChar,
    string (StringFormatter::*formatBuilder)(const string&, int, int,
                                                  char) const) const {
  auto [usableWidth, labelLength] = calculateStringMetrics(label);
  string truncatedLabel = truncateLabel(label, usableWidth);

  int totalPadding = std::max(0, usableWidth - labelLength);
  int leftPadding = totalPadding / 2;
  int rightPadding = totalPadding - leftPadding;

  return (this->*formatBuilder)(truncatedLabel, leftPadding, rightPadding,
                                borderChar);
}

string StringFormatter::formatCentered(const string& label,
                                            const char& borderChar) const {
  return buildCentered(label, borderChar,
                      &StringFormatter::buildFormattedString);
}

string StringFormatter::formatFullBorder(const string& label,
                                              const char& borderChar) const {
  return buildCentered(label, borderChar,
                      &StringFormatter::buildFullBorderFormattedString);
}

string StringFormatter::formatSideBorder(const string& label,
                                         const char& border_char) const {
  auto [usableWidth, labelLength] = calculateStringMetrics(label);
  string truncatedLabel = truncateLabel(label, usableWidth);
  int spaces =
      std::max(0, usableWidth - labelLength - 1);  // subtract left padding

  return buildFormattedString(truncatedLabel, spaces > 0 ? 1 : 0, spaces,
                              border_char);
}

string StringFormatter::toStringWithPrecision(double value, int precision) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(precision) << value;
  return oss.str();
}


// Table Formatter
// Public

TableFormatter::TableFormatter(int width) : m_width(width) {}

bool TableFormatter::setColumnWidths(const vector<int>& widths) {
  int sum = 0;
  for (auto width : widths) {
    sum += width;
  }
  if (sum > m_width) {
    return false;
  }
  m_col_widths = widths;
  return true;
}

void TableFormatter::setHeaders(const vector<string>& headers) {
  m_headers = headers;
}

void TableFormatter::addRow(const vector<string>& row) {
  m_rows.push_back(row);
}

void TableFormatter::clearRows() {
  m_rows.clear();
}

string TableFormatter::render() const {
  string result;
  string border = "+";
  bool isFirstWidth = true;
  for (int width : m_col_widths) {
    int adjustedWidth = isFirstWidth ? width : width - 2;
    isFirstWidth = false;

    border += string(adjustedWidth, '-') + "+";
  }
  border += "\n";

  // Add headers
  result += border;
  if (!m_headers.empty()) {
    result += formatRow(m_headers) + "\n";
    result += border;
  }

  // Add rows
  for (const auto& row : m_rows) {
    result += formatRow(row) + "\n";
  }
  result += border;

  return result;
}

// Private

string TableFormatter::truncateString(const string& str, int width) const {
  if (static_cast<int>(str.length()) > width) {
    return str.substr(0, width - 3) + "...";
  }
  return str;
}

string TableFormatter::formatRow(const vector<string>& row) const {
  string result = "|";
  bool isFirstWidth = true;
  for (size_t i = 0; i < row.size(); ++i) {
    int width = m_col_widths[i];
    int adjustedWidth = isFirstWidth ? width - 2 : width - 4;
    isFirstWidth = false;

    string cell = truncateString(row[i], adjustedWidth);
    result += " " + cell + string(adjustedWidth - cell.length(), ' ') + " |";
  }
  return result;
}

// Checks whether provided value is a positive real number
bool isPositiveRealNum(double number) {
  return std::isnormal(number) && number > 0;
}

string trim(const string& str) {
  const auto start = str.find_first_not_of(" \t\n\r");
  if (start == std::string::npos) return "";  // String is all whitespace

  const auto end = str.find_last_not_of(" \t\n\r");
  return str.substr(start, end - start + 1);
}

}  // namespace mini_utils
