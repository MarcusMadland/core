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
 * @todo Split this into one header and one cpp file
 */

#pragma once

#include <cstdio>
#include <mutex>

#include <bgfx/platform.h>

/*
 * This is needed to use colors inside the windows console window.
 */
#ifdef BX_PLATFORM_WINDOWS 
	#include <Windows.h> 
#endif

/*
 * Simple Logger class to log information to the console.
 */
namespace Core
{
	class Logger final
	{
	public:
		/*
		 * The log priorities in order.
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

	public:
		Logger() = default;

		static Logger& GetInstance()
		{
			static Logger instance;
			return instance;
		}

		/*
		 * Set the desired priority of the logger. Any messages lower than the
		 * current priority will not be logged.
		 *
		 * @param newPriority The desired priority type.
		 */
		static void SetPriority(LogPriority newPriority)
		{
			GetInstance().priority = newPriority;
		}

		/*
		 * Get the current priority of the logger as type.
		 */
		static LogPriority GetPriority()
		{
			return GetInstance().priority;
		}

		/*
		 * Logs the message and args with the message priority using std::printf.
		 * Finds out what priority we are in and logs the category before the
		 * message. If priority is below our current priority the message will not
		 * be logged.
		 *
		 * @param messagePriority The desired priority type of the message.
		 * @param message The message to print to the console.
		 * @param args Arguments that are used inside the message, if any.
		 */
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
				/*
				 * If the current priority is higher than the message priority we
				 * don't want to display it.
				 */
				return;
			}

			/*
			 * If the message is empty make sure the user knows.
			 */
			if (message == "" || message == nullptr)
			{
				message = "No message to log";
				messagePriority = LogPriority::Critical;
			}

			/*
			 * Switches on each priority type and sets a message color and Title
			 * to display the text with.
			 */
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
			/*
			 * Set the console attribute color to the text to the color of the
			 * priority type on windows only.
			 */
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif

			/*
			 * Finally prints the title, message and arguments to the console.
			 */
			std::printf(messageTitle);
			std::printf(message, args...);
			std::printf("\n");
		}

	public:
		/*
		 * Log a message and args with the Trace priority.
		 *
		 * @param message The message to print to the console.
		 * @param args Arguments that are used inside the message, if any.
		 */
		template<typename... Args>
		static void LogTrace(const char* message, Args... args)
		{
			GetInstance().Log(LogPriority::Trace, message, args...);
		}

		/*
		 * Log a message and args with the Debug priority.
		 *
		 * @param message The message to print to the console.
		 * @param args Arguments that are used inside the message, if any.
		 */
		template<typename... Args>
		static void LogDebug(const char* message, Args... args)
		{
			GetInstance().Log(LogPriority::Debug, message, args...);
		}

		/*
		 * Log a message and args with the Info priority.
		 *
		 * @param message The message to print to the console.
		 * @param args Arguments that are used inside the message, if any.
		 */
		template<typename... Args>
		static void LogInfo(const char* message, Args... args)
		{
			GetInstance().Log(LogPriority::Info, message, args...);
		}

		/*
		 * Log a message and args with the Warn priority.
		 *
		 * @param message The message to print to the console.
		 * @param args Arguments that are used inside the message, if any.
		 */
		template<typename... Args>
		static void LogWarn(const char* message, Args... args)
		{
			GetInstance().Log(LogPriority::Warn, message, args...);
		}

		/*
		 * Log a message and args with the Error priority.
		 *
		 * @param message The message to print to the console.
		 * @param args Arguments that are used inside the message, if any.
		 */
		template<typename... Args>
		static void LogError(const char* message, Args... args)
		{
			GetInstance().Log(LogPriority::Error, message, args...);
		}

		/*
		 * Log a message and args with the Critical priority.
		 *
		 * @param message The message to print to the console.
		 * @param args Arguments that are used inside the message, if any.
		 */
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