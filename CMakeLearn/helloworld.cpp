#include <string>
#include <iostream>
#include "message.hpp"

int main() {
    Message say_hello("Hello, CMake World!");
    std::cout << say_hello << std::endl;
    
    Message say_goodbye("Goodbye, Cmake world!");
    std::cout << say_goodbye << std::endl;
    
    return EXIT_SUCCESS;
}