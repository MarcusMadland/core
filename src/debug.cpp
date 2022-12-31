

#include "crpch.hpp"

#include <filesystem>
#include <bgfx/bgfx.h>

#include "debug.hpp"
#include "app/app.hpp"

namespace Core
{
	namespace Capture
	{
		void Screenshot()
		{
			std::string screenshotPath = "../debug/screenshots/";

			auto dirIter = std::filesystem::directory_iterator(screenshotPath);
			int fileCount = 0;
			for (auto& entry : dirIter)
			{
				if (entry.is_regular_file())
				{
					fileCount++;
				}
			}
			std::string screenshotTitle = std::string("screenshot_") + std::string(std::to_string(fileCount));

			bgfx::requestScreenShot(BGFX_INVALID_HANDLE, (std::string(screenshotPath) + screenshotTitle).c_str());

			Logger::LogWarn("Screenshot saved to %s", (std::string(screenshotPath) + screenshotTitle + ".tga").c_str());
		}

		void CaptureBegin()
		{
			bgfx::reset(App::Instance().GetWindow().GetWidth(), App::Instance().GetWindow().GetHeight(), App::Instance().GetWindow().GetResetFlags() | BGFX_RESET_CAPTURE);
		}

		void CaptureEnd()
		{
			bgfx::reset(App::Instance().GetWindow().GetWidth(), App::Instance().GetWindow().GetHeight(), App::Instance().GetWindow().GetResetFlags());
		}
	}
}