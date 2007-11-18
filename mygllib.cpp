#include <boost/algorithm/string.hpp>
#include <vector>
#include "game.hpp"
#include "mygllib.h"
//void RenderMap(FTFont* font, multimap<wstring,wstring> v, wstring tstr)
//{
//	//for(multimap<wstring,wstring >::iterator i = v.find(tstr); i != v.end();++i) {
//	for(multimap<wstring,wstring >::iterator i = v.begin(); i != v.end();++i) {
//		glPushMatrix();
//		font->Render((*i).first.c_str());
//		glPopMatrix();
//		glTranslatef(.0f, -font->LineHeight(), .0f);
//	}
//}
//void RenderVector(FTFont* font, vector<wstring> v, int num)
//{
////	for(vector<wstring>::iterator i = v.begin(); i != v.end();++i,num++) {
//	for(; num < v.size();num++) {
//		glPushMatrix();
//		font->Render(v[num].c_str());
//		glPopMatrix();
//		glTranslatef(.0f, -font->LineHeight(), .0f);
//	}
//}
//void RenderVector(FTFont* font, vector<wstring> v)
//{
//	for(vector<wstring>::iterator i = v.begin(); i != v.end();++i) {
//		glPushMatrix();
//		font->Render((*i).c_str());
//		glPopMatrix();
//		glTranslatef(.0f, -font->LineHeight(), .0f);
//	}
//}
void RenderText(FTFont* font, const std::wstring& str)
{
	using std::vector;
	using std::wstring;
	using namespace boost::algorithm;
	vector<wstring> v;
	split(v, str, is_any_of(L"\n"));
	for(vector<wstring>::iterator i = v.begin(); i != v.end();++i) {
		glPushMatrix();
		font->Render((*i).c_str());
		glPopMatrix();
		glTranslatef(.0f, -font->LineHeight(), .0f);
	}
}
