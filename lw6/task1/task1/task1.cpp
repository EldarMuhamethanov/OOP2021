#include <iostream>
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

using namespace std;

int main()
{
	string line;

	while (!cin.eof() && getline(cin, line))
	{
		try
		{
			CHttpUrl url(line);

			cout << "\nurl: " << url.GetURL() << "\n"
				<< "protocol: " << url.GetProtocolString() << "\n"
				<< "domain: " << url.GetDomain() << "\n"
				<< "port: " << to_string(url.GetPort()) << "\n"
				<< "document: " << url.GetDocument() << "\n\n";
		}
		catch (const CUrlParsingError& e)
		{
			cout << e.what() << "\n\n";
		}
	}

	return 0;
}