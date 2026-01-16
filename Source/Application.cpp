#include "Application.h"
#include "json.hpp"
#include <Gorgon/Graphics/Color.h>
#include <Gorgon/UI/Dialog.h>
#include <Gorgon/UI/Dimension.h>
#include <Gorgon/UI/Organizers/Flow.h>
#include <Gorgon/UI/Window.h>
#include <Gorgon/Window.h>
#include <Gorgon/Input/Mouse.h>

using json = nlohmann::json;

Application::Application(UI::Window& window) :
    window(window),
    addButton("Add Task")
    
{
    window.Add(inputPanel);
    inputPanel.SetHeight(4_u);
    inputPanel.SetWidth(100_perc);
    inputPanel.AttachOrganizer(inputOrganizer);
    
    
    // Add textbox and button to input panel
   inputOrganizer <<  taskInput << addButton ;
    taskInput.SetWidth(30_u);
    taskInput.Focus();
    
    // Add task list panel below
    window.Add(taskListPanel);
    taskListPanel.SetWidth(100_perc);
    taskListPanel.AttachOrganizer(taskListOrganizer);
    taskListPanel.Move(0_u, 4_u);
    
    // Connect the button click event
    addButton.ClickEvent.Register([this]() {
        AddTask();
    });

    
    inputPanel.SetDefault(addButton);
    Run();
}

bool Application::Quit() {
    return true;
}

void Application::Run(){

}

void Application::AddTask() {
    auto text = taskInput.GetText();
    
    if(text.empty()) {
        UI::ShowMessage("Error", "Please enter a task");
        return;
    }

    auto taskItem = new TaskItem(text);
    taskItem->getDeleteButton()->ClickEvent.Register([this, taskItem]() {
        DeleteTask(*taskItem);
    });
    taskItems.push_back(taskItem);

    taskListPanel.Add(*taskItem);
    taskInput.Set(" "); // clearing the input box
}

void Application::SaveTasks() {
    for (const auto& item : taskItems) {
        Task task;
        task.text = item->GetTaskText();
        task.completed = item->IsCompleted();
        tasks.push_back(task);
    }
}

void Application::DeleteTask(TaskItem& item) {
    taskListPanel.Remove(item);
    
    auto it = std::find(taskItems.begin(), taskItems.end(), &item);
    if (it != taskItems.end()) {
        taskItems.erase(it);
    }
}