

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

		
		static void DrawDebugPyramid(glm::vec4 color, glm::vec3 start,
			glm::vec3 end, glm::vec3 scale = glm::vec3(1.0f));

		
		static void DrawDebugCube(glm::vec4 color, glm::vec3 position,
			glm::quat rotation = glm::vec3(0.0f),
			glm::vec3 scale = glm::vec3(1.0f));

		
		static void DrawDebugSphere(glm::vec4 color, glm::vec3 position,
			float radius = 1.0f);

		
		static void DrawDebugQuad(glm::vec4 color, glm::vec3 position,
			glm::quat rotation = glm::vec3(0.0f),
			glm::vec2 scale = glm::vec2(1.0f));

		
		static void DrawDebugGrid(glm::vec4 color, glm::vec3 position,
			uint32_t gridCount = 1);

		
		static void DrawDebugLine(glm::vec4 color, glm::vec3 start,
			glm::vec3 end);

		
		static void DrawDebugArrow(glm::vec4 color, glm::vec3 position,
			glm::vec3 direction, float length = 1.0f);

		
		static void DrawDebugWorldCoord(glm::vec3 position, float scale = 1.0f);

		
		static void DrawDebugCircle(glm::vec4 color, glm::vec3 position,
			glm::quat rotation = glm::vec3(0.0f),
			glm::vec2 scale = glm::vec2(1.0f));

		
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