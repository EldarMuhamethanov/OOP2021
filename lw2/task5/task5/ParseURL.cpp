#include <string>
#include <map>
#include <regex>
#include <regex>
#include "ParseURL.h"

using namespace std;

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
    map<string, Protocol> stringToProtocolMap{
        {"http", Protocol::HTTP},
        {"https", Protocol::HTTPS},
        {"ftp", Protocol::FTP},
    };
    map<Protocol, int> ProtocolToDefaultPort{
        {Protocol::HTTP, 80},
        {Protocol::HTTPS, 443},
        {Protocol::FTP, 21},
    };
    regex urlRegex("(.+)(:\/\/)([^\/]+)(\/)?(.+)?");
    smatch urlMatch;
    if (regex_search(url, urlMatch, urlRegex))
    {
        string stringProtocol = urlMatch[1];
        transform(stringProtocol.begin(), stringProtocol.end(), stringProtocol.begin(), tolower);
        if (stringToProtocolMap.find(stringProtocol) != stringToProtocolMap.end())
        {
            protocol = stringToProtocolMap[stringProtocol];
        }
        else
        {
            return false;
        }
        regex hostRegex("(.+[^:])(:)([^:].+)");
        smatch hostMatch;
        string hostString = urlMatch[3];
        if (regex_search(hostString, hostMatch, hostRegex))
        {
            host = hostMatch[1];
            int urlPort = stoi(hostMatch[3]);
            if (urlPort > 0 && urlPort < 65536)
            {
                port = urlPort;
            }
            else
            {
                return false;
            }
        }
        else
        {
            host = hostString;
            port = ProtocolToDefaultPort[protocol];
        }
        if (urlMatch.length() >= 6)
        {
            document = urlMatch[5];
        }
        return true;
    }
    else
    {
        return false;
    }
}