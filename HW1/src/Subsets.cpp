#include <iostream>
#include <string>
using namespace std;

// 使用遞迴來生成所有子集合
void getSubsets(char* elements, int size, int index, char* subset, int subsetSize) {
    // 當處理到最後一個元素時，輸出當前子集合
    if (index == size) {
        cout << "(";
        for (int i = 0; i < subsetSize; i++) {
            cout << subset[i] << ",";
        }
        if (subsetSize==0) {
            cout << "), ";
        } else {
            cout << "\b), ";
        }

        return;
    }

    // 不選擇當前元素
    getSubsets(elements, size, index + 1, subset, subsetSize);

    // 選擇當前元素
    subset[subsetSize] = elements[index];
    getSubsets(elements, size, index + 1, subset, subsetSize + 1);
}

int main() {
    string SetName;
    cout << "請輸入集合名稱: ";
    cin >> SetName;
    int size;
    cout << "請輸入集合大小: ";
    cin >> size;

    char *elements = new char[size]; // 定義集合陣列
    cout << "請輸入 "<< size <<" 個元素: ";
    for (int i = 0; i < size; i++) {
        cin >> elements[i]; // 讀取size個元素
    }

    char *subset = new char[size]; // 用來存儲子集合的暫存陣列
    cout << "(" << SetName << ") = {";
    getSubsets(elements, size, 0, subset, 0); // 遞迴生成子集合
    cout << "\b\b}" << endl;

    return 0;
}
