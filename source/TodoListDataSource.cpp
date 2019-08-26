#include "TodoListDataSource.h"
#include "TodoListItem.h"

#include <bdn/ui.h>

using namespace bdn::ui;

TodoListDataSource::TodoListDataSource(std::shared_ptr<TodoStore> store)
{
    _store = store;
    _store->load();
    empty = _store->todos.empty();
}

void TodoListDataSource::add(const std::string &entry)
{
    _store->todos.push_back({entry, false});
    _store->save();
    empty = false;
}

void TodoListDataSource::remove(int index)
{
    assert(index >= 0 && index < _store->todos.size());
    _store->todos.erase(_store->todos.begin() + index);
    _store->save();
    
    empty = _store->todos.empty();
}

size_t TodoListDataSource::numberOfRows() { return _store->todos.size(); }

std::shared_ptr<bdn::ui::View> TodoListDataSource::viewForRowIndex(size_t rowIndex,
                                                                   std::shared_ptr<bdn::ui::View> reusableView)
{
    if (!reusableView) {
        reusableView = std::make_shared<TodoListItem>(bdn::needsInit);
    }

    if (auto item = std::dynamic_pointer_cast<TodoListItem>(reusableView)) {
        item->text = _store->todos.at(rowIndex).text;
        item->completed.onChange().unsubscribeAll();
        item->completed = _store->todos.at(rowIndex).completed;
        item->completed.onChange() += [=](const auto &property) {
            _store->todos.at(rowIndex).completed = property.get();
            _store->save();

            _entryCompletedChanged.notify(rowIndex, property.get());
        };

#ifdef BDN_PLATFORM_OSX
        item->_deleteButton->onClick().unsubscribeAll();
        item->_deleteButton->onClick().subscribe([rowIndex, this](const auto &) {
            this->remove(rowIndex);
            _onChange.notify();
        });
#endif
    }

    return reusableView;
}

float TodoListDataSource::heightForRowIndex(size_t rowIndex) { return 50; }
