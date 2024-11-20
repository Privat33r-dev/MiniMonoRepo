#ifndef CLOCK_H
#define CLOCK_H
#include "mini_utils.h"

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using std::string;

class Clock {
 private:
  unsigned short int m_hours, m_minutes, m_seconds;
  unsigned short int m_width = 26;
  mini_utils::StringFormatter m_formatter;

  const string kClockSeparator = "    ";

  // Print border composed of start characters, optionally formatted for 2
  // clocks
  void PrintStyledBorder(bool doubleBorder = false);

  // Get formatted time in 12- and 24-hour formats
  string GetFormattedTime(bool is24HoursFormat) const;

  // Adjust the time by carrying over values. For example, if seconds >= 60,
  // they will be converted to minutes.
  void AdjustTime();

 public:
  Clock();
  Clock(int hours, int minutes, int seconds);

  // Display the time menu for user interaction
  void DisplayMenu();

  // Print time in 12- and 24-hour formats
  void DisplayTime();

  // Get time from user in 24-hour format (hh:mm:ss)
  void GetTimeFromUser();

  // Execute user-selected instruction
  bool ExecInstructionFromUser();

  // Add one second to the time
  void AddOneSecond();

  // Add one minute to the time
  void AddOneMinute();

  // Add one hour to the time
  void AddOneHour();

  // Start the command-line interface (CLI) for interacting with the clock
  void StartCli();
};

#endif  // CLOCK_H
