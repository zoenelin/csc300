#ifndef LL_H
#define LL_H

#include <iostream>
using namespace std;

struct node
{
    int data;
    struct node *next;
    node *prev; // Task 3: convert InsertNode and deleteNode into doubly linked list
};

void insertNode(node *&head, int index, int data);
void deleteNode(node *&head, int index);
void displayList(node *head);
node* searchNode(node *head, int key);
node* reverseList(node *head); // Task 2: implement a function called reverseList


#endif