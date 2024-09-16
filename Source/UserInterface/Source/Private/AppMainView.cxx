// Author: Lucas Vilas-Boas
// Year : 2024
// Repo : https://github.com/lucoiso/vk-imgui-template-project

module;

#include <imgui.h>
#include <imgui_internal.h>

module UserInterface.AppMainView;

import UserInterface.Win32ParentingHelper;
import luGUI.UserInterface.Items.Item;
import luGUI.UserInterface.Items.Input;
import luGUI.UserInterface.Items.Button;
import luGUI.UserInterface.Items.Text;
import luGUI.UserInterface.Items.Image;
import luGUI.UserInterface.Panels.Stack;
import luGUI.UserInterface.Panels.Grid;
import luGUI.UserInterface.Controls.Window.Flags;
import RenderCore.Utils.EnumHelpers;

using namespace UserInterface;

AppMainView::AppMainView(Control *const Parent)
    : Control(Parent)
{
}

void AppMainView::Paint()
{
    ImGuiWindowClass MainWindowClass;
    MainWindowClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;

    ImGui::SetNextWindowClass(&MainWindowClass);

    if (ImGui::Begin("##Main", nullptr, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration))
    {
        CreateBody();
    }

    ImGui::End();
}

void AppMainView::CreateBody() const
{
    constexpr auto PlaceholderKey = "Placeholder";
    constexpr auto MaxWidth = 600.F;

    static auto MainGrid = luGUI::Grid::Create(MaxWidth)
                           ->Add<luGUI::Image>(0, 0, PlaceholderKey)
                           ->Add<luGUI::Text> (0, 1, PlaceholderKey, "Placeholder: 1")
                           ->Add<luGUI::Image>(1, 0, PlaceholderKey)
                           ->Add<luGUI::Text> (1, 1, PlaceholderKey, "Placeholder: 2");

    MainGrid->Draw();

    constexpr luGUI::TextInputSettings          TextSettings { .Multiline = true };
    constexpr luGUI::NumberInputSettings<float> FloatSettings { .Slider = true };

    static auto MainStack = luGUI::Stack::Create(luGUI::Orientation::Vertical, MaxWidth)
                            ->Add<luGUI::TextInput> ("Placeholder: 3", TextSettings)
                            ->Add<luGUI::FloatInput>("Placeholder: 4", FloatSettings)
                            ->Add<luGUI::TextInput> ("Placeholder: 5")
                            ->Add<luGUI::IntInput>  ("Placeholder: 6")
                            ->Add<luGUI::Button>    ("Placeholder: 7");

    MainStack->Draw();

    #ifdef _WIN32
    if (auto const *const ParentWindow = dynamic_cast<AppWindow *>(GetParent()))
    {
        static std::shared_ptr<luGUI::Stack> const SetAsChildStack = CreateWin32ParentingStack(ParentWindow, MaxWidth);
        SetAsChildStack->Draw();
    }
    #endif
}
