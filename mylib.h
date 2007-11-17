#include <vector>
#include <map>
#include <string>

std::vector<std::wstring>
kana2roma(std::multimap<std::wstring,std::wstring>, std::wstring);
const std::multimap<std::wstring,std::wstring>& init(const char*);
void convertMultiByteToWideChar(const char*, std::wstring&);
