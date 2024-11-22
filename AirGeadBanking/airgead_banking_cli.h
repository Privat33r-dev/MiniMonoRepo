#include "mini_utils.h"
#ifndef AIR_GEAD_BANKING_CLI_H
#define AIR_GEAD_BANKING_CLI_H

namespace airgead_banking_cli {
const int DEFAULT_WIDTH = 80;

class DepositCalculator {
 public:
  static long double calculateCompoundInterest(long double principal,
                                               long double interestRatePercent,
                                               long double monthlyDeposit = 0,
                                               int years = 1);
};

class AirgeadBankingCli {
 public:
  AirgeadBankingCli(int t_width = DEFAULT_WIDTH, double t_principal = 0,
                    double t_monthlyDeposit = 0, double t_annualRate = 0,
                    int t_years = 0);
  // Start CLI session with user
  void startCli();

 private:
  const int MIN_INVEST_YEARS = 1;
  const int MAX_INVEST_YEARS = 50;
  int m_width;
  double m_principal;
  double m_monthlyDeposit;
  double m_annualRate;
  int m_years;
  mini_utils::StringFormatter m_string_formatter;
  mini_utils::TableFormatter m_table_formatter;

  // Collect principal, deposit, annual percent rate and deposit term from user
  void getValuesFromUser();

  // Ask user to press "Enter" button to continue
  void pressToContinue();

  // Make necessary calculations based on user input and render output table
  std::string getTable(bool withDeposits);
};
}  // namespace airgead_banking_cli

#endif  // AIR_GEAD_BANKING_CLI_H