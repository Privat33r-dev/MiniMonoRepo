#ifndef CLOCK_H
#define CLOCK_H
#include <string>

#include "mini_utils.h"

namespace clock_cli {
using std::string;

class Clock {
 private:
  // Expected range of values is 0..60,
  // hence unsigned short int, which ranges 0..65535
  unsigned short m_hours = 0;
  unsigned short m_minutes = 0;
  unsigned short m_seconds = 0;

  // Clock formatting width, expected range 0..1000 (ultra wide screen)
  unsigned short m_width = 26;

  mini_utils::StringFormatter m_formatter;

  // Separator between 24- and 12-hour clocks
  const string CLOCK_SEPARATOR = "    ";

  // Print border composed of start characters, optionally formatted for two
  // clocks
  void printStyledBorder(bool doubleBorder = false);

  // Get formatted time in 12-hour formats
  string getFormattedTime12Hours() const;

  // Get formatted time in 24-hour formats
  string getFormattedTime24Hours() const;

  // Adjust the time by carrying over values. For example, if seconds >= 60,
  // they will be converted to minutes.
  void adjustTime();

 public:
  Clock();
  Clock(int hours, int minutes, int seconds);

  // Display the time menu for user interaction
  void displayMenu();

  // Print time in 12- and 24-hour formats
  void displayTime();

  // Get time from user in 24-hour format (hh:mm:ss)
  void getTimeFromUser();

  // Execute user-selected instruction
  bool execInstructionFromUser();

  // Add one second to the time
  void addOneSecond();

  // Add one minute to the time
  void addOneMinute();

  // Add one hour to the time
  void addOneHour();

  // Helper to get 12- or 24-hours formatted time
  string formatTime(unsigned short hours, const string& PERIOD,
                    unsigned short minutes, unsigned short seconds) const;

  // Start the command-line interface (CLI) for interacting with the clock
  void startCli();
};

}  // namespace clock_cli
#endif  // CLOCK_H
