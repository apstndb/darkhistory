#include "mylib.h"
#include <boost/algorithm/string.hpp>
using namespace boost::algorithm;
//wstring wstr(L"24時間働けますが？\n何か？\nほげ\n\nあああ");
//vector<vector<wstring> > table;
//multimap<wstring,wstring> hash;
//ifstream hoge("roma2hira.dat");
//wstring str,wstr(L"つるぺたはにゃーん");
//string mstr;
//FTFont *font;
vector<wstring> kana2roma(multimap<wstring,wstring> v, wstring tstr)
{
	//wcout << tstr;
	vector<wstring> result;
	
	for(int i = 0; i <= tstr.size();i++)
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
		//temp += tstr.substr(0,i);
	}
	
	if(result.size() == 0) { result.push_back(L""); }
	
	return result; 
}
//wstring kana2roma(multimap<wstring,wstring>, wstring);
//wstring kana2roma(multimap<wstring,wstring> v, wstring tstr)
//{
//	wstring temp(L"");
//	for(int i = 0; i <= tstr.size();i++)
//	{
//		multimap<wstring,wstring>::iterator iter = v.find(tstr.substr(0,i));
//		if(iter!=v.end()) {
//			temp = (*iter).second
//				+ kana2roma(hash,tstr.substr(i));
//		}
//		//temp += tstr.substr(0,i);
//	}
//	return temp; 
//}
void RenderMap(FTFont* font, multimap<wstring,wstring> v, wstring tstr)
{
	//for(multimap<wstring,wstring >::iterator i = v.find(tstr); i != v.end();++i) {
	for(multimap<wstring,wstring >::iterator i = v.find(tstr); i != v.end();++i) {
		glPushMatrix();
		font->Render((*i).first.c_str());
		glPopMatrix();
		glTranslatef(.0f, -font->LineHeight(), .0f);
	}
}
//void RenderVector(FTFont*, vector<vector<wstring> >);
//void RenderVector(FTFont* fnt, vector<vector<wstring> > v)
void RenderVector(FTFont* font, vector<wstring> v)
{
	//	    split(v, str, is_any_of(L"\n"));
	//for(vector<vector<wstring> >::iterator i = v.begin(); i != v.end();++i) {
	for(vector<wstring>::iterator i = v.begin(); i != v.end();++i) {
		glPushMatrix();
		//fnt->Render((*i)[1].c_str());
		font->Render((*i).c_str());
		glPopMatrix();
		glTranslatef(.0f, -font->LineHeight(), .0f);
	}
}
//    vector<wstring>& kana2roma(wstring);
//    vector<wstring>& kana2roma(wstring kana)
//    {
//	table.find(kana[0])
//   }
void RenderText(FTFont* font, wstring str)
{
	vector<wstring> v;
	split(v, str, is_any_of(L"\n"));
	for(vector<wstring>::iterator i = v.begin(); i != v.end();++i) {
		glPushMatrix();
		font->Render((*i).c_str());
		glPopMatrix();
		glTranslatef(.0f, -font->LineHeight(), .0f);
	}
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

