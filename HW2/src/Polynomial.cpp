#include <iostream>
using namespace std;

// ========== 多項式類別
class Polynomial
{
private:
    Term *termArray;
    int capacity;
    int terms;
    
    void double_size()
    {
        capacity *=2;
        Term* new_termArray = new Term[capacity];
        Term* recycler = termArray;
        copy(termArray, termArray + terms, new_termArray);

        delete[] recycler;
        termArray = new_termArray;
    }
    
    void copy(Term* arr, Term* arr_end, Term* new_arr)
    {
        int i = 0;
        while ((arr+i) != arr_end)
        {
            new_arr[i].coef = arr[i].coef;
            new_arr[i].exp = arr[i].exp;
            i++;
        }
    }
public:
    Polynomial()
    {
        termArray = new Term[4];
        capacity = 4;
        terms = 0;
    }

    ~Polynomial()
    {
        delete[] termArray;
    }

    Polynomial Add(Polynomial poly)
    {
        if(terms == capacity) double_size();

    }

    Polynomial Mult(Polynomial poly)
    {

    }

    float Eval(float f)
    {

    }
};

class Term
{
friend Polynomial;
private:
    float coef;
    int exp;
};

// ========== 主程式
int main()
{

}