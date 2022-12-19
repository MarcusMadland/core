#include "crpch.hpp"

#include <bgfx/bgfx.h>
#include <glm/gtx/vector_angle.hpp>

#include "debug/debug_draw.hpp"
#include "debug/logger.hpp"
#include "utils.hpp"
#include "math.hpp"
#include "graphics/vertex_array.hpp"
#include "graphics/renderer.hpp"

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
		bgfx::VertexBufferHandle cubeVbh = bgfx::createVertexBuffer(bgfx::makeRef(cubePrim->GetVertices().data(), cubePrim->GetVertices().size() * sizeof(PrimitiveVertex)), layout);
		bgfx::IndexBufferHandle cubeIbh = bgfx::createIndexBuffer(bgfx::makeRef(cubePrim->GetIndices().data(), cubePrim->GetIndices().size() * sizeof(uint16_t)));
		vaoCube = VertexArray::Create(cubeVbh, cubeIbh);

		// Shape (Sphere)
		static Core::Ref<Core::Sphere> spherePrim = Core::MakeRef<Core::Sphere>();
		bgfx::VertexBufferHandle sphereVbh = bgfx::createVertexBuffer(bgfx::makeRef(spherePrim->GetVertices().data(), spherePrim->GetVertices().size() * sizeof(PrimitiveVertex)), layout);
		bgfx::IndexBufferHandle sphereIbh = bgfx::createIndexBuffer(bgfx::makeRef(spherePrim->GetIndices().data(), spherePrim->GetIndices().size() * sizeof(uint16_t)));
		vaoSphere = VertexArray::Create(sphereVbh, sphereIbh);

		// Shape (Pyramid)
		static Core::Ref<Core::Pyramid> pyramidPrim = Core::MakeRef<Core::Pyramid>();
		bgfx::VertexBufferHandle pyramidVbh = bgfx::createVertexBuffer(bgfx::makeRef(pyramidPrim->GetVertices().data(), pyramidPrim->GetVertices().size() * sizeof(PrimitiveVertex)), layout);
		bgfx::IndexBufferHandle pyramidIbh = bgfx::createIndexBuffer(bgfx::makeRef(pyramidPrim->GetIndices().data(), pyramidPrim->GetIndices().size() * sizeof(uint16_t)));
		vaoPyramid = VertexArray::Create(pyramidVbh, pyramidIbh);

		// Shape (Quad)
		static Core::Ref<Core::Quad> quadPrim = Core::MakeRef<Core::Quad>();
		bgfx::VertexBufferHandle quadVbh = bgfx::createVertexBuffer(bgfx::makeRef(quadPrim->GetVertices().data(), quadPrim->GetVertices().size() * sizeof(PrimitiveVertex)), layout);
		bgfx::IndexBufferHandle quadIbh = bgfx::createIndexBuffer(bgfx::makeRef(quadPrim->GetIndices().data(), quadPrim->GetIndices().size() * sizeof(uint16_t)));
		vaoQuad = VertexArray::Create(quadVbh, quadIbh);

		// Shape (Line)
		static Core::Ref<Core::Line> linePrim = Core::MakeRef<Core::Line>();
		bgfx::VertexBufferHandle lineVbh = bgfx::createVertexBuffer(bgfx::makeRef(linePrim->GetVertices().data(), linePrim->GetVertices().size() * sizeof(PrimitiveVertex)), layout);
		bgfx::IndexBufferHandle lineIbh = bgfx::createIndexBuffer(bgfx::makeRef(linePrim->GetIndices().data(), linePrim->GetIndices().size() * sizeof(uint16_t)));
		vaoLine = VertexArray::Create(lineVbh, lineIbh);
		
		// Shape (Grid)
		static Core::Ref<Core::Grid> gridPrim = Core::MakeRef<Core::Grid>();
		bgfx::VertexBufferHandle gridVbh = bgfx::createVertexBuffer(bgfx::makeRef(gridPrim->GetVertices().data(), gridPrim->GetVertices().size() * sizeof(PrimitiveVertex)), layout);
		bgfx::IndexBufferHandle gridIbh = bgfx::createIndexBuffer(bgfx::makeRef(gridPrim->GetIndices().data(), gridPrim->GetIndices().size() * sizeof(uint16_t)));
		vaoGrid = VertexArray::Create(gridVbh, gridIbh);
		
		// Shape (Circle)
		static Core::Ref<Core::Circle> circlePrim = Core::MakeRef<Core::Circle>();
		bgfx::VertexBufferHandle circleVbh = bgfx::createVertexBuffer(bgfx::makeRef(circlePrim->GetVertices().data(), circlePrim->GetVertices().size() * sizeof(PrimitiveVertex)), layout);
		bgfx::IndexBufferHandle circleIbh = bgfx::createIndexBuffer(bgfx::makeRef(circlePrim->GetIndices().data(), circlePrim->GetIndices().size() * sizeof(uint16_t)));
		vaoCircle = VertexArray::Create(circleVbh, circleIbh);

		// Shader
		shader = Renderer::GetShaderLibrary()->Get("debugdraw");

		// Uniforms
		u_color = bgfx::createUniform("u_color", bgfx::UniformType::Vec4);


		Logger::LogInfo("Debug Draw allocated debug shapes");
	#endif
	}

	void DebugDraw::DrawDebugShape(const Ref<VertexArray>& vao, glm::vec4 color)
	{
	#ifdef _DEBUG
		// Uniforms
		bgfx::setUniform(u_color, &color[0]);

		// Submit
		bgfx::setVertexBuffer(0, vao->vbh);
		bgfx::setIndexBuffer(vao->ibh);

		// State
		bgfx::setState(BGFX_STATE_DEFAULT | BGFX_STATE_PT_LINESTRIP);

		// Submit
		bgfx::submit(0, shader->handle); // @todo Should camera be hard coded to 0? Draw debug only supports 1 viewport.
	#endif
	}
	void DebugDraw::DrawDebugShapeTransform(const Ref<VertexArray>& vao, glm::vec4 color, Transform transform)
	{
	#ifdef _DEBUG
		// Transform
		glm::mat4 matrix = Core::Math::ComposeMatrix(transform);
		bgfx::setTransform(&matrix[0][0]);

		// Draw with color
		DrawDebugShape(vao, color);
	#endif
	}
	void DebugDraw::DrawDebugShapeMatrix(const Ref<VertexArray>& vao, glm::vec4 color, glm::mat4 matrix)
	{
	#ifdef _DEBUG
		// Transform
		bgfx::setTransform(&matrix[0][0]);

		// Draw with color
		DrawDebugShape(vao, color);
	#endif
	}
	
	void DebugDraw::DrawDebugPyramid(glm::vec4 color, glm::vec3 start, glm::vec3 end, glm::vec3 scale /* = glm::vec3(1.0f) */)
	{
		// Handle direction to euler orientation
		glm::vec3 direction = glm::normalize(end - start);
		glm::vec3 orientation = Math::OrientationFromVectorXZ(direction);

		// Scale matrix from the distance between the two points 
		glm::vec3 finalScale = scale * glm::vec3(glm::length(end - start));

		GetInstance().DrawDebugShapeTransform(GetInstance().vaoPyramid, color, Transform(start, orientation, finalScale));
	}
	void DebugDraw::DrawDebugCube(glm::vec4 color, glm::vec3 position, glm::vec3 orientation /* = glm::vec3(0.0f) */, glm::vec3 scale /* = glm::vec3(1.0f)*/)
	{
		GetInstance().DrawDebugShapeTransform(GetInstance().vaoCube, color, Transform(position, orientation, scale));
	}
	void DebugDraw::DrawDebugSphere(glm::vec4 color, glm::vec3 position, float radius /* = 1.0f */)
	{
		GetInstance().DrawDebugShapeTransform(GetInstance().vaoSphere, color, Transform(position, glm::vec3(0.0f), glm::vec3(radius)));
	}
	void DebugDraw::DrawDebugQuad(glm::vec4 color, glm::vec3 position, glm::vec3 orientation  /* = glm::vec3(0.0f) */, glm::vec2 scale /* = glm::vec2(1.0f) */)
	{
		GetInstance().DrawDebugShapeTransform(GetInstance().vaoQuad, color, Transform(position, glm::vec3(orientation), glm::vec3(scale, 1.0f)));
	}
	void DebugDraw::DrawDebugGrid(glm::vec4 color, glm::vec3 position, uint32_t gridCount /* = 1 */)
	{
		for (uint32_t x = 0; x < gridCount; x++)
		{
			for (uint32_t y = 0; y < gridCount; y++)
			{
				GetInstance().DrawDebugShapeTransform(GetInstance().vaoGrid, color, 
					Transform(position + glm::vec3(x * 2, 0.0f, y * 2), glm::vec3(90.0f, 0.0f, 0.0f),
						glm::vec3(1.0f)));
			}
		}
	}
	void DebugDraw::DrawDebugLine(glm::vec4 color, glm::vec3 start, glm::vec3 end)
	{
		// Handle direction to euler orientation
		glm::vec3 direction = glm::normalize(end - start);
	    glm::vec3 orientation = Math::OrientationFromVectorXZ(direction);

		// Scale matrix from the distance between the two points 
		glm::vec3 scale = glm::vec3(glm::length(end - start));

		GetInstance().DrawDebugShapeTransform(GetInstance().vaoLine, color, Transform(start, orientation, scale));
	}
	void DebugDraw::DrawDebugArrow(glm::vec4 color, glm::vec3 position, glm::vec3 direction, float length /* = 1.0f */)
	{
		glm::vec3 lineEnd = position + (direction * length);

		DrawDebugLine(color, position, lineEnd);
		DrawDebugPyramid(color, lineEnd, lineEnd + (direction), glm::vec3(0.05f, 0.05f, 0.05f));
	}
	void DebugDraw::DrawDebugWorldCoord(glm::vec3 position)
	{
		DrawDebugLine(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), position, position + glm::vec3(1.0f, 0.0f, 0.0f));
		DrawDebugLine(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), position, position + glm::vec3(0.0f, 1.0f, 0.0f));
		DrawDebugLine(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), position, position + glm::vec3(0.0f, 0.0f, 1.0f));
	}
	void DebugDraw::DrawDebugCircle(glm::vec4 color, glm::vec3 position, glm::vec3 orientation, glm::vec2 scale)
	{
		GetInstance().DrawDebugShapeTransform(GetInstance().vaoCircle, color, Transform(position, orientation, glm::vec3(scale, 0.0f)));
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
