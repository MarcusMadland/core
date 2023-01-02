#include "crpch.hpp"

#include "debug/logger.hpp"

namespace Core
{
	void Logger::SetPriority(const LogPriority& newPriority)
	{
		GetInstance().priority = newPriority;
	}

	LogPriority Logger::GetPriority()
	{
		return GetInstance().priority;
	}
	
}