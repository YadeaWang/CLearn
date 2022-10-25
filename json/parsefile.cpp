#include "nlohmann/json.hpp"
#include <string>
#include <iostream>
#include <fstream>


int main()
{
    std::ifstream i("input.json");
    auto j = nlohmann::json::parse(i); // 无序解析
    // auto j = nlohmann::order_json::parse(i); 有序解析
    std::cout << j.dump(2) << std::endl;
}