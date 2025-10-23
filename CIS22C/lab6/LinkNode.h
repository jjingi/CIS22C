// Lab#: Lab3
// Jin Gi Min
// Fumiya Koseki
// Link Node which has Currency pointer has data and next is pointer to the next Node

#pragma once
#ifndef LINKNODE_H
#define LINKNODE_H

#include <iostream>
#include <string>
#include "Currency.h"

struct LinkNode {
  Currency* data;
  LinkNode* next = nullptr;
};

#endif
