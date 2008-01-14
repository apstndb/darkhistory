#ifndef MYLIB_HPP
#define MYLIB_HPP
//#include <string>

/**
 * 2つのコンテナの先頭から最長一致する部分の長さを返す
 */
size_t matchLength(const wchar_t* a, const wchar_t* b);

/**
 * マルチバイト文字列をワイド文字列に変換する
 */
void convertMultiByteToWideChar(const char*, std::wstring&);
/**
 * ワイド文字列をマルチバイト文字列に変換する
 */
void convertWideCharToMultiByte(const wchar_t*, std::string&);
#endif // MYLIB_HPP
