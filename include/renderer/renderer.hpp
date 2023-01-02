#pragma once

#include "shader.hpp"
#include "buffers.hpp"
#include "batch.hpp"
#include "camera.hpp"
#include "mesh.hpp"
#include "math/transform.hpp"

namespace core
{
	class Renderer
	{
	public:
		static void init();
		static void shutdown();

		static bool begin(ref<Camera> camera);// if camera is nullptr, we use view id 0
		static void end();

		static void submitVertexArray(ref<VertexArray> vao, ref<Shader> shader);

		static void submitVertexArrayTransform(ref<VertexArray> vao, ref<Shader> shader, Transform transform);
		static void submitMesh(ref<Mesh> mesh, Transform transform);
		static void submitBatch(ref<Batch> batch);

		static ref<ShaderManager> getShaderManager();

	private:

	};
}