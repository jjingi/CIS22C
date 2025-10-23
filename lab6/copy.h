#pragma once
#include <iostream>
#include <cmath>
#include "BST.h"

class HeapNode : public BSTNode {
private:
    BSTNode* parent = nullptr;
};

class MiniHeap : public BST
{
private:
    int count = 0;
    BSTNode *arr[20];

public:
    int getCount() { return count; }
    bool insert(Currency *insertData);
    BSTNode *search(Currency *key);
    Currency *remove(Currency *deleteData);
    int parentPoint(int i);
    int left_child(int i);
    int right_child(int i);
    void reheapUp(int position);
    void reheapDown(int position);
    void makeBST(BSTNode *root, int i);
};

int MiniHeap::parent(int i)
{
    return (i - 1) / 2;
}

int MiniHeap::left_child(int i)
{
    return (2 * i + 1);
}

int MiniHeap::right_child(int i)
{
    return (2 * i + 2);
}

void MiniHeap::reheapUp(int position)
{
    std::cout << position << " " << parent(position) << std::endl;
    if ( parent(position) > -1 && position > 0 && arr[parent(position)] -> data -> isGreater(*arr[position] -> data))
    {

        BSTNode *swap = arr[parent(position)];
        arr[parent(position)] = arr[position];
        arr[position] = swap;
        reheapUp(parent(position));
    }
}

void MiniHeap::reheapDown(int position)
{
    int smallest = position;
    int left = left_child(position);
    int right = right_child(position);

    if (left < count && arr[smallest]->data->isGreater(*arr[left]->data))
    {
        smallest = left;
    }

    if (right < count && arr[smallest]->data->isGreater(*arr[right]->data))
    {
        smallest = right;
    }

    if (smallest != position)
    {
        BSTNode *swap = arr[position];
        arr[position] = arr[smallest];
        arr[smallest] = swap;
        reheapDown(smallest);
    }
}
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

    BSTNode *temp = new HeapNode();
    temp->data = insertData;
    // arr[count++] = temp;
    // insertSuccess = true;
    // int position = count - 1;
    
    // reheapUp(position);
    // makeBST(getRoot(),0);
if (count == 0)
{
    setRoot(temp);
    insertSuccess = true;
}
else
{
    int position = count;
    int n = 2;
    while (position % static_cast<int>(pow(2, n)) != position)
    {
        position = position % static_cast<int>(pow(2, n++));
    }
    int level = n - 1;
    BSTNode *iter = getRoot();
    int start = 0;
    int end = pow(2, n);
    for (int i = 0; i < level; i++)
    {
        if (((start + end) / 2) <= position)
        {
            if (i == level - 1)
            {
                iter->right = temp;
                temp -> parent = iter;
                insertSuccess = true;
            }
            else
            {
                iter = iter->right;
                start = (start + end) / 2;
            }
        }
        else
        {
            if (i == level - 1)
            {
                iter->left = temp;
                insertSuccess = true;
            }
            else
            {
                iter = iter->left;
                end = (start + end) / 2;
            }
        }
    }
    reheapUp(count);
}
return insertSuccess;

    return insertSuccess;
}

Currency *MiniHeap::remove(Currency *deleteData)
{
    bool removed = false;
    if (count == 0)
    {
        throw std::invalid_argument("Invalid data");
    }

    int index = -1;
    for (int i = 0; i < count; i++)
    {
        if (arr[count]->data->isEqual(*deleteData))
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        return nullptr;
    }

    Currency *removedData = arr[index]->data;
    arr[index] = arr[--count];
    delete arr[count];
    reheapDown(index);
    makeBST(getRoot(),0);
    return removedData;
}

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

// void MiniHeap::makeBST(BSTNode *root, int i)
// {
//     if (i == 0)
//     {
//         setRoot(arr[0]);
//         makeBST(root, ++i);
//     }
//     else if (root == nullptr)
//     {
//         return;
//     }
//     else
//     {
//         root->left = arr[left_child(i)];
//         makeBST(root->left, left_child(i));
//         root->right = arr[right_child(i)];
//         makeBST(root->right, right_child(i));
//     }
// }

void MiniHeap::makeBST(BSTNode *root, int i) {
    if (i >= count) {
        return;
    }

    if (i == 0) {
        setRoot(arr[0]);
        makeBST(getRoot(), ++i);
    } else {
        if (root == nullptr) {
            return;
        }

        int leftIndex = left_child(i);
        int rightIndex = right_child(i);

        if (leftIndex < count) {
            root->left = arr[leftIndex];
            makeBST(root->left, leftIndex);
        }

        if (rightIndex < count) {
            root->right = arr[rightIndex];
            makeBST(root->right, rightIndex);
        }
    }
}
// if (count == 0)
// {
//     setRoot(temp);
//     insertSuccess = true;
// }
// else
// {
//     int position = count;
//     int n = 2;
//     while (position % static_cast<int>(pow(2, n)) != position)
//     {
//         position = position % static_cast<int>(pow(2, n++));
//     }
//     int level = n - 1;
//     BSTNode *iter = getRoot();
//     int start = 0;
//     int end = pow(2, n);
//     for (int i = 0; i < level; i++)
//     {
//         if (((start + end) / 2) <= position)
//         {
//             if (i == level - 1)
//             {
//                 iter->right = temp;
//                 insertSuccess = true;
//             }
//             else
//             {
//                 iter = iter->right;
//                 start = (start + end) / 2;
//             }
//         }
//         else
//         {
//             if (i == level - 1)
//             {
//                 iter->left = temp;
//                 insertSuccess = true;
//             }
//             else
//             {
//                 iter = iter->left;
//                 end = (start + end) / 2;
//             }
//         }
//     }
//     reheapUp(count);
// }
// return insertSuccess;