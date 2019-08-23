#include "Todo.h"

using nlohmann::json;

void to_json(nlohmann::json& j, const Todo& todo)
{
    j = json{{"text", todo.text}, {"completed", todo.completed}};
}

void from_json(const nlohmann::json& j, Todo& todo)
{
    j.at("text").get_to(todo.text);
    j.at("completed").get_to(todo.completed);
}
