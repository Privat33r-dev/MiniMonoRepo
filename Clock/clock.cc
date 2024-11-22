#include "clock.h"

#include <iostream>

#include "mini_utils.h"

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
    cout << kClockSeparator << border;
  }
  cout << endl;
}

void Clock::displayTime() {
  printStyledBorder(true);

  cout << m_formatter.formatCentered("12-Hour Clock") << kClockSeparator
       << m_formatter.formatCentered("24-Hour Clock") << endl;

  cout << m_formatter.formatCentered(getFormattedTime(false)) << kClockSeparator
       << m_formatter.formatCentered(getFormattedTime(true)) << endl;

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
  // Declare temporary variables for user input of hours, minutes, and seconds
  unsigned short userInputHours, userInputMinutes, userInputSeconds;

  string timeInput = mini_utils::getValidatedInput<string>(
      "Enter time in the (24 hour) format hh:mm:ss: ",
      [&userInputHours, &userInputMinutes,
       &userInputSeconds](const string& input) {
        char colon1, colon2;
        std::stringstream inputStream(input);

        // Validate the input format and range of hours, minutes, and seconds
        if (inputStream >> userInputHours >> colon1 >> userInputMinutes >>
                colon2 >> userInputSeconds &&
            colon1 == ':' && colon2 == ':' && userInputHours >= 0 &&
            userInputHours < 24 && userInputMinutes >= 0 &&
            userInputMinutes < 60 && userInputSeconds >= 0 &&
            userInputSeconds < 60) {
          return true;  // Validation successful
        }
        return false;  // Validation failed
      });

  // Assign validated values to class member variables representing time
  m_hours = userInputHours;
  m_minutes = userInputMinutes;
  m_seconds = userInputSeconds;
}

string Clock::getFormattedTime(bool is24HoursFormat) const {
  std::ostringstream oss;

  string period = "";
  if (!is24HoursFormat) {
    period = m_hours >= 12 ? " PM" : " AM";
  }
  unsigned short formattedHours = is24HoursFormat ? m_hours : m_hours % 12;
  // 12 AM/PM instead of 0 to conform to standards
  if (formattedHours == 0 && !is24HoursFormat) formattedHours = 12;

  oss << setfill('0') << setw(2) << formattedHours << ":" << setw(2)
      << m_minutes << ":" << setw(2) << m_seconds << period;

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
      cout << m_formatter.formatSideBorder("Exiting program...") << endl;
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
