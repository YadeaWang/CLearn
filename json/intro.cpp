#include "nlohmann/json.hpp"
#include <string>
#include <iostream>

using json = nlohmann::json;

namespace ns {
    struct person {
        std::string name;
        std::string address;
        int age;
    };

    void to_json(json& j, const person& p) {
        j = json{
            {"name", p.name},
            {"address", p.address},
            {"age", p.age}
        };
    }

    void from_json(const json& j, person& p) {
        j.at("name").get_to(p.name);
        j.at("address").get_to(p.address);
        j.at("age").get_to(p.age);
    }
} /* namespace ns */

int main() {
    ns::person p = {"Ned", "744 NY", 18};

    // convert to json
    json j;
    j["name"] = p.name;
    j["address"] = p.address;
    j["age"] = p.age;

    // convert from json
    ns::person p2 {
        j["name"].get<std::string>(),
        j["address"].get<std::string>(),
        j["age"].get<int>()
    };

    json jsonp = p;
    std::cout << jsonp << std::endl;

    auto p3 = j.get<ns::person>();

    // assert(p == p3);
}