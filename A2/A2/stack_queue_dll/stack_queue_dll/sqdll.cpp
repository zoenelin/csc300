#include "sqdll.h"

void enqueueFront(node *&head, node *&tail, int value)
{
    // Create the node to be inserted at the front
    node *newNode = new node;
    newNode->data = value;
    newNode->next = head;     // newNode points to first element in the list
    newNode->prev = nullptr;  // no prior elements befor newNode

    // If the deque is empty, then newNode also becomes both the head and the tail
    if (head == nullptr){
        head = tail = newNode;
    }
    else { // If not empty, just make newNode the head
        head->prev = newNode;
        head = newNode;
    }

}

// Task 2: Complete the enqueueBack function to implement a doubly ended queue
void enqueueBack(node *&head, node *&tail, int value)
{
    // Create the node to be inserted at the back
    node *newNode = new node;
    newNode->data = value;
    newNode->next = nullptr; // newNode points to nullptr as its the tail
    newNode->prev = tail;  // previous newNode points to tail 

    // If the deque is empty, then newNode also becomes both the head and the tail
    if (head == nullptr)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode; // the tail point to newNode
        tail = newNode; // tail updates the newNode
    }

}

// Task 2: Complete the dequeueFront function to implement a doubly ended queue
void dequeueFront(node *&head, node *&tail)
{
    // Displays a message and returns the que is empty
    if(head == nullptr)
    {
        cout << "Que is empty, nothing to dequeue" << endl;
        return;
    }
    node *dltTemp = head; // save the head node of deleted 
    head = head->next; // head pointer is updated to next

    // if the que becomes empty then tail is updated
    if(head == nullptr)
    {
        tail = nullptr;
    }
    else
    {
        head->prev = nullptr; // prev pointer of new head updates
    }
    delete dltTemp; // frees the memory of the deleted node

}

// Task 2: Complete the dequeueBack function to implement a doubly ended queue
void dequeueBack(node *&head, node *&tail)
{
    // Displays a message and reutns the que is empty
    if(head == nullptr)
    {
        cout << "Que is empty, nothing to dequeue" << endl;
        return;
    }
    node *dltTemp = tail; // save the tail node of deleted 
    tail = tail->prev; // tail pointer is updated to previous
    
    // if the que becomes empty then head is updated
    if(tail == nullptr)
    {
        head = nullptr;
    }
    else
    {
        tail->next = nullptr; // next pointer of new tail updates
    }
    delete dltTemp; // frees the memory of the deleted node

}

void displayList(node *head)
{
    node *walker = head;

    while(walker != nullptr){
        cout << walker->data << " ";
        walker = walker -> next;
    }
    cout << endl;
}
