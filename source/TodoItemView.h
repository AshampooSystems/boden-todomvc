#pragma once

#include <bdn/ui.h>

class TodoItemView : public bdn::ui::CoreLess<bdn::ui::ContainerView>
{
public:
    bdn::Property<std::string> text;
    bdn::Property<bool> completed;

public:
    using CoreLess<ContainerView>::CoreLess;

public:
    void init() override;

#ifdef BDN_PLATFORM_OSX
  public:
    std::shared_ptr<bdn::ui::Button> _deleteButton;
#endif
};
