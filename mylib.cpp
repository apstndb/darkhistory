#include "mylib.h"
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
using std::wifstream;
using std::pair;
using std::locale;
using std::wcout;
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

const multimap<wstring,wstring>& init(const char* filename)
{
	setlocale(LC_ALL, "");
	static multimap<wstring,wstring> hash;
	wifstream dat(filename);
	wstring str;
	if(!dat.is_open()) {exit(1);}
	//locale::global(locale(""));
	dat.imbue(locale(""));

	while(getline(dat,str)) 
	{
		vector<wstring> v;
		trim(str);
		if(starts_with(str, "#")) continue;
		split(v, str, is_space());
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
