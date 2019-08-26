#include "TodoStore.h"
#include <nlohmann/json.hpp>
#include <bdn/path.h>
#include <fstream>

using nlohmann::json;
using bdn::path::documentDirectoryPath;

void TodoStore::load()
{
    json todosJSON;

    std::ifstream file(todoFilePath());
    if (!file.good()) return;
    
    file >> todosJSON;

    todos.clear();
    
    for (auto todo : todosJSON) {
        todos.push_back(todo);
    }
}

void TodoStore::save()
{
    json todosJSON;
    for (auto todo : todos) {
        todosJSON.push_back(todo);
    }
    
    std::ofstream file(todoFilePath());
    file << todosJSON;
}

void TodoStore::add(const std::string &todoText)
{
    todos.push_back({todoText, false});
    save();
}

void TodoStore::remove(size_t index)
{
    assert(index >= 0 && index < todos.size());
    todos.erase(todos.begin() + index);
    save();
}

std::string TodoStore::todoFilePath()
{
    return documentDirectoryPath() + "/todo.json";
}
