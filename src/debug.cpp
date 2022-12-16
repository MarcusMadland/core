/*
 * Copyright 2022 Marcus Madland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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