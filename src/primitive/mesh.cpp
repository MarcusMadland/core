#include "crpch.hpp"

#include "primitive/mesh.hpp"
#include "debug/logger.hpp"

namespace Core
{
	Mesh::Mesh()
	{
		
	}

	Ref<Mesh> Mesh::Create()
	{
		return MakeRef<Mesh>();
	}
}