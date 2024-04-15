#include <stdexcept>
#include <string>
#include <utility>

class RedefinitionException : public std::exception
{
private:
	std::string errorMessage;

public:
	explicit RedefinitionException(std::string message) : errorMessage(std::move(message))
	{
	}

	const char* what() const noexcept override
	{
		return errorMessage.c_str();
	}
};

class UndeclaredException : public std::exception
{
private:
	std::string errorMessage;

public:
	UndeclaredException(std::string message) : errorMessage(std::move(message))
	{
	}

	const char* what() const noexcept override
	{
		return errorMessage.c_str();
	}
};

class InvalidNameException : public std::exception
{
private:
	std::string errorMessage;

public:
	InvalidNameException(std::string message) : errorMessage(std::move(message))
	{
	}

	const char* what() const noexcept override
	{
		return errorMessage.c_str();
	}
};