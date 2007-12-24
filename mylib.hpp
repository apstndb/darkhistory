#ifndef MYLIB_HPP
#define MYLIB_HPP
#include <string>

const std::wstring find_matchstr(const std::wstring&, const std::wstring&);

void convertMultiByteToWideChar(const char*, std::wstring&);
void convertWideCharToMultiByte(const wchar_t*, std::string&);
#endif // MYLIB_HPP
