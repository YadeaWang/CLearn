#include "nlohmann/json.hpp"
#include <string>
#include <iostream>

using json = nlohmann::json;

int main()
{
    // test for pointer
    json jp;
    jp["array"] = {"A", "B", "C"};
    jp["nested"]["one"] = 1;
    jp["nested"]["two"] = 2;
    jp["nested"]["three"] = {true, false};

    std::cout << jp << std::endl;

    // same with above
    jp = json::parse(R"({
        "array": ["A", "B", "C"],
        "nested": {
            "one": 1,
            "two": 2,
            "three": [true, false]
        }
    })");

    std::cout << jp << std::endl;

    // flatten & unflatten
    auto j_flat = jp.flatten();
    std::cout << j_flat << std::endl;

    // json pointer
    json::json_pointer p1("/nested/one");
    auto p2 = "/nested/two"_json_pointer; // p1 equals p2

    std::cout << jp["/array"_json_pointer] << std::endl;
    std::cout << jp[json::json_pointer("/nested/one")] << std::endl;
    std::cout << jp[p2] << std::endl;

    std::cout << "*************" << std::endl;

    std::cout << jp.at(json::json_pointer("/nested/three/1")) << std::endl;
    std::cout << jp.value(json::json_pointer("/nested/four"), 0) << std::endl;
}