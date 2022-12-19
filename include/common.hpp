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

#pragma once

#include <memory>

/*
 * Smart Pointers
 */
namespace Core
{
	/*
	 * Unique Pointer, destroys itself when out of scope
	 */
	template<typename T>
	using Scope = std::unique_ptr<T>;

	/*
	 * Shared Pointer, destroys itself when all owners are destroyed or .reset()
	 * has been used
	 */
	template<typename T>
	using Ref = std::shared_ptr<T>;

	/*
	 * Makes a unique pointer
	 */
	template<typename T, typename ... Args>
	constexpr Scope<T> MakeScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	/*
	 * Makes a shared pointer
	 */
	template<typename T, typename ... Args>
	constexpr Ref<T> MakeRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}