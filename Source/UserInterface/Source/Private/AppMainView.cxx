// Author: Lucas Vilas-Boas
// Year : 2024
// Repo : https://github.com/lucoiso/vk-imgui-template-project

module;

module UserInterface.AppMainView;

import luGUI.UserInterface.Singletons.ImageManager;
import luGUI.UserInterface.Singletons.FontManager;

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
    static bool IsOpen = true;
    if (ImGui::Begin("AppMainView", &IsOpen, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration))
    {
        CreateBody();
    }
    ImGui::End();

    if (!IsOpen)
    {
        if (auto* const ParentWindow = dynamic_cast<AppWindow*>(GetParent()))
        {
            ParentWindow->RequestClose();
        }
    }
}

void AppMainView::PrepareIcons()
{
    strzilla::string const Key = "Placeholder";
    strzilla::string const Path = "Resources/Icons/Placeholder.png";

    if (luGUI::ImageManager::Get().RegisterTexture(Key, Path))
    {
        m_PlaceholderIcon.SetKey(Key);
    }
}

void AppMainView::PrepareFonts()
{
    strzilla::string const Key = "Placeholder";
    strzilla::string const Path = "Resources/Fonts/BebasNeue-Regular.ttf";

    if (luGUI::FontManager::Get().RegisterFont(Key, Path))
    {
        luGUI::FontManager::Get().BuildFonts();
        m_PlaceholderText.SetKey(Key);
        m_PlaceholderText.SetText(Key);
    }
}

void AppMainView::CreateBody() const
{
    float const WindowWidth = ImGui::GetWindowSize().x;
    float const WindowHeight = ImGui::GetWindowSize().y;

    luGUI::ImageDefinitions const& Definitions = m_PlaceholderIcon.GetDefinitions();
    strzilla::string_view const Text = m_PlaceholderText.GetText();

    float const ContentWidth = ImGui::CalcTextSize(std::data(Text)).x + Definitions.Size.x;
    float const ContentHeight = ImGui::CalcTextSize(std::data(Text)).y + Definitions.Size.y;

    ImGui::SetCursorPosX((WindowWidth - ContentWidth) * 0.5f);
    ImGui::SetCursorPosY((WindowHeight - ContentHeight) * 0.5f);

    m_PlaceholderIcon.Draw();
    ImGui::SameLine();
    m_PlaceholderText.Draw();
}
