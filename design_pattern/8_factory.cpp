#include <iostream>
#include <memory>

using namespace std;

/********** Product **********/
class COperation
{
public:
	virtual ~COperation() = default;
	virtual double getResult(double numA, double numB) const = 0;
};

/********** ConcreteProduct **********/
class COperationAdd : public COperation
{
public:
	double getResult(double numA, double numB) const override {
		return numA + numB;
	}
};

class COperationSub : public COperation
{
public:
	double getResult(double numA, double numB) const override {
		return numA - numB;
	}
};

class COperationMul : public COperation
{
public:
	double getResult(double numA, double numB) const override {
		return numA * numB;
	}
};

/********** Factory **********/
class COperationFactory
{
public:
	virtual ~COperationFactory() = default;
	virtual unique_ptr<COperation> GetOperator() const = 0;
};

/********** Concrete Factory **********/
class COperationFactoryAdd : public COperationFactory
{
public:
	unique_ptr<COperation> GetOperator() const override {
		return make_unique<COperationAdd>();
	}
};

class COperationFactorySub : public COperationFactory
{
public:
	unique_ptr<COperation> GetOperator() const override {
		return make_unique<COperationSub>();
	}
};

class COperationFactoryMul : public COperationFactory
{
public:
	unique_ptr<COperation> GetOperator() const override {
		return make_unique<COperationMul>();
	}
};

// Client
int main()
{
	unique_ptr<COperationFactory> upFactory = std::make_unique<COperationFactoryAdd>();
	unique_ptr<COperation> up = upFactory->GetOperator();

	cout << up->getResult(1, 2) << endl;
}