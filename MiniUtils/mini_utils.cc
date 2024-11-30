// MiniUtils.cpp : Defines the functions for the static library.
#include "mini_utils.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace mini_utils {
using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::string;

// Formatter
// Public
Formatter::Formatter(int width) : m_width(width) {}

// Protected
string Formatter::truncateString(const string& STR, int width) const {
  if (static_cast<int>(STR.length()) > width) {
    return STR.substr(0, width - 3) + "...";
  }
  return STR;
}

void Formatter::setWidth(int newWidth) { m_width = newWidth; }

// StringFormatter
// Private
StringFormatter::StringMetrics StringFormatter::calculateStringMetrics(
    const string& LABEL) const {
  const int MIN_PADDING = 2;                       // Borders (e.g., "*TEXT*")
  const int USABLE_WIDTH = m_width - MIN_PADDING;  // Max text size
  const int LABEL_LENGTH = static_cast<int>(LABEL.length());
  return {USABLE_WIDTH, LABEL_LENGTH};
}

// Builds a formatted string with space padding between the borders and the
// label.
// NOTE: here and after 'LABEL' uses uppercase as per assignment-specific style
// guidelines.
string StringFormatter::buildFormattedString(const string& LABEL,
                                             int leftPadding, int rightPadding,
                                             char borderChar) const {
  return string(1, borderChar) + string(leftPadding, ' ') + LABEL +
         string(rightPadding, ' ') + string(1, borderChar);
}

// Builds a formatted string with border characters around the label,
// and spaces between the label and the borders.
string StringFormatter::buildFullBorderFormattedString(const string& LABEL,
                                                       int leftPadding,
                                                       int rightPadding,
                                                       char borderChar) const {
  return string(leftPadding, borderChar) + " " + LABEL + " " +
         string(rightPadding, borderChar);
}

void clearInput() {
  cin.clear();  // Reset the error flags on std::cin
  cin.ignore(std::numeric_limits<std::streamsize>::max(),
             '\n');  // Discard invalid input in the buffer
}

// Public

StringFormatter::StringFormatter(int width) : Formatter(width) {}

string StringFormatter::horizontalSeparator(const char BORDER_CHAR) const {
  return string(m_width, BORDER_CHAR);
}

string StringFormatter::horizontalSeparatorWithSides(
    const char SEPARATOR_CHAR, const char SIDE_CHAR) const {
  return SIDE_CHAR + string(m_width - 2, SEPARATOR_CHAR) + SIDE_CHAR;
}

string StringFormatter::buildCentered(
    const string& LABEL, const char BORDER_CHAR,
    string (StringFormatter::*formatBuilder)(const string&, int, int, char)
        const) const {
  auto [usableWidth, labelLength] = calculateStringMetrics(LABEL);
  string truncatedLabel = truncateString(LABEL, usableWidth);

  const int TOTAL_PADDING = std::max(0, usableWidth - labelLength);
  const int LEFT_PADDING = TOTAL_PADDING / 2;
  const int RIGHT_PADDING = TOTAL_PADDING - LEFT_PADDING;

  return (this->*formatBuilder)(truncatedLabel, LEFT_PADDING, RIGHT_PADDING,
                                BORDER_CHAR);
}

string StringFormatter::formatCentered(const string& LABEL,
                                       const char BORDER_CHAR) const {
  return buildCentered(LABEL, BORDER_CHAR,
                       &StringFormatter::buildFormattedString);
}

string StringFormatter::formatFullBorder(const string& LABEL,
                                         const char BORDER_CHAR) const {
  return buildCentered(LABEL, BORDER_CHAR,
                       &StringFormatter::buildFullBorderFormattedString);
}

string StringFormatter::formatSideBorder(const string& LABEL,
                                         const char BORDER_CHAR) const {
  const auto [USABLE_WIDTH, LABEL_LENGTH] = calculateStringMetrics(LABEL);
  string truncatedLabel = truncateString(LABEL, USABLE_WIDTH);
  const int SPACES =
      std::max(0, USABLE_WIDTH - LABEL_LENGTH - 1);  // subtract left padding

  return buildFormattedString(truncatedLabel, SPACES > 0 ? 1 : 0, SPACES,
                              BORDER_CHAR);
}

string StringFormatter::toStringWithPrecision(double value,
                                              int precision) const {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(precision) << value;
  return oss.str();
}

// Table Formatter
// Public

TableFormatter::TableFormatter(int width) : Formatter(width) {}

bool TableFormatter::setColumnWidths(const vector<int>& WIDTHS) {
  int sum = 0;
  for (auto width : WIDTHS) {
    sum += width;
  }
  if (sum > m_width) {
    return false;
  }
  m_col_widths = WIDTHS;
  return true;
}

void TableFormatter::setHeaders(const vector<string>& HEADERS) {
  m_headers = HEADERS;
}

void TableFormatter::addRow(const vector<string>& ROW) {
  m_rows.push_back(ROW);
}

void TableFormatter::clearRows() { m_rows.clear(); }

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
  for (const auto& ROW : m_rows) {
    result += formatRow(ROW) + "\n";
  }
  result += border;

  return result;
}

// Private

string TableFormatter::formatRow(const vector<string>& ROW) const {
  string result = "|";
  bool isFirstWidth = true;
  for (size_t i = 0; i < ROW.size(); ++i) {
    int width = m_col_widths[i];
    int adjustedWidth = isFirstWidth ? width - 2 : width - 4;
    isFirstWidth = false;

    string cell = truncateString(ROW[i], adjustedWidth);
    result += " " + cell + string(adjustedWidth - cell.length(), ' ') + " |";
  }
  return result;
}

// Checks whether provided value is a positive real number
bool isPositiveRealNum(double number) {
  return std::isnormal(number) && number > 0;
}

string trim(const string& STR) {
  size_t first = 0;
  size_t last = STR.size();

  // Skip leading whitespaces
  while (first < last && std::isspace(STR.at(first))) {
    ++first;
  }

  // All characters are whitespace
  if (first == last) {
    return "";
  }

  // Skip trailing whitespaces
  while (last > first && std::isspace(STR.at(last - 1))) {
    --last;
  }

  // Return the trimmed substring,
  // always a new copy, even if string matches original,
  // to avoid unexpected behavior
  return STR.substr(first, last - first);
}

}  // namespace mini_utils
