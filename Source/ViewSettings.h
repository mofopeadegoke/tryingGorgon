#pragma once

#include <Gorgon/UI/Dialog.h>
#include <Gorgon/Widgets/Composer.h>
#include <Gorgon/Widgets/Checkbox.h>
#include <Gorgon/Widgets/Button.h>

class ViewSettings : public Gorgon::Widgets::Composer {
public:
    ViewSettings();

private:
    Gorgon::Widgets::Checkbox camera, mode, speed, ik, manual, debug;
    //Buttons save and load config
    Gorgon::Widgets::Button saveButton, loadButton;

    void saveConfig(bool camera, bool mode, bool speed, bool ik, bool manual, bool debug);
    void loadConfig(bool& camera, bool& mode, bool& speed, bool& ik, bool& manual, bool& debug);
};
