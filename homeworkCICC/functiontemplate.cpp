#include <iostream>

// 一个参数的函数模板
template <typename T>
T larger(T a, T b)
{
    return a > b ? a : b;
}

// special instance
template <>
int* larger(int* a, int* b)
{
    return *a > *b ? a : b;
}

// 函数返回类型auto
template <typename T1, typename T2>
auto larger(T1 a, T2 b)
{
    return a > b ? a : b;
}

// 拖尾返回类型
// template <typename T1, typename T2>
// auto larger(T1 a, T2 b) -> decltype(a > b ? a : b)
// {
//     return a > b ? a : b;
// }

int main()
{
    std::cout << larger(1.5, 2.5) << std::endl;
    std::cout << larger(1.5, 2) << std::endl; // auto implement funcation
}
