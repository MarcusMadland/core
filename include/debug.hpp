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

namespace core
{
	namespace capture
	{
		/*!
		 * Captures a screenshot of the screen
		 *
		 * @return A .png image located under debug/screenshots/
		 */
		void screenshot();

		/*!
		 * Begins screen capture of screen
		 * 
		 * @remark CaptureEnd() needs to be called to stop 
		 * capturing screen.
		 */
		void captureBegin();

		/*!
		 * Stops capturing screen 
		 * 
		 * @remark CaptureBegin() needs to be called before this
		 *
		 * @return A .avi video file located under debug/captures/
		 */
		void captureEnd();
	}
}