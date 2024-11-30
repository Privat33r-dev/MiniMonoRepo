#include <iostream>

#include "airgead_investment_planner_cli.h"

int main() {
  airgead_investment_planner_cli::InvestmentPlannerCli depositCalculatorCli =
      airgead_investment_planner_cli::InvestmentPlannerCli();

  bool isWillingToContinue = false;
  do {
    // Show calculator CLI
    depositCalculatorCli.startCli();

    // Ask user whether continuation is desirable
    const char CONTINUE_RESPONSE =
        std::toupper(mini_utils::getValidatedInput<char>(
            "Do you want to calculate with new values? (Y/N): ",
            // Validate that user response within accepted range
            [](char RESPONSE) {
              RESPONSE = std::toupper(RESPONSE);
              return RESPONSE == 'Y' || RESPONSE == 'N';
            },
            // Explain valid values to user
            "Y or N character",
            // Strict mode enabled ("y n" is not acceptable response)
            true));
    isWillingToContinue = CONTINUE_RESPONSE == 'Y';
  } while (isWillingToContinue);

  std::cout << "Goodbye!" << std::endl;
}
