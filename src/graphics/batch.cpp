#include "crpch.hpp"

#include "graphics/batch.hpp"

namespace Core
{
	Batch::Batch(const BatchParams& params)
	{
	}

	Batch::~Batch()
	{
	}

	Ref<Batch> Batch::Create(const BatchParams& params)
	{
		return MakeRef<Batch>(params);
	}
}