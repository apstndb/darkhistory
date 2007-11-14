#include "mylib.h"
#include <iostream>
#include <algorithm>
#include "boost/algorithm/string.hpp"
//#include <boost/lambda/lambda.hpp>
//#include <boost/lambda/algorithm.hpp>
//#include <boost/lambda/bind.hpp>
using namespace std;
//using std::wcout;
//using std::cout;
//using std::endl;
//using std::locale;
using namespace boost::algorithm;
//using namespace boost::lambda;
//void RenderMap(FTFont* font, multimap<wstring,wstring> v, wstring tstr)
//{
//	for(multimap<wstring,wstring >::iterator i = v.find(tstr); i != v.end();++i) {
//		glPushMatrix();
//		font->Render((*i).first.c_str());
//		glPopMatrix();
//		glTranslatef(.0f, -font->LineHeight(), .0f);
//	}
//}
int main(int argc, char** argv)
{
	//boost::lambda::placeholder1_type X;
	//boost::lambda::placeholder2_type Y;
	setlocale(LC_ALL, "");
	locale::global(locale(""));
	const multimap<wstring,wstring>& hash = init("roma2hira.dat");
	wcout.imbue(locale(""));
	wstring str,str2;
	convertMultiByteToWideChar(argv[1], str);
	convertMultiByteToWideChar(argv[2], str2);
	//cout << "hoge" <<endl;
	//wcout << str << flush;
	//OutputVector(kana2roma(hash,str));
	vector<wstring> vec = kana2roma(hash,str);
	OutputVector(ListMatchPrefix(vec,str2),wcout);
	//	for(vector<wstring>::iterator i = vec.begin(); i != vec.end();i++)
	//		{if((*i).substr(0,str2.size())==str2) wcout << *i << endl;}
	//	wcout << flush;
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
