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
    void SetCompleted(bool completed);
    std::string GetTaskText() const;

    auto getCheckbox() {
        return &checkbox;
    }

    auto getDeleteButton() {
        return &deleteButton;
    }   
    
private:
    Widgets::Checkbox checkbox;
    Widgets::Label taskLabel;
    Widgets::Button deleteButton;
    
    UI::Organizers::Flow organizer;
};