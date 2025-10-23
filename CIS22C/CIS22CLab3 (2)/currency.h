//Lab#: Lab2
//Fumiya Koseki
//Jin Gi Min

//Curreny class with _integerPart and _decimalPart. With _integerPart and _decimalPart, we can add, subtract, multiply, divide, and compare. When we print, we can print the currency in _integerPart._decimalPart form

/*
CHANGED
changed toString function to return the currency name at the end starting with Capital letter
*/


#pragma once
#ifndef CURRENCY_H
#define CURRENCY_H

#include <iostream>
#include <string>

class Currency {
private:
  int _integerPart = 0;
  int _decimalPart = 0;

public:
  Currency();

  Currency(double userInput);

  Currency(const Currency &rhs);

  virtual ~Currency() {}

  Currency &operator=(const Currency &rhs);

  void setIntergerPart(int integerPart);
  int getIntegerPart() const { return _integerPart; }

  void setDecimalPart(int decimalPart);
  int getDecimalPart() const { return _decimalPart; }

  /*
  sets currency name. Pure virtual
  pre: string userCurrencyName that represents the currencyName
  post: 
  return:
  */
  virtual void setCurrencyName(std::string userCurrencyName) = 0;

  /*
  gets currency name. Pure virtual
  pre:
  post:
  return: 
  */
  virtual std::string getCurrencyName() const = 0;

  void convert();
  virtual void add(const Currency &userAdd);
  virtual void subtract(const Currency &userSubtract);
  bool isEqual(const Currency &rhs);
  bool isGreater(const Currency &rhs);
  virtual std::string toString();
  virtual void print();
  void nameCheck(const Currency &c);
  void doAction(char action, const Currency &c);

};

Currency::Currency() {
  _integerPart = 0;
  _decimalPart = 0;
}

Currency::Currency(double userInput) {

  if (userInput < 0) {
    throw std::invalid_argument("Invalid constructor");
  }

  _integerPart = static_cast<int>(userInput);
  _decimalPart = static_cast<int>(userInput * 100) % 100;
}

Currency::Currency(const Currency &rhs) {
  _integerPart = rhs._integerPart;
  _decimalPart = rhs._decimalPart;
}
/*
Assignment Operator
pre: Currency &rhs - Currency object that is going to be copied
post:
return: *this - Currency object that is copied
*/
Currency &Currency::operator=(const Currency &rhs) {
  if (this != &rhs) {
    _integerPart = rhs._integerPart;
    _decimalPart = rhs._decimalPart;
  }

  return *this;
}
/*
convert if decimal part became greater than 99 or less than 0
pre:
post:
return:

if (decimalpoin became smaller than 0)
  integer Part -= 1
  decimal Part = (100 - (-decimalPart))
else (decimal Part is bigger than 0 especially for it's bigger than 100)
  integer Part += decimalPart / 100
  decimal Part = decimalPart % 100
end if

*/
void Currency::convert() {
  if (_decimalPart < 0) {
    _integerPart -= 1;
    _decimalPart += 100;
  } else {
    _integerPart += _decimalPart / 100;
    _decimalPart = _decimalPart % 100;
  }
}
/*
setters
pre: positive integer that is going to be set.
post: throw exception if the argumentis negative
return: 
*/
void Currency::setIntergerPart(int integerPart) {
  if (integerPart < 0) {
    throw std::invalid_argument("Invalid argument");
  }
  _integerPart = integerPart;
}

void Currency::setDecimalPart(int decimalPart) {
  if (decimalPart < 0) {
    throw std::invalid_argument("Invalid argument");
  }
  _decimalPart = decimalPart;
  convert();
}
/*
getters 
pre:
post:
return: member variables
*/

/*
add integer part and decimal part of object to calling object
convert if decimal part became greater than 99 or less than 0
pre: Currency &userAdd - Currency object that is going to be added
post:
return:
*/
void Currency::add(const Currency &userAdd) {
  if (getCurrencyName() != userAdd.getCurrencyName()) {
    throw std::invalid_argument("Invalid addition");
  }
  // We could use nameCheck(userAdd) here but to match the instruction's sample output, we intentionally left this duplicated code

  _integerPart += userAdd._integerPart;
  _decimalPart += userAdd._decimalPart;
  convert();
}

/*
subtract integer part and decimal part of object to calling object
convert if decimal part became greater than 99 or less than 0
pre: Currency &userSubtract - Currency object that is going to be subtracted
post: throw an exception if userSubtract is greater than the calling object
*/
void Currency::subtract(const Currency &userSubtract) {
  if (getCurrencyName() != userSubtract.getCurrencyName()) {
    throw std::invalid_argument("Invalid subtraction");
  }
  // We could use nameCheck(userSubtract) here but to match the instruction's sample output, we intentionally left this duplicated code
  if(isEqual(userSubtract) || isGreater(userSubtract)) {
    _integerPart -= userSubtract._integerPart;
    _decimalPart -= userSubtract._decimalPart;
    convert();
  }  
  else {
    throw std::invalid_argument("Invalid subtraction");
  }
}

/*
check argument object and calling object is same or not
pre: Currency &rhs - Currency object that is going to be compared
post: throw exception if the currency types of rhs and calling object are not same
return: equalOrNot - true if the argument object and calling object are same, false if not
*/
bool Currency::isEqual(const Currency &rhs) {
  bool equalOrNot = true;
  nameCheck(rhs);
  if (_integerPart != rhs._integerPart) {
    equalOrNot = false;
  } else if (_decimalPart != rhs._decimalPart) {
    equalOrNot = false;
  }

  return equalOrNot;
}

/*
check argument object is greater than calling object
pre: Currency &rhs - Currency object that is going to be compared
post: throw exception if the currency types of rhs and calling object are not same
return: greaterOrNot - true if the argument object is greater than calling object, false if not
*/
bool Currency::isGreater(const Currency &rhs) {
  nameCheck(rhs);
  bool greaterOrNot = false;
  if (_integerPart > rhs._integerPart) {
    greaterOrNot = true;
  }

  else if (_integerPart == rhs._integerPart) {
    if (_decimalPart > rhs._decimalPart) {
      greaterOrNot = true;
    }
  }
  return greaterOrNot;
}

/*
change integer _integerPart and _decimalPart to string and combine those to
_integerPart._decimalPart form
pre:
post:
return:
*/
std::string Currency::toString() {
  /*
    Original Code
    return std::to_string(_integerPart) + "." + (_decimalPart < 10 ? "0" : "") + 
    std::to_string(_decimalPart);
  */
  char temp = toupper(getCurrencyName()[0]);
  return std::to_string(_integerPart) + "." + (_decimalPart < 10 ? "0" : "") +
         std::to_string(_decimalPart) + " " + temp + getCurrencyName().substr(1,getCurrencyName().length() - 1);
}

/*
print the currency with using toString method
pre:
post:
return:
*/
void Currency::print() { std::cout << toString() << " "; }

/*
  check if the argument's currencyName matches the caller's currencyName
  pre: Currency &c - Currency object that is going to be checked
  post: throw an exception if the name doesn't match
  return:
*/
void Currency::nameCheck(const Currency &c){
  if(getCurrencyName() != c.getCurrencyName()){
    throw std::invalid_argument("Invalid currency type");
  }
}

/*
add or subtract depending on "char action"
pre: char action - decides add or subtract. This should be either 'a' or 's'
     Currency &c - Currency object that is going to be added or subtracted
post: throw exception if "action" is neither 'a' nor 's'
return:
*/
void Currency::doAction(char action, const Currency &c) {
  if(action == 'a'){
    add(c);
  }
  else if(action == 's'){
    subtract(c);
  }
  else{
    throw std::runtime_error("Invalid action");
  }

  
}

#endif