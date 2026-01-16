#pragma once

#include <Gorgon/Widgets/Composer.h>
#include <Gorgon/Widgets/Checkbox.h>
#include <Gorgon/Widgets/Label.h>
#include <Gorgon/Widgets/Button.h>
#include <Gorgon/UI/Organizers/Flow.h>
#include <string>

namespace Widgets = Gorgon::Widgets;
namespace UI = Gorgon::UI;

using namespace Gorgon::UI::literals;

class TaskItem : public Widgets::Composer {
public:
    TaskItem(const std::string& taskText);
    
    bool IsCompleted() const;
    std::string GetTaskText() const;
    
private:
    Widgets::Checkbox checkbox;
    Widgets::Label taskLabel;
    Widgets::Button deleteButton;
    
    UI::Organizers::Flow organizer;
};