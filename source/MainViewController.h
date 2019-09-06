#pragma once

#include <bdn/ui.h>

#include "TodoListDataSource.h"
#include "TodoStore.h"

class MainViewController
{
public:
    MainViewController();
    virtual ~MainViewController() = default;

private:
    std::shared_ptr<bdn::ui::Window> _window;
    std::shared_ptr<bdn::ui::TextField> _newEntryField;
    std::shared_ptr<bdn::ui::ListView> _listView;
    std::shared_ptr<bdn::ui::ContainerView> _mainContainer;

    std::shared_ptr<TodoListDataSource> _todoDataSource;
    std::shared_ptr<TodoStore> _todoStore;
};
