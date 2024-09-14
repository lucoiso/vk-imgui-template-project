// Author: Lucas Vilas-Boas
// Year : 2024
// Repo : https://github.com/lucoiso/vk-imgui-template-project

module;

#include "UserInterfaceModule.hpp"

export module UserInterface.AppMainView;

import UserInterface.Window;
import luGUI.UserInterface.Controls.Control;
import luGUI.UserInterface.Items.Image;
import luGUI.UserInterface.Items.Text;

namespace UserInterface
{
    export class USERINTERFACEMODULE_API AppMainView : public luGUI::Control
    {
        luGUI::Image m_PlaceholderIcon {};
        luGUI::Text  m_PlaceholderText {};

    public:
        explicit AppMainView(Control *);

    protected:
        void OnInitialize() override;
        void Paint() override;

    private:
        void PrepareIcons();
        void PrepareFonts();

        void CreateBody() const;
    };
} // namespace UserInterface
