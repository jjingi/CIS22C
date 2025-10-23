// Lab#: Lab5
// Fumiya Koseki
// Jin Gi Min

#include <iostream>
#include "Dollar.h"
#include "Hash.h"

using namespace std;

const int SIZE_OF_ARRAY = 29;
int main()
{
  Element *elements = new Element[SIZE_OF_ARRAY]{};
  Currency *data[] = {
      new Dollar(57.12), new Dollar(23.44), new Dollar(87.43),
      new Dollar(68.99), new Dollar(111.22), new Dollar(44.55),
      new Dollar(77.77), new Dollar(18.36), new Dollar(543.21),
      new Dollar(20.21), new Dollar(345.67), new Dollar(36.18),
      new Dollar(48.48), new Dollar(101.00), new Dollar(11.00),
      new Dollar(21.00), new Dollar(51.00), new Dollar(1.00),
      new Dollar(251.00), new Dollar(151.00)};

  int dataSize = sizeof(data) / sizeof(data[0]);

  for (int i = 0; i < dataSize; i++)
  {
    elements[i].setData(data[i]);
  }

  try
  {
    Hash hash(SIZE_OF_ARRAY);

    for (int i = 0; i < dataSize; i++)
    {
      hash.insert(hash.getHash(), elements[i]);
    }

    hash.print();

    char continueOrNot = 'y';
    double userInput;
    while (tolower(continueOrNot) == 'y')
    {
      cout << "\nEnter a number for searching: ";
      cin >> userInput;
      Currency *temp = new Dollar(userInput);
      int index = hash.search(temp);
      if (index == -1)
      {
        cout << "Invalid Data" << endl;
      }
      else
      {
        cout << userInput << " Index is at: " << index << endl;
      }
      cout << "Do you want to continue? (y/n): ";
      cin >> continueOrNot;
      delete temp;
    }
    cout << "\nProgram ends" << endl;

    delete[] elements;
    for (int i = 0; i < 20; i++)
    {
      delete data[i];
    }
  }
  catch (invalid_argument &e)
  {
    cout << e.what() << endl;
  }
}