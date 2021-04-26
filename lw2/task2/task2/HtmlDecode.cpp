#include "HtmlDecode.h"
#include <map>
#include <iostream>
#include <regex>

using namespace std;


regex GetHtmlToSymbolRegex(map<string, string> const& htmlToSymbolMap)
{
	string htmlRegexString;
	for (auto& html : htmlToSymbolMap)
	{
		htmlRegexString += "(" + html.first + ")" + "|";
	}
	if (htmlRegexString.size() > 0)
	{
		htmlRegexString.pop_back();
	}
	regex htmlRegex(htmlRegexString);
	return htmlRegex;
}

string HtmlDecode(string const& html)
{
	string result;
	static const map<string, string> htmlToSymbolMap{
		{"&quot;", "\""},
		{"&apos;", "'"},
		{"&lt;", "<"},
		{"&gt;", ">"},
		{"&amp;", "&"}
	};
	regex htmlRegex = GetHtmlToSymbolRegex(htmlToSymbolMap);

	const vector<smatch> matches{
		sregex_iterator{html.begin(), html.end(), htmlRegex},
		sregex_iterator{}
	};

	if (matches.size() == 0)
	{
		return html;
	}
	for(smatch const& match : matches)
	{
		string prefix = match.prefix();
		result += prefix + htmlToSymbolMap.at(match[0]);
	}
	result += matches.back().suffix();

	return result;
}