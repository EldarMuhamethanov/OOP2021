#include <string>
#include <map>
#include <regex>
#include <regex>
#include <optional>
#include "ParseURL.h"

using namespace std;

const int PROTOCOL_SUBMATCH_INDEX = 1;
const int HOST_SUBMATCH_INDEX = 3;
const int DOCUMENT_SUBMATCH_INDEX = 5;
const int MAX_PORT_VALUE = 65535;

const map<string, Protocol> stringToProtocolMap{
    {"http", Protocol::HTTP},
    {"https", Protocol::HTTPS},
    {"ftp", Protocol::FTP},
};
const map<Protocol, int> protocolToDefaultPort{
    {Protocol::HTTP, 80},
    {Protocol::HTTPS, 443},
    {Protocol::FTP, 21},
};

bool GetValidPort(string const& portString, int& port)
{
    regex portRegex(R"(\d*$)");
    smatch portMatch;
    if (regex_match(portString, portMatch, portRegex))
    {
        port = stoi(portMatch[0]);
        if (port > 0 && port <= MAX_PORT_VALUE)
        {
            return true;
        }
    }
    return false;
}

bool GetValidProtocol(string protocolString, Protocol& protocol)
{
    transform(protocolString.begin(), protocolString.end(), protocolString.begin(), tolower);
    if (stringToProtocolMap.find(protocolString) != stringToProtocolMap.end())
    {
        protocol = stringToProtocolMap.at(protocolString);
        return true;
    }
    return false;
}

bool ParseHost(const string& hostString, string& host, int& port, const Protocol& protocol)
{
    regex hostRegex(R"((.*)(:)(.*))");
    smatch hostMatch;

    if (regex_search(hostString, hostMatch, hostRegex))
    {
        host = hostMatch[1];
        if (host.find(':') != std::string::npos)
        {
            return false;
        }
        if (hostMatch.length() > 3 && !GetValidPort(hostMatch[3], port))
        {
            return false;
        }
    }
    else
    {
        host = hostString;
        port = protocolToDefaultPort.at(protocol);
    }
    return true;
}

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
    regex urlRegex(R"((.+)(://)([^/]+)(/)?(.+)?)");
    smatch urlMatch;
    if (regex_search(url, urlMatch, urlRegex))
    {
        string stringProtocol = urlMatch[PROTOCOL_SUBMATCH_INDEX];
        if (!GetValidProtocol(stringProtocol, protocol))
        {
            return false;
        }
        string hostPart = urlMatch[HOST_SUBMATCH_INDEX];
        if (!ParseHost(hostPart, host, port, protocol))
        {
            return false;
        }
        if (urlMatch.length() > DOCUMENT_SUBMATCH_INDEX)
        {
            document = urlMatch[DOCUMENT_SUBMATCH_INDEX];
        }
        return true;
    }
    return false;
}