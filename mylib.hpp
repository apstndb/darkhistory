#ifndef MYLIB_HPP
#define MYLIB_HPP
#include <string>

void convertMultiByteToWideChar(const char*, std::wstring&);
void convertWideCharToMultiByte(const wchar_t*, std::string&);
#endif // MYLIB_HPP
