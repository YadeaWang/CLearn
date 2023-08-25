#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Subject;

class Observer
{
public:
    Observer(Subject* subject) : m_subject(subject) {}
    virtual ~Observer() = default;
    virtual void update() = 0;

protected:
    Subject* m_subject;
};

class Subject
{
public:
    virtual ~Subject() = default;
    void attach(Observer* observer) {
        m_observers.emplace_back(observer);
    }
    void detach(Observer* observer) {
        m_observers.erase(
            remove(m_observers.begin(), m_observers.end(), observer),
            m_observers.end()
        );
    }
    void notify() {
        for (auto m : m_observers)
            m->update();
    }
    void set(string state) {
        m_state = state;
    }
    string get() {
        return m_state;
    }
private:
    string m_state;
    vector<Observer*> m_observers;
};

class ConcreteObserver : public Observer
{
public:
    ConcreteObserver(Subject* subject, string name) : Observer(subject), m_name(name) {

    }
    void update() override {
        cout << "observer: " << m_name << " set new state: " << m_subject->get() << endl;
    }

private:
    string m_name;
};

int main()
{
    Subject sub;
    Observer* plus = new ConcreteObserver(&sub, "Plus");
    sub.attach(new ConcreteObserver(&sub, "A"));
    sub.attach(new ConcreteObserver(&sub, "B"));
    sub.attach(new ConcreteObserver(&sub, "C"));
    sub.attach(plus);

    sub.set("open");
    sub.notify();

    sub.set("save");
    sub.detach(plus);
    sub.notify();
}
