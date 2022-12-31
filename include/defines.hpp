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
 * Collection of commonly used defines
 */
#pragma once

/*
 * Math
 */
#define CORE_PI 				(3.1415926535897932f)
#define CORE_VERY_SMALL_NUMBER	(1.e-8f)
#define CORE_SMALL_NUMBER		(1.e-4f)
#define CORE_BIG_NUMBER			(3.4e+38f)


/*
 * Color Presets
 */
#define CORE_COLOR_BLACK	 	glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
#define CORE_COLOR_WHITE	 	glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
#define CORE_COLOR_RED			glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
#define CORE_COLOR_GREEN	 	glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)
#define CORE_COLOR_BLUE			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
#define CORE_COLOR_YELLOW		glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)
#define CORE_COLOR_CYAN			glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)
#define CORE_COLOR_MAGENTA	    glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)