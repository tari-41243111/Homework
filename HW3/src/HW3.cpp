#include <iostream>
#include <cmath>
using namespace std;

template<typename T>
class CircularLinkedListWithHeaderNode;
template<typename T>
class ChainNode;

class Polynomial;
class Term;

// ========== ChainNode 節點結構
template<typename T>
class ChainNode
{
	friend CircularLinkedListWithHeaderNode<T>;
private:
	T data;
	ChainNode<T>* link;
public:
    ChainNode() { link = nullptr; }
	ChainNode(const T data, ChainNode<T>* link) {
		this->data = data;
		this->link = link;
	}
};

// ========== Linked List with Header Node 實作
template<typename T>
class CircularLinkedListWithHeaderNode
{
private:
	ChainNode<T>* header;
    int n; // Node 數量

    // ---------- availableList 方法實作
    static ChainNode<T>* availableList;  // 可用串列

    void recycle(ChainNode<T>* recycleNode) {
        recycleNode->link = availableList;
        availableList = recycleNode;
        n--;
    }

    void clear() {
        ChainNode<T>* currentNode = header->link;
        while (currentNode != header) {
            ChainNode<T>* next = currentNode->link;
            recycle(currentNode);
            currentNode = next;
        }
        header->link = header;
        n = 0;
    }

    ChainNode<T>* getNode() {
        ChainNode<T>* node;
        if (availableList) {
            node = availableList;
            availableList = availableList->link;
        } else {
            node = new ChainNode<T>();
        }
        return node;
    }

    ChainNode<T>* getNode(const T& theElement, ChainNode<T>* link) {
        ChainNode<T>* node;
        if (availableList) {
            node = availableList;
            availableList = availableList->link;
        } else {
            node = new ChainNode<T>();
        }
        node->data = theElement;
        node->link = link;
        n++;
        return node;
    }

public:
    // ---------- Linked List with Header Node 函式成員
	CircularLinkedListWithHeaderNode() {
        header = getNode();
        header->link = header;
        n = 0;
    }
	~CircularLinkedListWithHeaderNode() 
	{
        clear();
        recycle(header);
	};
	
	bool IsEmpty() const { return header->link == header; }
    
	// ---------- 插入(預設在尾端插入)
	void Insert(const T& theElement, int theIndex)
	{
		if (theIndex < 0 || theIndex > n)
			throw "Bad insert index";
        
		ChainNode<T>* beforeNode = header;
		for (int i = 0; i < theIndex; i++) {
			beforeNode = beforeNode->link;
		}
		beforeNode->link = getNode(theElement,beforeNode->link);
	}
    void InsertLast(const T& theElement) {
        Insert(theElement, n);
    }
	// ---------- 刪除
    void Delete(int theIndex) {
        if (theIndex < 0 || theIndex >= n)
            throw "Bad delete index";

        ChainNode<T>* beforeNode = header;
        for (int i = 0; i < theIndex; i++) {
            beforeNode = beforeNode->link;
        }
        ChainNode<T>* deleteNode = beforeNode->link;
        beforeNode->link = deleteNode->link;
        recycle(deleteNode);
    }

    // ---------- 取得 data
    T Get(int theIndex) const {
        if (theIndex < 0 || theIndex >= n)
            throw "Bad get index";

        ChainNode<T>* currentNode = header->link;
        for (int i = 0; i < theIndex; i++) {
            currentNode = currentNode->link;
        }
        return currentNode->data;
    }

    // ========== Iterator 方法實作
    class ChainIterator {
    private:
        ChainNode<T>* current;
    public:
        ChainIterator(ChainNode<T>* startNode = NULL) : current(startNode) {}
        T& operator* () const { return current->data; }
        T* operator->() const { return &current->data; }
        ChainIterator& operator++() {
            current = current->link;
            return *this;
        }
        bool operator==(const ChainIterator& other) const { return current == other.current; }
        bool operator!=(const ChainIterator& other) const { return current != other.current; }
    };

    ChainIterator begin() const { return ChainIterator(header->link); }
    ChainIterator end() const { return ChainIterator(header); }
};

template<typename T>
ChainNode<T>* CircularLinkedListWithHeaderNode<T>::availableList = nullptr;

// ========== Term 結構
class Term {
    public:
    int coef; // 係數
    int exp;  // 次數
    Term(int c = 0, int e = 0) : coef(c), exp(e) {}
    bool operator<(const Term& other) const { return exp < other.exp; }
    bool operator==(const Term& other) const { return exp == other.exp; }
    bool operator!=(const Term& other) const { return exp != other.exp; }
};

// ========== Polynomial 實作
class Polynomial {
private:
    CircularLinkedListWithHeaderNode<Term> poly;
public:
    Polynomial() {}

    Polynomial(const Polynomial& other) {
        for (auto it = other.poly.begin(); it != other.poly.end(); ++it) {
            poly.InsertLast(*it);
        }
    }

    ~Polynomial() {}

    const Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            poly = CircularLinkedListWithHeaderNode<Term>();
            for (auto it = other.poly.begin(); it != other.poly.end(); ++it) {
                poly.InsertLast(*it);
            }
        }
        return *this;
    }

    // ---------- 加法
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;
        auto it1 = poly.begin();
        auto it2 = other.poly.begin();

        while (it1 != poly.end() || it2 != other.poly.end()) {
            if (it1 == poly.end()) {
                result.poly.InsertLast(*it2);
                ++it2;
            } else if (it2 == other.poly.end()) {
                result.poly.InsertLast(*it1);
                ++it1;
            } else if (it1->exp > it2->exp) {
                result.poly.InsertLast(*it1);
                ++it1;
            } else if (it1->exp < it2->exp) {
                result.poly.InsertLast(*it2);
                ++it2;
            } else {
                int newCoef = it1->coef + it2->coef;
                if (newCoef != 0) {
                    result.poly.InsertLast(Term(newCoef, it1->exp));
                }
                ++it1;
                ++it2;
            }
        }

        return result;
    }

    // ---------- 減法
    Polynomial operator-(const Polynomial& other) const {
        Polynomial result;
        auto it1 = poly.begin();
        auto it2 = other.poly.begin();

        while (it1 != poly.end() || it2 != other.poly.end()) {
            if (it1 == poly.end()) {
                result.poly.InsertLast(Term(-it2->coef, it2->exp));
                ++it2;
            } else if (it2 == other.poly.end()) {
                result.poly.InsertLast(*it1);
                ++it1;
            } else if (it1->exp > it2->exp) {
                result.poly.InsertLast(*it1);
                ++it1;
            } else if (it1->exp < it2->exp) {
                result.poly.InsertLast(Term(-it2->coef, it2->exp));
                ++it2;
            } else {
                int newCoef = it1->coef - it2->coef;
                if (newCoef != 0) {
                    result.poly.InsertLast(Term(newCoef, it1->exp));
                }
                ++it1;
                ++it2;
            }
        }

        return result;
    }

    // ---------- 乘法(多項式相乘)
    Polynomial operator*(const Polynomial& other) const {
        Polynomial result;

        for (auto it1 = poly.begin(); it1 != poly.end(); ++it1) {
            Polynomial temp;
            for (auto it2 = other.poly.begin(); it2 != other.poly.end(); ++it2) {
                temp.poly.InsertLast(Term(it1->coef * it2->coef, it1->exp + it2->exp));
            }
            result = result + temp;
        }

        return result;
    }

    // ---------- 帶入 x 值
    float Evaluate(float x) const {
        float result = 0;
        for (auto it = poly.begin(); it != poly.end(); ++it) {
            result += it->coef * pow(x, it->exp);
        }
        return result;
    }

    // ---------- 重載 >>
    friend istream& operator>>(istream& is, Polynomial& p) {
        int n;
        is >> n;
        for (int i = 0; i < n; ++i) {
            float coef;
            int exp;
            is >> coef >> exp;
            p.poly.InsertLast(Term(coef, exp));
        }
        return is;
    }

    // ---------- 重載 <<
    friend ostream& operator<<(ostream& os, const Polynomial& p) {
        bool first = true;
        for (auto it = p.poly.begin(); it != p.poly.end(); ++it) {
            if (!first && it->coef > 0) {
                os << " + ";
            }
            first = false;
            os << it->coef << "x^" << it->exp;
        }
        return os;
    }
};

// ========== 主程式
int main() {
    Polynomial p1, p2;
    cout << "輸入第一個多項式 (n, c1, e1, ...): ";
    cin >> p1;
    cout << "輸入第二個多項式 (n, c1, e1, ...): ";
    cin >> p2;

    cout << "第一個多項式: " << p1 << endl;
    cout << "第二個多項式: " << p2 << endl;

    cout << "相加結果: " << (p1 + p2) << endl;
    cout << "相減結果: " << (p1 - p2) << endl;
    cout << "相乘結果: " << (p1 * p2) << endl;

    float x;
    cout << "輸入一個值 x 計算 p1 的值: ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Evaluate(x) << endl;

    return 0;
}
