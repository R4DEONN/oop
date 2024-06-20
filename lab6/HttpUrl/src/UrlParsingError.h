#pragma once

#include "string"
#include "stdexcept"

class UrlParsingError : public std::invalid_argument
{
public:
	explicit UrlParsingError(const std::string& message)
		: std::invalid_argument(message)
	{
	}

	[[nodiscard]] const char* what() const noexcept override
	{
		return std::invalid_argument::what();
	}
};
