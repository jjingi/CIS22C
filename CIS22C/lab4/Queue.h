// Lab#: Lab3
// Jin Gi Min
// Fumiya Koseki
// derived class Queue from the SinglyLinkedList class. work as a queue. First in, first out

/*
CHANGED
We added isQueueEmpty method to check the queue is empty or not
*/

#pragma once
#include "SinglyLinkedList.h"

class Queue : protected SinglyLinkedList{
public:
  /*
  Queue constructor
  pre:
  post
  return:
  */
  Queue() : SinglyLinkedList(){} 
  /*
  Queue destructor
  pre:
  post
  return:
  */
  ~Queue() override {}

  /*
  creat Queue, call SinglyLinkedList creatList()
  pre:
  post: 
  return:
  */
  void creatQueue(){createList();}

  /*
  destroy Queue, call SinglyLinkedList destroyList()
  pre:
  post:
  return:
  */
  void destroyQueue(){destroyList();}

  /*
  add Currency* to the end of the queue
  pre: addData - Currency object that is going to be enqueued
  post: 
  return:
  */
  void enqueue(Currency* enqueueData){ addCurrency(enqueueData, getCount()); }

  /*
  remove Currency* from the front of the queue
  pre:
  post: throw exception if list is empty 
  retyrn: Currency* - Currency object that is removed
  */
  Currency* dequeue() { return removeCurrency(0); }

  /*
  peek the front of the queue
  pre:
  post: throw exception if list is empty
  return: Currency* - Currency object that is peeked front
  */
  Currency* peekFront() { return getCurrency(0); }

  /*
  peek the back of the queue
  pre:
  post: throw exception if list is empty
  return: Currency* - Currency object that is peeked back
  */
  Currency* peekRear() { return getCurrency(getCount()-1); }

  /*
  print the queue
  pre:
  post:
  return:
  */
  std::string printQueue() { return printList(); }

  /*
  check if the queue is empty
  pre:
  post: 
  return true or false
  */

  //FIXED 
  bool isQueueEmpty(){ return isListEmpty();}
};


