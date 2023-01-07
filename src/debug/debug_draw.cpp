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

#include <bgfx/bgfx.h>
#include <glm/gtx/vector_angle.hpp>

#include "debug/debug_draw.hpp"
#include "debug/logger.hpp"
#include "debug/debug_shape.hpp"
#include "math.hpp"
#include "renderer/renderer.hpp"
#include "renderer/shader.hpp"

namespace core
{
	DebugDraw::DebugDraw()
		: u_color()
	{
	#ifdef _DEBUG
		// Vertex Layout
		layout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8)
			.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
			.end();

		// Shape (Cube)
		static ref<Cube> cubePrim = makeRef<Cube>();
		const bgfx::VertexBufferHandle cubeVbh = bgfx::createVertexBuffer(
			bgfx::makeRef(cubePrim->getVertices().data(),
				static_cast<uint32_t>(cubePrim->getVertices().size() *
					sizeof(PrimitiveVertex))), layout);
		const bgfx::IndexBufferHandle cubeIbh = bgfx::createIndexBuffer(
			bgfx::makeRef(cubePrim->getIndices().data(),
				static_cast<uint32_t>(cubePrim->getIndices().size() *
					sizeof(uint16_t))));
		vaoCube = VertexArray::create(cubeVbh, cubeIbh);

		// Shape (Sphere)
		static ref<Sphere> spherePrim = makeRef<Sphere>();
		const bgfx::VertexBufferHandle sphereVbh = bgfx::createVertexBuffer(
			bgfx::makeRef(spherePrim->getVertices().data(),
				static_cast<uint32_t>(spherePrim->getVertices().size() *
					sizeof(PrimitiveVertex))), layout);
		const bgfx::IndexBufferHandle sphereIbh = bgfx::createIndexBuffer(
			bgfx::makeRef(spherePrim->getIndices().data(),
				static_cast<uint32_t>(spherePrim->getIndices().size() *
					sizeof(uint16_t))));
		vaoSphere = VertexArray::create(sphereVbh, sphereIbh);

		// Shape (Pyramid)
		static ref<Pyramid> pyramidPrim = makeRef<Pyramid>();
		const bgfx::VertexBufferHandle pyramidVbh = bgfx::createVertexBuffer(
			bgfx::makeRef(pyramidPrim->getVertices().data(),
				static_cast<uint32_t>(pyramidPrim->getVertices().size() *
					sizeof(PrimitiveVertex))), layout);
		const bgfx::IndexBufferHandle pyramidIbh = bgfx::createIndexBuffer(
			bgfx::makeRef(pyramidPrim->getIndices().data(),
				static_cast<uint32_t>(pyramidPrim->getIndices().size() *
					sizeof(uint16_t))));
		vaoPyramid = VertexArray::create(pyramidVbh, pyramidIbh);

		// Shape (Quad)
		static ref<Quad> quadPrim = makeRef<Quad>();
		const bgfx::VertexBufferHandle quadVbh = bgfx::createVertexBuffer(
			bgfx::makeRef(quadPrim->getVertices().data(),
				static_cast<uint32_t>(quadPrim->getVertices().size() *
					sizeof(PrimitiveVertex))), layout);
		const bgfx::IndexBufferHandle quadIbh = bgfx::createIndexBuffer(
			bgfx::makeRef(quadPrim->getIndices().data(),
				static_cast<uint32_t>(quadPrim->getIndices().size() *
					sizeof(uint16_t))));
		vaoQuad = VertexArray::create(quadVbh, quadIbh);

		// Shape (Line)
		static ref<Line> linePrim = makeRef<Line>();
		const bgfx::VertexBufferHandle lineVbh = bgfx::createVertexBuffer(
			bgfx::makeRef(linePrim->getVertices().data(),
				static_cast<uint32_t>(linePrim->getVertices().size() *
					sizeof(PrimitiveVertex))), layout);
		const bgfx::IndexBufferHandle lineIbh = bgfx::createIndexBuffer(
			bgfx::makeRef(linePrim->getIndices().data(),
				static_cast<uint32_t>(linePrim->getIndices().size() *
					sizeof(uint16_t))));
		vaoLine = VertexArray::create(lineVbh, lineIbh);
		
		// Shape (Grid)
		static ref<Grid> gridPrim = makeRef<Grid>();
		const bgfx::VertexBufferHandle gridVbh = bgfx::createVertexBuffer(
			bgfx::makeRef(gridPrim->getVertices().data(),
				static_cast<uint32_t>(gridPrim->getVertices().size() *
					sizeof(PrimitiveVertex))), layout);
		const bgfx::IndexBufferHandle gridIbh = bgfx::createIndexBuffer(
			bgfx::makeRef(gridPrim->getIndices().data(),
				static_cast<uint32_t>(gridPrim->getIndices().size() *
					sizeof(uint16_t))));
		vaoGrid = VertexArray::create(gridVbh, gridIbh);
		
		// Shape (Circle)
		static ref<Circle> circlePrim = makeRef<Circle>();
		const bgfx::VertexBufferHandle circleVbh = bgfx::createVertexBuffer(
			bgfx::makeRef(circlePrim->getVertices().data(),
				static_cast<uint32_t>(circlePrim->getVertices().size() *
					sizeof(PrimitiveVertex))), layout);
		const bgfx::IndexBufferHandle circleIbh = bgfx::createIndexBuffer(
			bgfx::makeRef(circlePrim->getIndices().data(),
				static_cast<uint32_t>(circlePrim->getIndices().size() *
					sizeof(uint16_t))));
		vaoCircle = VertexArray::create(circleVbh, circleIbh);

		// Shader
		shader = Renderer::getShaderManager()->get("debugdraw");

		// Uniforms
		u_color = bgfx::createUniform("u_color", bgfx::UniformType::Vec4);


		Logger::logInfo("Debug Draw allocated debug shapes");
	#endif
	}

	void DebugDraw::drawDebugShape(const ref<VertexArray>& vao, glm::vec4 color,
		const Transform& transform) const
	{
	#ifdef _DEBUG
		assert(vao, "Vertex Array Buffer is null");
		
		// Uniforms
		bgfx::setUniform(u_color, &color[0]);

		// State
		bgfx::setState(BGFX_STATE_DEFAULT | BGFX_STATE_PT_LINESTRIP);

		// Submit
		Renderer::submitVertexArrayTransform(vao, shader, transform);
	#endif
	}
	
	void DebugDraw::drawDebugPyramid(const glm::vec4& color,
			const glm::vec3& start, const glm::vec3& end,
			const glm::vec3& scale /*= glm::vec3(1.0f)*/)
	{
		// Handle direction to euler rotation
		const glm::quat offset = math::toQuat(90.0f, 90.0f, 0.0f);
		const glm::quat rotation = math::findLookAtRotation(start, end) *
			offset;

		// Scale matrix from the distance between the two points 
		const glm::vec3 finalScale = scale * glm::vec3(
			glm::length(end - start));

		getInstance().drawDebugShape(getInstance().vaoPyramid, color,
			Transform(start, rotation, finalScale));
	}
	void DebugDraw::drawDebugCube(const glm::vec4& color,
			const glm::vec3& position,
			const glm::quat& rotation /*= glm::vec3(0.0f )*/,
			const glm::vec3& scale/* = glm::vec3(1.0f) */)
	{
		getInstance().drawDebugShape(getInstance().vaoCube, color,
			Transform(position, rotation, scale));
	}
	void DebugDraw::drawDebugSphere(const glm::vec4& color,
		const glm::vec3& position, const float& radius )
	{
		getInstance().drawDebugShape(getInstance().vaoSphere, color,
			Transform(position, glm::vec3(0.0f),
				glm::vec3(radius)));
	}
	void DebugDraw::drawDebugQuad(const glm::vec4& color,
		const glm::vec3& position, const glm::quat& rotation,
		const glm::vec2& scale )
	{
		getInstance().drawDebugShape(getInstance().vaoQuad, color,
			Transform(position, rotation, glm::vec3(scale, 1.0f)));
	}
	void DebugDraw::drawDebugGrid(const glm::vec4&color,
		const glm::vec3& position, const uint32_t& gridCount)
	{
		for (uint32_t x = 0; x < gridCount; x++)
		{
			for (uint32_t y = 0; y < gridCount; y++)
			{
				getInstance().drawDebugShape(getInstance().vaoGrid, color,
					Transform(position + glm::vec3(x * 2, 0.0f, y * 2),
						math::toQuat(90.0f, 0.0f, 0.0f),
						glm::vec3(1.0f)));
			}
		}
	}
	void DebugDraw::drawDebugLine(const glm::vec4& color, const glm::vec3& start,
		const glm::vec3& end)
	{
		// Handle direction to euler rotation
	    const glm::quat rotation = math::findLookAtRotation(start, end);

		// Scale matrix from the distance between the two points 
		const glm::vec3 scale = glm::vec3(glm::length(end - start));

		getInstance().drawDebugShape(getInstance().vaoLine, color,
			Transform(start, rotation, scale));
	}
	void DebugDraw::drawDebugArrow(const glm::vec4& color,
		const glm::vec3& position, const glm::vec3& direction,
		const float& length)
	{
		const glm::vec3 lineEnd = position + (direction * length);

		drawDebugLine(color, position, lineEnd);
		drawDebugPyramid(color, lineEnd, lineEnd + (direction),
			glm::vec3(0.05f, 0.05f, 0.05f));
	}
	void DebugDraw::drawDebugWorldCoord(const glm::vec3& position,
		const float& scale )
	{
		drawDebugLine(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), position,
			position + glm::vec3(scale, 0.0f, 0.0f));
		drawDebugLine(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), position,
			position + glm::vec3(0.0f, scale, 0.0f));
		drawDebugLine(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), position,
			position + glm::vec3(0.0f, 0.0f, scale));
	}
	void DebugDraw::drawDebugCircle(const glm::vec4& color,
		const glm::vec3& position, const glm::quat& rotation,
		const glm::vec2& scale)
	{
		getInstance().drawDebugShape(getInstance().vaoCircle, color,
			Transform(position, rotation, glm::vec3(scale, 0.0f)));
	}
	void DebugDraw::drawDebugText(const uint16_t& x, const uint16_t& y,
		const char* text, ...)
	{
	// @todo glm::vec4 to vga ansi code rgb const char format

	#ifdef _DEBUG
		va_list argList;
		va_start(argList, text);
		bgfx::dbgTextPrintfVargs(x, y, 0x0f, (std::string() +
			std::string(text)).c_str(), argList);
		va_end(argList);
	#endif
	}
}
