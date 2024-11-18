#include "pch.h"
#include "clock.h"

using std::cin;
using std::cout;
using std::endl;
using std::setfill;
using std::setw;
using std::string;

// See function descriptions in a header file

string Clock::FormatCenteredLabel(const string& label) {
  const int usableWidth = width - 2;  // Width without borders

  int labelLength = label.length();
  int spaces =
      std::max(0, usableWidth - labelLength);  // To ensure no negative padding

  int paddingLeft = spaces / 2;
  int paddingRight = spaces - paddingLeft;

  // Construct the formatted label with padding and borders
  string result =
      "*" + string(paddingLeft, ' ') + label + string(paddingRight, ' ') + "*";

  return result;
}

string Clock::FormatSimpleLabel(const string& label) {
  const int usableWidth = width - 3;  // Width without borders and left padding
  int labelLength = label.length();
  int spaces = std::max(0, usableWidth - labelLength);

  // Construct the label with a left border, label, spaces, and a right border
  return "* " + label + string(spaces, ' ') + "*";
}

void Clock::PrintStyledBorder(bool doubleBorder) {
  string border(width, '*');
  cout << border;
  if (doubleBorder) {
    cout << kClockSeparator << border;
  }
  cout << endl;
}

void Clock::DisplayTime() {
  PrintStyledBorder(true);

  cout << FormatCenteredLabel("12-Hour Clock") << kClockSeparator
       << FormatCenteredLabel("24-Hour Clock") << endl;

  cout << FormatCenteredLabel(GetFormattedTime(false)) << kClockSeparator
       << FormatCenteredLabel(GetFormattedTime(true)) << endl;

  PrintStyledBorder(true);
}

void Clock::ClearInput() {
  cin.clear();  // Reset the error flags on std::cin
  cin.ignore(std::numeric_limits<std::streamsize>::max(),
             '\n');  // Discard invalid input in the buffer
}

template <typename T>
T Clock::GetValidatedInput(const std::string& prompt,
                           std::function<bool(T)> validator) {
  T input;
  while (true) {
    cout << prompt;
    cin >> input;

    // Check if input is valid
    if (cin.fail()) {
      ClearInput();
      cout << "Invalid input. Please try again." << endl;
    } else if (validator(input)) {
      break;  // Input is valid and passes the validator function
    } else {
      cout << "Input does not meet the criteria. Please try again." << endl;
    }
  }
  return input;
}

Clock::Clock() : hours(0), minutes(0), seconds(0) {}

Clock::Clock(int hours, int minutes, int seconds)
    : hours(hours), minutes(minutes), seconds(seconds) {}

void Clock::DisplayMenu() {
  PrintStyledBorder();
  cout << FormatSimpleLabel("1 - Add One Hour") << endl
       << FormatSimpleLabel("2 - Add One Minute") << endl
       << FormatSimpleLabel("3 - Add One Second") << endl
       << FormatSimpleLabel("4 - Exit Program") << endl;
  PrintStyledBorder();
}

void Clock::GetTimeFromUser() {
  // Declare temporary variables for user input of hours, minutes, and seconds
  unsigned short userInputHours, userInputMinutes, userInputSeconds;

  string timeInput = GetValidatedInput<string>(
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
  hours = userInputHours;
  minutes = userInputMinutes;
  seconds = userInputSeconds;
}

string Clock::GetFormattedTime(bool is24HoursFormat) {
  std::ostringstream oss;

  string period = "";
  if (!is24HoursFormat) {
    period = hours >= 12 ? " PM" : " AM";
  }
  unsigned short formattedHours = is24HoursFormat ? hours : hours % 12;
  // 12 AM/PM instead of 0 to conform to standards
  if (formattedHours == 0 && !is24HoursFormat) formattedHours = 12;

  oss << setfill('0') << setw(2) << formattedHours << ":" << setw(2) << minutes
      << ":" << setw(2) << seconds << period;

  return oss.str();
}

bool Clock::ExecInstructionFromUser() {
  int choice = GetValidatedInput<int>("Enter your choice: ", [](int input) {
    return input >= 1 && input <= 4;
  });
  switch (choice) {
    case 1:
      AddOneHour();
      DisplayTime();
      break;
    case 2:
      AddOneMinute();
      DisplayTime();
      break;
    case 3:
      AddOneSecond();
      DisplayTime();
      break;
    case 4:
      cout << FormatSimpleLabel("Exiting program...") << endl;
      return false;
  }
  return true;
}

void Clock::AddOneSecond() {
  ++seconds;
  AdjustTime();
}

void Clock::AddOneMinute() {
  ++minutes;
  AdjustTime();
}

void Clock::AddOneHour() {
  ++hours;
  AdjustTime();
}

void Clock::AdjustTime() {
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
  minutes += adjustUnit(seconds, 60);  // Adjust seconds to minutes
  hours += adjustUnit(minutes, 60);    // Adjust minutes to hours
  adjustUnit(hours, 24);               // Adjust hours to 24-hour format
}

void Clock::StartCli() {
  GetTimeFromUser();
  do {
    DisplayMenu();
  } while (ExecInstructionFromUser());
}
