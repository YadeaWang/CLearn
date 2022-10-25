#include <string>
#include <iostream>
#include <memory>
#include <cstdio>

using namespace std;

class Base {
public:
    Base() {ptr = new int(5);}
    virtual ~Base() {
        if (ptr)
            delete ptr;
        ptr = nullptr;
    }
    virtual void show() {
        printf("In Base %x, %d\n", ptr, *ptr);
    }
    int *ptr;
};

class Paisheng : public Base {
public:
    Paisheng() {
        ptr2 = new int(10);
    }
    ~Paisheng() {
        if (ptr2)
            delete ptr2;
        ptr2 = nullptr;
    }
    void show() override {
        printf("In Paisheng %x, %d\n", ptr2, *ptr2);
    }
    int *ptr2;
};

int main() {
    Base *base = new Paisheng();
    base->show();
    return 0;
}