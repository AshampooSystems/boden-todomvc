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

std::string TodoStore::todoFilePath()
{
    return documentDirectoryPath() + "/todo.json";
}
