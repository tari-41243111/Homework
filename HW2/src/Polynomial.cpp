#include <iostream>
#include <cmath>
using namespace std;

class Term;
class Polynomial;

// ========== 多項式項數單位
class Term
{
friend Polynomial;
friend ostream& operator<<(ostream& output, const Polynomial& poly);
private:
    float coef; // 係數
    int exp;    // 次數
};

// ========== 多項式類別
class Polynomial
{
friend ostream& operator<<(ostream& output, const Polynomial& poly);
private:
    Term *termArray; // 存放多項式的陣列
    int capacity;    // 陣列配置大小
    int terms;       // 非零項數
public:
    Polynomial()
    {
        termArray = new Term[2];
        capacity = 2;
        terms = 0;
    }
    
    // ---------- 新增一個項數到多項式
    void newTerm(const float theCoef, const int theExp)  
    {
        if(terms==capacity) 
        {
            capacity *=2;
            Term* new_termArray = new Term[capacity];
            Term* recycler = termArray;

            for (int i = 0; i < terms; ++i) {
                new_termArray[i] = termArray[i];
            }

            delete[] recycler;
            termArray = new_termArray;
        }

        termArray[terms].coef=theCoef;
        termArray[terms++].exp=theExp;
    }

    // ---------- 依照次數大到小排序
    void Soft ()
    {
        for (int i = 0; i < terms - 1; i++) {
            for (int j = 0; j < terms - i - 1; j++) {
                if (termArray[j].exp < termArray[j + 1].exp) {
                    Term temp = termArray[j];
                    termArray[j] = termArray[j + 1];
                    termArray[j + 1] = temp;
                }
            }
        }
    }

    // ---------- 多項式相加
    Polynomial Add(Polynomial poly)
    {
        Soft();
        poly.Soft();

        Polynomial result;
        int i = 0, j = 0;

        while (i < this->terms || j < poly.terms)
        {
            if (j >= poly.terms || this->termArray[i].exp > poly.termArray[j].exp)
            {
                result.newTerm(this->termArray[i].coef, this->termArray[i].exp);
                i++;
            } 
            else if (i >= poly.terms || this->termArray[i].exp < poly.termArray[j].exp)
            {
                result.newTerm(poly.termArray[j].coef, poly.termArray[j].exp);
                j++;
            }
            else
            {
                float sumCoef = this->termArray[i].coef + poly.termArray[j].coef;
                if (sumCoef != 0) result.newTerm(sumCoef, this->termArray[i].exp);
                i++; j++;
            } 
        }

        return result;
    }

    // ---------- 多項式相乘
    Polynomial Mult(Polynomial poly)
    {
        Polynomial result;

        for (int i = 0; i < this->terms; ++i)
        {
            for (int j = 0; j < poly.terms; ++j)
            {
                float newCoef = this->termArray[i].coef * poly.termArray[j].coef;
                int newExp = this->termArray[i].exp + poly.termArray[j].exp;

                bool contain = false;
                for (int k = 0; k < result.terms; ++k)
                {
                    if (result.termArray[k].exp == newExp)
                    {
                        result.termArray[k].coef += newCoef;
                        contain = true;
                        break;
                    }
                }
                if (!contain) result.newTerm(newCoef, newExp);
            }
        }

    result.Soft();
    return result;
    }

    // ---------- 計算 x 代入某數的結果
    float Eval(float x)
    {
        float result = 0;
        for (int i = 0; i < this->terms; ++i)
            result += termArray[i].coef * pow(x, termArray[i].exp);
        return result;
    }
};

// ========== 重載 >>Polynomial
istream& operator>>(istream& input, Polynomial& poly)
{
    int theCoef, theExp;
    cout << "兩數 m 和 n 關係為 mx^n, 兩者都為0時停止讀取: " << endl << "請輸入 m 和 n : ";
    while(input>>theCoef>>theExp)
    {
        if(theCoef==0 && theExp==0) break;
        poly.newTerm(theCoef,theExp);
        cout << "請輸入 m 和 n : ";
    }
    return input;
}

// ========== 重載 <<Polynomial
ostream& operator<<(ostream& output, const Polynomial& poly)
{
    for (int i = 0; i < poly.terms; ++i)
    {
        if (i > 0 && poly.termArray[i].coef > 0) output << " + ";
        output << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
    }
    return output;
}

// ========== 主程式
int main()
{
    Polynomial a,b;
    
    cout << "請輸入最簡多項式a:" << endl;
    cin >> a;
    cout << "請輸入最簡多項式b:" << endl;
    cin >> b;

    a.Soft();
    b.Soft();
    cout << "多項式a: " << a << endl << "多項式b: " << b << endl;

    cout << "兩式相加: " << a.Add(b) << endl;
    cout << "兩式相乘: " << a.Mult(b) << endl;
    cout << "相乘結果代入1: " << a.Mult(b).Eval(1) << endl;

    return 0;
}
