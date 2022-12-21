#pragma once

#include "shader.hpp"
#include "vertex_array.hpp"
#include "system/camera.hpp"
#include "math/transform.hpp"
#include "primitive/mesh.hpp"

namespace Core
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		// if camera is nullptr, we use view id 0
		static bool Begin(Ref<Camera> camera);
		static void End();

		static void SubmitVertexArray(Ref<VertexArray> vao, Ref<Shader> shader);
		static void SubmitVertexArrayTransform(Ref<VertexArray> vao, Ref<Shader> shader, Transform transform);
		static void SubmitMesh(Ref<Mesh> mesh, Transform transform);

		static Ref<ShaderManager> GetShaderManager();

	private:

	};
}