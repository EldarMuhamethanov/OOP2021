#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <algorithm>
#include <cctype>
#include <regex>

using namespace std;

CHttpUrl::CHttpUrl(string const& url)
{
	regex urlRegex(R"(^(.+)://([^/:]+)(:?)([^/]*)(/?.*)$)");
	smatch match;

	if (regex_search(url, match, urlRegex))
	{
		string protocolString = match[1];
		string domain = match[2];
		string port = match[4].matched ? match[4].str() : "";
		string document = match[5].str();

		if (!isValidDomain(domain))
			throw CUrlParsingError("invalid domain");
		
		m_protocol = ConvertToValidProtocol(protocolString);
		m_domain = domain;
		m_port = match[3].matched && !match[3].str().empty()
			? ConvertStringToValidPort(port)
			: m_protocolToDefaultPortMap.at(m_protocol);
		m_document = ConvertToValidDocument(document);

		return;
	}
	throw CUrlParsingError("invalid url");
}

CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol)
{
	if (!isValidDomain(domain))
		throw CUrlParsingError("invalid domain");

	m_protocol = protocol;
	m_domain = domain;
	m_port = m_protocolToDefaultPortMap.at(protocol);
	m_document = ConvertToValidDocument(document);
}

CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol, unsigned short port)
{
	if (!isValidDomain(domain))
		throw CUrlParsingError("invalid domain");

	if (!isValidPort(port))
		throw CUrlParsingError("invalid port");

	m_protocol = protocol;
	m_domain = domain;
	m_port = port;
	m_document = ConvertToValidDocument(document);
}

std::string CHttpUrl::GetURL()const
{
	string res;
	string domain = GetDomain();
	unsigned short port = GetPort();
	string protocol = GetProtocolString();
	string document = GetDocument();

	res = protocol + "://" + domain;
	if (!isDefaultPort(port))
	{
		res += ":" + to_string(port);
	}
	res += document;

	return res;
}
std::string CHttpUrl::GetDomain()const
{
	return m_domain;
}
std::string CHttpUrl::GetDocument()const
{
	return m_document;
}
Protocol CHttpUrl::GetProtocol()const
{
	return m_protocol;
}
unsigned short CHttpUrl::GetPort()const
{
	return m_port;
}

std::string CHttpUrl::GetProtocolString() const
{
	static const std::map<Protocol, std::string> protocolToStringMap{
		{Protocol::HTTP, "http"},
		{Protocol::HTTPS, "https"},
	};

	return protocolToStringMap.at(m_protocol);
}

bool CHttpUrl::isValidPort(unsigned short port) const
{
	return 0 < port && port;
}
bool CHttpUrl::isValidDomain(std::string domain) const
{
	return !domain.empty();
}

bool CHttpUrl::isDefaultPort(unsigned short port) const
{
	for (auto protocol : m_protocolToDefaultPortMap)
	{
		if (port == protocol.second)
			return true;
	}
	return false;
}

Protocol CHttpUrl::ConvertToValidProtocol(std::string protocol) const
{
	string protocolInLower = protocol;
	transform(protocolInLower.begin(), protocolInLower.end(), protocolInLower.begin(), ::tolower);

	const std::map<std::string, Protocol> stringToProtocolMap{
		{"http", Protocol::HTTP},
		{"https", Protocol::HTTPS},
	};

	if (!protocol.empty())
	{
		for (auto protocolPair : stringToProtocolMap)
		{
			if (protocolInLower == protocolPair.first)
				return protocolPair.second;
		}
	}	

	throw CUrlParsingError("invalid protocol");
}

string CHttpUrl::ConvertToValidDocument(string document) const
{
	if (document.empty() || document[0] != '/')
	{
		return "/" + document;
	}
	return document;
}

unsigned short CHttpUrl::ConvertStringToValidPort(std::string port) const
{
	regex portRegex(R"(^\d+$)");
	smatch match;
	if (regex_match(port, match, portRegex))
	{
		unsigned short portInInt = stoi(port);
		if (isValidPort(portInInt))
			return portInInt;
	}
	throw CUrlParsingError("invalid port");
}