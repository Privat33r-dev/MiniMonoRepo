#ifndef CLOCK_H
#define CLOCK_H

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
  unsigned short int hours, minutes, seconds;
  unsigned short int width = 26;
  const string kClockSeparator = "    ";

  // Center the label within a specified width, adding padding and borders.
  string FormatCenteredLabel(const string& label);

  // Format the label within a specified width, adding fixed left padding and
  // borders.
  string FormatSimpleLabel(const string& label);

  // Print border composed of start characters, optionally formatted for 2
  // clocks
  void PrintStyledBorder(bool doubleBorder = false);

  // Get formatted time in 12- and 24-hour formats
  string GetFormattedTime(bool is24HoursFormat);

  // Clear the input buffer in case of invalid input,
  // ensuring that subsequent input operations are not affected.
  void ClearInput();

  // Get validated input from user using provided validator
  template <typename T>
  T GetValidatedInput(const std::string& prompt,
                      std::function<bool(T)> validator);

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
