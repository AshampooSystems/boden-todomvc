#pragma once

#include <string>
#include <nlohmann/json.hpp>

struct Todo
{
    std::string text;
    bool completed;
};

void to_json(nlohmann::json& j, const Todo& todo);
void from_json(const nlohmann::json& j, Todo& todo);
