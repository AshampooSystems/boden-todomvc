#pragma once

#include "Todo.h"
#include <vector>

class TodoStore
{
public:
	void load();
	void save();

public:
	std::vector<Todo> todos;
    
private:
    std::string todoFilePath();
};
