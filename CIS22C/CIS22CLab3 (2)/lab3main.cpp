// Lab#: Lab3
// Jin Gi Min
// Fumiya Koseki
#include <iostream>
#include "Queue.h"
#include "Stack.h"
#include "dollar.h"

using namespace std;

const int ARR_SIZE = 20;
int main()
{
  cout << "Welcome to Jin Gi Min and Fumiya Koseki's ADT demo" << endl << endl;


  try
  {
    Currency *arr[ARR_SIZE] = {new Dollar(57.12), new Dollar(23.44), new Dollar(87.43), new Dollar(68.99), new Dollar(111.22), new Dollar(44.55), new Dollar(77.77), new Dollar(18.36), new Dollar(543.21), new Dollar(20.21), new Dollar(345.67), new Dollar(36.18), new Dollar(48.48), new Dollar(101.00), new Dollar(11.00), new Dollar(21.00), new Dollar(51.00), new Dollar(1.00), new Dollar(251.00), new Dollar(151.00)};
    
    SinglyLinkedList singlyLinkedList1;
    Stack stack1;
    Queue queue1;
    Currency *removed = nullptr;
    Currency *temp = nullptr;

    for (int i = 0; i < 7; i++)
    {
      singlyLinkedList1.addCurrency(arr[i], 0);
    }

    temp = new Dollar(87.43);
    cout << "Index of Dollar object with value 87.43: " << singlyLinkedList1.findCurrency(temp) << endl;
    delete temp;
    
    temp = new Dollar(44.56);
    cout << "Index Dollar object with value 44.56: " << singlyLinkedList1.findCurrency(temp) << endl;
    delete temp;

    temp = new Dollar(111.22);
    removed = singlyLinkedList1.removeCurrency(temp);
    delete temp;

    removed = singlyLinkedList1.removeCurrency(2);

    cout << singlyLinkedList1.printList() << endl;

    for (int i = 8; i <= 11; i++)
    {
      singlyLinkedList1.addCurrency(arr[i], i % 5);
    }

    removed = singlyLinkedList1.removeCurrency(singlyLinkedList1.countCurrency() % 6);
    removed = singlyLinkedList1.removeCurrency(singlyLinkedList1.countCurrency() / 7);
    
    cout << singlyLinkedList1.printList() << endl;

    // stack
    for (int i = 13; i < 20; i++)
    {
      stack1.push(arr[i]);
    }

    cout << "Value of peeked object: " << stack1.peek()->toString() << endl;

    for (int i = 0; i < 3; i++)
    {
      removed = stack1.pop();
    }
    cout << stack1.printStack() << endl;
    
    for (int i = 0; i < 5; i++)
    {
      stack1.push(arr[i]);
    }
    
    removed = stack1.pop();
    removed = stack1.pop();
    
    cout << stack1.printStack() << endl;

    // Queue
    for (int i = 0; i < 7; i++)
    {
      queue1.enqueue(arr[2 * i + 5]);
    }

    cout << "Peek front: " << queue1.peekFront()->toString() << ". Peek rear: " << queue1.peekRear()->toString() << endl;

    removed = queue1.dequeue();
    removed = queue1.dequeue();
    
    cout << queue1.printQueue() << endl;

    for (int i = 10; i < 15; i++)
    {
      queue1.enqueue(arr[i]);
    }

    for (int i = 0; i < 3; i++)
    {
      removed = queue1.dequeue();
    }

    cout << queue1.printQueue() << endl;

    for (int i = 0; i < ARR_SIZE; i++)
    {
      delete arr[i];
    }
  }
  catch (invalid_argument &e)
  {
    cout << e.what() << endl;
  }

  cout << "\nGood bye" << endl;

  return 0;
}

// what we need to do: 1. handle deleting the memory in the heap 2. find what's exception and just simple return