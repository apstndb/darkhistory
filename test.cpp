#include "mylib.h"
#include <string>
#include <iostream>
using namespace std;
int main(int argc, char** argv)
{
	wstring wstr, wstr2;//(L"‚Ê‚é‚Û");
	multimap<wstring,wstring> map = init("roma2hira.dat");
	setlocale(LC_ALL,"");
	if(argc==3) {
	convertMultiByteToWideChar(argv[1] , wstr);
		convertMultiByteToWideChar(argv[2] , wstr2);
	//OutputVector(kana2roma(map, wstr));
	vector<wstring> vec = kana2roma(map, wstr);
	//OutputVector(ListMatchPrefix(vec ,wstr2));
	vec = ListMatchPrefix(vec ,wstr2);
	OutputVector(vec,wcout);
	wcout << (match(vec,wstr2)?L"match":L"unmatch") << endl;
	wcout << vec.size() << endl;
	}
	//wcout << wstr << endl;
	return 0;
}
