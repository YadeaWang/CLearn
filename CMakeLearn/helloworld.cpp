#include <string>
#include <iostream>
#include <cstdlib>

std::string say_hello() { return std::string("Hello, CMake world!"); }

int main() {
    std::cout << say_hello() << std::endl;
    return EXIT_SUCCESS;
}