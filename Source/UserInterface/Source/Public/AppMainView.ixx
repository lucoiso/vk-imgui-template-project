// Author: Lucas Vilas-Boas
// Year : 2024
// Repo : https://github.com/lucoiso/vk-imgui-template-project

module;

#include "UserInterfaceModule.hpp"

export module UserInterface.AppMainView;

import UserInterface.Window;
import luGUI.UserInterface.Control;

namespace UserInterface
{
    export class USERINTERFACEMODULE_API AppMainView : public luGUI::Control
    {
    public:
        explicit AppMainView(Control *);

    protected:
        void Paint() override;

    private:
        static void CreateBody();
    };
} // namespace UserInterface