#pragma once
#include <iostream>
#include <map>

enum class Protocol
{
	HTTP,
	HTTPS
};


class CHttpUrl
{
public:
	explicit CHttpUrl(std::string const& url);
	CHttpUrl(std::string const& domain,	std::string const& document, Protocol protocol = Protocol::HTTP);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port);

	std::string GetURL()const;
	std::string GetDomain()const;
	std::string GetDocument()const;
	Protocol GetProtocol()const;
	unsigned short GetPort()const;

	std::string GetProtocolString() const;

private:
	bool isValidDomain(std::string domain) const;
	bool isValidPort(unsigned short port) const;

	bool isDefaultPort(unsigned short port) const;

	Protocol ConvertToValidProtocol(std::string protocol) const;
	std::string ConvertToValidDocument(std::string document) const;
	unsigned short ConvertStringToValidPort(std::string port) const;

private:
	const std::map<Protocol, unsigned short> m_protocolToDefaultPortMap{
		{Protocol::HTTP, 80},
		{Protocol::HTTPS, 443},
	};

	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};

