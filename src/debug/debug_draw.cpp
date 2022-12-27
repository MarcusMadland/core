#include "crpch.hpp"

#include <bgfx/bgfx.h>
#include <glm/gtx/vector_angle.hpp>

#include "debug/debug_draw.hpp"
#include "debug/logger.hpp"
#include "math.hpp"
#include "graphics/renderer.hpp"
#include "graphics/shader.hpp"
#include "primitive/primitive.hpp"

namespace Core
{
	DebugDraw::DebugDraw()
	{
	#ifdef _DEBUG
		// Vertex Layout
		layout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8)
			.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
			.end();

		// Shape (Cube)
		static Core::Ref<Core::Cube> cubePrim = Core::MakeRef<Core::Cube>();
		bgfx::VertexBufferHandle cubeVbh = bgfx::createVertexBuffer(bgfx::makeRef(cubePrim->GetVertices().data(), static_cast<uint32_t>(cubePrim->GetVertices().size() * sizeof(PrimitiveVertex))), layout);
		bgfx::IndexBufferHandle cubeIbh = bgfx::createIndexBuffer(bgfx::makeRef(cubePrim->GetIndices().data(), static_cast<uint32_t>(cubePrim->GetIndices().size() * sizeof(uint16_t))));
		vaoCube = VertexArray::Create(cubeVbh, cubeIbh);

		// Shape (Sphere)
		static Core::Ref<Core::Sphere> spherePrim = Core::MakeRef<Core::Sphere>();
		bgfx::VertexBufferHandle sphereVbh = bgfx::createVertexBuffer(bgfx::makeRef(spherePrim->GetVertices().data(), static_cast<uint32_t>(spherePrim->GetVertices().size() * sizeof(PrimitiveVertex))), layout);
		bgfx::IndexBufferHandle sphereIbh = bgfx::createIndexBuffer(bgfx::makeRef(spherePrim->GetIndices().data(), static_cast<uint32_t>(spherePrim->GetIndices().size() * sizeof(uint16_t))));
		vaoSphere = VertexArray::Create(sphereVbh, sphereIbh);

		// Shape (Pyramid)
		static Core::Ref<Core::Pyramid> pyramidPrim = Core::MakeRef<Core::Pyramid>();
		bgfx::VertexBufferHandle pyramidVbh = bgfx::createVertexBuffer(bgfx::makeRef(pyramidPrim->GetVertices().data(), static_cast<uint32_t>(pyramidPrim->GetVertices().size() * sizeof(PrimitiveVertex))), layout);
		bgfx::IndexBufferHandle pyramidIbh = bgfx::createIndexBuffer(bgfx::makeRef(pyramidPrim->GetIndices().data(), static_cast<uint32_t>(pyramidPrim->GetIndices().size() * sizeof(uint16_t))));
		vaoPyramid = VertexArray::Create(pyramidVbh, pyramidIbh);

		// Shape (Quad)
		static Core::Ref<Core::Quad> quadPrim = Core::MakeRef<Core::Quad>();
		bgfx::VertexBufferHandle quadVbh = bgfx::createVertexBuffer(bgfx::makeRef(quadPrim->GetVertices().data(), static_cast<uint32_t>(quadPrim->GetVertices().size() * sizeof(PrimitiveVertex))), layout);
		bgfx::IndexBufferHandle quadIbh = bgfx::createIndexBuffer(bgfx::makeRef(quadPrim->GetIndices().data(), static_cast<uint32_t>(quadPrim->GetIndices().size() * sizeof(uint16_t))));
		vaoQuad = VertexArray::Create(quadVbh, quadIbh);

		// Shape (Line)
		static Core::Ref<Core::Line> linePrim = Core::MakeRef<Core::Line>();
		bgfx::VertexBufferHandle lineVbh = bgfx::createVertexBuffer(bgfx::makeRef(linePrim->GetVertices().data(), static_cast<uint32_t>(linePrim->GetVertices().size() * sizeof(PrimitiveVertex))), layout);
		bgfx::IndexBufferHandle lineIbh = bgfx::createIndexBuffer(bgfx::makeRef(linePrim->GetIndices().data(), static_cast<uint32_t>(linePrim->GetIndices().size() * sizeof(uint16_t))));
		vaoLine = VertexArray::Create(lineVbh, lineIbh);
		
		// Shape (Grid)
		static Core::Ref<Core::Grid> gridPrim = Core::MakeRef<Core::Grid>();
		bgfx::VertexBufferHandle gridVbh = bgfx::createVertexBuffer(bgfx::makeRef(gridPrim->GetVertices().data(), static_cast<uint32_t>(gridPrim->GetVertices().size() * sizeof(PrimitiveVertex))), layout);
		bgfx::IndexBufferHandle gridIbh = bgfx::createIndexBuffer(bgfx::makeRef(gridPrim->GetIndices().data(), static_cast<uint32_t>(gridPrim->GetIndices().size() * sizeof(uint16_t))));
		vaoGrid = VertexArray::Create(gridVbh, gridIbh);
		
		// Shape (Circle)
		static Core::Ref<Core::Circle> circlePrim = Core::MakeRef<Core::Circle>();
		bgfx::VertexBufferHandle circleVbh = bgfx::createVertexBuffer(bgfx::makeRef(circlePrim->GetVertices().data(), static_cast<uint32_t>(circlePrim->GetVertices().size() * sizeof(PrimitiveVertex))), layout);
		bgfx::IndexBufferHandle circleIbh = bgfx::createIndexBuffer(bgfx::makeRef(circlePrim->GetIndices().data(), static_cast<uint32_t>(circlePrim->GetIndices().size() * sizeof(uint16_t))));
		vaoCircle = VertexArray::Create(circleVbh, circleIbh);

		// Shader
		shader = Renderer::GetShaderManager()->Get("debugdraw");

		// Uniforms
		u_color = bgfx::createUniform("u_color", bgfx::UniformType::Vec4);


		Logger::LogInfo("Debug Draw allocated debug shapes");
	#endif
	}

	void DebugDraw::DrawDebugShape(const Ref<VertexArray>& vao, glm::vec4 color, Transform transform)
	{
	#ifdef _DEBUG
		// Uniforms
		bgfx::setUniform(u_color, &color[0]);

		// State
		bgfx::setState(BGFX_STATE_DEFAULT | BGFX_STATE_PT_LINESTRIP);

		// Submit
		Renderer::SubmitVertexArrayTransform(vao, shader, transform);
	#endif
	}
	
	void DebugDraw::DrawDebugPyramid(glm::vec4 color, glm::vec3 start, glm::vec3 end, glm::vec3 scale /* = glm::vec3(1.0f) */)
	{
		// Handle direction to euler rotation
		const glm::quat offset = Core::Math::ToQuat(90.0f, 90.0f, 0.0f);
		glm::quat rotation = Math::FindLookAtRotation(start, end) * offset;

		// Scale matrix from the distance between the two points 
		glm::vec3 finalScale = scale * glm::vec3(glm::length(end - start));

		GetInstance().DrawDebugShape(GetInstance().vaoPyramid, color, Transform(start, rotation, finalScale));
	}
	void DebugDraw::DrawDebugCube(glm::vec4 color, glm::vec3 position, glm::quat rotation /* = glm::vec3(0.0f) */, glm::vec3 scale /* = glm::vec3(1.0f)*/)
	{
		GetInstance().DrawDebugShape(GetInstance().vaoCube, color, Transform(position, rotation, scale));
	}
	void DebugDraw::DrawDebugSphere(glm::vec4 color, glm::vec3 position, float radius /* = 1.0f */)
	{
		GetInstance().DrawDebugShape(GetInstance().vaoSphere, color, Transform(position, glm::vec3(0.0f), glm::vec3(radius)));
	}
	void DebugDraw::DrawDebugQuad(glm::vec4 color, glm::vec3 position, glm::quat rotation  /* = glm::vec3(0.0f) */, glm::vec2 scale /* = glm::vec2(1.0f) */)
	{
		GetInstance().DrawDebugShape(GetInstance().vaoQuad, color, Transform(position, rotation, glm::vec3(scale, 1.0f)));
	}
	void DebugDraw::DrawDebugGrid(glm::vec4 color, glm::vec3 position, uint32_t gridCount /* = 1 */)
	{
		for (uint32_t x = 0; x < gridCount; x++)
		{
			for (uint32_t y = 0; y < gridCount; y++)
			{
				GetInstance().DrawDebugShape(GetInstance().vaoGrid, color,
					Transform(position + glm::vec3(x * 2, 0.0f, y * 2), Math::ToQuat(90.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
			}
		}
	}
	void DebugDraw::DrawDebugLine(glm::vec4 color, glm::vec3 start, glm::vec3 end)
	{
		// Handle direction to euler rotation
	    glm::quat rotation = Math::FindLookAtRotation(start, end);

		// Scale matrix from the distance between the two points 
		glm::vec3 scale = glm::vec3(glm::length(end - start));

		GetInstance().DrawDebugShape(GetInstance().vaoLine, color, Transform(start, rotation, scale));
	}
	void DebugDraw::DrawDebugArrow(glm::vec4 color, glm::vec3 position, glm::vec3 direction, float length /* = 1.0f */)
	{
		glm::vec3 lineEnd = position + (direction * length);

		DrawDebugLine(color, position, lineEnd);
		DrawDebugPyramid(color, lineEnd, lineEnd + (direction), glm::vec3(0.05f, 0.05f, 0.05f));
	}
	void DebugDraw::DrawDebugWorldCoord(glm::vec3 position, float scale /* = 1.0f */)
	{
		DrawDebugLine(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), position, position + glm::vec3(scale, 0.0f, 0.0f));
		DrawDebugLine(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), position, position + glm::vec3(0.0f, scale, 0.0f));
		DrawDebugLine(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), position, position + glm::vec3(0.0f, 0.0f, scale));
	}
	void DebugDraw::DrawDebugCircle(glm::vec4 color, glm::vec3 position, glm::quat rotation, glm::vec2 scale)
	{
		GetInstance().DrawDebugShape(GetInstance().vaoCircle, color, Transform(position, rotation, glm::vec3(scale, 0.0f)));
	}
	void DebugDraw::DrawDebugText(uint16_t x, uint16_t y, const char* text, ...)
	{
	// @todo glm::vec4 to vga ansi code rgb const char format

	#ifdef _DEBUG
		va_list argList;
		va_start(argList, text);
		bgfx::dbgTextPrintfVargs(x, y, 0x0f, (std::string(/*Color ansi escape code*/) + std::string(text)).c_str(), argList);
		va_end(argList);
	#endif
	}
}
