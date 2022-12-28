#pragma once

#include "shader.hpp"
#include "vertex_array.hpp"
#include "system/camera.hpp"
#include "math/transform.hpp"
#include "primitive/mesh.hpp"

namespace Core
{
	struct RenderParams
	{

	};

	struct BatchRenderParams
	{
		const size_t maxTriangleCount = 1000;
		const size_t maxVertexCount = maxTriangleCount * 4;
		const size_t maxIndexCount = maxTriangleCount * 6;
		const size_t maxTextures = 8;
	};

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static bool Begin(Ref<Camera> camera);// if camera is nullptr, we use view id 0
		static void End();

		static void SubmitVertexArray(Ref<VertexArray> vao, Ref<Shader> shader);

		static void SubmitVertexArrayTransform(Ref<VertexArray> vao, Ref<Shader> shader, Transform transform);
		static void SubmitMesh(Ref<Mesh> mesh, Transform transform);

		static Ref<ShaderManager> GetShaderManager();

	private:

	};
}