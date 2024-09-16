// Author: Lucas Vilas-Boas
// Year : 2024
// Repo : https://github.com/lucoiso/vk-imgui-template-project

module;

#include "UserInterfaceModule.hpp"
#include <memory>

export module UserInterface.Win32ParentingHelper;

import luGUI.UserInterface.Items.Item;
import luGUI.UserInterface.Panels.Stack;

import UserInterface.Window;

namespace UserInterface
{
    export USERINTERFACEMODULE_API std::shared_ptr<luGUI::Stack> CreateWin32ParentingStack(AppWindow const*, float, luGUI::Alignment);
} // namespace UserInterface
