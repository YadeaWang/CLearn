#include <iostream>
#include <memory>

using namespace std;

class Work;
class State
{
public:
    virtual ~State() = default;
    virtual void handle(Work* work) = 0;
};

class Work
{
public:
    void setHour(int hour) {
        m_hour = hour;
    }
    int getHour() {
        return m_hour;
    }
    void setTaskFinish(bool flag) {
        m_task_finish = flag;
    }
    bool getTaskFinish() {
        return m_task_finish;
    }
    void setState(unique_ptr<State> state) {
        m_state.swap(state);
    }
    void handle() {
        m_state->handle(this);
    }

private:
    int m_hour = 0;
    bool m_task_finish = false;
    unique_ptr<State> m_state = nullptr;
};

class SleepState : public State
{
public:
    void handle(Work* work) override {
        cout << "sleep" << endl;
    };
};

class RestState : public State
{
public:
	void handle(Work* work) override {
        cout << "rest" << endl;
	}
};

class EveningState : public State
{
public:
	void handle(Work* wk) override {
		if (wk != nullptr)
		{
			if (wk->getTaskFinish())
			{
                wk->setState(make_unique<RestState>());
                wk->handle();
			}
			else
			{
				if (wk->getHour() < 21)
				{
					cout << "working before 21:00" << endl;
				}
				else
				{
                    wk->setState(make_unique<SleepState>());
                    wk->handle();
				}
			}
		}
	}
};

int main()
{
    Work wk;
    wk.setState(make_unique<EveningState>());
    wk.setHour(12);
    wk.handle();

    wk.setHour(22);
    wk.handle();

    /**
     * 注意：如果state在之前已经被修改，则状态行为取决于被修改的状态，而不是初始状态。
     * 下面这个task finish就没有影响到状态行为。所以最好不要在Client改状态。
     * 把状态的变化封装在Context/State内部，以防不知道何时发生状态改变，以及不知道当前状态是什么。
     */
    wk.setTaskFinish(true);
    wk.handle();

    return 0;
}