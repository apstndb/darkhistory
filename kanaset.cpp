#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "kanaset.hpp"
#include "mylib.h"
using namespace std;
using namespace boost::algorithm;
KanaSet::KanaSet(const char* filename)
{
	setlocale(LC_ALL, "");
//	static multimap<wstring,wstring> hash;
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
		if(2 != v.size()) continue;
		//hash.insert(pair<wstring,wstring>(v[1],v[0]));
		push(KanaYomi(v[1],v[0]));
	}
}
wstring KanaSet::to_kana(const wstring& yomi)
{
	if(!yomi.size()) {
		return yomi;
	} else {
		wstring kana;
		kanaset_yomi_index& index = kanaset.get<by_yomi>();
		kanaset_yomi_index::iterator iter;
		for(unsigned int i = 1; i <= yomi.size();i++) {
			iter = index.find(yomi.substr(0,i));
			if(iter != index.end())
				return iter->kana + to_kana(yomi.substr(i));
		}
	}
	if(yomi.size()>1 && yomi[0] == L'n')
		return L'ん' + to_kana(yomi.substr(1));
	else return ((yomi[0]==yomi[1])?L'っ':yomi[0]) + to_kana(yomi.substr(1));
	
}
