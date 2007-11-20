#ifndef MYLIB_HPP
#define MYLIB_HPP
#include <boost/range.hpp>
#include <string>


//template<typename Range>
const std::wstring find_matchstr(const std::wstring&, const std::wstring&);

void convertMultiByteToWideChar(const char*, std::wstring&);
void convertWideCharToMultiByte(const wchar_t*, std::string&);
#endif // MYLIB_HPP
