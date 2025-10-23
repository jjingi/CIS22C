// Lab2
// Fumiya Koseki
// Jin Gi Min
// child class of Currency class

/*
CHANGED
changed print function to return the toString function and deleted std::cout << "Dollar"; line
*/

#pragma once
#ifndef DOLLAR_H
#define DOLLAR_H

#include "currency.h"

class Dollar : public Currency {
private:
  std::string currencyName = "dollar";

public:
  Dollar() : currencyName("dollar") {}

  Dollar(std::string userCurrencyName) : currencyName(userCurrencyName) {}

  Dollar(double userInput) : Currency(userInput) {}

  Dollar(double userInput, std::string userCurrencyName) : Currency(userInput), currencyName(userCurrencyName) {}

  ~Dollar() override {}

  /*
  setter
  pre: userCurrencyName - string that represents the name of the currency
  post:
  return:
  */
  void setCurrencyName(std::string userCurrencyName) override {
    currencyName = userCurrencyName;
  }


  /*
  getter
  pre:
  post:
  return: currencyName - name of the currency(Dollar)
  */
  std::string getCurrencyName() const override { return currencyName; }

  void print() override;

};


/*
user Currency class print function and add Dollar at the end
pre:
post:
return:
*/
void Dollar::print() {
  // FIXED: delete std::cout << "Dollar"; since we add it to toString
  /*
  Original Code
  Currency::print();
  std::cout << "Dollar";
  */
  Currency::print();
}
#endif
