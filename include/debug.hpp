#pragma once

#include "debug/logger.hpp"
#include "debug/debug_draw.hpp"

namespace Core
{
	namespace Capture
	{
		void Screenshot();

		void CaptureBegin();
		void CaptureEnd();
	}
}