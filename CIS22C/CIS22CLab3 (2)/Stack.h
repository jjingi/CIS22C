// Lab#: Lab3
// Jin Gi Min
// Fumiya Koseki
// derived class Stack from the SinglyLinkedList class. work as a stack. First in, last out
#pragma once
#ifndef STACK_H
#define STACK_H

#include "SinglyLinkedList.h"

class Stack : protected SinglyLinkedList {
public:
  /*
  constructor
  pre:
  post:
  return:
  */
  Stack() : SinglyLinkedList() {}

  /*
  destructor
  pre:
  post:
  return:
  */
  ~Stack() override {}

  /*
  create stack setting member variables to default
  pre:
  post:
  return:
  */  
  void creatStack() {createList();}
  /*
  clears up all the nodes
  pre:
  post:
  return:
  */
  void destroyStack() {destroyList();}
  /*
  add a new node at the top of the stack
  pre: Currency* pushData - pointer to the Currency that is going to be added
  post:
  return:
  */
  void push(Currency* pushData) {addCurrency(pushData, 0);};

  /*
  removes the node at the top
  pre:
  post:throw exception if the list is empty
  return: Currency* removeCurrency(0) - the copy of the removed object
  */
  Currency* pop() {return removeCurrency(0);};

  /*
  get the pointer to the Currency at the top of the stack
  pre:
  post:
  return: Currency* getCurrency(0) - pointer to Currency at the top of the stack
  */
  Currency* peek() {return getCurrency(0);};

  /*
  get all of the data in the stack
  pre:
  post:
  return: string printList() - string of all the data in the stack
  */
  std::string printStack() {return printList(); };

};

#endif