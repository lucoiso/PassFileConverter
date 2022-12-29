// Author: Lucas Oliveira Vilas-Bôas
// Year: 2022
// Repository:

#pragma once

#include <iostream>
#include <string>

namespace Helper
{
	inline const std::string askQuestion(const std::string& question)
	{
		std::cout << question;
		std::string answer;
		std::getline(std::cin, answer);

		return answer;
	}
	
	inline constexpr void setMemberValue(const auto value, auto& member)
	{
		if (value == member)
		{
			return;
		}

		member = value;
	}

	template<typename ArgTy>
	inline constexpr const bool hasInvalidData(const ArgTy& arg)
	{
		if (arg.empty())
		{
			return true;
		}

		for (const auto& iterator : "|,;\"")
		{
			if (arg.contains(iterator))
			{
				return true;
			}
		}

		return false;
	}

	template<typename ArgTy, typename ...Args>
	inline constexpr const bool hasInvalidData(const ArgTy& arg, Args&& ...args)
	{
		return hasInvalidData(arg) || hasInvalidData(std::forward<Args>(args)...);
	}

	template<typename ArgTy>
	inline constexpr const bool hasEmptyData(const ArgTy& arg)
	{
		return arg.empty();
	}

	template<typename ArgTy, typename ...Args>
	inline constexpr const bool hasEmptyData(const ArgTy& arg, Args&& ...args)
	{
		return arg.empty() || hasEmptyData(std::forward<Args>(args)...);
	}
}