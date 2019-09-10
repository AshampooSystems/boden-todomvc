#include "TodoListDataSource.h"
#include "TodoItemView.h"

#include <bdn/ui.h>

using namespace bdn::ui;

TodoListDataSource::TodoListDataSource(std::shared_ptr<TodoStore> store)
{
    _store = store;
}

size_t TodoListDataSource::numberOfRows() { return _store->todos.size(); }

std::shared_ptr<bdn::ui::View> TodoListDataSource::viewForRowIndex(const std::shared_ptr<ListView>& listView,
                                                                   size_t rowIndex,
                                                                   std::shared_ptr<bdn::ui::View> reusableView)
{
    if (!reusableView) {
        reusableView = std::make_shared<TodoItemView>(bdn::needsInit);
    }

    auto item = std::dynamic_pointer_cast<TodoItemView>(reusableView);
    
    item->text = _store->todos.at(rowIndex).at("text");
    item->completed = _store->todos.at(rowIndex).at("completed");
    
    std::weak_ptr<View> weakItem(item);
    
    item->completed.onChange().unsubscribeAll();
    item->completed.onChange() += [list=listView.get(), weakItem, this](const auto &property) {
        if(auto rowIndex = list->rowIndexForView(weakItem.lock())) {
            _store->todos.at(*rowIndex).at("completed") = property.get();
            _store->save();
        }
    };

#ifdef BDN_PLATFORM_OSX
    item->_deleteButton->onClick().unsubscribeAll();
    item->_deleteButton->onClick().subscribe([rowIndex, this](const auto &) {
        _store->remove(rowIndex);
        _onChange.notify();
    });
#endif

    return reusableView;
}

float TodoListDataSource::heightForRowIndex(size_t rowIndex) { return 50; }
