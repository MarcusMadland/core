#pragma once

#include "shader.hpp"
#include "vertex_array.hpp"
#include "batch.hpp"
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

		static bool Begin(Ref<Camera> camera);// if camera is nullptr, we use view id 0
		static void End();

		static void SubmitVertexArray(Ref<VertexArray> vao, Ref<Shader> shader);

		static void SubmitVertexArrayTransform(Ref<VertexArray> vao, Ref<Shader> shader, Transform transform);
		static void SubmitMesh(Ref<Mesh> mesh, Transform transform);
		static void SubmitBatch(Ref<Batch> batch);

		static Ref<ShaderManager> GetShaderManager();

	private:

	};
}