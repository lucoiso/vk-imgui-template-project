// Author: Lucas Vilas-Boas
// Year : 2024
// Repo : https://github.com/lucoiso/vk-imgui-template-project

module;

module UserInterface.AppMainView;

using namespace UserInterface;

AppMainView::AppMainView(Control *const Parent)
    : Control(Parent)
{
}

void AppMainView::Paint()
{
    static bool IsOpen = true;
    if (ImGui::Begin("AppMainView", &IsOpen, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration))
    {
        CreateBody();
    }
    ImGui::End();

    if (!IsOpen)
    {
        if (auto* const ParentWindow = static_cast<AppWindow*>(GetParent()))
        {
            ParentWindow->RequestClose();
        }
    }
}

void AppMainView::CreateBody()
{
    constexpr auto PlaceholderText = "Placeholder";

    float const WindowWidth = ImGui::GetWindowSize().x;
    float const TextWidth   = ImGui::CalcTextSize(PlaceholderText).x;

    float const WindowHeight = ImGui::GetWindowSize().y;
    float const TextHeight   = ImGui::CalcTextSize(PlaceholderText).y;

    ImGui::SetCursorPosX((WindowWidth - TextWidth) * 0.5f);
    ImGui::SetCursorPosY((WindowHeight - TextHeight) * 0.5f);

    ImGui::Text(PlaceholderText);
}
