#include "TaskItem.h"

TaskItem::TaskItem(const std::string& taskText)
    : Composer({30_u, 2_u})
    , checkbox("", false)
    , taskLabel(taskText)
    , deleteButton("Delete")
{
    AttachOrganizer(organizer);
    deleteButton.SetText("Delete");
    
    organizer << checkbox << taskLabel << deleteButton;
    
    taskLabel.SetWidth(2_u);
    checkbox.SetWidth(1_u);

    checkbox.ChangedEvent.Register([this]() {
        
    });
    
    deleteButton.ClickEvent.Register([this]() {
        
    });
}

bool TaskItem::IsCompleted() const {
    return checkbox.GetState();
}

std::string TaskItem::GetTaskText() const {
    return taskLabel.GetText();
}