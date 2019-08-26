#pragma once

#include <bdn/Notifier.h>
#include <bdn/platform.h>
#include <bdn/ui/ListViewDataSource.h>

#include "TodoStore.h"

class TodoListDataSource : public bdn::ui::ListViewDataSource
{
public:
    TodoListDataSource(std::shared_ptr<TodoStore> store);
    
public:
    size_t numberOfRows() override;
    std::shared_ptr<bdn::ui::View> viewForRowIndex(size_t rowIndex,
                                                   std::shared_ptr<bdn::ui::View> reusableView) override;
    float heightForRowIndex(size_t rowIndex) override;

    bdn::Notifier<size_t, bool> &entryCompletedChanged() { return _entryCompletedChanged; }

#ifdef BDN_PLATFORM_OSX
    bdn::Notifier<> &onChange() { return _onChange; }
#endif

private:
    bdn::Notifier<size_t, bool> _entryCompletedChanged;
    std::shared_ptr<TodoStore> _store;

#ifdef BDN_PLATFORM_OSX
    bdn::Notifier<> _onChange;
#endif
};
