#include <iostream>

#include "airgead_investment_planner_cli.h"

int main() {
  airgead_investment_planner_cli::InvestmentPlannerCli depositCalculatorCli =
      airgead_investment_planner_cli::InvestmentPlannerCli();
  depositCalculatorCli.startCli();
}
