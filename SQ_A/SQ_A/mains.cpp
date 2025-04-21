#include "sq.h"

int main()
{
    int choice, data, size, top;
    bool empty;

    Stack stack(5);

    do {
        cout << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Peek" << endl;
        cout << "4. isEmpty" << endl;
        cout << "5. size" << endl;
        cout << "6. Exit" << endl;
        cout << endl;

        cin >> choice;

        switch(choice)
        {
            case 1:
                cout << "What value do you want to push  ";
                cin >> data;
                stack.push(data);
                break;
            case 2:
                stack.pop();
                break;
            case 3:
                top = stack.peek();
                cout << "Peek: " << top << endl;
                break;
            case 4:
                empty = stack.isEmpty();
                cout <<"Is Empty: " << (empty ? "Yes" : "No") << endl;
                break;
            case 5:
                size = stack.size();
                cout <<"Size: " << size << endl;
                break;
            case 6:
                cout <<"See you" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
        stack.display();

    } while(choice != 6);

    return 0;
}