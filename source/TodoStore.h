#pragma once

#include "Todo.h"
#include <vector>

class TodoStore
{
public:
	TodoStore(std::function<void(const TodoStore*)> storeDidChangedHandler);

	void load();
	void save();

	void add(const std::string &todoText);
	void remove(size_t index);

public:
	std::vector<Todo> todos;
    
private:
    std::string todoFilePath();

private:
    std::function<void(const TodoStore*)> _storeDidChangeHandler;
};
