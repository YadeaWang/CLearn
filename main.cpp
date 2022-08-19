#include "functiontemplate.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    std::cout << larger(1.5, 2.5) << std::endl;
    
    std::cout << larger(1.5, 2) << std::endl; // auto implement funcation
}
