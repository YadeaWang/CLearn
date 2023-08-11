#include <iostream>
#include <memory>

using namespace std;

class operation
{
public:
    /**
     * 任何一个函数都不能只有声明，没有实现！virtual函数也一样。
     * 如果要求所有子类都各自override，那应该设为纯虚函数；
     * 如果有默认实现，那就应该写{...}
     */
    virtual double getResult() const = 0;
    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }
    double getX() const { return x; }
    double getY() const { return y; }
private:
    double x = .0;
    double y = .0;
};

class operationAdd : public operation
{
    double getResult() const override{
        return getX() + getY();
    }
};

class operationSub : public operation
{
    double getResult() const override{
        return getX() - getY();
    }
};

class operationMul : public operation
{
    double getResult() const override{
        return getX() * getY();
    }
};

class operationFactory
{
public:
    static unique_ptr<operation> createOperation(char operate)
    {
        unique_ptr<operation> oper = nullptr;
        switch (operate)
        {
        case '+':
            oper = make_unique<operationAdd>();
            break;
        case '-':
            oper = make_unique<operationSub>();
            break;
        case '*':
            oper = make_unique<operationMul>();
            break;
        default:
            break;
        }
        return oper;
    }
};

// Client
int main()
{
    unique_ptr<operation> op = operationFactory::createOperation('+');
    op->setX(10);
    op->setY(99);
    cout << op->getResult() << endl;
}