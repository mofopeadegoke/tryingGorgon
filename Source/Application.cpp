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

    window.Add(titleLabel);
    titleLabel.Move(18_u, 4_u);
    
    
    // Connect the button click event
    addButton.ClickEvent.Register([this]() {
        AddTask();
    });

    
    inputPanel.SetDefault(addButton);
    LoadTasks();
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
    taskItem->getCheckbox()->ChangedEvent.Register([this](bool) {
        SaveTasks();
    });
    taskItems.push_back(taskItem);

    taskListPanel.Add(*taskItem);
    taskInput.Set(" "); // clearing the input box
    SaveTasks();
}

void Application::SaveTasks() {
    tasks.clear();

    for (const auto& item : taskItems) {
        Task task;
        task.text = item->GetTaskText();
        task.completed = item->IsCompleted();
        tasks.push_back(task);
    }

    json tasksInJson = json::array();
    std::ofstream file("tasks.json");
    for (const auto& task : tasks) {
        tasksInJson.push_back({ {"text", task.text}, {"completed", task.completed} });
    }
    file << tasksInJson.dump(4);    
    file.close();
    int numberOfTasks = taskItems.size();
    titleLabel.SetText("0 out of " + std::to_string(numberOfTasks) + " tasks completed");
}

void Application::DeleteTask(TaskItem& item) {
    taskListPanel.Remove(item);
    
    auto it = std::find(taskItems.begin(), taskItems.end(), &item);
    if (it != taskItems.end()) {
        taskItems.erase(it);
    }
    SaveTasks();

}

void Application::LoadTasks() {
    std::ifstream file("tasks.json");
    
    if (!file.is_open()) {
        std::cout << "No tasks.json found (OK for first run)\n";
        return;
    }
    
    try {
        json tasksInJson;
        file >> tasksInJson;
        file.close();
        
        for (const auto& taskJson : tasksInJson) {
            std::string text = taskJson.value("text", "");
            bool completed = taskJson.value("completed", false);
            
            if (!text.empty()) {
                // Create task widget
                auto taskItem = new TaskItem(text);
                taskItem->SetCompleted(completed);
                
                // Register events
                taskItem->getDeleteButton()->ClickEvent.Register([this, taskItem]() {
                    DeleteTask(*taskItem);
                });                

                taskItem->getCheckbox()->ChangedEvent.Register([this](bool) {
                    SaveTasks();
                });
                
                // Add to list and UI
                taskItems.push_back(taskItem);
                taskListPanel.Add(*taskItem);
                taskListOrganizer.Add(*taskItem);
            }
        }
        
        std::cout << "Loaded " << taskItems.size() << " tasks\n";
        int numberOfTasks = taskItems.size();
        titleLabel.SetText("0 out of " + std::to_string(numberOfTasks) + " tasks completed");
        
    } catch (const std::exception& e) {
        std::cerr << "Error loading tasks: " << e.what() << "\n";
    }
}