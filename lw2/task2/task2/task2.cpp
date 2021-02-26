#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <utility>
#include <map>
#include <regex>
#include <iterator>

using namespace std;


string HtmlDecode(string const& html)
{
	string result = html;
	string str = html;
	map<string, string> htmlToSymbolMap{
		{"&quot;", "\""},
		{"&apos;", "'"},
		{"&lt;", "<"},
		{"&gt;", ">"},
		{"&amp;", "&"}
	};
	regex reg("&+[quot|apos|lt|gt|amp]+;");
	int symbolIndex = 0;
	while (true)
	{
		smatch match;
		if (!regex_search(str, match, reg))
		{
			break;
		}
		string prefix = match.prefix();
		string suffix = match.suffix();
		result = prefix + htmlToSymbolMap[match[0]] + suffix;
		str = suffix;
	}

	return result;
}

int main()
{
	string line;
	getline(cin, line);
	string decodedString = HtmlDecode(line);

	cout << decodedString;
	return 0;
}