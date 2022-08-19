#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
std::ostream &printArray(std::ostream &os, T &array)
{
    size_t len = sizeof(array) / sizeof(array[0]);
    for (size_t i = 0; i < len; i++)
    {
        os << array[i] << "\t";
    }

    os << std::endl;
    return os;
}

template <typename T>
std::ostream &printArray(std::ostream &os, std::vector<T> &array)
{
    std::for_each(array.begin(), array.end(),
                [&os](auto value)
                { os << value << "\t"; });

    os << std::endl;
    return os;
}

int main()
{
    float arr[10] = {2};
    printArray(std::cout, arr);

    std::vector<int> vec(10, 2);
    printArray(std::clog, vec);

    std::vector<int> vint = {1, 5, 7, 2, 0, 4, 9};
    std::sort(vint.begin(), vint.end(), std::greater<int>());
    for(int value : vint)
    {
        std::cout << value << "\t"; 
    }
    std::cout << std::endl;

}


    