#include <cstdlib>
#include <iostream>
#include <string>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

std::string say_hello()
{
/*
#ifdef IS_INTEL_CXX_COMPILER
    // only compiled when Intel compiler is selected
    // such compiler will not compile the other branches
    return std::string("Hello Intel compiler!");
#elif IS_GNU_CXX_COMPILER
    // only compiled when GNU compiler is selected
    // such compiler will not compile the other branches
    return std::string("Hello GNU compiler!");
#elif IS_PGI_CXX_COMPILER
    // etc.
    return std::string("Hello PGI compiler!");
#elif IS_XL_CXX_COMPILER
    return std::string("Hello XL compiler!");
#else
    return std::string("Hello unknown compiler - have we met before?");
#endif
*/

    std::string arch_info(TOSTRING(ARCHITECTURE));
    arch_info += std::string(" architecture. ");
#ifdef IS_32_BIT_ARCH
    return arch_info + std::string("Compiled on a 32 bit host processor.");
#elif IS_64_BIT_ARCH
    return arch_info + std::string("Compiled on a 64 bit host processor.");
#else
    return arch_info + std::string("Neither 32 nor 64 bit, puzzling ...");
#endif
}

int main()
{
    std::cout << say_hello() << std::endl;
    return EXIT_SUCCESS;
}