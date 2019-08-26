#include <bdn/log.h>
#include <bdn/ui.h>
#include <bdn/ui/yoga.h>

#include "MainViewController.h"

using bdn::Rect;
using namespace bdn::ui;

MainViewController::MainViewController()
{
    _window = std::make_shared<Window>();
    _window->title = "TodoMVC";
    _window->geometry = Rect{0, 0, 300, 500};
    _window->setLayout(std::make_shared<yoga::Layout>());

    _mainContainer = std::make_shared<ContainerView>();
    _mainContainer->stylesheet =
        FlexJsonStringify({"flexGrow" : 1.0, "direction" : "Column", "justifyContent" : "Center"});

    _newEntryField = std::make_shared<TextField>();
    _newEntryField->placeholder = "What needs to be done?";
    _newEntryField->stylesheet = FlexJsonStringify({"alignSelf" : "Center", "size": { "width": "100%", "height": 50 }});

    _mainContainer->addChildView(_newEntryField);

    _listView = std::make_shared<ListView>();
    _listView->enableSwipeToDelete = true;
 
    _todoStore = std::make_shared<TodoStore>([this](auto) { _listView->reloadData(); });
    _todoStore->load();

    _todoDataSource = std::make_shared<TodoListDataSource>(_todoStore);
    _todoDataSource->entryCompletedChanged() += [=](auto, auto) { /*listView->reloadData();*/ };

    _listView->dataSource = _todoDataSource;
    _listView->stylesheet = FlexJsonStringify({"flexGrow" : 1.0});

    _mainContainer->addChildView(_listView);

    _listView->onDelete() += [this](int index) { _todoStore->remove(index); };

    _newEntryField->onSubmit() += [=](auto ev) {
        if (!_newEntryField->text->empty()) {
            _todoStore->add(_newEntryField->text);
            _newEntryField->text = std::string();
        }
    };
    
#ifdef BDN_PLATFORM_OSX
    _todoDataSource->onChange() += [this]() { _listView->reloadData(); };
#endif

    _window->contentView = _mainContainer;
    _window->visible = true;
}
