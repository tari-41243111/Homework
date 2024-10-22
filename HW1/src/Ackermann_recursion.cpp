#include <iostream>
using namespace std;

// 遞迴 Ackermann 直接套用規則
int Ackermann(int m,int n) {
    if (m==0)
        return n + 1;
    else if (n==0)
        return Ackermann(m - 1, 1);
    return Ackermann(m - 1, Ackermann(m, n - 1));
}

int main() {
    int m,n;
    cout << "請輸入 m 和 n 的值: ";
    while(cin>>m>>n) {
        cout << "Ackermann(" << m << ", " << n << ") = " << Ackermann(m,n) << endl << "請輸入 m 和 n 的值: ";
    }
}