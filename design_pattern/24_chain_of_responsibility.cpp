#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Container;

/* 处理者接口声明了一个创建处理者链的方法。还声明了一个执行请求的方法。*/
class ComponentWithContextualHelp
{
public:
    virtual void showHelp() const = 0;
    virtual ~ComponentWithContextualHelp() = default;
};

/* 简单组件的基础类。*/
class Component : public ComponentWithContextualHelp
{
public:
    void showHelp() const override {
        if (!tooltipText.empty()) {
            cout << tooltipText << endl;
        } else {
            container->showHelp();
        }
    }
    void setText(const string& text) {
        tooltipText = text;
    }
    /* 组件容器在处理者链中作为“下一个”链接。*/
    Container* container;

private:
    string tooltipText;
};

/**
 * 容器可以将简单组件和其他容器作为其子项目。
 * 链关系将在这里建立。该类将从其父类处继承 showHelp（显示帮助）的行为。
 */
class Container : public Component
{
public:
    void add(Component& child) {
        childern.emplace_back(child);
        child.container = this;
    }
private:
    vector<Component*> childern;
};

class Button : public Component
{


};

class Panel : public Component
{

};

class Dialog : public Component
{

};

int main()
{
    
    return 0;
}
