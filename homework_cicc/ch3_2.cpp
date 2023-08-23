#include <iostream>
#include <vector>

template <typename ostream, typename container>
void printArray(ostream& os, container& arr)
{
    for(auto val : arr)
        os << val << "\t";

    os << std::endl;
}

int main(int argc, char** argv)
{
    float arr[10] = {2};
    printArray(std::cout, arr);

    std::vector<int> vec(10, 2);
    printArray(std::clog, vec);
}
