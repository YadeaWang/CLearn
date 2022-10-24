#include "nlohmann/json.hpp"
#include <string>
#include <iostream>

using json = nlohmann::json;

enum TaskState {
    TS_STOPPED,
    TS_RUNNING,
    TS_COMPLETED,
    TS_INVALID = -1,
};

NLOHMANN_JSON_SERIALIZE_ENUM( TaskState, {
    {TS_INVALID, nullptr},     // 这个会是json.get<>(TaskState)的默认值,第一个位置
    {TS_STOPPED, "stopped"},
    {TS_RUNNING, "running"},
    {TS_COMPLETED, "completed"},
})

int main() {
    json j = TS_STOPPED;
    assert(j == "stopped");

    json j3 = "running";
    assert(j3.get<TaskState>() == TS_RUNNING);

    json jPi = 3.14;
    assert(jPi.get<TaskState>() == (TaskState)-1);
    std::cout << (TaskState)-1 << std::endl;
}