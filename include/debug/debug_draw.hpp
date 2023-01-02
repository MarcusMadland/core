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
 * Class responsible for drawing debug shapes
 */
#pragma once

#include <glm/glm.hpp>

#include "common.hpp"
#include "renderer/buffers.hpp"
#include "renderer/shader.hpp"
#include "math/transform.hpp"

 /*
  * Forward Declarations
  */
struct bgfx::VertexLayout;
struct bgfx::UniformHandle;

namespace core
{
	class DebugDraw final
	{
	public:
		DebugDraw();

		/*
		 * Gets an instance of this class. 
		 *
		 * @remark Does not get initialized until the first time this is called
		 * 
		 * @return Reference to this class.
		 */
		static DebugDraw& getInstance()
		{
			static DebugDraw instance;
			return instance;
		}

		/*
		 * Draws a debug pyramid from start position to end position with
		 * given color and scale
		 *
		 * @param[in] color Color of pyramid in RGBA format
		 * @param[in] start Start position of pyramid (center of bottom quad) in
		 * world space
		 * @param[in] start End position of pyramid (top where triangles meet)
		 * in world space
		 * @param[in] scale Scale in all three directions
		 */
		static void drawDebugPyramid(const glm::vec4& color,
			const glm::vec3& start, const glm::vec3& end,
			const glm::vec3& scale = glm::vec3(1.0f));

		/*
		 * Draws a debug cube with given color and transform
		 *
		 * @param[in] color Color of cube in RGBA format
		 * @param[in] position Position of cube (center of bottom quad) in
		 * world space
		 * @param[in] rotation Rotation of cube in quaternion
		 * @param[in] scale Scale in all three directions
		 */
		static void drawDebugCube(const glm::vec4& color,
			const glm::vec3& position,
			const glm::quat& rotation = glm::vec3(0.0f),
			const glm::vec3& scale = glm::vec3(1.0f));

		/*
		 * Draws a debug sphere with given color and transform
		 *
		 * @param[in] color Color of sphere in RGBA format
		 * @param[in] position Position of sphere (center of sphere) in world
		 * space
		 * @param[in] radius Scale in all radius
		 */
		static void drawDebugSphere(glm::vec4 color, glm::vec3 position,
			float radius = 1.0f);

		/*
		 * Draws a debug quad with given color and transform
		 *
		 * @param[in] color Color of quad in RGBA format
		 * @param[in] position Position of quad (center of quad) in world space
		 * @param[in] rotation Rotation of quad in quaternion
		 * @param[in] scale Scale in two directions (width, height), depth is
		 * irrelevant
		 */
		static void drawDebugQuad(glm::vec4 color, glm::vec3 position,
			glm::quat rotation = glm::vec3(0.0f),
			glm::vec2 scale = glm::vec2(1.0f));

		/*
		 * Draws a debug grid with given color and position
		 *
		 * @remark Uses one draw call each quad, do not overuse. This is meant
		 * to be used for debug purposes only
		 *
		 * @param[in] color Color of grid in RGBA format
		 * @param[in] position Position of grid (center of first quad) in world
		 * space
		 * @param[in] gridCount The amount of grids to be drawn
		 */
		static void drawDebugGrid(glm::vec4 color, glm::vec3 position,
			uint32_t gridCount = 1);

		/*
		 * Draws a debug line from start to end
		 *
		 * @param[in] color Color of line in RGBA format
		 * @param[in] start Start position of the line in world space
		 * @param[in] end End position of the line in world space
		 */
		static void drawDebugLine(glm::vec4 color, glm::vec3 start,
			glm::vec3 end);

		/*
		 * Draws a debug arrow in a given direction
		 *
		 * @param[in] color Color of line in RGBA format
		 * @param[in] position Start position of the arrow (root) in world space
		 * @param[in] direction The direction the arrow should point. Should be
		 * normalized
		 * @param[in] length The length of the arrow in the given direction
		 */
		static void drawDebugArrow(glm::vec4 color, glm::vec3 position,
			glm::vec3 direction, float length = 1.0f);

		/*
		 * Draws debug world coordinates
		 *
		 * @remark Red is X, Green is Y, Blue is Z
		 * 
		 * @param[in] position Position of the coordinates
		 * @param[in] scale The length of all three lines
		 */
		static void drawDebugWorldCoord(glm::vec3 position, float scale = 1.0f);

		/*
		 * Draws a debug circle with given color and transform
		 *
		 * @param[in] color Color of circle in RGBA format
		 * @param[in] position Position of circle (center of circle) in world
		 * space
		 * @param[in] rotation Rotation of circle in quaternion
		 * @param[in] scale Scale in two directions (width, height), depth is
		 * irrelevant
		 */
		static void drawDebugCircle(glm::vec4 color, glm::vec3 position,
			glm::quat rotation = glm::vec3(0.0f),
			glm::vec2 scale = glm::vec2(1.0f));

		/*
		 * Draws a debug circle with given color and transform
		 *
		 * @todo Yet to be implemented
		 */
		static void drawDebugText(uint16_t x, uint16_t y, const char* text, ...);

	private:
		void drawDebugShape(const ref<VertexArray>& vao, glm::vec4 color, 
			Transform transform);
		
	private:
		ref<Shader> shader;

		bgfx::VertexLayout layout;
		bgfx::UniformHandle u_color;

		ref<VertexArray> vaoCube;
		ref<VertexArray> vaoSphere;
		ref<VertexArray> vaoPyramid;
		ref<VertexArray> vaoQuad;
		ref<VertexArray> vaoLine;
		ref<VertexArray> vaoGrid;
		ref<VertexArray> vaoCircle;
	};
}