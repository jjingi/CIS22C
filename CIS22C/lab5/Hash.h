// Lab#: Lab5
// Fumiya Koseki
// Jin Gi Min

#pragma once

#include "Currency.h"
#include <iostream>
#include <cmath>
class Element
{
private:
  Currency *_data = nullptr;
  bool _emptySinceStart = true;

public:
  Element() : _data(nullptr), _emptySinceStart(true) {}
  Element(Currency *data) : _data(data), _emptySinceStart(false) {}
  /*
  check the element data currency pointer is empty or not
  pre:
  post:
  return:
  */
  bool isEmpty() { return _data == nullptr; }
  /*
  get data of currency pointer in element
  pre:
  post:
  return: _data -> currency* in the element
  */
  Currency *getData() { return _data; }
  /*
  set data of currency pointer in element
  pre: Currency* data - currency pointer that is going to be set
  post:
  return:
  */
  void setData(Currency *data) { _data = data; }
  /*
  get emptySinceStart
  pre:
  post:
  return: _emptySinceStart -> bool that is true if the element is empty since start
  */
  bool getEmptySinceStart() { return _emptySinceStart; }
  /*
  set emptySinceStart
  pre: bool emptySinceStart - bool that is true if the element is empty since start
  post:
  return:
  */
  void setEmptySinceStart(bool emptySinceStart) { _emptySinceStart = emptySinceStart; }
};
class Hash
{
private:
  int _size = 0;
  int loadCount = 0;
  int collisionCount = 0;
  Element *_hash;

public:
  Hash() : _size(0), _hash(nullptr) {}
  Hash(int size);
  ~Hash() { delete[] _hash; }
  /*
  get Hash table
  pre:
  post:
  return: _hash -> hash table array
  */
  Element *getHash() { return _hash; }
  /*
  get size of hash table
  pre:
  post:
  return: _size -> size of hash table
  */
  int getSize() { return _size; }
  /*
  get loadCount
  pre:
  post:
  return: loadCount -> load count of hash table
  */
  int getLoadCount() { return loadCount; }
  /*
  get collisionCount
  pre:
  post:
  return: collisionCount -> collision count of hash table
  */
  int getCollisionCount() { return collisionCount; }
  int hashScheme(Element e);
  bool insert(Element *table, Element e);
  bool remove(Element e);
  void resizeCheck(int numProbed);
  void resize();
  void print();
  int search(Currency *userInput);
};
Hash::Hash(int size) : _size(size)
{
  if (size < 0)
  {
    throw std::invalid_argument("Invalid size");
  }
  _hash = new Element[_size];
}

/*
pusedorandom hash scheme except moduler operator
pre: Element e -> element that we will get key from
post:
return: key -> key of element
*/
int Hash::hashScheme(Element e)
{
  return 2 * e.getData()->getIntegerPart() + 3 * e.getData()->getDecimalPart();
}

/*
insert element to hash table
pre: Element* table -> hash table array, Element e -> element that we will insert to hash table
post:
return: true if insert successfully, false if not
*/
bool Hash::insert(Element *table, Element e)
{
  int i = 0;
  int bucketsProbed = 0;
  int bucket = (hashScheme(e)) % _size;
  while (bucketsProbed < _size)
  {
    if (table[bucket].isEmpty())
    {
      table[bucket] = e;
      table[bucket].setEmptySinceStart(false);
      if (table == _hash)
      {
        loadCount++;
      }
      resizeCheck(bucketsProbed);
      return true;
    }
    i++;
    //used c1 = 1, c2 = 1  for collision resolution
    bucket = (hashScheme(e) % _size + 1 * i + 1 * i * i) % _size;
    bucketsProbed++;
    collisionCount++;
    resizeCheck(bucketsProbed);
  }
  // when it's cyclic hash, start linear probing
  bucketsProbed = 0;
  bucket = (hashScheme(e)) % _size;
  while (bucketsProbed < _size)
  {
    if (table[bucket].isEmpty())
    {
      table[bucket] = e;
      table[bucket].setEmptySinceStart(false);
      if (table == _hash)
      {
        loadCount++;
      }
      resizeCheck(bucketsProbed);
      return true;
    }
    bucket = ++bucket % _size;
    bucketsProbed++;
    collisionCount++;
    resizeCheck(bucketsProbed);
  }
  return false;
}

/*
remove element from hash table
pre: Element e -> element that we will remove from hash table
post:
return: true if remove successfully, false if not
*/
bool Hash::remove(Element e)
{
  bool result;
  int bucket = search(e.getData());
  if (bucket == -1)
  {
    result = false;
  }
  else
  {
    _hash[bucket].setData(nullptr);
    result = true;
  }
  return result;
}

/*
check if the load count is greater than 0.6 or collision happened more than size/3, if so, resize the hash table
pre: int numProbed -> number of buckets probed
post:
return:
*/
void Hash::resizeCheck(int numProbed)
{
  if (static_cast<double>(loadCount) / _size >= 0.6)
  {
    resize();
  }
  else if (numProbed >= (_size / 3))
  {
    resize();
  }
}
/*
resize the hash table
pre:
post:
return:
*/
void Hash::resize()
{
  int newSize = _size * 2;
  bool isPrime = true;
  do
  {
    isPrime = true;
    if (newSize % 2 == 0)
    {
      isPrime = false;
      newSize++;
      continue;
    }
    for (int i = 3; i < sqrt(newSize); i = i + 2)
    {
      if (newSize % i == 0)
      {
        isPrime = false;
        newSize++;
        continue;
      }
    }
  } while (!isPrime);
  Element *newHash = new Element[newSize]{};
  int bucket = 0;
  int _oldsize = _size;
  _size = newSize;
  while (bucket < _oldsize)
  {
    if (!_hash[bucket].isEmpty())
    {
      insert(newHash, _hash[bucket]);
    }
    bucket++;
  }
  delete[] _hash;
  _hash = newHash;
}

/*
print the hash table
pre:
post:
return:
*/
void Hash::print()
{
  std::cout << "\nThe numner of the loaded data: " << loadCount << std::endl;
  std::cout << "Load Factor: " << static_cast<double>(loadCount) / _size << std::endl;
  std::cout << "The number of the collision happened: " << collisionCount << std::endl;
}

/*
search the hash table
pre: Currency* userInput -> currency pointer that we will search
post:
return: bucket -> index of bucket that the currency pointer is in
*/
int Hash::search(Currency *userInput)
{
  Element e = Element(userInput);
  int i = 0;
  int bucketsProbed = 0;
  int bucket = hashScheme(e) % _size;
  while (!_hash[bucket].getEmptySinceStart() && bucketsProbed < _size)
  {
    if (!_hash[bucket].isEmpty() && _hash[bucket].getData()->isEqual(*e.getData()))
    {
      return bucket;
    }
    i++;
    //used c1 = 1, c2 = 1  for collision resolution
    bucket = (hashScheme(e) % _size + 1 * i + 1 * i * i) % _size;
    bucketsProbed++;
  }
  // when it's cyclic hash, start linear probing
  bucketsProbed = 0;
  bucket = (hashScheme(e)) % _size;
  while (!_hash[bucket].getEmptySinceStart() && bucketsProbed < _size)
  {
    if (!_hash[bucket].isEmpty() && _hash[bucket].getData()->isEqual(*e.getData()))
    {
      return bucket;
    }
    bucket = ++bucket % _size;
    bucketsProbed++;
  }
  return -1;
}