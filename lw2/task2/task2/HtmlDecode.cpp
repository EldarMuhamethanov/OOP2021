#include "HtmlDecode.h"
#include <map>
#include <regex>

using namespace std;

string HtmlDecode(string const& html)
{
	string result;
	string str = html;
	map<string, string> htmlToSymbolMap{
		{"&quot;", "\""},
		{"&apos;", "'"},
		{"&lt;", "<"},
		{"&gt;", ">"},
		{"&amp;", "&"}
	};
	regex reg("&+[quot|apos|lt|gt|amp]+;");
	smatch match;
	while (true)
	{
		if (!regex_search(str, match, reg))
		{
			result += str;
			break;
		}
		string prefix = match.prefix();
		string suffix = match.suffix();
		result += prefix + htmlToSymbolMap[match[0]];
		str = suffix;
	}

	return result;
}