/*
 * Copyright 2022 Marcus Madland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Class responsible for debug console logging
 *
 * @remark Most function definitions are inside this header file because of the
 * use of templated args
 */
#pragma once

#include <cstdio>
#include <mutex>
#include <bgfx/platform.h>

/*
 * This is needed to use colors inside the windows console window
 */
#ifdef BX_PLATFORM_WINDOWS 
	#include <Windows.h> 
#endif

namespace core
{
	/*
	 * Log priorities in order.
	 */
	enum class LogPriority
	{
		Trace,
		Debug,
		Info,
		Warn,
		Error,
		Critical
	};

	class Logger final
	{
	public:
		Logger() = default;

		/*
		 * Gets an instance of this class. 
		 *
		 * @remark Does not get initialized until the first time this is called
		 * 
		 * @return Reference to this class.
		 */
		static Logger& getInstance()
		{
			static Logger instance;
			return instance;
		}

		/*!
		 * Set the desired priority of the logger. Any messages lower than the
		 * current priority will not be logged
		 *
		 * @param[in] newPriority The desired priority type
		 */
		static void setPriority(const LogPriority& newPriority);

		/*!
		 * Get the current priority of the logger as type
		 *
		 * @return Current set log priority
		 */
		static LogPriority getPriority();
		
	private:
		/*
		 * Logs the message and args with the message priority using std::printf.
		 * If priority is below our global priority the message will not
		 * be logged
		 *
		 * @param[in] messagePriority The desired priority type of the message
		 * @param[in] message The message to print to the console
		 * @param[in] args Arguments that are used inside the message, if any
		 */
		template<typename... Args>
		void log(const LogPriority& messagePriority, const char* message, Args... args)
		{

			// Skip logging when in release mode
#ifdef NDEBUG
			return;
#endif

			// Skip logging if this message's priority is below our global
			// priority
			if (getPriority() > priority)
			{
				return;
			}

			// Skip logging if message is invalid
			if (message == "" || message == nullptr)
			{
				return;
			}

			// Construct logging title with the priority name
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
				messageTitle = "[Critical] Debug text is missing title ";
				break;
			}

			// Since std::printf is called multiple times- it can be called
			// in different orders because of other threads
			std::scoped_lock lock(logMutex);

#ifdef BX_PLATFORM_WINDOWS
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif

			// Print final message with constructed title and arguments
			std::printf(messageTitle);
			std::printf(message, args...);
			std::printf("\n");
		}

	public:
		/*!
		 * Log a message and args with the Trace priority
		 *
		 * @param[in] message The message to print to the console
		 * @param[in] args Arguments that are used inside the message, if any
		 */
		template<typename... Args>
		static void logTrace(const char* message, Args... args)
		{
			getInstance().log(LogPriority::Trace, message, args...);
		}

		/*!
		 * Log a message and args with the Debug priority
		 *
		 * @param[in] message The message to print to the console
		 * @param[in] args Arguments that are used inside the message, if any
		 */
		template<typename... Args>
		static void logDebug(const char* message, Args... args)
		{
			getInstance().log(LogPriority::Debug, message, args...);
		}

		/*!
		 * Log a message and args with the Info priority
		 *
		 * @param[in] message The message to print to the console
		 * @param[in] args Arguments that are used inside the message, if any
		 */
		template<typename... Args>
		static void logInfo(const char* message, Args... args)
		{
			getInstance().log(LogPriority::Info, message, args...);
		}

		/*!
		 * Log a message and args with the Warn priority
		 *
		 * @param[in] message The message to print to the console
		 * @param[in] args Arguments that are used inside the message, if any
		 */
		template<typename... Args>
		static void logWarn(const char* message, Args... args)
		{
			getInstance().log(LogPriority::Warn, message, args...);
		}

		/*!
		 * Log a message and args with the Error priority
		 *
		 * @param[in] message The message to print to the console
		 * @param[in] args Arguments that are used inside the message, if any
		 */
		template<typename... Args>
		static void logError(const char* message, Args... args)
		{
			getInstance().log(LogPriority::Error, message, args...);
		}
		
		/*!
		 * Log a message and args with the Critical priority
		 *
		 * @param[in] message The message to print to the console
		 * @param[in] args Arguments that are used inside the message, if any
		 */
		template<typename... Args>
		static void logCritical(const char* message, Args... args)
		{
			getInstance().log(LogPriority::Critical, message, args...);
		}

	private:
		LogPriority priority = LogPriority::Info;
		std::mutex logMutex;
	};
	
}