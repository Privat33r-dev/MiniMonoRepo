/*
 * Airgead Investment Planner
 */
#include "airgead_investment_planner_cli.h"

#include <cmath>
#include <iostream>

#include "mini_utils.h"

namespace airgead_investment_planner_cli {
using std::cout;
using std::endl;
using std::string;

long double DepositCalculator::calculateCompoundInterest(
    long double principal, long double interestRatePercent,
    long double monthlyDeposit, int years) {
  const double MONTHS_IN_A_YEAR = 12.0L;
  const double PERCENTAGE_TO_DECIMAL = 100.0L;

  // Convert percentage to decimal
  long double annualInterestRate = interestRatePercent / PERCENTAGE_TO_DECIMAL;
  // Calculate monthly rate
  long double monthlyRate = annualInterestRate / MONTHS_IN_A_YEAR;

  // Calculate total number of months in the period
  int totalMonths = years * static_cast<int>(MONTHS_IN_A_YEAR);

  // Calculate compounded principal amount
  long double compoundedPrincipal =
      principal * pow(1.0L + monthlyRate, totalMonths);

  // Calculate future value of monthly deposits (with early deposit adjustment)
  long double futureValueOfDeposits =
      monthlyDeposit * (pow(1.0L + monthlyRate, totalMonths + 1) - 1) /
          monthlyRate -
      monthlyDeposit;

  // Return the total compounded value (principal + deposits)
  return compoundedPrincipal + futureValueOfDeposits;
}

InvestmentPlannerCli::InvestmentPlannerCli(int t_width, double t_principal,
                                     double t_monthlyDeposit,
                                     double t_annualRate, int t_years)
    : m_width(t_width),
      m_string_formatter(t_width),
      m_table_formatter(t_width),
      m_principal(t_principal),
      m_monthlyDeposit(t_monthlyDeposit),
      m_annualRate(t_annualRate),
      m_years(t_years) {}

std::string InvestmentPlannerCli::trimUserFormatting(
    const std::string& ORIG_STR) {
  const std::string RESULT = mini_utils::trim(ORIG_STR);
  size_t start = RESULT.find_first_not_of("$%");
  // If all characters are '$' or '%', return an empty string
  return (start != std::string::npos) ? RESULT.substr(start) : "";
}

void InvestmentPlannerCli::getValuesFromUser() {
  // Can't pass member data in the lambda
  const int MIN_YEARS = MIN_INVEST_YEARS;
  const int MAX_YEARS = MAX_INVEST_YEARS;

  // Bug or feature: hexadecimal input support
  m_principal = mini_utils::getValidatedInput<double>(
      "Initial Investment Amount (in $): ", mini_utils::isPositiveRealNum,
      "positive real number", false, trimUserFormatting);
  m_monthlyDeposit = mini_utils::getValidatedInput<double>(
      "Monthly Deposit (in $): ", mini_utils::isPositiveRealNum,
      "positive real number", false, trimUserFormatting);
  m_annualRate = mini_utils::getValidatedInput<double>(
      "Annual Interest Rate (in %): ", mini_utils::isPositiveRealNum,
      "positive real number", false, trimUserFormatting);
  m_years = mini_utils::getValidatedInput<int>(
      "Investment Term (Years): ",
      [MIN_YEARS, MAX_YEARS](int input) {
        return input >= MIN_YEARS && input <= MAX_YEARS;
      },
      "integer between " + std::to_string(MIN_INVEST_YEARS) + " and " +
          std::to_string(MAX_INVEST_YEARS));
}

string InvestmentPlannerCli::getTable(bool withDeposits) {
  // Setup table formatting
  std::vector<string> headers = {"Year", "End of the Year Balance",
                                 "End of the Year Earned Interest"};
  m_table_formatter.setHeaders(headers);
  if (!m_table_formatter.setColumnWidths({10, 35, 35})) {
    cout << "Unexpected error happened: unable to set table column widths."
         << endl;
    return "";
  }

  double lastYearBalance = m_principal;
  const double MONTHLY_DEPOSIT = withDeposits ? m_monthlyDeposit : 0;
  const double ANNUAL_DEPOSIT = MONTHLY_DEPOSIT * 12;

  for (int currentYear = 1; currentYear < m_years + 1; ++currentYear) {
    string yearRow = std::to_string(currentYear);

    // Calculate year-end balance
    long double yearEndBalance = DepositCalculator::calculateCompoundInterest(
        m_principal, m_annualRate, MONTHLY_DEPOSIT, currentYear);

    // Calculate year-end earned interest
    double earnedInterest = yearEndBalance - (lastYearBalance + ANNUAL_DEPOSIT);

    // Convert to strings for table formatting
    string formattedEndYearBalance =
        "$" + m_string_formatter.toStringWithPrecision(yearEndBalance);
    string formattedEndYearInterest =
        "$" + m_string_formatter.toStringWithPrecision(earnedInterest);

    // Add row to the table
    m_table_formatter.addRow(
        {yearRow, formattedEndYearBalance, formattedEndYearInterest});

    lastYearBalance = yearEndBalance;
  }
  const string OUT_SUFFIX = (withDeposits ? "" : "out");
  const string HEADER =
      m_string_formatter.horizontalSeparatorWithSides('-', '+') + "\n" +
      m_string_formatter.formatCentered("Balance and Interest With" +
                                            OUT_SUFFIX +
                                            " Additional Monthly Deposits",
                                        '|') +
      "\n";

  // Ideally, we can defer cleaning table and just return the result,
  // but defer implementation would overcomplicate things.
  const string RESULT = HEADER + m_table_formatter.render();

  // Clean table
  m_table_formatter.clearRows();

  return RESULT;
}

void InvestmentPlannerCli::pressToContinue() {
  cout << "Press enter to continue..." << endl;
  std::cin.get();
  std::cout << "\x1b[1A\x1b[1A"  // Move cursor two lines up
            << "\x1b[2K";        // Delete the entire line
}

void InvestmentPlannerCli::startCli() {
  const char FORMAT_CHAR = '-';
  cout << m_string_formatter.horizontalSeparator(FORMAT_CHAR) << endl
       << m_string_formatter.formatFullBorder("Airgead Investment Calculator",
                                              FORMAT_CHAR)
       << endl
       << m_string_formatter.horizontalSeparator(FORMAT_CHAR) << endl
       << endl;

  getValuesFromUser();
  pressToContinue();

  cout << getTable(false) << endl << getTable(true) << endl;
}
}  // namespace airgead_investment_planner_cli