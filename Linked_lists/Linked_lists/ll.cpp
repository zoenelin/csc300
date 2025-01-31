#include "ll.h"

void insertNode(node *&head, int index, int data) // Task 3: Convert into doubly linked list
{
    node* newNode = new node;
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr; // Initializing  prev - Task 3

    if(index == 0)
    {
        newNode->next = head;
        if (head != nullptr) // prev set to newNode - Task 3
        {
            head->prev = newNode; 
        }
        head = newNode;
    }
    else
    {
        node* walker = head;
        int wIndex = 0;
        while(walker != NULL && wIndex < index-1)
        {
            walker = walker->next;
            wIndex++;
        }
        if(walker == nullptr)
        {
            cout << "Index is too large, can't insert" << endl;
            return;
        }
        else
        {
            newNode->next = walker->next;
            newNode->prev = walker; // Task 3
            if (walker->next != nullptr)
            {
                walker->next->prev = newNode; // Task 3
            }
            walker->next = newNode;
        }

    }
}

// Task 1: Complete deleteNode function
void deleteNode(node *&head, int index) // Task 3: Convert into a doubly linked list
{
    if(head == nullptr)
    {
        cout << "List is empty, nothing to delete" << endl;
        return;
    }
    if(index == 0)
    {
        node* temp = head; // temp is a placeholder for head - Task 1
        head = head->next;
        if (head != nullptr)
        {
            head->prev = nullptr; // Task 3
        }
        delete temp;
    }
    else
    {
        node* walker = head;
        int wIndex = 0;
        while(walker != nullptr && wIndex < index-1)
        {
            walker = walker->next;
            wIndex++;
        }
        if(walker == nullptr || walker->next == nullptr)
        {
            cout << "Index is too large, can't delete" << endl;
            return;
        }
        else
        {
            node* temp = walker->next; 
            walker->next = walker->next->next; 
            if (walker->next != nullptr)
            {
                walker->next->prev = walker; // update prev - Task 3
            }
            delete temp;
        }
        
    }
}    

void displayList(node *head) 
{
    node* walker = head;

    while(walker != nullptr)
    {
        cout << walker->data<<" ";
        walker = walker->next;
    }
    cout<<endl;

}

node* searchNode(node *head, int key) // Task 1: complete the searchNode function
{
    node* walker = head;
    int index = 0;
    while(walker != nullptr)
    {
        if(walker->data == key)
            return walker;
        walker = walker->next;
    }
    return nullptr;
}

node* reverseList(node *head) // Task 2: implement a function called reverseList
{
    if(head == nullptr)
    {
        cout << "nothing to reverse, please insert nodes before reversing list." << endl;
        return head;
    }

    node* prev = nullptr; //   ^
    node* current = head; //   ^
    node* next = nullptr; // initialize

    while (current != nullptr) // reverses the list
    {
        next = current->next;
        current->next = prev; // reverse
        prev = current; 
        current = next;
        prev->data;
    }
    return prev; // new head of the now reversed list
}