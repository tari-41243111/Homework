#include <iostream>

using namespace std;

extern void print_arr(int* arr, int size);
extern void change_size(int*& arr, int size, int new_size);
extern void copy(int* arr, int* are_end, int* new_arr);

void print_arr(int* arr, int size) {
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << '\n';
}

void change_size(int*& arr, int size, int new_size) {
    int* new_arr = new int[new_size] {0};
    int* recycler = arr;
    copy(arr, arr + size, new_arr);

    // Increase every elements by size.
    for (int i = 0; i < new_size; i++) new_arr[i] += new_size;

    delete[] recycler;
    arr = new_arr;
}

void copy(int* arr, int* arr_end, int* new_arr)
{
    int i = 0;
    while ((arr+i) != arr_end)
    {
        new_arr[i] = arr[i];
        i++;
    }
}

int main() {
    int size = 3;
    int* arr = new int[size];

    // Inserting elements.
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    };

    print_arr(arr, size);  // Print initial array.

    int new_size = size * 2;
    change_size(arr, size, new_size);
    print_arr(arr, new_size);  // Size has changed, print the new array.
}
/*
    41243111 王家偉
    我使用 size*2
    我覺得再次數上比 size+2 少
    在空間上又比 size*size 少
*/