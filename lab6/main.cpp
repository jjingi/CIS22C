/*
Lab# : Lab 6
Jin Gi Min
*/
#include <iostream>
#include "MiniHeap.h"
using namespace std;

int main()
{
  MiniHeap test(20);
  const int ARR_SIZE = 20;
  Currency *arr[ARR_SIZE] = {
      new Dollar(57.12), new Dollar(23.44), new Dollar(87.43),
      new Dollar(68.99), new Dollar(111.22), new Dollar(44.55),
      new Dollar(77.77), new Dollar(18.36), new Dollar(543.21),
      new Dollar(20.21), new Dollar(345.67), new Dollar(36.18),
      new Dollar(48.48), new Dollar(101.00), new Dollar(11.00),
      new Dollar(21.00), new Dollar(51.00), new Dollar(1.00),
      new Dollar(251.00), new Dollar(151.00)};
  for (int i = 0; i < 10; i++)
  {
    test.insert(arr[i]);
  }
  cout << "-------Insert Until 10th element-------" << endl << endl;
  cout << "BreadthFirst: " << test.breadthFirstTraversal() << endl
       << endl;
  cout << "InOrder: " << test.inorderTraversal() << endl
       << endl;
  cout << "PreOrder: " << test.preorderTraversal() << endl
       << endl;
  cout << "PostOrder: " << test.postorderTraversal() << endl
       << endl;
  for (int i = 10; i < 20; i++)
  {
    test.insert(arr[i]);
  }
  cout << "-------Insert every elements-------" << endl << endl;
  cout << "BreadthFirst: " << test.breadthFirstTraversal() << endl
       << endl;

  cout << "InOrder: " << test.inorderTraversal() << endl
       << endl;
  cout << "PreOrder: " << test.preorderTraversal() << endl
       << endl;
  cout << "PostOrder: " << test.postorderTraversal() << endl
       << endl;

  return 0;
}