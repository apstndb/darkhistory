#include "mylib.hpp"
#include <fstream>
#include <iostream>
#ifndef WIN32
#include <iconv.h>
#endif
#include <boost/algorithm/string.hpp>
//using std::ifstream;
//using std::pair;
//using std::string;
using std::wstring;
//using std::multimap;
//using std::vector;
//using namespace boost::algorithm;
/*vector<wstring> kana2roma(multimap<wstring,wstring> v, wstring tstr)
{
	vector<wstring> result;

	for(unsigned int i = 0; i <= tstr.size();i++)
	{
		std::pair<multimap<wstring,wstring>::iterator, std::multimap<wstring,wstring>::iterator> iterpair;
		multimap<wstring,wstring>::iterator j;
		iterpair = v.equal_range(tstr.substr(0,i));
		for(j = iterpair.first;j!=iterpair.second;j++) {
			vector<wstring> temp;
			temp=kana2roma(v,tstr.substr(i));
			for(vector<wstring>::iterator iter = temp.begin(); iter != temp.end(); iter++){
				result.push_back( (*j).second+(*iter));
			}
		}
	}

	if(result.size() == 0) { result.push_back(L""); }

	return result; 
}
const multimap<wstring,wstring>& init(const char* filename)
{
	setlocale(LC_ALL, "");
	static multimap<wstring,wstring> hash;
	ifstream dat(filename);
	wstring wstr;
	string str;
	if(!dat.is_open()) {
		exit(512);

	}
	//locale::global(locale(""));
	//dat.imbue(locale(""));
	//iconv_t cd = iconv_open("WCHAR_T", "UTF8");
#ifndef WIN32
	iconv_t cd = iconv_open("WCHAR_T", "CP932");
#endif

	while(getline(dat,str)) 
	{
#ifndef WIN32
		wchar_t dstrbuf[512] ;
		char* sstr = (char*)str.c_str() ;
		//		const char* sstr = sstrbuf ;
		char* dstr = (char*)dstrbuf ;
		size_t size1 = str.size()+1;
		size_t size2 = sizeof(dstrbuf)/sizeof(dstrbuf[0]);
		iconv(cd, &sstr, &size1,&dstr,&size2);
		*((wchar_t* )dstr) = L'\0';
		wstr = dstrbuf;
#else

		convertMultiByteToWideChar(str.c_str(), wstr);
#endif
		vector<wstring> v;
		trim(wstr);
		if(starts_with(wstr, "#")) continue;
		split(v, wstr, is_space());
		if(v.size() != 2) continue;
		hash.insert(pair<wstring,wstring>(v[1],v[0]));
	}
	return hash;
}
*/
void convertMultiByteToWideChar(const char* pStrMultiByte, std::wstring& rStrWideChar)
{
	size_t numWCharsNeeded =  ::mbstowcs(NULL, pStrMultiByte, 0);
	wchar_t* pStrWChar = new wchar_t[numWCharsNeeded + 1];
	size_t numWCharsConverted =::mbstowcs(pStrWChar, pStrMultiByte, numWCharsNeeded);
	pStrWChar[numWCharsConverted] = L'\0';

	rStrWideChar = pStrWChar;
	delete[] pStrWChar;
}
