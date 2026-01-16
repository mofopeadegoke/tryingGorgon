#include "TaskItem.h"

TaskItem::TaskItem(const std::string& taskText)
    : Composer({30_u, 2_u})
    , checkbox("", false)
    , taskLabel(taskText)
    , deleteButton("Delete")
{
    AttachOrganizer(organizer);
    
    Add(checkbox);
    Add(taskLabel);
    Add(deleteButton);
    
    organizer << checkbox << 1 << taskLabel << 1 << deleteButton;
    
    taskLabel.SetWidth(100_perc);

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