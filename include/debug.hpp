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

/*
 * Collection of commonly used debug utilities 
 */
#pragma once

#include "debug/logger.hpp"
#include "debug/debug_draw.hpp"

namespace Core
{
	namespace Capture
	{
		/*
		 * Captures a screenshot of the screen
		 *
		 * @return A .png image located under debug/screenshots/
		 */
		void Screenshot();

		/*
		 * Begins screen capture of screen. CaptureEnd() needs to be called to
		 * stop capturing screen.
		 */
		void CaptureBegin();

		/*
		 * Stops capturing screen. CaptureBegin() needs to be called to stop
		 * capturing screen.
		 *
		 * @return A .avi video file located under debug/captures/
		 */
		void CaptureEnd();
	}
}