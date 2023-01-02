#include "crpch.hpp"

#include "debug/logger.hpp"

namespace core
{
	void Logger::setPriority(const LogPriority& newPriority)
	{
		getInstance().priority = newPriority;
	}

	LogPriority Logger::getPriority()
	{
		return getInstance().priority;
	}
	
}