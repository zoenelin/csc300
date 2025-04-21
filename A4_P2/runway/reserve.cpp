#include "reserve.h"

reservation::reservation(int t) {
    time = t;
    left = nullptr;
    right = nullptr; 
}


BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

void BST::clearTree(reservation* node)
{
    if (root == nullptr)
        return;

    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// reserve new landing time
bool BST::reserve(int time) 
{
    if (checkConflict(root, time)) {
        return false; // conflict - reservation fails
    }
 
    insert(root, time); 
    return true; // no conflict - reservation successful
}

// check for landing time conflicts within 3 minutes (Use recursion)
bool BST::checkConflict(reservation* node, int time) 
{
    if (node == nullptr) // no conflict if empty
    {
        return false;
    }
    
    if (time >= node->time - 3 && time <= node->time + 3) // check landing time is within 3-min interval(s) of node 
    {
        return true;
    }

    if (time < node->time) // checks left or right subtree for conflicts
    {
        return checkConflict(node->left, time);
    }
        else
        {
            return checkConflict(node->right, time);
        }
}

// insert new reservation and update subtree size (make sure to avoid inserting duplicates)
void BST::insert(reservation*& node, int time) 
{
    if (node == nullptr) // if empty, create new reservation
    {
        node = new reservation(time);
        node->subtreeSize = 1; // initialization of subtree size 
        return;
    }

    // using recursion insert time at left or right subtree
    if (time < node->time)
    {
        insert(node->left, time);
    }
    else if (time > node->time)
    {
        insert(node->right, time);
    }
    else
    {
        return;
    }

    // same as before - just make sure to update subtree size for inserted node

    // update subtree size 
    node->subtreeSize = 1;
    if (node->left != nullptr)
    {
        node->subtreeSize =+ node->left->subtreeSize;
    }
    if (node->right != nullptr)
    {
        node->subtreeSize =+ node->right->subtreeSize;
    }
}

// Count nodes with times <= t
int BST::countPlanes(reservation* node, int t) 
{
    if (node == nullptr) // if empty count equals 0
    {
        return 0;
    }
    if (node->time <= t) // count all nodes in left and right subtrees that are less than or equal to t
    {
        return 1 + countPlanes(node->left, t) + countPlanes(node->right, t);   
    }
    else
    {
        return countPlanes(node->left, t); // counts only nodes in left subtree that are greater or equal to t 
    }
}

void BST::inorder(reservation* root)
{
    if (root == nullptr)
        return;
    
    inorder(root->left);
    cout << root->time << " ";
    inorder(root->right);
}