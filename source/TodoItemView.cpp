#include "TodoItemView.h"

#include <bdn/ui/yoga.h>

using namespace bdn::ui;

void TodoItemView::init()
{
    // Item height is controlled by TodoListDataSource::heightForRowIndex()
    stylesheet = FlexJsonStringify({
        "direction": "Row",
        "flexGrow": 1,
        "alignItems": "Center",
        "padding": 5
    });

    auto checkbox = std::make_shared<Checkbox>();
    checkbox->checked.bind(completed);
    checkbox->stylesheet = FlexJsonStringify({"flexShrink" : 0});

    addChildView(checkbox);

    auto label = std::make_shared<Label>();
    label->text.bind(text);

    addChildView(label);

#ifdef BDN_PLATFORM_OSX
    label->stylesheet = FlexJsonStringify({"flexGrow" : 1});

    _deleteButton = std::make_shared<Button>();
    _deleteButton->label = "X";
    addChildView(_deleteButton);
#endif
}
