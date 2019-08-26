#pragma once

#include "Todo.h"
#include <vector>

class TodoStore
{
public:
	void load();
	void save();

	void add(const std::string &todoText);
	void remove(size_t index);

public:
	std::vector<Todo> todos;
    
private:
    std::string todoFilePath();
};
