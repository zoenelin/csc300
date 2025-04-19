#include "heap.h"

HEAP::HEAP(int size) {
    capacity = size;
    heapSize = 0;
    array = new int[capacity];
}

HEAP::~HEAP() {
    delete[] array;
}

int HEAP::leftChild(int index) {
    return 2*index + 1;
}
int HEAP::rightChild(int index) {
    return 2*index + 2;
}
int HEAP::parent(int index) {
    return (index - 1) / 2;
}

void HEAP::insertH(int data) {
    if (heapSize == capacity) {
        cout << "Heap overflow - can't insert"<< endl;
        return;
    }

    array[heapSize] = data;
    heapifyUp(heapSize);
    heapSize++;
}

void HEAP::heapifyUp(int index) {
    while(index != 0 && array[parent(index)] < array[index]) {
        swap(array[parent(index)], array[index]);
        index = parent(index);
    }
}

int HEAP::peek() {
    if (heapSize <= 0) {
        cout << "Heap is empty" << endl;
        return -1;
    }

    return array[0];
}

void HEAP::deleteMax() {
    if (heapSize <= 0) {
        cout << "Heap is empty - nothing to delete" << endl;
        return;
    }

    if (heapSize == 1) {
        heapSize--;
        return;
    }

    array[0] = array[heapSize - 1];
    heapSize--;

    heapifyDown(0);
}

void HEAP::deleteH(int data) {
    int index = -1;

    // search for data - linear search :( O(n)
    for (int i = 0; i < heapSize; i++) {
        if (array[i] == data) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Element not found - can't delete"  << endl;
        return;
    }

    array[index] = array[heapSize - 1];
    heapSize--;

    heapifyDown(index);
}

// Task 1 = implement heapifyDown() function
void HEAP::heapifyDown(int index) 
{
    while (leftChild(index) < heapSize) {
        int largest = leftChild(index);
        if (rightChild(index) < heapSize && array[rightChild(index)] > array[largest]) {
            largest = rightChild(index);
        }
        if (array[index] >= array[largest]) {
            break;
        }
        swap(array[index], array[largest]);
        index = largest;
    }
}

// Task 2 - implement buildH() function 
void HEAP::buildH(int arr[], int n) 
{
    if (array != nullptr)
    {
        delete[] array;
    }

    heapSize = n;
    capacity = n;
    array = new int[capacity];

    for (int i = 0; i < n; i++)
    {
        array[i] = arr[i];
    }

    for (int i = (n / 2) - 1; i >= 0; i--)
    {
        heapifyDown(i);
    }
}

// Task 3 implement replace() function 
void HEAP::replace(int oldData, int newData)
{
    int index = -1;
    for (int i = 0; i < heapSize; i++)
    {
        if (array[i] == oldData)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        return;
    }

    array[index] = newData;

    if (newData > oldData)
    {
        heapifyUp(index);
    }
    else
    {
        heapifyDown(index);
    }
}

// Task 4 - Implement heapSort() function
void HEAP::heapSort(int arr[], int n)
{
    for (int i = (n / 2) - 1; i >= 0; i--)
    {
        int index = i;
        
        while (2 * index + 1 < n)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (arr[left] > arr[largest]) largest = left;
            if (right < n && arr[right] > arr[largest]) largest = right;

            if (largest == index) break;

            swap(arr[index], arr[largest]);
            index = largest;
        }
    }

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        int index = 0;

        while (2 * index + 1 < i)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (arr[left] > arr[largest]) largest = left;
            if (right < i && arr[right] > arr[largest]) largest = right;

            if (largest == index) break;

            swap(arr[index], arr[largest]);
            index = largest;
        }
    }
}

void HEAP::printHeap(int index, int depth) {
    if (index >= heapSize)
        return;

    printHeap(rightChild(index), depth + 1);

    for (int i = 0; i < depth; i++) {
        cout << "  "; // indentation based on depth
    }

    cout << array[index] << endl;

    printHeap(leftChild(index), depth + 1);
}

// Extra Credit Below!!!

// helper function for Min Heap
void HEAP::heapifyDownMin(int index)
{

}

void HEAP::switchMinMax()
{

}