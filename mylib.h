#include <vector>
#include <map>
#include <string>
using std::wstring;
using std::multimap;
using std::vector;
vector<wstring> kana2roma(multimap<wstring,wstring>, wstring);
void convertMultiByteToWideChar(const char* , std::wstring& );
const multimap<wstring,wstring>& init(const char*);
