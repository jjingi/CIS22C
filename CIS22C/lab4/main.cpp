//Lab#: Lab4
//Fumiya Koseki
//Jin Gi Min

#include "BST.h"
#include "Dollar.h"
#include <fstream>
#include <iostream>

using namespace std;

const int ARR_SIZE = 20;

int main() {
  int menuNum;
  double currencyData;
  BST tree;
  ofstream outFile;
  Currency* inputTemp;
  Currency *arr[ARR_SIZE] = {
      new Dollar(57.12),  new Dollar(23.44),  new Dollar(87.43),
      new Dollar(68.99),  new Dollar(111.22), new Dollar(44.55),
      new Dollar(77.77),  new Dollar(18.36),  new Dollar(543.21),
      new Dollar(20.21),  new Dollar(345.67), new Dollar(36.18),
      new Dollar(48.48),  new Dollar(101.00), new Dollar(11.00),
      new Dollar(21.00),  new Dollar(51.00),  new Dollar(1.00),
      new Dollar(251.00), new Dollar(151.00)};
  Queue insertedQueue;
  
  outFile.open("output.txt");
  if (!outFile) {
    std::cout << "Fail to open file" << std::endl;
  }

  for (int i = 0; i < ARR_SIZE; i++) {
    tree.insert(arr[i]);
  }
  tree.print(outFile);
  do {
    cout << "Choose your action 1) add 2) search 3) delete 4) print 5) exit: ";
    cin >> menuNum;
    try {
    switch (menuNum) {
    case 1:
      cout << "Enter the Currency Value you want to add: ";
      cin >> currencyData;
      inputTemp = new Dollar(currencyData);
      insertedQueue.enqueue(inputTemp);
      if (!tree.insert(inputTemp)) {
        std::cout << "Error: " << currencyData<<" is Invalid input(Ignored)" << endl << endl;
        outFile << "Error: \"" << currencyData << "\" is Invalid input(Ignored)" << endl << endl;
      }
      break;
    case 2:
      cout << "Enter the Currency Value you want to search: ";
      cin >> currencyData;
      inputTemp = new Dollar(currencyData);
      if(tree.search(inputTemp) != nullptr) {
        cout << "\nFound" << endl;
      }
      else {
        cout << "\n" << currencyData << " Not Found" << endl;
        outFile << currencyData << " Not Found\n" << endl;
      }
      delete inputTemp;
      break;
    case 3:
      cout << "Enter the Currency Value you want to delete: ";
      cin >> currencyData;
      inputTemp = new Dollar(currencyData);
      if(tree.remove(inputTemp) == nullptr) {
        cout << "Couldn't find " << currencyData << endl;
        outFile << "Couldn't find " << currencyData << endl;
      }
      delete inputTemp;
      break;
    case 4:
    case 5:
      tree.print(outFile);
      break;
    default:
      break;
    }
    }catch(invalid_argument &e) {
      cout << e.what() << " " << currencyData << " is ignored" << endl;
      outFile << e.what() << " " << currencyData << " is ignored" << endl;
    }
    cout << endl;
  } while (menuNum != 5);

  outFile.close();
  
  while(!insertedQueue.isQueueEmpty()){
    delete insertedQueue.dequeue();
  }
    
  for (int i = 0; i < ARR_SIZE; i++) {
    delete arr[i];
  }
}
