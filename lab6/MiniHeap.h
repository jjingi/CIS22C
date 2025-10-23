/*
Lab# : Lab 6
Jin Gi Min
Make a mini heap dervied from BST
*/
#pragma once
#include <iostream>
#include <cmath>
#include "BST.h"

class HeapNode : public BSTNode
{
public:
    HeapNode *parent = nullptr;
    HeapNode() : BSTNode(), parent(nullptr) {}
    ~HeapNode() {}
    void setParent(HeapNode *parent) { this->parent = parent; }
    HeapNode *getParent() { return parent; }
};

class MiniHeap : public BST
{
private:
    int count = 0;
    HeapNode **arr = nullptr;
    int SIZE = 0;

public:
    MiniHeap() : BST()
    {
        arr = new HeapNode *[0];
    }
    MiniHeap(int size)
    {
        arr = new HeapNode *[size];
        SIZE = size;
    }
    ~MiniHeap() override;
    bool insert(Currency *insertData) override; 
    BSTNode *search(Currency *key) override;
    Currency *remove(Currency *deleteData) override;
    void reheapUp(int i);
    void reheapDown(int i);
    int parentIndex(int i) { return (i - 1) / 2; }
    int leftIndex(int i) { return (2 * i + 1); }
    int rightIndex(int i) { return (2 * i + 2); }
    void pointSet(HeapNode *tree, int i);
};

MiniHeap::~MiniHeap() {
    for (int i = 0; i < SIZE; i++) {
        if(arr[i]) {
            delete arr[i];
        }
    }
}

/*
Pre: insertData -> Currency pointer data which will be inserted
Post:
return: if success to insert - ture. Otherwise, false
*/
bool MiniHeap::insert(Currency *insertData)
{
    bool insertSuccess = false;
    if (insertData == nullptr)
    {
        return false;
    }
    else if (Dollar(0).isGreater(*insertData))
    {
        return false;
    }

    HeapNode *temp = new HeapNode();
    temp->data = insertData;
    arr[count] = temp;
    insertSuccess = true;
    reheapUp(count++);

    root = arr[0];
    pointSet(static_cast<HeapNode *>(getRoot()), 0);
    return insertSuccess;
}

/*
Pre: tree - HeapNode which parent, left and right node pointer will be set
     i - index of the parameter name tree
Post:
return:
*/
void MiniHeap::pointSet(HeapNode *tree, int i)
{
    if (tree == nullptr)
    {
        return;
    }

    if (i == 0)
    {
        if (leftIndex(i) < SIZE)
        {

            tree->setLeft(arr[leftIndex(i)]);
            pointSet(static_cast<HeapNode *>(root->left), leftIndex(i));
        }
        if (rightIndex(i) < SIZE)
        {
            tree->setRight(arr[rightIndex(i)]);
            pointSet(static_cast<HeapNode *>(root->right), rightIndex(i));
        }
    }
    else
    {
        if (parentIndex(i) >= 0 && parentIndex(i) < SIZE)
        {
            tree->parent = arr[parentIndex(i)];
        }
        if (leftIndex(i) < SIZE)
        {
            tree->setLeft(arr[leftIndex(i)]);
            pointSet(static_cast<HeapNode *>(tree->left), leftIndex(i));
        }
        if (rightIndex(i) < SIZE)
        {
            tree->setRight(arr[rightIndex(i)]);
            pointSet(static_cast<HeapNode *>(tree->right), rightIndex(i));
        }
    }
}

/*
Pre: i - index of the heapNode
post:
return:
*/
void MiniHeap::reheapUp(int i)
{
    if (arr[parentIndex(i)] == nullptr || arr[i] == nullptr)
    {
        return;
    }
    if (arr[parentIndex(i)]->data->isGreater(*arr[i]->data))
    {
        HeapNode *swap = arr[i];
        arr[i] = arr[parentIndex(i)];
        arr[parentIndex(i)] = swap;
        reheapUp(parentIndex(i));
    }
}

/*
Pre: i - index of the heapNode
post: 
return:
*/
void MiniHeap::reheapDown(int i) {
    int smallestIndex = i;
    
    if (leftIndex(i) < SIZE && arr[leftIndex(i)] != nullptr && arr[i]->data->isGreater(*arr[leftIndex(i)]->data)) {
        smallestIndex = leftIndex(i);
    }

    if (rightIndex(i) < SIZE && arr[rightIndex(i)] != nullptr && arr[i]->data->isGreater(*arr[rightIndex(i)]->data)) {
        smallestIndex = rightIndex(i);
    }

    if (smallestIndex != i) {
        if (i == 0) {
            setRoot(arr[smallestIndex]);
        }
        HeapNode *swap = arr[i];
        arr[i] = arr[smallestIndex];
        arr[smallestIndex] = swap;
        reheapDown(smallestIndex);
    }
}

/*
Pre: key - key currency data to search the HeapNode which has same value data as key
post:
return:
*/
BSTNode *MiniHeap::search(Currency *key)
{
    for (int i = 0; i < count; i++)
    {
        if (arr[i]->data->isEqual(*key))
        {
            return arr[i];
        }
    }
    return nullptr;
}

/*
Pre: deleteData - currency pointer which has the value that we're trying to delete
post:
return:
*/
Currency *MiniHeap::remove(Currency *deleteData)
{

    Currency* removedData = nullptr;

    int index = -1;

    for (int i = 0; i < count; i++)
    {

        if (arr[i]->data->isEqual(*deleteData))
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        return nullptr;
    }
    removedData = arr[index]->data;
    delete arr[index];
    arr[index] = arr[--count];
    arr[count] = nullptr;
    setRoot(arr[0]);
    reheapDown(index);
    pointSet(static_cast<HeapNode *>(getRoot()), 0);
    return removedData;
}