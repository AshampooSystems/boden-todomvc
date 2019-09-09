#pragma once

#include <bdn/ui.h>
#include "TodoStore.h"

class TodoListDataSource : public bdn::ui::ListViewDataSource
{
public:
    TodoListDataSource(std::shared_ptr<TodoStore> store);
    
public:
    size_t numberOfRows() override;
    std::shared_ptr<bdn::ui::View> viewForRowIndex(const std::shared_ptr<bdn::ui::ListView>& listView,
                                                   size_t rowIndex,
                                                   std::shared_ptr<bdn::ui::View> reusableView) override;

    float heightForRowIndex(size_t rowIndex) override;

#ifdef BDN_PLATFORM_OSX
    bdn::Notifier<> &onChange() { return _onChange; }
#endif

private:
    std::shared_ptr<TodoStore> _store;

#ifdef BDN_PLATFORM_OSX
    bdn::Notifier<> _onChange;
#endif
};
