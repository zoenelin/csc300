#ifndef SQLL_H
#define SQLL_H

#include <iostream>
using namespace std;

class Node;

struct node{
    Node* data;
    struct node* next;
};

void push(node*& head, Node* value); 
void pop(node*& head);

#endif