// Author: Lucas Vilas-Boas
// Year : 2024
// Repo : https://github.com/lucoiso/vk-imgui-template-project

module;

export module UserInterface.AppMainView;

import UserInterface.Window;
import RenderCore.UserInterface.Control;

namespace UserInterface
{
    export class AppMainView final : public RenderCore::Control
    {
    public:
        explicit AppMainView(Control *);

    protected:
        void Paint() override;

    private:
        static void CreateBody();
    };
} // namespace UserInterface