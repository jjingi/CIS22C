// Lab#: Lab3
// Jin Gi Min
// Fumiya Koseki
// Singly Linked List class which has add, remove, find and other various functions or linked list
#pragma once
#include "LinkNode.h"

class SinglyLinkedList
{
private:
  int count = 0;
  LinkNode *start = nullptr;
  LinkNode *end = nullptr;

public:
  SinglyLinkedList() : count(0), start(nullptr), end(nullptr) {}
  virtual ~SinglyLinkedList();

  /*
  set the count member variable
  pre: count - count of nodes
  post:
  return: void
  */
  void setCount(int count) { this->count = count; }
  /*
  get count member variable
  pre:
  post:
  return: (int) - member variable count
  */
  int getCount() const { return count; }
  
  /*
  set start node pointer
  pre: start - start of the list
  post:
  return: void
  */
  void setStart(LinkNode *start) { this->start = start; }
  /*
  get start node pointer
  pre:
  post:
  return: (LinkNode*) - pointer of the starting node
  */
  LinkNode *getStart() const { return start; }

  /*
  set end node pointer
  pre: end - end of the list
  post:
  return: void
  */
  void setEnd(LinkNode *end) { this->end = end; }
  /*
  get end node pointer
  pre:
  post:
  return: (LinkNode*) - pointer of the ending node
  */
  LinkNode *getEnd() const { return end; }

  void createList();
  void destroyList();

  void addCurrency(Currency *addData, int index);

  Currency *removeCurrency(Currency *removeData);
  Currency *removeCurrency(int index);

  int findCurrency(Currency *searchData);
  Currency *getCurrency(int index);

  std::string printList();
  /*
  check if the list is empty or not
  pre:
  post:
  return: true or false
  */
  bool isListEmpty(){return count == 0;}

  /*
    tells the count
    pre:
    post:
    return: member variable "count"
  */
  int countCurrency(){return count;}
};

/*
SinglyLinkedList class destructor
pre:
post:
return:
*/
SinglyLinkedList::~SinglyLinkedList()
{
  LinkNode *temp = start;
  while (start != nullptr)
  {
    start = start->next;
    delete temp;
    temp = start;
  }
  count = 0;
}

/*
creat the singly linked list
pre:
post:
return:
*/
void SinglyLinkedList::createList()
{
  count = 0;
  start = nullptr;
  end = nullptr;
}

/*
destroy the linked list
pre:
post:
void:
*/
void SinglyLinkedList::destroyList()
{
  LinkNode *temp = start;
  while (start != nullptr)
  {
    start = start->next;
    delete temp;
    temp = start;
  }
  count = 0;
}

/*
add new node which data is addData to the linked list
pre: addData - data that is going to be added, int index - the index new node is added and it should be in range of 0 to count - 1
post: throw exception if index is bigger than count or less than 0
return: 
*/
void SinglyLinkedList::addCurrency(Currency *addData, int index)
{
  LinkNode *newNode = new LinkNode;
  newNode->data = addData;
  LinkNode *preNode = start;
  if (count < index || index < 0)
  {
    throw std::invalid_argument("invalid index");
  }
  else if (isListEmpty())
  {
    start = newNode;
    end = newNode;
    count++;
  }
  else
  {
    for (int i = 0; i < index - 1; i++)
    {
      preNode = preNode->next;
    }
    if (index == 0)
    {
      newNode->next = preNode;
      start = newNode;
      count++;
    }
    else if (preNode->next == nullptr)
    {
      preNode->next = newNode;
      end = newNode;
      count++;
    }
    else
    {
      newNode->next = preNode->next;
      preNode->next = newNode;
      count++;
    }
  }
}

/*
remove node which data is same as removeData, if we cannot find return nullptr
pre: removeData - the data we're searching to delete
post: if list is empty, throw exceoption.
return: (Currency*) - the currency object in the node which is removed
*/
Currency *SinglyLinkedList::removeCurrency(Currency *removeData)
{
  LinkNode *preNode = start;
  Currency *copy = nullptr;
  if (isListEmpty())
  {
    throw std::invalid_argument("memory underflow");
  }
  else if (count == 1 && preNode->data->isEqual(*removeData))
  {
    copy = preNode->data;
    delete start;
    start = nullptr;
    end = nullptr;
    count = 0;
  }

  else
  {
    while (preNode->next != nullptr)
    {
      if (preNode->next->data->isEqual(*removeData))
      {
        copy = preNode->next->data;
        LinkNode *temp = preNode->next;
        preNode->next = preNode->next->next;
        if (end == temp)
        {
          end = nullptr;
        }
        delete temp;
        temp = nullptr; // do we need this
        count--;
        break; // should we delete all of the Currency with same valu or just first one
      }
      else
      {
        preNode = preNode->next;
      }
    }
  }
  return copy;
}

/*
remove node at the index passed as parameter
pre: index - the index of the node we're removing. it should be in range from 0 to count - 1
post: if list is empty, throw exceoption. if index is bigger than count or less than 0, throw exception
return: (Currency*) - the currency object in the node which is removed
*/
Currency *SinglyLinkedList::removeCurrency(int index)
{
  LinkNode *preNode = start;
  LinkNode *sucNode = nullptr;
  Currency *copy = nullptr;
  if (isListEmpty())
  {
    throw std::invalid_argument("memory underflow");
  }

  if (count - 1 < index || index < 0)
  {
    throw std::invalid_argument("invalid index");
  }
  else
  {
    for (int i = 0; i < index - 1; i++)
    {
      preNode = preNode->next;
    }

    if (index == 0)
    {
      sucNode = start->next;
      copy = preNode->data;
      delete preNode;
      start = sucNode;
      if (sucNode == nullptr)
      {
        end = nullptr;
      }
    }
    else if (preNode->next != nullptr)
    {

      sucNode = preNode->next->next;
      copy = preNode->next->data;
      delete preNode->next;
      preNode->next = sucNode;
      if (sucNode == nullptr)
      {
        end = sucNode;
      }

    }
    count--;
  }

  return copy;
}

/*
find the node which data is same as searchData and return the index, if we cannot find return -1
pre: searchData - the data we're searching to find
post: if list is empty, throw exceoption.
return: index of the Node we found
*/
int SinglyLinkedList::findCurrency(Currency *searchData)
{
  LinkNode *curNode = start;
  int index = 0;
  if (isListEmpty())
  {
    throw std::invalid_argument("invalid argument");
  }
  else
  {
    while (curNode != nullptr)
    {
      if (curNode->data->isEqual(*searchData))
      {
        break;
      }
      curNode = curNode->next;
      index++;
    }
    if (curNode == nullptr)
    {
      index = -1;
    }
  }
  return index;
}

/*
return the pointer to the Currency at the index
pre: "index" should be within the range of the list
post: throw exception if "index" is out the range of the list
return: copy - pointer to Currency at the index
*/
Currency *SinglyLinkedList::getCurrency(int index)
{
  LinkNode *curNode = start;
  Currency *copy = nullptr;
  if (count - 1 < index || index < 0)
  {
    throw std::invalid_argument("invalid index");
  }
  else if (count != 0)
  {
    for (int i = 0; i < index; i++)
    {
      curNode = curNode->next;
    }
    copy = curNode->data;
  }
  return copy;
}

/*
get all the data in th list and return it as a string
pre:
post:
return: entireList - string of entire list
*/
std::string SinglyLinkedList::printList()
{
  LinkNode *curNode = start;
  std::string entireList = "";
  while (curNode != nullptr)
  {
    entireList = entireList + curNode->data->toString() + "\t";
    curNode = curNode->next;
  }
  return entireList;
}





/* Q & A Board
1. Do we need to delete all datas if there's same data in the list? no
2. destructor & destroy same
3. count == 0,1 or isEqual()
4. if we can't find Currency object in the list, should we throw an exception? or just nullptr or 0
5. do we need to assign nullptr after deleting local pointer? @removeCurrency(Currency*)
6.is it better to use two pointer to keep track the node so that the code looks prettier, or should I reduce the amount of variable(local tho)
7. do we remove all node with same value or just the first one
8. countCurrency and getCount looks same, do we need to include both method?

9. Should we use the dummy node list or usual one.
10. protected or private SinglyLinkedList.
11. should we grab the returned copy from removeCurrency() in variable
12. instruction E  skipping #8

*/
// Currency *SinglyLinkedList::removeCurrency(int index)
/*
if(index < 0 || index > count - 1){
  throw std::invalid_argument("no node");
}
Currency* currNode = start;
Currency* preNode = nullptr;
Currency* copy = nullptr;
if(count != 0){
  if(count == 1){
    copy = start->data;
    delete start;
    start = nullptr;
    end = nullptr;
  }
  else{
    for(int i=0;i<index;i++){
      preNode = currNode;
      currNode = currNode->next;
      preNode->next = currNode->next;
      if(currNode = start){
        start = currNode->next;
      }
      else if(currNode == end){
        end = preNode;
      }
      copy = currNode->data;
      delete currNode;
      currNode = nullptr;
    }
  }
  count--;
}

*/

// if(index < 0 || index > count - 1){
//   throw std::invalid_argument("no node");
// }
// LinkNode* currNode = start;
// LinkNode* preNode = nullptr;
// Currency* copy = nullptr;
// if(count != 0){
//   if(count == 1){
//     copy = start->data;
//     delete start;
//     start = nullptr;
//     end = nullptr;
//   }
//   else{
//     for(int i=0;i<index;i++){
//       preNode = currNode;
//       currNode = currNode->next;
//       preNode->next = currNode->next;
//       if(currNode == start){
//         start = currNode->next;
//       }
//       else if(currNode == end){
//         end = preNode;
//       }
//       copy = currNode->data;
//       delete currNode;
//       currNode = nullptr;
//     }
//   }
//   count--;
// }