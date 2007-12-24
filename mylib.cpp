#include "mylib.hpp"
#include <iostream>
const std::wstring find_matchstr(const std::wstring& l, const std::wstring& r)
{
	using namespace std;
	std::wstring::const_iterator li = l.begin(), le = l.end(), ri = r.begin();
	for(;li!=le;++li,++ri) {
		if(*li!=*ri) break;
	}
	return std::wstring(l.begin(), li);

	
}
void convertMultiByteToWideChar(const char* pStrMultiByte, std::wstring& rStrWideChar)
{
	size_t numWCharsNeeded =  ::mbstowcs(NULL, pStrMultiByte, 0);
	wchar_t* pStrWChar = new wchar_t[numWCharsNeeded + 1];
	size_t numWCharsConverted =::mbstowcs(pStrWChar, pStrMultiByte, numWCharsNeeded);
	pStrWChar[numWCharsConverted] = L'\0';

	rStrWideChar = pStrWChar;
	delete[] pStrWChar;
}
void convertWideCharToMultiByte(const wchar_t* pStrWideChar, std::string& rStrMultiByte)
{
	size_t numCharsNeeded = ::wcstombs(NULL, pStrWideChar, 0);
	char* pStrMultiByte = new char[numCharsNeeded + 1];
	size_t numCharsConverted = ::wcstombs(pStrMultiByte, pStrWideChar, numCharsNeeded);
	pStrMultiByte[numCharsConverted] = '\0';

	rStrMultiByte = pStrMultiByte;
	delete[] pStrMultiByte;
}

