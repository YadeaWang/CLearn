#include <iostream>
#include <vector>
using namespace std;

class myClass
{
public:
    myClass() { cout << "default cstr" << endl; }
    ~myClass() = default;
    // myClass(const myClass& lvalue) { cout << "copy lvalue cstr" << endl; }
    // myClass(myClass&& lvalue) { cout << "copy rvalue cstr" << endl; }
    // myClass& operator=(const myClass& lvalue) { 
    //     cout << "copy lvalue assign" << endl; 
    //     return *this;
    // }
    // myClass& operator=(myClass&& lvalue) { 
    //     cout << "copy rvalue assign" << endl; 
    //     return *this;
    // }
};

vector<myClass> func()
{
    vector<myClass> ans;
    myClass test1 = myClass();
    myClass test2 = myClass();
    cout << &test1 << '\t' << &test2 << '\t' << &ans << endl;
    ans.emplace_back(test1);
    ans.emplace_back(test2);
    return ans;
}

int main()
{
    vector<myClass> test = func();
    cout << &test[0] << '\t' << &test[1] << '\t' << &test << endl;
}

