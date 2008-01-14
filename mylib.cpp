#include <string>
#include <iostream>
#include "mylib.hpp"
size_t matchLength(const wchar_t* a, const wchar_t* b)
{
	size_t i;

	for(i = 0; a && a[i] == b[i]; i++)
		;
	return i;
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

