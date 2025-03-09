#include "bstP.h"

node::node(int value)
{
    data = value;
    leftChild = nullptr;
    rightChild = nullptr;
}

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

void BST::clearTree(node* node)
{
    if(node == nullptr)
        return;
    
    clearTree(node->leftChild);
    clearTree(node->rightChild);
    delete node;
}

// Task 5: Modify the existing insert() functions to check and handle duplicate insertions
void BST::insertNode(node*& root, int data)
{
    if(root == nullptr)
    {
        root = new node(data);
        return;
    }

    if(data < root->data)
        insertNode(root->leftChild, data);
    else if (data > root->data)
        insertNode(root->rightChild, data);
    else    // Task 5
        cout << "value: " << data << "has already been inserted. Enter a different value" << endl;
}

node* BST::searchNode(node*& root, int data)
{
    if (root == nullptr || root->data == data)
        return root;
    if (data < root->data)
        return searchNode(root->leftChild, data);
    return searchNode(root->rightChild, data);
}

void BST::deleteNode(node*& root, int data)
{
    if (root == nullptr)
        return;

    if (data < root->data)
        deleteNode(root->leftChild, data);
    else if (data > root->data)
        deleteNode(root->rightChild, data);
    else {
        if (root->leftChild == nullptr) {
            node* temp = root->rightChild;
            delete root;
            root = temp;
        }
        else if (root->rightChild == nullptr) {
            node* temp = root->leftChild;
            delete root;
            root = temp;
        }
        else {
            node* temp = root->rightChild;
            while (temp->leftChild != nullptr)
                temp = temp->leftChild;
            root->data = temp->data;
            deleteNode(root->rightChild, temp->data);
        }
    }
}

void BST::preorder(node* root)
{
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preorder(root->leftChild);
    preorder(root->rightChild);
}

void BST::inorder(node* root)
{
    if (root == nullptr)
        return;
    inorder(root->leftChild);
    cout << root->data << " ";
    inorder(root->rightChild);
}

void BST::postorder(node* root)
{
    if (root == nullptr)
        return;
    postorder(root->leftChild);
    postorder(root->rightChild);
    cout << root->data << " ";
}


void BST::printTree(node* root, int space)
{
    const int COUNT = 10;
    if (root == nullptr)
        return;
    space += COUNT;
    printTree(root->rightChild, space);
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->data << endl;
    printTree(root->leftChild, space);
}

// Task 1: Implement height() function 
int BST::height(node* node)
{
    if (node == nullptr)
        return 0;
    int heightL = height(node->leftChild);
    int heightR = height(node->rightChild);
    return 1 + max(heightL, heightR);
}

// Task 2: Implement countNodes() function
int BST::countNodes(node* node)
{
    if (node == nullptr)
        return 0;
    int countL = countNodes(node->leftChild);
    int countR = countNodes(node->rightChild);
    return 1 + countL + countR;
}

// Task 3: Implement isBalanced() function -- this is the helper function
int BST::isBalancedHelper(node* node)
{
    if (node == nullptr)
        return 0;
    int heightL = isBalancedHelper(node->leftChild);
    int heightR = isBalancedHelper(node->rightChild);
    if (heightL == -1 || heightR == -1 || heightL - heightR > 1)
        return -1;
    else
        return 1 + (heightL > heightR ? heightL : heightR);
}

// Task 3: Implement isBalanced() function
bool BST::isBalanced(node* node)
{
    return isBalancedHelper(node) != -1;
}

// Task 4: Implement BFS() function
void BST::BFS(node* root)
{
    if (root == nullptr)
        return;
    class Queue
    {
        private:
            int capacity;
            node** arr;
            int front;
            int rear;
            int queue_size;
        
        public:
            Queue(int cap)  // constructor
            {
                capacity = cap;
                arr = new node*[capacity];
                front = 0;
                rear = -1;
                queue_size = 0;
            }

            ~Queue()    // destructor
            {
                delete[] arr;
            }

            void enqueue(node* value)   // insert node into queue
            {
                if (rear >= capacity -1)
                {
                    cout << "Queue overflow" << endl;
                    return;
                }

                if (isEmpty())
                {
                    front = 0;
                    rear = 0;
                }
                else
                {
                    rear++;
                }
                arr[rear] = value;
                queue_size++;
            }

            node* dequeue()     // remove node from queue
            {
                if (isEmpty())
                {
                    cout << "Queue underflow" << endl;
                    return nullptr;
                }

                node* dequeued = arr[front];
                front++;
                queue_size--;

                if (isEmpty())
                {
                    cout << "Queue underflow" << endl;
                    return nullptr;
                }

                front++;
                queue_size--;

                if (isEmpty())
                {
                    front = -1;
                    rear = -1;
                }

                return dequeued;
            }

            bool isEmpty()
            {
                return queue_size == 0;
            }
    };
    
    Queue q(20);

    q.enqueue(root);

    while (!q.isEmpty())
    {
        node* current = q.dequeue();
        cout << current->data << " ";

        if (current->leftChild != nullptr)
            q.enqueue(current->leftChild);
        if (current->rightChild != nullptr)
            q.enqueue(current->rightChild);
    }
}



