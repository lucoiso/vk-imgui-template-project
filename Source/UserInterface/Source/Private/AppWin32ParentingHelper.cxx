// Author: Lucas Vilas-Boas
// Year : 2024
// Repo : https://github.com/lucoiso/vk-imgui-template-project

module;

#ifdef _WIN32
    #include <Windows.h>
    #include <imgui.h>
#endif // _WIN32

module UserInterface.Win32ParentingHelper;

#ifdef _WIN32
import luGUI.UserInterface.Items.ComboBox;
import luGUI.UserInterface.Items.Button;
import luGUI.UserInterface.Items.Text;

using namespace UserInterface;

BOOL CALLBACK EnumWindowsProc(HWND Handle, LPARAM const UserData)
{
    if (char WindowTitle[64];
        IsWindowVisible(Handle) && GetWindowTextA(Handle, WindowTitle, sizeof(WindowTitle)) && strlen(WindowTitle) > 0)
    {
        if (auto * const WindowMap = reinterpret_cast<std::unordered_map<strzilla::string, ::HWND>*>(UserData))
        {
            WindowMap->emplace(WindowTitle, Handle);
        }
    }

    return TRUE;
}

static std::unordered_map<strzilla::string, ::HWND> s_WindowHandlesMap { };
static std::vector<strzilla::string> s_WindowHandlesOptions {};
static strzilla::string s_CurrentOwningHandle {};

static void UpdateAvailableHandles()
{
    s_WindowHandlesMap.clear();
    s_WindowHandlesOptions.clear();

    s_WindowHandlesMap.reserve(16);
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&s_WindowHandlesMap));

    if (!std::empty(s_WindowHandlesMap))
    {
        s_WindowHandlesOptions.reserve(std::size(s_WindowHandlesMap));

        for (strzilla::string const &OptionIt : s_WindowHandlesMap | std::views::keys)
        {
            s_WindowHandlesOptions.emplace_back(OptionIt);

            if (std::empty(s_CurrentOwningHandle))
            {
                s_CurrentOwningHandle = OptionIt;
            }
        }
    }
}

std::shared_ptr<luGUI::Stack> UserInterface::CreateWin32ParentingStack(AppWindow const* const Window, float const Width, luGUI::Alignment const Alignment)
{
    if (std::empty(s_WindowHandlesMap))
    {
        UpdateAvailableHandles();
    }

    return luGUI::Stack::Create  (luGUI::Orientation::Horizontal, Width, Alignment)
           ->Add<luGUI::Text>    ("Parent Process:")
           ->Add<luGUI::ComboBox>("##ParentProcess",
                                  &s_WindowHandlesOptions,
                                  [] (strzilla::string const& Value)
                                  {
                                      s_CurrentOwningHandle = Value;
                                  })
           ->Add<luGUI::Button>  ("Re-Parent",
                                 [Window]
                                 {
                                     Window->SetAsChildOf(s_WindowHandlesMap.at(s_CurrentOwningHandle));
                                 })
           ->Add<luGUI::Button>  ("Refresh",
                                 []
                                 {
                                     UpdateAvailableHandles();
                                 })
           ->Add<luGUI::Button>  ("Reset",
                                 [Window]
                                 {
                                     Window->SetAsChildOf(nullptr);
                                 });
}
#endif