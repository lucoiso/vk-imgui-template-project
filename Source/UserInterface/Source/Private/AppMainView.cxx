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
import luGUI.UserInterface.Controls.Window.Flags;
import RenderCore.Utils.EnumHelpers;

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

#ifdef _WIN32
BOOL CALLBACK EnumWindowsProc(HWND Handle, LPARAM const UserData)
{
    if (char WindowTitle[256];
        IsWindowVisible(Handle) && GetWindowTextA(Handle, WindowTitle, sizeof(WindowTitle)) && strlen(WindowTitle) > 0)
    {
        auto const * const PairData = reinterpret_cast<std::pair<std::vector<const char*>*, std::unordered_map<strzilla::string, HWND>*>*>(UserData);
        PairData->first->emplace_back(PairData->second->emplace(WindowTitle, Handle).first->first.c_str());
    }

    return TRUE;
}

static void SetAsChilfOf(AppWindow* const Window)
{
    static std::vector ComboOptions { "None" };
    static std::unordered_map<strzilla::string, ::HWND> ExistingWindowHandles { };

    static auto UpdateList = [&]
    {
        ComboOptions.clear();
        ComboOptions.reserve(64);
        ComboOptions.emplace_back("None");

        std::pair EnumData(&ComboOptions, &ExistingWindowHandles);
        EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&EnumData));
    };

    if (std::size(ComboOptions) == 1)
    {
        UpdateList();
    }

    ImGui::Text("Set Parent");
    ImGui::SameLine();

    static std::int32_t CurrentSelection = 0;
    if (ImGui::Combo("##SetAsChildOfComboBox", &CurrentSelection, std::data(ComboOptions), static_cast<std::int32_t>(std::size(ComboOptions))))
    {
        Window->SetAsChildOf(ExistingWindowHandles.at(ComboOptions.at(CurrentSelection)));
    }

    ImGui::SameLine();
    if (ImGui::Button("Refresh##SetAsChildOfRefreshButton"))
    {
        UpdateList();
    }
}
#endif

void AppMainView::Paint()
{
    ImGuiWindowClass MainWindowClass;
    MainWindowClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;

    ImGui::SetNextWindowClass(&MainWindowClass);

    if (ImGui::Begin("##Main", nullptr, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration))
    {
        CreateBody();

        #ifdef _WIN32
        if (auto *const ParentWindow = dynamic_cast<AppWindow *>(GetParent());
            ParentWindow != nullptr && RenderCore::HasFlag(ParentWindow->GetInitializationFlags(), luGUI::InitializationFlags::WITHOUT_TITLEBAR))
        {
            SetAsChilfOf(ParentWindow);
        }
        #endif
    }

    ImGui::End();
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
