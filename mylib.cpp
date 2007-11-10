#include "mylib.h"
#include <fstream>
#include <iostream>
#ifndef WIN32
#include <iconv.h>
#endif
#include <boost/algorithm/string.hpp>
#include <boost/shared_container_iterator.hpp>
using std::wifstream;
using std::ifstream;
using std::pair;
using std::string;
using std::locale;
using std::wcout;
using std::cout;
using std::endl;
using namespace boost::algorithm;
vector<wstring> kana2roma(multimap<wstring,wstring> v, wstring tstr)
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
void convertMultiByteToWideChar(const char* pStrMultiByte, std::wstring& rStrWideChar)
{
	size_t numWCharsNeeded =  ::mbstowcs(NULL, pStrMultiByte, 0);
	wchar_t* pStrWChar = new wchar_t[numWCharsNeeded + 1];
	size_t numWCharsConverted =::mbstowcs(pStrWChar, pStrMultiByte, numWCharsNeeded);
	pStrWChar[numWCharsConverted] = L'\0';

	rStrWideChar = pStrWChar;
	delete[] pStrWChar;
}

const vector<pair<wstring,wstring> >& initvec(const char* filename)
{
	setlocale(LC_ALL, "");
//	static multimap<wstring,wstring> hash;
	static vector<pair<wstring,wstring> > vec;
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
		/*wstring */wstr = dstrbuf;
#else

		convertMultiByteToWideChar(str.c_str(), wstr);
#endif
		vector<wstring> v;
		trim(wstr);
		if(starts_with(wstr, "#")) continue;
		split(v, wstr, is_space());
		if(v.size() != 2) continue;
		vec.push_back(pair<wstring,wstring>(v[1],v[0]));
	}
	return vec;
}
void initset(const char* filename, KanaSet& set)
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
		/*wstring */wstr = dstrbuf;
#else

		convertMultiByteToWideChar(str.c_str(), wstr);
#endif
		vector<wstring> v;
		trim(wstr);
		if(starts_with(wstr, "#")) continue;
		split(v, wstr, is_space());
		if(v.size() != 2) continue;
		//hash.insert(pair<wstring,wstring>(v[1],v[0]));
		set.push(KanaYomi(v[1],v[0]));
	}
//	return hash;
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
		/*wstring */wstr = dstrbuf;
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
vector<wstring> ListMatchPrefix(vector<wstring>& vec,wstring str)
{
	vector<wstring> result;
	//for(vector<wstring>::iterator i = vec.begin(); i != vec.end();i++)
	//		{if((*i).substr(0,str.size())==str) result.push_back(*i);}
	for(vector<wstring>::iterator i = vec.begin(); i != vec.end();i++)
	{
		if(ComparePrefix((*i),str)) result.push_back(*i);
	}
	return result;
}
bool ComparePrefix(wstring lstr,wstring sstr)
{
	return lstr.substr(0,sstr.size())==sstr;

}
void OutputVector(vector<wstring> v)
{
	for(vector<wstring>::iterator i = v.begin(); i != v.end();++i) {
		wcout << *i << endl;
	}
}
bool match(vector<wstring> v, wstring s)
{
	for(vector<wstring>::iterator i = v.begin(); i != v.end();++i) {
		if(*i == s) {return true;}
	}
	return false;
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
			iter = index.find(yomi.substr(0,1));
			if(iter != index.end())
				return iter->kana + to_kana(yomi.substr(1));
		}
	}
	return yomi;
}
//vector<KanaYomiPtr> KanaSet::searchByKana(const wstring &kana)
//vector<KanaYomi> KanaSet::searchByKana(const wstring &kana)
//{
//	vector<KanaYomi> hit;
//	if(kanaset.empty())
//		return hit;
//	kanaset_kana_index &kana_index = kanaset.get<by_kana>();
//	kanaset_kana_index::const_iterator last = kana_index.upper_bound(kana);
//	
//	for(kanaset_kana_index::const_iterator itr = kana_index.lower_bound(kana);
//			itr != last; ++itr) {
//		hit.push_back(*itr);
//	}
//	return hit;
//}
//KanaYomi KanaSet::searchByYomi(const wstring &yomi)
//{
//	KanaYomi entry;
//	if(kanaset.empty())
//		return entry;
//	kanaset_yomi_index &yomi_index = kanaset.get<by_yomi>();
//	kanaset_yomi_index::const_iterator itr = yomi_index.find(yomi);
//	if(itr == yomi_index.end())
//		return entry;
//	return *itr;
//}
