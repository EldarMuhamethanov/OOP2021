#include <iostream>
#include <string>
#include <regex>
#include <map>
#include "ParseURL.h"

using namespace std;

void WriteUrlInfo(string const& url, string const& host, int port, string const& document)
{
    cout << url << endl;
    cout << "HOST: " << host << endl;
    cout << "PORT: " << port<< endl;
    cout << "DOC: " << document << endl;
}

int main()
{
    string url;
    getline(cin, url);
    while (!url.empty())
    {
        Protocol protocol;
        int port;
        string host;
        string document;
        bool isValidUrl = ParseURL(url, protocol, port, host, document);
        if (isValidUrl)
        {
            WriteUrlInfo(url, host, port, document);
        }
        else
        {
            cout << "invalid url" << endl;
        }
        cout << endl;
        getline(cin, url);
    }
}