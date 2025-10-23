//Lab#: Lab4
//Fumiya Koseki
//Jin Gi Min
#pragma once
#ifndef BST_H
#define BST_H
#include "Dollar.h"
#include "Queue.h"
#include <fstream>
#include <iostream>

class BSTNode {
public:
  Currency *data = nullptr;
  BSTNode *left = nullptr;
  BSTNode *right = nullptr;
  BSTNode() : data(nullptr), left(nullptr), right(nullptr) {}
  /*
  set the data of BSTNode
  pre: data - currency pointer data
  post:
  return:
  */
  void setData(Currency *data) { this->data = data; }
  /*
  get the data of BSTNode
  pre:
  post:
  return: data - Currency object that is stored in the node
  */
  Currency *getData() { return data; }
  /*
  set the left node of BSTNode
  pre: left - BSTNode pointer points left child Node in BST
  post:
  return:
  */
  void setLeft(BSTNode *left) { this->left = left; }
  /*
  get the left node of BSTNode
  pre:
  post:
  return: left - pointer to the left node
  */
  BSTNode *getLeft() { return left; }
  /*
  set the right node of BSTNode
  pre: right - BSTNode pointer points right child Node in BST
  post:
  return:
  */
  void setRight(BSTNode *right) { this->right = right; }
  /*
  get the right node of BSTNode
  pre:
  post:
  return: right - pointer to the right node
  */
  BSTNode *getRight() { return right; }
  void destroyBSTNode();
};

/*
destroy the all the BSTNode in the tree recursively
pre:
post:
return:
*/
void BSTNode::destroyBSTNode() {
  if (this->left) 
    this -> left->destroyBSTNode();
    delete this->left;
  
  if (this->right) 
    this->right->destroyBSTNode();
    delete this->right;
}

class BST {
private:
  std::string breadthFirstTraversalRecur(BSTNode *tree);  
  std::string preorderTraversalRecur(BSTNode *tree);
  std::string inorderTraversalRecur(BSTNode *tree);
  std::string postorderTraversalRecur(BSTNode *tree);
  bool insertRecursive(BSTNode *parent, BSTNode *temp);
  BSTNode *searchRecur(BSTNode *tree, Currency *key);
  void destroyBST();

public:
  BSTNode *root = nullptr;
  BST() : root(nullptr) {}
  virtual ~BST() {destroyBST(); }
  /*
  get the root of the BST
  pre:
  post:
  return: root - pointer to the root of the BST
  */
  BSTNode *getRoot() { return root; }
  /*
  set the root of the BST
  pre: root - BSTNode pointer points the root of the BST
  post:
  return:
  */
  void setRoot(BSTNode *root) { this->root = root; }
  /*
  call the breadthFirstTraversal Recursively
  pre:
  post:
  return: the result of breadth first traversal
  */
  std::string breadthFirstTraversal() {return breadthFirstTraversalRecur(root);}
  /*
  call the preorderTraversal Recursively
  pre:
  post:
  return: the result of preorder traversal
  */
  std::string preorderTraversal() {return preorderTraversalRecur(root);}
  /*
  call the inorderTraversal Recursively
  pre:
  post:
  return: the result of inorder traversal
  */
  std::string inorderTraversal() {return inorderTraversalRecur(root);}
  /*
  call the postorderTraversal Recursively
  pre:
  post:
  return: the result of postorder traversal
  */
  std::string postorderTraversal() {return postorderTraversalRecur(root);}
  /*
  search the key in the BST
  pre: key - Currency object that is going to be searched
  post:
  return: the BSTNode that has the key
  */
  virtual BSTNode *search(Currency *key) {return searchRecur(root, key);}
  virtual bool insert(Currency *insertData);

  virtual Currency *remove(Currency *deleteData);
  void print(std::ofstream &outFile);
  int count(BSTNode *tree);
  /*
  check the tree is empty
  pre:
  post:
  return: true is root is nullptr otherwise, return false
  */
  bool isEmpty() {return root == nullptr; }

  /*
  check the node is empty
  pre:
  post:
  return: true is node is nullptr otherwise, return false
  */
  bool isNodeEmpty(BSTNode *node) { return node == nullptr; }
};




/*
show the breadth first traversal with recursively
pre: tree - parameter of the recursive function. check tree is not nullptr
post:
return: the result of breadth first traversal
*/
std::string BST::breadthFirstTraversalRecur(BSTNode *tree) {
  std::string traversalData = "";
  if (tree == nullptr) {
    return traversalData;
  }
  Queue que;
  que.enqueue(tree->data);

  while (!que.isQueueEmpty()) {
      Currency *nodeKey = que.peekFront();
      traversalData += nodeKey->toString() + "\t";
      BSTNode *node = search(nodeKey);
      que.dequeue();

      if (node->left != nullptr) {
        que.enqueue(node->left->data);
      }
      if (node->right != nullptr) {
        que.enqueue(node->right->data);
      }
    
  }

  return traversalData;
}

/*
show the preorder traversal with recursively
pre: tree - parameter of the recursive function. check tree is not nullptr
post:
return: the result of preorder traversal
*/
std::string BST::preorderTraversalRecur(BSTNode *tree) {
  std::string traversalData = "";
  if (!isNodeEmpty(tree)) {
    traversalData += tree->data->toString() + "\t";
    traversalData += preorderTraversalRecur(tree->left);
    traversalData += preorderTraversalRecur(tree->right);
  }
  return traversalData;
}

/*
show the inorder traversal with recursively
pre: tree - parameter of the recursive function. check tree is not nullptr
post:
return: the result of inorder traversal
*/
std::string BST::inorderTraversalRecur(BSTNode *tree) {
  std::string traversalData = "";
  if (!isNodeEmpty(tree)) {
    traversalData += inorderTraversalRecur(tree->left);
    traversalData += tree->data->toString() + "\t";
    traversalData += inorderTraversalRecur(tree->right);
  }
  return traversalData;
}

/*
show the postorder traversal with recursively
pre: tree - parameter of the recursive function. check tree is not nullptr
post:
return: the result of postorder traversal
*/
std::string BST::postorderTraversalRecur(BSTNode *tree) {
  std::string traversalData = "";
  if (!isNodeEmpty(tree)) {
    traversalData += postorderTraversalRecur(tree->left);
    traversalData += postorderTraversalRecur(tree->right);
    traversalData += tree->data->toString() + "\t";
  }
  return traversalData;
}

/*
search the key in the BST
pre: tree - parameter of the recursive function. check tree is not nullptr
post:
return: the BSTNode that has the key
*/
BSTNode *BST::searchRecur(BSTNode *tree, Currency *key) {
  if (tree == nullptr) {
    return nullptr;
  } else if (tree->data->isEqual(*key)) {
    return tree;
  } else if (tree->data->isGreater(*key)) {
    return searchRecur(tree->left, key);
  } else {
    return searchRecur(tree->right, key);
  }
}

/*
insert the key in the BST
pre: insertData - Currency object that is going to be inserted
post:
return: if the key is inserted successfully, return true, otherwise return false
*/
bool BST::insert(Currency *insertData) {
  bool insertSuccess = false;
  if (insertData == nullptr) {
    return false;
  }
  else if (Dollar(0).isGreater(*insertData)) {
    return false;
  }

  BSTNode *temp = new BSTNode();
  temp->data = insertData;

  if (root == nullptr) {
    root = temp;
    insertSuccess = true;
  } else {
    insertSuccess = insertRecursive(root, temp);
  }
  return insertSuccess;
}

/*
insert the key in the BST recursively
pre: parent - BSTNode pointer points the parent of the BSTNode that is going to be      inserted also used for recursive function
     insertNode - BSTNode pointer points the BSTNode that is going to be inserted
post:
return: if the key is inserted successfully, return true, otherwise return false
*/
bool BST::insertRecursive(BSTNode *parent, BSTNode *insertNode) {
  bool insertSuccess = false;
  if (parent->data->isEqual(*insertNode->data)) {
    insertSuccess = false;
  } else if (parent->data->isGreater(*insertNode->data)) {
    if (parent->left == nullptr) {
      parent->left = insertNode;
      insertSuccess = true;
    } else {
      insertSuccess = insertRecursive(parent->left, insertNode);
    }
  } else {
    if (parent->right == nullptr) {
      parent->right = insertNode;
      insertSuccess = true;
    } else {
      insertSuccess = insertRecursive(parent->right, insertNode);
    }
  }
  return insertSuccess;
}

/*
remove the key in the BST
pre: deleteData - Currency object that is going to be deleted
post:
return: if the key is deleted successfully, return true, otherwise return false
*/
Currency *BST::remove(Currency *deleteData) {
  BSTNode *parent = nullptr;
  BSTNode *current = root;
  Currency* deletedCurrency = nullptr;
  while (current != nullptr) {
    if (current->data->isEqual(*deleteData)) {
      deletedCurrency = current -> data;
      if (current->left == nullptr && current->right == nullptr) {
        if (parent == nullptr) {
          root = nullptr;
        } else if (parent->left == current) {
          parent->left = nullptr;
        } else {
          parent->right = nullptr;
        }
        delete current;
      } else if (current->right == nullptr) {
        if (parent == nullptr) {
          root = current->left;
        } else if (parent->left == current) {
          parent->left = current->left;
        } else {
          parent->right = current->left;
        }
        delete current;
      } else if (current->left == nullptr) {
        if (parent == nullptr) {
          root = current->right;
        } else if (parent->left == current) {
          parent->left = current->right;
        } else {
          parent->right = current->right;
        }
        delete current;
      } else {
        BSTNode *succesor = current->right;
        while (succesor->left != nullptr) {
          succesor = succesor->left;
        }
        Currency *temp = succesor->data;
        remove(succesor->data);
        current->data = temp;
      }
      return deletedCurrency;
    } else if (deleteData->isGreater(*current->data)) {
      parent = current;
      current = current->right;
    } else {
      parent = current;
      current = current->left;
    }
  }
  return nullptr;
}


/*
show the BST in the console
pre: outFile - output file stream
post:
return:
*/
void BST::print(std::ofstream &outFile) {
  std::cout << "Breadth-First Traversal: " << breadthFirstTraversal();
  outFile << "Breadth-First Traversal: " << breadthFirstTraversal();
  std::cout << std::endl << std::endl;
  outFile << std::endl << std::endl;
  
  std::cout << "Inorder Traversal: " << inorderTraversal();
  outFile << "Inorder Traversal: " << inorderTraversal();
  std::cout << std::endl << std::endl;
  outFile << std::endl << std::endl;
  
  std::cout << "Preorder Traversal: " << preorderTraversal();
  outFile << "Preorder Traversal: " << preorderTraversal();
  std::cout << std::endl << std::endl;
  outFile << std::endl << std::endl;

  std::cout << "Postorder Traversal: " << postorderTraversal();
  outFile << "Postorder Traversal: " << postorderTraversal();
  std::cout << std::endl << std::endl;
  outFile << std::endl << std::endl;
}

/*
count the number of nodes in the BST
pre: tree - parameter of the recursive function. check tree is not nullptr
post:
return: the number of nodes in the BST
*/
int BST::count(BSTNode *tree) {
  if (root == nullptr) {
    return 0;
  }
  Queue que;
  int count = 0;
  que.enqueue(root->data);
  while (!que.isQueueEmpty()) { // isListEmpty is protected
    // Currency* copy = new Currency(*que.peekFront());
    //  I cannot make Currency copy since it is abstract
    // nvm it should be working

      Currency *nodeKey = que.peekFront();
      count++;
      BSTNode *node = search(nodeKey);
      que.dequeue();
      if (node->left != nullptr) {
        que.enqueue(node->left->data);
      }
      if (node->right != nullptr) {
        que.enqueue(node->right->data);
      }
  }
  return count;
}

/*
count the number of leaf nodes in the BST
pre: tree - parameter of the recursive function. check tree is not nullptr
post:
return: the number of leaf nodes in the BST
*/
void BST::destroyBST() {

  if (this->root) {
    this -> root->destroyBSTNode();
    delete this->root;
    this->root = nullptr;
  }
}

#endif

/* Question

1. what does count do
2. In which order should print() print
3. does use of lab3 queue mean add and submit a queue and linkedlist file?
4. what does traversal do ? print? return array of Currency*, can we use
ofstream as a parameter?
*/

/*
new question
can I modify Queue since isNodeEmpty() is not accessible because I don't have
isNodeEmpty in Queue() and SinglyLinkedList is protected
  */
//junk code
// std::string BST::breadthFirstTraversal(BSTNode *tree) {
//   // std::queue<BSTNode*> que;
//   // que.push(root);
//   // while(!que.empty()){
//   //   BSTNode* node =  que.front();
//   //   node->data->print();
//   //   que.pop();
//   //   if(node->left != nullptr){
//   //     que.push(node->left);
//   //   }
//   //   if(node->right != nullptr){
//   //     que.push(node->right);
//   //   }
//   // }
//   std::string traversalData = "";
//   Queue que;
//   Currency* nodeKey;
//   BSTNode* node;
//   int peekCount = 0;
//   que.enqueue(root->data);
//   while(que.peekFront() != nullptr){//isListEmpty is protected
//     //Currency* copy = new Currency(*que.peekFront());
//     // I cannot make Currency copy since it is abstract
//     //nvm it should be working
//     nodeKey = que.peekFront();
//     peekCount++;
//     traversalData += nodeKey->toString() + "\t";
//     node = search(tree, nodeKey);
//     que.dequeue();
//     if(node->left != nullptr){
//       que.enqueue(node->left->data);
//     }
//     if(node->right != nullptr){
//       que.enqueue(node->right->data);
//     }
//   }
//   nodeKey = que.peekFront();
//   traversalData += nodeKey -> toString() + "\t";
//   que.dequeue();
//   return traversalData;
// }