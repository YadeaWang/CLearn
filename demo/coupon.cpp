#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include "ql/time/all.hpp"

using namespace std;
using namespace QuantLib;

vector<double> calCoupons(const vector<Date>& paySchedule, Date resetDate, double old, double newly)
{
    vector<double> coupons(paySchedule.size(), old);
    size_t dist = -1;
    if(find(paySchedule.begin(), paySchedule.end(), resetDate) != paySchedule.end())
    {
        cout << "********case 1********" << endl;
        dist = distance(paySchedule.begin(), find(paySchedule.begin(), paySchedule.end(), resetDate));
        cout << "distance = " << dist << endl;
        
        // update coupons
        fill(coupons.begin() + dist + 1, coupons.end(), newly);
    }
    else if(lower_bound(paySchedule.begin(), paySchedule.end(), resetDate) != paySchedule.end())
    {
        cout << "********case 2********" << endl;
        // lower_bound 大于等于  upper_bound 大于
        auto it = lower_bound(paySchedule.begin(), paySchedule.end(), resetDate);
        dist = distance(paySchedule.begin(), it);
        cout << "distance = " << dist << endl;

        // update coupons
        fill(coupons.begin() + dist + 1, coupons.end(), newly);
        int days = paySchedule[dist] - paySchedule[dist - 1];
        double avg = old * (resetDate - paySchedule[dist - 1]) / days + newly * (paySchedule[dist] - resetDate) / days;
        coupons[dist] = avg;
    }
    else
    {
        cerr << "invalid reset date" << endl;
    }
    return coupons;
}

vector<vector<double>> test()
{
    vector<vector<double>> ans;
    vector<double> a(10, 1);
    vector<double> b(10, 2);
    vector<double> c(10, 3);
    vector<double> d(10, 4);
    cout << &a << '\t' << &b << '\t' << &c << '\t' << &d << endl;
    ans.push_back(std::move(a));
    ans.push_back(std::move(b));
    ans.push_back(c);
    ans.push_back(std::move(d));
    cout << &ans << endl;
    return ans;
}

class A
{
public:
    void setA(int x)
    {
        a = x;
    }
    int getA()
    {
        std::cout << a << endl;
    }
private:
    int a;
};

class B : protected A
{
public:
    int getB()
    {
        cout << b << endl;
    }

private:
    int b;
};

int main()
{
    vector<Date> paySchedule {
        Date(31, Jan, 2023),
        Date(28, Feb, 2023),
        Date(31, Mar, 2023),
        Date(30, Apr, 2023),
        Date(31, May, 2023),
        Date(30, Jun, 2023),
        Date(26, Jul, 2023),
        Date(26, Aug, 2023),
        Date(26, Sep, 2023),
        Date(31, Oct, 2023),
        Date(26, Nov, 2023),
        Date(26, Dec, 2023),
        Date(26, Jan, 2024),
        Date(26, Feb, 2024),
        Date(26, Mar, 2024),
        Date(26, Apr, 2024)
    };
    // Date resetDate = Date(20, April, 2024);
    // double old = 3.5e-2;
    // double newly = 3.4e-2;

    // auto result = calCoupons(paySchedule, resetDate, old, newly);
    
    DayCounter d1 = Thirty360(Thirty360::BondBasis);
    DayCounter d2 = Thirty360(Thirty360::USA);
    DayCounter d3 = Thirty360(Thirty360::European);
    DayCounter d4 = Thirty360(Thirty360::EurobondBasis);
    DayCounter d5 = Actual365Fixed();

    // for (int i = 1; i < paySchedule.size(); ++i)
    // {
    //     cout << d1.dayCount(paySchedule[i - 1], paySchedule[i]) << '\t';
    //     cout << d2.dayCount(paySchedule[i - 1], paySchedule[i]) << '\t';
    //     cout << d3.dayCount(paySchedule[i - 1], paySchedule[i]) << '\t';
    //     cout << d4.dayCount(paySchedule[i - 1], paySchedule[i]) << '\t';
    //     cout << d5.dayCount(paySchedule[i - 1], paySchedule[i]) << '\t';
    //     cout << endl;
    // }

    // vector<vector<double>> ans = test();
    // for (int i = 0; i < ans.size(); ++i)
    //     cout << &ans[i] << '\t';

    // cout << endl;
    // cout << &ans << endl;

    A a1 = A();
    a1.setA(10);
    B b1 = B();
    A a2 = b1;
    a2.getA();

    return 0;
}