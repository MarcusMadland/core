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

#pragma once

#include <glm/glm.hpp>

#include "common.hpp"
#include "graphics/vertex_array.hpp"
#include "graphics/shader.hpp"
#include "math/transform.hpp"

struct bgfx::VertexLayout;
struct bgfx::UniformHandle;

namespace Core
{
	class DebugDraw final
	{
	public:
		DebugDraw();

		static DebugDraw& GetInstance()
		{
			static DebugDraw instance;
			return instance;
		}

		/*
		 * Draws a debug pyramid shape
		 *
		 * @param color Color of the shape in RGBA
		 * @param start Shape start position in world space
		 * @param end Shape end position in world space
		 * @param scale The size / scale of the shape that gets multiplied to
		 * the generated shape from start to end
		 */
		static void DrawDebugPyramid(glm::vec4 color, glm::vec3 start,
			glm::vec3 end, glm::vec3 scale = glm::vec3(1.0f));

		/*
		 * Draws a debug cube shape
		 *
		 * @param color Color of the shape in RGBA
		 * @param position Position in world space
		 * @param rotation Rotation in euler
		 * @param scale The size / scale of the shape
		 */
		static void DrawDebugCube(glm::vec4 color, glm::vec3 position,
			glm::quat rotation = glm::vec3(0.0f),
			glm::vec3 scale = glm::vec3(1.0f));

		/*
		 * Draws a debug sphere shape
		 *
		 * @param color Color of the shape in RGBA
		 * @param position Position in world space
		 * @param radius The size / scale of the shape in radius
		 */
		static void DrawDebugSphere(glm::vec4 color, glm::vec3 position,
			float radius = 1.0f);

		/*
		 * Draws a debug quad shape
		 *
		 * @param color Color of the shape in RGBA
		 * @param position Position in world space
		 * @param rotation Rotation in euler
		 * @param radius The size / scale of the shape
		 */
		static void DrawDebugQuad(glm::vec4 color, glm::vec3 position,
			glm::quat rotation = glm::vec3(0.0f),
			glm::vec2 scale = glm::vec2(1.0f));

		/*
		 * Draws a debug grid shape
		 *
		 * @param color Color of the shape in RGBA
		 * @param position Position in world space
		 * @param gridCount The amount of grids, 1 = 2x2, 2 = 4x4 ..
		 */
		static void DrawDebugGrid(glm::vec4 color, glm::vec3 position,
			uint32_t gridCount = 1);

		/*
		 * Draws a debug line shape
		 *
		 * @param color Color of the shape in RGBA
		 * @param start Shape start position in world space
		 * @param end Shape end position in world space
		 */
		static void DrawDebugLine(glm::vec4 color, glm::vec3 start,
			glm::vec3 end);

		/*
		 * Draws a debug arrow shape
		 *
		 * @param color Color of the shape in RGBA
		 * @param position Position in world space
		 * @param direction Shape direction, should be normalized
		 * @param length The length of the shape
		 */
		static void DrawDebugArrow(glm::vec4 color, glm::vec3 position,
			glm::vec3 direction, float length = 1.0f);

		/*
		 * Draws a debug world coordinate shape
		 *
		 * @param color Color of the shape in RGBA
		 * @param position Position in world space
		 */
		static void DrawDebugWorldCoord(glm::vec3 position, float scale = 1.0f);

		/*
		 * Draws a debug circle shape
		 *
		 * @param color Color of the shape in RGBA
		 * @param position Position in world space
		 * @param rotation Rotation in euler
		 * @param scale The size / scale of the shape
		 */
		static void DrawDebugCircle(glm::vec4 color, glm::vec3 position,
			glm::quat rotation = glm::vec3(0.0f),
			glm::vec2 scale = glm::vec2(1.0f));

		/*
		 * Draws a debug cube shape
		 *
		 * @param x X position on screen
		 * @param y Y position on screen
		 * @param text Text that should be displayed, can be used with args
		 */
		static void DrawDebugText(uint16_t x, uint16_t y, const char* text, ...);

	private:
		void DrawDebugShape(const Ref<VertexArray>& vao, glm::vec4 color, 
			Transform transform);
		
	private:
		Ref<Shader> shader;

		bgfx::VertexLayout layout;
		bgfx::UniformHandle u_color;

		Ref<VertexArray> vaoCube;
		Ref<VertexArray> vaoSphere;
		Ref<VertexArray> vaoPyramid;
		Ref<VertexArray> vaoQuad;
		Ref<VertexArray> vaoLine;
		Ref<VertexArray> vaoGrid;
		Ref<VertexArray> vaoCircle;
	};
}