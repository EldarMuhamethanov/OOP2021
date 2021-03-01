#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <utility>
#include <map>
#include <regex>
#include <iterator>
#include "HtmlDecode.h"

using namespace std;

int main()
{
	string line;
	getline(cin, line);
	string decodedString = HtmlDecode(line);

	cout << decodedString;
	return 0;
}