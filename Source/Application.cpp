#include "Application.h"

#include <Gorgon/Graphics/Color.h>
#include <Gorgon/UI/Dialog.h>
#include <Gorgon/UI/Dimension.h>
#include <Gorgon/UI/Organizers/Flow.h>
#include <Gorgon/UI/Window.h>
#include <Gorgon/Window.h>
#include <Gorgon/Input/Mouse.h>

Application::Application(UI::Window& window) :
    window(window),
    addButton("Add Task")
    
{
    window.Add(inputPanel);
    inputPanel.SetHeight(4_u);
    inputPanel.SetWidth(100_perc);
    inputPanel.AttachOrganizer(inputOrganizer);
    
    // Add textbox and button to input panel
    inputOrganizer.Add(taskInput);
    inputOrganizer.Add(addButton);
    taskInput.SetWidth(30_u);
    taskInput.Focus();
    
    // Add task list panel below
    window.AddNextTo(taskListPanel);
    taskListPanel.SetWidth(100_perc);
    taskListPanel.AttachOrganizer(taskListOrganizer);
    
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
    
    // For now, just show a message - we'll improve this next
    UI::ShowMessage("Task Added", "Task: " + text);
    
    // Clear the input - setter not available for this Inputbox type, so no action performed.
}