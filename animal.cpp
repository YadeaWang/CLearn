#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <algorithm>

class Animal
{
public:
    Animal():publicn1{"1"}, protectedn2{"2"}, privaten3{"3"} {}

public:
    string publicn1;

protected:
    string protectedn2;

private:
    string privaten3;
};

class Cat: protected Animal
{
public:
    void show() {
        cout << publicn1 << endl;
        cout << protectedn2 << endl;
        // dosomething();
        // cout << protectedn2 << endl;
        // cout << privaten3 << endl;
    }

    void dosomething() {
        protectedn2 = "n2";
    }

};

int main()
{

// base + derivatives 子类中/子类对象 调用父类的成员，父类的权限+继承方式
// base  父类对象
// derivatives  子类对象
    Animal cute;

    // Cat c;
    // c.dosomething();
    // c.show();
    // c.publicn1;
    // cout << c.publicn1 << endl;
    // Animal animal = cat;
    // animal.eat();

    vector<int> aa = {1,2,3,4,5};
    vector<int> bb = {6,7,8,9,10};

    int val = 4;

    vector<int> cc;
    vector<int> dd;

    cout << *upper_bound(aa.cbegin(), aa.cend(), val) << endl;
    cc.insert(cc.end(), aa.cbegin(), upper_bound(aa.cbegin(), aa.cend(), val));
    dd.insert(dd.end(), bb.cbegin(), bb.cbegin() + cc.size());

    for(auto c : cc)
        cout << c << '\t';

    cout << endl;

    for(auto d: dd)
        cout << d << '\t';
    return 0;
}


