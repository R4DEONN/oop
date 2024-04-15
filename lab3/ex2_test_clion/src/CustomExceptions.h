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

	[[nodiscard]] const char* what() const noexcept override
	{
		return errorMessage.c_str();
	}
};

class UndeclaredException : public std::exception
{
private:
	std::string errorMessage;

public:
	explicit UndeclaredException(std::string message) : errorMessage(std::move(message))
	{
	}

	[[nodiscard]] const char* what() const noexcept override
	{
		return errorMessage.c_str();
	}
};

class InvalidNameException : public std::exception
{
private:
	std::string errorMessage;

public:
	explicit InvalidNameException(std::string message) : errorMessage(std::move(message))
	{
	}

	[[nodiscard]] const char* what() const noexcept override
	{
		return errorMessage.c_str();
	}
};

class SyntaxException : public std::exception
{
private:
	std::string errorMessage;

public:
	explicit SyntaxException(const std::string& message)
	{
		errorMessage = "Syntax error: " + message;
	}

	[[nodiscard]] const char* what() const noexcept override
	{
		return errorMessage.c_str();
	}
};