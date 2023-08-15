#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

// terminal: g++ 21_singleton.cpp -lpthread
class Singleton
{
public:
    static Singleton* GetInstance()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (instance_ == nullptr)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(110));
            instance_ = new Singleton();
        }
        return instance_;
        
        // if (instance_ == nullptr)
        // {
        //     mutex_->lock();
        //     if (instance_ == nullptr)
        //     {
        //         instance_ = new Singleton();
        //     }
        //     mutex_->unlock();
        // }
        // return instance_;
    }

private:
    Singleton() = default;
    static Singleton* instance_;
    static mutex* mutex_;
};

Singleton *Singleton::instance_ = nullptr;
mutex *Singleton::mutex_ = new mutex();

void say(Singleton* ins)
{
    cout << (void *)ins << endl;
}

int main()
{
    vector<thread> pools(100);
    for (int i = 0; i < pools.size(); ++i)
    {
        Singleton* ins = Singleton::GetInstance();
        pools[i] = thread(&say, ins);
    }
    for (int i = 0; i < pools.size(); ++i)
    {
        pools[i].join();
    }
    return 0;
}