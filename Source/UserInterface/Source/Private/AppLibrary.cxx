// Author: Lucas Vilas-Boas
// Year : 2024
// Repo : https://github.com/lucoiso/vk-imgui-template-project

module;

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/keywords/format.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>

#if defined(_WIN32) && !defined(_DEBUG)
    #include <Windows.h>
#endif

module UserInterface.Library;

import UserInterface.Window;

import RenderCore.UserInterface.Window;
import RenderCore.UserInterface.Window.Flags;
import RenderCore.Utils.EnumHelpers;

using namespace UserInterface;

void SetupBoostLog()
{
    auto const FormatTimeStamp = boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f");
    auto const FormatThreadId  = boost::log::expressions::attr<boost::log::attributes::current_thread_id::value_type>("ThreadID");
    auto const FormatSeverity  = boost::log::expressions::attr<boost::log::trivial::severity_level>("Severity");

    boost::log::formatter const LogFormatter
        = boost::log::expressions::format("[%1%] (%2%) [%3%] %4%") % FormatTimeStamp % FormatThreadId % FormatSeverity % boost::log::expressions::smessage;

    #ifndef _DEBUG
    boost::log::core::get()->set_filter(boost::log::trivial::severity != boost::log::trivial::debug);

    #ifdef _WIN32
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    #endif
    #else
    auto const ConsoleSink = boost::log::add_console_log(std::clog);
    ConsoleSink->set_formatter(LogFormatter);
    #endif

    auto const LogFileSink = boost::log::add_file_log("renderer-application.log");
    LogFileSink->set_formatter(LogFormatter);

    boost::log::add_common_attributes();
}

std::int32_t UserInterface::Execute()
{
    SetupBoostLog();

    std::int32_t Output { EXIT_FAILURE };

    RenderCore::Renderer::SetFPSLimit(60.F);
    RenderCore::Renderer::SetVSync(true);

    constexpr RenderCore::InitializationFlags Flags = RenderCore::InitializationFlags::ENABLE_IMGUI     |
                                                      RenderCore::InitializationFlags::ENABLE_DOCKING   |
                                                      RenderCore::InitializationFlags::WITHOUT_TITLEBAR |
                                                      RenderCore::InitializationFlags::ALWAYS_ON_TOP;

    constexpr auto WindowTitle = "lucoiso/vk-imgui-template-project";

    constexpr std::uint16_t WindowWidth = 500U;
    constexpr auto WindowHeight        = static_cast<std::uint16_t>(WindowWidth / 2.F);

    if (UserInterface::AppWindow Window;
        Window.Initialize(WindowWidth, WindowHeight, WindowTitle, Flags))
    {
        while (Window.IsOpen())
        {
            Window.PollEvents();
        }

        Window.Shutdown();
        Output = EXIT_SUCCESS;
    }

    return Output;
}
