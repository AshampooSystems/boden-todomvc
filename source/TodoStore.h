#pragma once

#include "Todo.h"

#include <vector>
#include <nlohmann/json.hpp>

class TodoStore
{
public:
	// Add a todo at the end of the list and call save()
	void add(const std::string &todoText);
	// Remove the todo at the given index from the list and call save()
	void remove(size_t index);

	// Load the todo list from device storage as a JSON file
	void load();
	// Save the todo list to device storage as a JSON file
	void save();

public:
	// The list of todos
    nlohmann::json todos = std::vector<Todo>();
    
private:
	// Returns the path of the todo.json file on internal device storage
    std::string todoFilePath();
};
