#include "clock.h"

#include <iomanip>

#include "mini_utils.h"

namespace clock_cli {
using std::cin;
using std::cout;
using std::endl;
using std::setfill;
using std::setw;
using std::string;

using mini_utils::StringFormatter;

void Clock::printStyledBorder(bool doubleBorder) {
  string border(m_width, '*');
  cout << border;
  if (doubleBorder) {
    cout << CLOCK_SEPARATOR << border;
  }
  cout << endl;
}

void Clock::displayTime() {
  printStyledBorder(true);

  cout << m_formatter.formatCentered("12-Hour Clock") << CLOCK_SEPARATOR
       << m_formatter.formatCentered("24-Hour Clock") << endl;

  cout << m_formatter.formatCentered(getFormattedTime12Hours())
       << CLOCK_SEPARATOR
       << m_formatter.formatCentered(getFormattedTime24Hours()) << endl;

  printStyledBorder(true);
}

// TODO: check whether the formatter is leaking
// Maybe even make a dependency injection for formatter
Clock::Clock() : m_hours(0), m_minutes(0), m_seconds(0), m_formatter(m_width) {}

Clock::Clock(int hours, int minutes, int seconds)
    : m_hours(hours),
      m_minutes(minutes),
      m_seconds(seconds),
      m_formatter(m_width) {}

void Clock::displayMenu() {
  printStyledBorder();
  cout << m_formatter.formatSideBorder("1 - Add One Hour") << endl
       << m_formatter.formatSideBorder("2 - Add One Minute") << endl
       << m_formatter.formatSideBorder("3 - Add One Second") << endl
       << m_formatter.formatSideBorder("4 - Exit Program") << endl;
  printStyledBorder();
}

void Clock::getTimeFromUser() {
  std::cout << "Please enter time in 24-hour format:" << std::endl;

  // Collect input from user
  m_hours = mini_utils::getValidatedInput<int>(
      "Hours: ",
      [](const int& HOURS_INPUT) {
        return HOURS_INPUT >= 0 && HOURS_INPUT <= 23;
      },
      "integer in range from 0 to 23");

  m_minutes = mini_utils::getValidatedInput<int>(
      "Minutes: ",
      [](const int& MINUTES_INPUT) {
        return MINUTES_INPUT >= 0 && MINUTES_INPUT <= 59;
      },
      "integer in range from 0 to 59");

  m_seconds = mini_utils::getValidatedInput<int>(
      "Seconds: ",
      [](const int& SECONDS_INPUT) {
        return SECONDS_INPUT >= 0 && SECONDS_INPUT <= 59;
      },
      "integer in range from 0 to 59");
}

string Clock::getFormattedTime24Hours() const {
  return formatTime(m_hours, "", m_minutes, m_seconds);
}

string Clock::getFormattedTime12Hours() const {
  unsigned short formattedHours = (m_hours % 12 == 0) ? 12 : m_hours % 12;
  string period = (m_hours >= 12) ? " PM" : " AM";
  return formatTime(formattedHours, period, m_minutes, m_seconds);
}

string Clock::formatTime(unsigned short hours, const string& PERIOD,
                         unsigned short minutes, unsigned short seconds) const {
  std::ostringstream oss;
  oss << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2)
      << minutes << ":" << std::setw(2) << seconds << PERIOD;
  return oss.str();
}

bool Clock::execInstructionFromUser() {
  int choice = mini_utils::getValidatedInput<int>(
      "Enter your choice: ",
      [](int input) { return input >= 1 && input <= 4; });
  switch (choice) {
    case 1:
      addOneHour();
      displayTime();
      break;
    case 2:
      addOneMinute();
      displayTime();
      break;
    case 3:
      addOneSecond();
      displayTime();
      break;
    case 4:
      cout << m_formatter.formatSideBorder("Exiting program...");
      return false;
  }
  return true;
}

void Clock::addOneSecond() {
  ++m_seconds;
  adjustTime();
}

void Clock::addOneMinute() {
  ++m_minutes;
  adjustTime();
}

void Clock::addOneHour() {
  ++m_hours;
  adjustTime();
}

void Clock::adjustTime() {
  // Helper lambda to adjust time units
  auto adjustUnit = [](unsigned short& unit, unsigned short maxLimit) {
    if (unit >= maxLimit) {
      unsigned short overflow = unit / maxLimit;
      unit %= maxLimit;
      return overflow;
    }
    return (unsigned short)0;
  };

  // Adjust seconds, minutes, and hours
  m_minutes += adjustUnit(m_seconds, 60);  // Adjust seconds to minutes
  m_hours += adjustUnit(m_minutes, 60);    // Adjust minutes to hours
  adjustUnit(m_hours, 24);                 // Adjust hours to 24-hour format
}

void Clock::startCli() {
  getTimeFromUser();
  do {
    displayMenu();
  } while (execInstructionFromUser());
}
}  // namespace clock_cli