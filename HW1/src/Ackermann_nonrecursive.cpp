#include <iostream>
using namespace std;

// 自定義堆疊結構
const int MAX_STACK_SIZE = 100000;  // 堆疊上限

struct Stack {
    int m[MAX_STACK_SIZE];
    int n[MAX_STACK_SIZE];
    int top;

    // 初始化
    Stack() {
        top = -1;
    }

    // 檢查堆疊是否為空
    bool Empty() {
        return top == -1;
    }

    // 推入堆疊
    void push(int mV, int nV) {  // mV = mValue, nV = nValue
        if (top < MAX_STACK_SIZE - 1) {
            top++;
            m[top] = mV;
            n[top] = nV;
        } else {
            cout << "堆疊溢位！" << endl;
            exit(1);
        }
    }

    // 彈出堆疊
    void pop() {
        if (!Empty()) {
            top--;
        } else {
            cout << "堆疊為空！" << endl;
            exit(1);
        }
    }

    // 取得堆疊頂部的 m 值
    int getM() {
        if (!Empty()) {
            return m[top];
        }
        return -1;  // 堆疊空
    }

    // 取得堆疊頂部的 n 值
    int getN() {
        if (!Empty()) {
            return n[top];
        }
        return -1;  // 堆疊空
    }
};

// 非遞迴 Ackermann
int Ackermann(int m, int n) {
    Stack stack;  // 使用自定義堆疊
    stack.push(m, n);

    while (!stack.Empty()) {
        m = stack.getM();  // 取得最上層 m 值
        n = stack.getN();  // 取得最上層 n 值
        stack.pop();  // 取值後消除堆疊最上層

        if (m == 0) {  // n+1, if m=0
            n += 1;
            if (!stack.Empty()) {
                int temp = stack.getM();
                stack.pop();          // 每次計算到 n+1 需要返回上一層
                stack.push(temp, n);  // m 值不變, 更新 n 的值
            }
        } else if (n == 0) {
            stack.push(m-1, 1);  // A(m-1, 1), if n=0
        } else {                 // A(m-1, A(m, n-1)), otherwise
            stack.push(m-1, -1); // 分解上式為 A(m-1, -1) 和 A(m, n-1),
            stack.push(m, n-1);  // 以模擬函式展開處理, 其中 -1 代表A(m, n-1)展開值
        }
    }

    return n;  //回傳最終值
}

int main() {
    int m, n;

    cout << "請輸入 m 和 n 的值: ";
    while(cin >> m >> n) {
        cout << "Ackermann(" << m << ", " << n << ") = " << Ackermann(m, n) << endl << "請輸入 m 和 n 的值: ";
    }
    
    return 0;
}
