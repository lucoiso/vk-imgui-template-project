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
    public:
        explicit AppMainView(Control *);

    protected:
        void OnInitialize() override;
        void Paint() override;

    private:
        static void PrepareIcons();
        static void PrepareFonts();
        static void CreateBody();
    };
} // namespace UserInterface
