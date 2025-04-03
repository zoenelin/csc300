#include "parse.h"

// ======================= PUBLIC FUNCTIONS ================================================

// Node constructor
Node::Node(string val)
{
    value = val;
    left = nullptr;
    right = nullptr; 
}

// Constructor - initializing root
Parser::Parser()
{
    root = nullptr; 
}

// Destructor - free tree memory
Parser::~Parser() 
{
    if (root) {
        if (root->left) {
            delete root->left;
        }
        if (root->right) {
            delete root->right;
        }
        delete root;
        root = nullptr; // avoids dangling pointer
    }
}

void Parser::preOrder() 
{
    preOrderTraversal(root);
    cout << endl;
}

void Parser::inOrder() 
{
    inOrderTraversal(root);
    cout << endl;
}

void Parser::postOrder() 
{
    postOrderTraversal(root);
    cout << endl;
}

double Parser::evaluate() 
{
    return evaluateTree(root);
}

Node* Parser::simplify() 
{
    root = simplifyTree(root);
    return root;
}

// Task 1
// push for buildExpressionTree
void push(node*& head, Node* value) 
{
    node* newNode = new node;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

// Task 1
// pop for buildExpressionTree
void pop(node*& head) 
{
    if (head == nullptr)
        return;

    node* temp = head;
    head = head->next;
    delete temp;
}

// Task 1
// Build the expression tree from a postfix expression
// Use the stack implementation from prior assignments
Node* Parser::buildExpressionTree(const string& postfix) {
    node* stack = nullptr; // initialize linked list

    for (size_t i = 0; i < postfix.length(); ++i) {
        char current = postfix[i];

        // For skipping spaces
        if (current == ' ') {
            continue;
        }

        // Handle numbers
        if (isdigit(current) || (current == '-' && i + 1 < postfix.length() && isdigit(postfix[i + 1]))) {
            int number = 0;
            bool isNeg = false;

            // for skipping any negative signs
            if (current == '-') {
                isNeg = true;
                i++; 
            }

            // construct the expression from postfix
            while (i < postfix.length() && isdigit(postfix[i])) {
                number = number * 10 + (postfix[i] - '0');
                i++;
            }
            i--;

            if (isNeg) number = -number;

            // create and push number to stack
            Node* newNode = new Node(to_string(number));
            push(stack, newNode);
        }
        // handles operators
        else if (current == '+' || current == '-' || current == '*' || current == '/') {
            if (!stack || !stack->next) {
                return nullptr; 
            }

            // pop 2 numbers from the stack
            Node* rightChild = stack->data;
            pop(stack);

            Node* leftChild = stack->data;
            pop(stack);

            // create new operator and set left and right child
            Node* newNode = new Node(string(1, current));
            newNode->left = leftChild;
            newNode->right = rightChild;

            // Push to stack
            push(stack, newNode);
        } else {
            return nullptr;
        }
    }

    // check for root
    if (!stack || stack->next) {
        return nullptr; 
    }

    Node* treeRoot = stack->data;
    pop(stack);

    root = treeRoot;
    return root;

}

// ======================= PRIVATE FUNCTIONS ================================================

// Check if the string is a number
bool Parser::isNumber(const string& s) {
    for (char c : s) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
    }
    return true;
}

// Recursive Pre-order traversal (C-L-R)
void Parser::preOrderTraversal(Node* node) {
    if (!node) 
        return;
    cout << node->value << " ";
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
}


// Recursive In-order traversal (L-C-R)
void Parser::inOrderTraversal(Node* node) {
    if (!node) 
        return;
    if (node->left) {
        cout << "( ";
        inOrderTraversal(node->left);
    }
    cout << node->value << " ";
    if (node->right) {
        inOrderTraversal(node->right);
        cout << ") ";
    }
}


// Recursive Post-order traversal (L-R-C)
void Parser::postOrderTraversal(Node* node) {
    if (!node) 
        return;
    postOrderTraversal(node->left);
    postOrderTraversal(node->right);
    cout << node->value << " ";
}

// Task 2
// Evaluate the expression tree
double Parser::evaluateTree(Node* node) {
    if (!node) return 0; // base case

    double result = 0;

    if (!node->left && !node->right)
    {
        bool negNum = false;
        int i = 0;

        // check if negative
        if (node->value[0] == '-')
        {
            negNum = true;
            i++;
        }

        // reads through the expression for numbers
        for (int j = i; node->value[j] != '\0'; j++)
        {
            if (node->value[j] < '0' || node->value[j] > '9')
            {
                return 0;
            }
        }

        // change string to integer
        while (node->value[i] != '\0')
        {
            result = result * 10 + (node->value[i] - '0');
            i++;
        }
        return negNum ? -result : result; // if needed - sign
    }

    // evaluates left and right subtrees 
    double leftValue = evaluateTree(node->left);
    double rightValue = evaluateTree(node->right);

    // operations
    if (node->value[0] == '+') return leftValue + rightValue;
    if (node->value[0] == '-') return leftValue - rightValue;
    if (node->value[0] == '*') return leftValue * rightValue;
    if (node->value[0] == '/') return leftValue / rightValue;

    return 0;
}

// Task 3
// Simplify the tree by applying constant folding and algebraic rules
Node* Parser::simplifyTree(Node* node) {
    if (!node) return nullptr; // base case

    // simplify left and right subtrees
    node->left = simplifyTree(node->left);
    node->right = simplifyTree(node->right);

    // constant folding 
    if (node->left && node->right && isNumber(node->left->value) && isNumber(node->right->value)) {
        double leftValue = evaluateTree(node->left);
        double rightValue = evaluateTree(node->right);
        double result = 0;

        // operations
        if (node->value[0] == '+') result = leftValue + rightValue;
        else if (node->value[0] == '-') result = leftValue - rightValue;
        else if (node->value[0] == '*') result = leftValue * rightValue;
        else if (node->value[0] == '/') result = leftValue / rightValue;
    

        // store as a string
        int intResult = (int)result;  
        int i = 0;

        // for negative numbers add - sign
        if (result < 0) {
            node->value[i++] = '-';
            intResult = -intResult;
        }

        // number count of result
        int temp = intResult;
        int numDigits = 0;

        do {
            temp /= 10;
            numDigits++;
        } while (temp > 0);

        // convert to string
        for (int j = numDigits - 1; j >= 0; --j) {
            node->value[i + j] = '0' + (intResult % 10);
            intResult /= 10;
        }

        // add null terminator
        i += numDigits;
        node->value[i] = '\0';

        // cleanup
        delete node->left;
        delete node->right;
        node->left = nullptr;
        node->right = nullptr;

        return node;
    }

    // algebraic simplification 
    if (node->value[0] == '*') {
        if (node->left->value[0] == '1' && node->left->value[1] == '\0') return node->right;
        if (node->right->value[0] == '1' && node->right->value[1] == '\0') return node->left;
        if ((node->left->value[0] == '0' && node->left->value[1] == '\0') ||
            (node->right->value[0] == '0' && node->right->value[1] == '\0')) {
            node->value[0] = '0';
            node->value[1] = '\0';
            delete node->left;
            delete node->right;
            node->left = nullptr;
            node->right = nullptr;
            return node;
        }
    }
    if (node->value[0] == '/') {
        if (node->right->value[0] == '1' && node->right->value[1] == '\0') return node->left;
    }

    return node;

}
