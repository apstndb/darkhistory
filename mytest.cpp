#include "mylib.h"
#include <iostream>
#include "boost/algorithm/string.hpp"
using namespace std;
//using std::wcout;
//using std::cout;
//using std::endl;
//using std::locale;
using namespace boost::algorithm;
//void RenderMap(FTFont* font, multimap<wstring,wstring> v, wstring tstr)
//{
//	for(multimap<wstring,wstring >::iterator i = v.find(tstr); i != v.end();++i) {
//		glPushMatrix();
//		font->Render((*i).first.c_str());
//		glPopMatrix();
//		glTranslatef(.0f, -font->LineHeight(), .0f);
//	}
//}
void OutputVector(vector<wstring> v)
{
	for(vector<wstring>::iterator i = v.begin(); i != v.end();++i) {
		wcout << *i << endl;
	}
}
int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	locale::global(locale(""));
	const multimap<wstring,wstring>& hash = init("roma2hira.dat");
	wcout.imbue(locale(""));
	wstring str;
	convertMultiByteToWideChar(argv[1], str);
	//cout << "hoge" <<endl;
	//wcout << str << flush;
	OutputVector(kana2roma(hash,str));
	return 0;
	}
//void RenderText(FTFont* font, wstring str)
//{
//	vector<wstring> v;
//	split(v, str, is_any_of(L"\n"));
//	for(vector<wstring>::iterator i = v.begin(); i != v.end();++i) {
//		glPushMatrix();
//		font->Render((*i).c_str());
//		glPopMatrix();
//		glTranslatef(.0f, -font->LineHeight(), .0f);
//	}
//}
