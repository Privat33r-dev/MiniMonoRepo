#include <iostream>

#include "airgead_banking_cli.h"

int main() {
  airgead_banking_cli::AirgeadBankingCli depositCalculatorCli =
      airgead_banking_cli::AirgeadBankingCli();
  depositCalculatorCli.startCli();
}
