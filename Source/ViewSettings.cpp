#include "ViewSettings.h"
#include "json.hpp"
#include <Gorgon/UI/Organizers/List.h>

ViewSettings::ViewSettings()
    : Composer({6, 5})
    , camera("Show Camera", true)
    , mode("Show Mode", true)
    , speed("Show Speed", true)
    , ik("Show IK", true)
    , manual("Manual Control", false)
    , debug("Show Debug Info", false)
    , saveButton("Save View Settings")
    , loadButton("Load View Settings")
{
    CreateOrganizer<Gorgon::UI::Organizers::List>();

    Add(camera);
    Add(mode);
    Add(speed);
    Add(ik);
    Add(manual);
    Add(debug);

    Add(saveButton);
    Add(loadButton);

    saveButton.ClickEvent.Register([this]() {
        saveConfig(camera.GetState(), mode.GetState(), speed.GetState(), ik.GetState(), manual.GetState(), debug.GetState());
    });

    loadButton.ClickEvent.Register([this]() {
        bool t_camera, t_mode, t_speed, t_ik, t_manual, t_debug;
        loadConfig(t_camera, t_mode, t_speed, t_ik, t_manual, t_debug);
        camera.SetState(t_camera);
        mode.SetState(t_mode);
        speed.SetState(t_speed);
        ik.SetState(t_ik);
        manual.SetState(t_manual);
        debug.SetState(t_debug);
    });
}

void ViewSettings::saveConfig(bool camera, bool mode, bool speed, bool ik, bool manual, bool debug)
{
    nlohmann::json config;
    config["camera"] = camera;
    config["mode"] = mode;
    config["speed"] = speed;
    config["ik"] = ik;
    config["manual"] = manual;
    config["debug"] = debug;

    std::ofstream ostream("viewsettings.json");
    ostream << config.dump(4);
}

void ViewSettings::loadConfig(bool& camera, bool& mode, bool& speed, bool& ik, bool& manual, bool& debug)
{
    std::ifstream file("viewsettings.json");
    if(!file.is_open()){
        Gorgon::UI::ShowMessage("Error", "Could not open viewsettings.json for reading");
        std::cerr << "Could not open viewsettings.json for reading\n";
        return;
    }
    nlohmann::json config;
    file >> config;

    camera = config.value("camera", true);
    mode = config.value("mode", true);
    speed = config.value("speed", true);
    ik = config.value("ik", true);
    manual = config.value("manual", false);
    debug = config.value("debug", false);
}
