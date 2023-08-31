#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

class ConcreteElementA;
class ConcreteElementB;

/**
 * 操作者/访问者，因为数据结构/分类很确定，所以直接指定对两个数据结构/分类的操作
 * 新增一个操作：只需要新增一个ConcreteVisitor，实现每个数据结构/分类的具体访问函数
 */
class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void visitConcreteElementA(ConcreteElementA* a) = 0;
    virtual void visitConcreteElementB(ConcreteElementB* b) = 0;
};
using pVisitor = shared_ptr<Visitor>;

// 具体操作1：定义Visitor1对两个Element的操作方式
class ConcreteVisitor1 : public Visitor
{
public:
    void visitConcreteElementA(ConcreteElementA* a) override {
        cout << "Concrete Visitor 1 -> Element A" << endl;
    }
    void visitConcreteElementB(ConcreteElementB* b) override {
        cout << "Concrete Visitor 1 -> Element B" << endl;
    }
};

// 具体操作2：定义Visitor2对两个Element的操作方式
class ConcreteVisitor2 : public Visitor
{
public:
    void visitConcreteElementA(ConcreteElementA* a) override {
        cout << "Concrete Visitor 2 -> Element A" << endl;
    }
    void visitConcreteElementB(ConcreteElementB* b) override {
        cout << "Concrete Visitor 2 -> Element B" << endl;
    }
};

/* Element的分类是固定的，只需要向所有Visitor放开对自己的访问 */
class Element
{
public:
    virtual void accept(Visitor* visitor) = 0;
};
using pElement = shared_ptr<Element>;

/**
 * 双分派：
 * 1.将当前类的操作函数->分派给访问者对该类别的具体操作函数
 * 2.将当前类对象->分派给访问者作为具体访问的对象
 */
class ConcreteElementA : public Element
{
public:
    void accept(Visitor* visit) override {
        visit->visitConcreteElementA(this);
    }
};

class ConcreteElementB : public Element
{
public:
    void accept(Visitor* visit) override {
        visit->visitConcreteElementB(this);
    }
};

class ObjectStructure
{
public:
    void attach(pElement element) {
        m_elements.push_back(element);
    }

    void detach(pElement element) {
        m_elements.erase(
            remove(
                m_elements.begin(), m_elements.end(), element
            ),
            m_elements.end()
        );
    }

    void accept(pVisitor visitor) {
        for (auto member : m_elements) {
            member->accept(visitor.get());
        }
    }

private:
    vector<pElement> m_elements;
};

int main()
{
    ObjectStructure os;
    os.attach(make_shared<ConcreteElementA>());
    os.attach(make_shared<ConcreteElementB>());
    
    pVisitor v1 = make_shared<ConcreteVisitor1>();
    pVisitor v2 = make_shared<ConcreteVisitor2>();
    // 如果新增了Visitor3，只需要实现Visitor3类，在这里accept(v3)即可

    os.accept(v1);
    os.accept(v2);
    
    return 0;
}