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

    // 对于const json，错误的索引会导致asserion fail 
    // const nlohmann::json const_j = {{"key", "value"}};
    // auto v = const_j["missing"];
    // std::cout << v << std::endl;

    // 但是非const的json，缺失索引会返回null
    nlohmann::json unconst_j = {{"key", "value"}};
    auto v = unconst_j["missing"];
    std::cout << v << std::endl;
}