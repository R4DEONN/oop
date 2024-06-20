#pragma once

#include "string"

enum class Protocol
{
	HTTP,
	HTTPS
};

class HttpUrl
{
public:
	HttpUrl(std::string const& url);

	HttpUrl(
		std::string  domain,
		std::string  document,
		Protocol protocol = Protocol::HTTP);

	HttpUrl(
		std::string  domain,
		std::string  document,
		Protocol protocol,
		unsigned short port);

	std::string GetURL() const;

	std::string GetDomain() const;

	std::string GetDocument() const;

	Protocol GetProtocol() const;

	unsigned short GetPort() const;

private:
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;

	static std::string ProtocolToString(Protocol protocol);
	static unsigned short GetDefaultPort(Protocol protocol);
	void ValidateDomain() const;
	void ValidatePort() const;
};