#include <iostream>

using namespace std;

class Memento
{
public:
    Memento() = default;
    Memento(int s1, int s2)
        : m_stateA(s1), m_stateB(s2) {
    }
    int getStateA() const { 
        return m_stateA;
    }
    int getStateB() const { 
        return m_stateB;
    }

private:
    int m_stateA = 0;
    int m_stateB = 0;
};

class Originator
{
public:
    void initState()
    {
        m_stateA = 100;
        m_stateB = 100;
    }

    void displayState()const
    {
        cout << "StateA " << m_stateA << "\tStateB " << m_stateB << endl;
    }

    void changeState()
    {
        m_stateA = 55;
        m_stateB = 99;
    }

    void recoveryState(const Memento& memo)
    {
        m_stateA = memo.getStateA();
        m_stateB = memo.getStateB();
    }

    Memento saveState() const
    {
        return Memento(m_stateA, m_stateB);
    }

private:
    int m_stateA = 0;
    int m_stateB = 0;
};

class Caretaker
{
public:
    void saveMemento(const Memento& memo) {
        this->memo = memo;
    }
    Memento getMemento() const {
        return memo;
    }

private:
    Memento memo;
};

int main()
{
    Originator org;
    org.initState();
    org.displayState();

    Caretaker taker;
    taker.saveMemento(org.saveState());

    org.changeState();
    org.displayState();

    org.recoveryState(taker.getMemento());
    org.displayState();

    return 0;
}