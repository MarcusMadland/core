



#pragma once

#include <cstdio>
#include <mutex>

#include <bgfx/platform.h>


#ifdef BX_PLATFORM_WINDOWS 
	#include <Windows.h> 
#endif


namespace Core
{
	class Logger final
	{
	public:
		
		enum class LogPriority
		{
			Trace,
			Debug,
			Info,
			Warn,
			Error,
			Critical
		};

	public:
		Logger() = default;

		static Logger& GetInstance()
		{
			static Logger instance;
			return instance;
		}

		
		static void SetPriority(LogPriority newPriority)
		{
			GetInstance().priority = newPriority;
		}

		
		static LogPriority GetPriority()
		{
			return GetInstance().priority;
		}

		
	private:
		template<typename... Args>
		void Log(LogPriority messagePriority, const char* message, Args... args)
		{
			#ifdef NDEBUG
				return;
			#endif

			std::scoped_lock lock(logMutex);

			if (GetPriority() > priority)
			{
				
				return;
			}

			
			if (message == "" || message == nullptr)
			{
				message = "No message to log";
				messagePriority = LogPriority::Critical;
			}

			
			const char* messageTitle;
			uint32_t color;
			switch (messagePriority)
			{
			case LogPriority::Trace:
				color = 15;
				messageTitle = "[Trace]      ";
				break;
			case LogPriority::Debug:
				color = 15;
				messageTitle = "[Debug]      ";
				break;
			case LogPriority::Info:
				color = 15;
				messageTitle = "[Info]	     ";
				break;
			case LogPriority::Warn:
				color = 14;
				messageTitle = "[Warn]       ";
				break;
			case LogPriority::Error:
				color = 4;
				messageTitle = "[Error]      ";
				break;
			case LogPriority::Critical:
				color = 15 + 4 * 16;
				messageTitle = "[Critical]   ";
				break;
			default:
				color = 15 + 4 * 16;
				messageTitle = "[Critical] DEBUG TEXT MISSING TITLE! - ";
				break;
			}

#ifdef BX_PLATFORM_WINDOWS
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif

			
			std::printf(messageTitle);
			std::printf(message, args...);
			std::printf("\n");
		}

	public:
		
		template<typename... Args>
		static void LogTrace(const char* message, Args... args)
		{
			GetInstance().Log(LogPriority::Trace, message, args...);
		}

		
		template<typename... Args>
		static void LogDebug(const char* message, Args... args)
		{
			GetInstance().Log(LogPriority::Debug, message, args...);
		}

		
		template<typename... Args>
		static void LogInfo(const char* message, Args... args)
		{
			GetInstance().Log(LogPriority::Info, message, args...);
		}

		
		template<typename... Args>
		static void LogWarn(const char* message, Args... args)
		{
			GetInstance().Log(LogPriority::Warn, message, args...);
		}

		
		template<typename... Args>
		static void LogError(const char* message, Args... args)
		{
			GetInstance().Log(LogPriority::Error, message, args...);
		}

		
		template<typename... Args>
		static void LogCritical(const char* message, Args... args)
		{
			GetInstance().Log(LogPriority::Critical, message, args...);
		}

	private:
		LogPriority priority = LogPriority::Info;
		std::mutex logMutex;
	};
}