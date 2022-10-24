#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

int Collatz(int val, std::vector<int>& memo);
const int MAX_RANGE = 10000;

int main()
{
    std::vector<int> memo(MAX_RANGE + 1, -1);
    int ans = -1;
    memo[1] = 1;
    for(int i = 3; i < MAX_RANGE; ++i)
    {
        ans = std::max(ans, Collatz(i, memo));
    }
    std::cout << "Collatz size less than " << MAX_RANGE << " is: " << ans << std::endl;
    return 0;
}

int Collatz(int val, std::vector<int>& memo)
{
    if(val < MAX_RANGE && memo[val] != -1)
        return memo[val];

    int steps = 0;
    if(val % 2 == 0)
        steps = Collatz(val / 2, memo) + 1;
    else
        steps = Collatz(val * 3 + 1, memo) + 1;

    if(val < memo.size())
        memo[val] = steps;

    return steps;
}