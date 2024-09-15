// Author: Lucas Vilas-Boas
// Year : 2024
// Repo : https://github.com/lucoiso/vk-imgui-template-project

module;

#include <imgui.h>
#include <imgui_internal.h>

module UserInterface.AppMainView;

import luGUI.UserInterface.Singletons.ImageManager;
import luGUI.UserInterface.Singletons.FontManager;

import luGUI.UserInterface.Items.Item;
import luGUI.UserInterface.Items.Input;
import luGUI.UserInterface.Items.Button;
import luGUI.UserInterface.Panels.Stack;
import luGUI.UserInterface.Panels.Grid;

using namespace UserInterface;

AppMainView::AppMainView(Control *const Parent)
    : Control(Parent)
{
}

void AppMainView::OnInitialize()
{
    PrepareIcons();
    PrepareFonts();
}

void AppMainView::Paint()
{
    ImGuiWindowClass MainWindowClass;
    MainWindowClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;

    ImGui::SetNextWindowClass(&MainWindowClass);

    static bool IsOpen = true;
    if (ImGui::Begin("##Main", &IsOpen, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration))
    {
        CreateBody();
    }
    ImGui::End();

    if (!IsOpen)
    {
        if (auto *const ParentWindow = dynamic_cast<AppWindow *>(GetParent()))
        {
            ParentWindow->RequestClose();
        }
    }
}

constexpr auto g_PlaceholderResourceKey = "Placeholder";

void AppMainView::PrepareIcons()
{
    if (constexpr auto Path = "Resources/Icons/Placeholder.png";
        !luGUI::ImageManager::Get().RegisterTexture(g_PlaceholderResourceKey, Path))
    {
        throw std::runtime_error("failed to prepare application icons");
    }
}

void AppMainView::PrepareFonts()
{
    if (constexpr auto Path = "Resources/Fonts/BebasNeue-Regular.ttf";
        luGUI::FontManager::Get().RegisterFont(g_PlaceholderResourceKey, Path))
    {
        luGUI::FontManager::Get().BuildFonts();
    }
    else
    {
        throw std::runtime_error("failed to prepare application fonts");
    }
}

void AppMainView::CreateBody()
{
    static auto MainGrid = luGUI::Grid::Create()
                           ->Add<luGUI::Image>(0, 0, g_PlaceholderResourceKey)
                           ->Add<luGUI::Text>(0, 1, g_PlaceholderResourceKey, "Placeholder: 1")
                           ->Add<luGUI::Image>(1, 0, g_PlaceholderResourceKey)
                           ->Add<luGUI::Text>(1, 1, g_PlaceholderResourceKey, "Placeholder: 2");

    MainGrid->Draw();

    constexpr luGUI::TextInputSettings          TextSettings { .Multiline = true };
    constexpr luGUI::NumberInputSettings<float> FloatSettings { .Slider = true };

    static auto MainStack = luGUI::Stack::Create(luGUI::Orientation::Vertical)
                            ->Add<luGUI::TextInput>("Placeholder: 3", TextSettings)
                            ->Add<luGUI::FloatInput>("Placeholder: 4", FloatSettings)
                            ->Add<luGUI::TextInput>("Placeholder: 5")
                            ->Add<luGUI::IntInput>("Placeholder: 6")
                            ->Add<luGUI::Button>("Placeholder: 7");

    MainStack->Draw();
}
