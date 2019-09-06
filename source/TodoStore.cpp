#include "TodoStore.h"

#include <bdn/path.h>
#include <fstream>
#include <filesystem>

using nlohmann::json;
using bdn::path::documentDirectoryPath;
using std::filesystem::path;
using std::filesystem::create_directories;

void TodoStore::add(const std::string &todoText)
{
    todos.push_back(Todo{todoText, false});
    save();
}

void TodoStore::remove(size_t index)
{
    if (index >= todos.size()) return;

    todos.erase(todos.begin() + index);
    save();
}

void TodoStore::load()
{
    std::ifstream file(todoFilePath());
    if (!file.good()) return;
    
    file >> todos;
}

void TodoStore::save()
{
    std::ofstream file(todoFilePath());
    file << todos;
}

std::string TodoStore::todoFilePath()
{
    path documentPath = path(documentDirectoryPath()) / "TodoMVC";
    create_directories(documentPath);
    
    return documentPath / "todo.json";
}
