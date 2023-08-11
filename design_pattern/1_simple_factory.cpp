#include <iostream>
#include <memory>

using namespace std;

class operation
{
public:
    virtual double getResult() const;
    void setX(double x) { x = x; }
    void setY(double y) { y = y; }
    double getX() const { return x; }
    double getY() const { return y; }
private:
    double x = .0;
    double y = .0;
};

class operationAdd : public operation
{
    double getResult() const {
        return getX() + getY();
    }
};

class operationSub : public operation
{
    double getResult() const {
        return getX() - getY();
    }
};

class operationMul : public operation
{
    double getResult() const {
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