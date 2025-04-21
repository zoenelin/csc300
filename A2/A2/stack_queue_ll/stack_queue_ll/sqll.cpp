#include "sqll.h"

void push(node *&head, int value)
{
    node *newNode = new node;
    newNode->data = value;
    newNode->next = nullptr;

    // INSERT AT INDEX 0
    newNode->next = head;
    head = newNode;
}

void pop(node *&head)
{
    if(head == nullptr){
        cout << "Stack is empty, nothing to pop" << endl;
        return;
    }

    // remove the head
    node *dltTemp = head;
    head = head->next;

    delete dltTemp;

}

// Task 1: Complete the enqueue function
void enqueue(node *&head, int value) 
{
    // Creates a new node
    node *newNode = new node;
    newNode->data = value;
    newNode->next = nullptr;

    // Make the head point to the new node if the stack is empty
    if(head == nullptr)
    {
        head = newNode;
    }
    else
    {
        // Moves to the end of the stack
        node *temp = head;
        while(temp->next != nullptr)
        {
            temp = temp->next;
        }
        // Adds the new node to the end of the stacks
        temp->next = newNode;
    }
}

// Task 2: Complete the dequeue function
void dequeue(node *&head) 
{
    // Displays a message and returns the stack is empty
    if(head == nullptr)
    {
        cout << "Stack is empty, nothing to dequeue" << endl;
        return;
    }
    else
    {
        node *temp = head; // Saves the next node to head
        head = head->next; // Updates the head
        delete temp; // free memory
    }
}

void displayList(node *head)
{
    node *walker = head;

    while(walker != nullptr){
        cout << walker->data << " ";
        walker = walker->next;
    }
    cout << endl;
}