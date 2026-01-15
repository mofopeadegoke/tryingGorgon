#include <Gorgon/Main.h>
#include <Gorgon/UI.h>
#include <Gorgon/UI/Organizers/Flow.h>
#include <Gorgon/UI/Window.h>
#include <Gorgon/Graphics/Color.h>
#include <Gorgon/Widgets/Generator.h>

#include "Application.h"

int main() {
    Gorgon::Initialize("Renegade Engine");

    //Change this line to change window size or window title
    Gorgon::UI::Window window({1200, 900}, "An application using Gorgon UI");

    Gorgon::Graphics::Initialize();

    auto &uigen = *new Gorgon::Widgets::SimpleGenerator;
       
    uigen.SetColor(Gorgon::Graphics::Color::Container, {{Gorgon::Graphics::Color::Black, Gorgon::Graphics::Color::White, 0.5f}, {Gorgon::Graphics::Color::Black, 0.8f}, Gorgon::Graphics::Color::Black});
    
    uigen.SetColor(Gorgon::Graphics::Color::Regular, {{Gorgon::Graphics::Color::White}, {Gorgon::Graphics::Color::Blue, 0.7f}, {Gorgon::Graphics::Color::DarkBlue}});
    
    uigen.SetColor(Gorgon::Graphics::Color::Odd, {{Gorgon::Graphics::Color::White, 0.9}, {Gorgon::Graphics::Color::Black, Gorgon::Graphics::Color::White, 0.28f}, {Gorgon::Graphics::Color::Black, 0.5}});
    
    uigen.SetColor(Gorgon::Graphics::Color::Disabled, {{Gorgon::Graphics::Color::White, 0.5f},{Gorgon::Graphics::Color::SemiDarkGrey, 0.8f}});
    
    uigen.SetColor(Gorgon::Graphics::Color::Hover, {Gorgon::Graphics::Color::White, {Gorgon::Graphics::Color::Tan, 0.3f}, Gorgon::Graphics::Color::LightBlue});

    uigen.SetColor(Gorgon::Graphics::Color::Link, {Gorgon::Graphics::Color::LightBlue, Gorgon::Graphics::Color::Transparent});
    
    uigen.SetColor(Gorgon::Graphics::Color::Edit, {Gorgon::Graphics::Color::White, {Gorgon::Graphics::Color::White, 0.2f}, Gorgon::Graphics::Color::AquaBlue});
    
    uigen.SetColor(Gorgon::Graphics::Color::Selection, {Gorgon::Graphics::Color::White, {Gorgon::Graphics::Color::LightBlue, 0.5f}, Gorgon::Graphics::Color::Transparent});
    
    uigen.SetColor(Gorgon::Graphics::Color::Info, {{Gorgon::Graphics::Color::Black,0.9f}, Gorgon::Graphics::Color::LightTan});
            
    uigen.SetColor(Gorgon::Graphics::Color::ActiveContainer, {Gorgon::Graphics::Color::White, {Gorgon::Graphics::Color::Black, Gorgon::Graphics::Color::White, 0.25f}, {Gorgon::Graphics::Color::LightBlue,0.75f}});
    
    uigen.SetColor(Gorgon::Graphics::Color::PassiveContiner, {Gorgon::Graphics::Color::White, {Gorgon::Graphics::Color::Black, Gorgon::Graphics::Color::White, 0.1f}, {Gorgon::Graphics::Color::Black,0.4f}});
    
    uigen.SetColor(Gorgon::Graphics::Color::Title, {Gorgon::Graphics::Color::Azure, Gorgon::Graphics::Color::Transparent});
    
    uigen.SetColor(Gorgon::Graphics::Color::Down, {Gorgon::Graphics::Color::White, Gorgon::Graphics::Color::Black, Gorgon::Graphics::Color::LightBlue});
    
    uigen.SetColor(Gorgon::Graphics::Color::Focus, {Gorgon::Graphics::Color::White, Gorgon::Graphics::Color::Black, {Gorgon::Graphics::Color::LightBlue, 0.8}});
            
    uigen.SetColor(Gorgon::Graphics::Color::Active, {{Gorgon::Graphics::Color::Black, Gorgon::Graphics::Color::White, 0.25f}, {Gorgon::Graphics::Color::White, 0.9}});

    uigen.InitFonts("noto sans", "", 6);
    uigen.InitDimensions(6);
    
    Gorgon::UI::Initialize(uigen);


    Application app(window);
    window.AllowResize();

    window.ClosingEvent.Register([&app](bool &allow) {
        allow = app.Quit();
    });

    window.Run();

    return 0;
}
