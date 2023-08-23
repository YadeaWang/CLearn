#include <iostream>
#include <memory>

class CAbstractClass
{
public:
	virtual ~CAbstractClass() = default;
	void TemplateMethod()
	{
		PrimitiveOperationA();
		PrimitiveOperationB();
		PrimitiveOperationC();
	}
protected:
	virtual void PrimitiveOperationA() const = 0;
	virtual void PrimitiveOperationB() const = 0;
	virtual void PrimitiveOperationC() const = 0;
};

class CConcreteClassA : public CAbstractClass
{
protected:
	virtual void PrimitiveOperationA() const override
	{
		std::cout << "class a -> op a" << std::endl;
	}

	virtual void PrimitiveOperationB() const override
	{
		std::cout << "class a -> op b" << std::endl;
	}

	virtual void PrimitiveOperationC() const override
	{
		std::cout << "class a -> op c" << std::endl;
	}
};

class CConcreteClassB : public CAbstractClass
{
protected:
	virtual void PrimitiveOperationA() const override
	{
		std::cout << "class b -> op a" << std::endl;
	}

	virtual void PrimitiveOperationB() const override
	{
		std::cout << "class b -> op b" << std::endl;
	}

	virtual void PrimitiveOperationC() const override
	{
		std::cout << "class b -> op c" << std::endl;
	}
};

int main()
{
	std::unique_ptr<CAbstractClass> up = std::make_unique<CConcreteClassA>();
	up->TemplateMethod();

	up.reset(new CConcreteClassB());
	up->TemplateMethod();

	return 0;
}