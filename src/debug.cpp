

#include "crpch.hpp"

#include <filesystem>
#include <bgfx/bgfx.h>

#include "debug.hpp"
#include "app/app.hpp"

namespace core
{
	namespace capture
	{
		void screenshot()
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

			Logger::logWarn("Screenshot saved to %s", (std::string(screenshotPath) + screenshotTitle + ".tga").c_str());
		}

		void captureBegin()
		{
			bgfx::reset(App::getInstance().getWindow().getWidth(), App::getInstance().getWindow().getWidth(), App::getInstance().getWindow().getResetFlags() | BGFX_RESET_CAPTURE);
		}

		void captureEnd()
		{
			bgfx::reset(App::getInstance().getWindow().getWidth(), App::getInstance().getWindow().getWidth(), App::getInstance().getWindow().getResetFlags());
		}
	}
}