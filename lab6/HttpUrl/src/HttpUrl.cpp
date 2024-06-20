#include "HttpUrl.h"
#include "UrlParsingError.h"
#include <regex>
#include <sstream>
#include <iostream>
#include <utility>

struct Args
{

};

HttpUrl::HttpUrl(std::string const& url)
{
	std::regex urlRegex(R"((http|https):\/\/([^\/:]+)(:\d+)?(\/.*)?)", std::regex::icase);
	std::smatch match;

	if (!std::regex_match(url, match, urlRegex))
	{
		throw UrlParsingError("Invalid URL");
	}

	std::string protocolStr = match[1];
	m_domain = match[2];
	std::string portStr = match[3];
	m_document = match[4];

	std::transform(protocolStr.begin(), protocolStr.end(), protocolStr.begin(),
		[](unsigned char c)
		{ return std::tolower(c); });

	if (protocolStr == "http")
	{
		m_protocol = Protocol::HTTP;
	}
	else
	{
		m_protocol = Protocol::HTTPS;
	}

	if (m_document.empty())
	{
		m_document = "/";
	}

	if (portStr.empty())
	{
		m_port = GetDefaultPort(m_protocol);
	}
	else
	{
		m_port = static_cast<unsigned short>(std::stoi(portStr.substr(1)));
	}

	ValidateDomain();
	ValidatePort();
}

HttpUrl::HttpUrl(std::string domain, std::string document, Protocol protocol)
	: m_domain(std::move(domain)),
	  m_document(std::move(document)),
	  m_protocol(protocol),
	  m_port(GetDefaultPort(protocol))
{
	//TODO: Выяснить какие бывают гаранития исключение
	if (m_document.empty() || m_document[0] != '/')
	{
		m_document = "/" + m_document;
	}
	ValidateDomain();
	ValidatePort();
	//TODO: port 65537 to 1 but
}

HttpUrl::HttpUrl(std::string domain, std::string document, Protocol protocol, unsigned short port)
	: m_domain(std::move(domain)),
	  m_document(std::move(document)),
	  m_protocol(protocol),
	  m_port(port)
{
	if (m_document.empty() || m_document[0] != '/')
	{
		m_document = "/" + m_document;
	}
	ValidateDomain();
	ValidatePort();
}

std::string HttpUrl::GetURL() const
{
	std::ostringstream url;
	url << ProtocolToString(m_protocol) << "://" << m_domain;
	if (m_port != GetDefaultPort(m_protocol))
	{
		url << ":" << m_port;
	}
	url << m_document;
	return url.str();
}

std::string HttpUrl::GetDomain() const
{
	return m_domain;
}

std::string HttpUrl::GetDocument() const
{
	return m_document;
}

Protocol HttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short HttpUrl::GetPort() const
{
	return m_port;
}

std::string HttpUrl::ProtocolToString(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return "http";
	case Protocol::HTTPS:
		return "https";
	default:
		throw std::invalid_argument("Unknown protocol");
	}
}

unsigned short HttpUrl::GetDefaultPort(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return 80;
	case Protocol::HTTPS:
		return 443;
	default:
		throw std::invalid_argument("Unknown protocol");
	}
}

//TODO: Сделать обычными функциями
void HttpUrl::ValidateDomain() const
{
	if (m_domain.empty())
	{
		throw std::invalid_argument("Domain cannot be empty");
	}
}

//TODO: Сделать обычными функциями
void HttpUrl::ValidatePort() const
{
	//TODO: Преверить пограничный случай с 1 и 65535
	if (m_port < 1 || m_port > 65535)
	{
		throw std::invalid_argument("Port must be in the range 1-65535");
	}
}
