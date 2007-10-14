#include <vector>
#include <map>
#include <string>
//#include <iostream>
//#include <fstream>
//
#include <FTGL/FTGLPolygonFont.h>
//#include <stdlib.h>    // For malloc() etc.
////#include <stdio.h>     // For printf(), fopen() etc.
//#include <math.h>      // For sin(), cos() etc.
//#include <GL/glfw.h>   // For GLFW, OpenGL and GLU

//#define FONT "/usr/share/fonts/WinFont/msgothic.ttc"
//#define SIZE 1.0
//#define DEPTH 0.5

//using namespace std;
//using namespace std;
//using namespace boost::algorithm;
using std::wstring;
using std::multimap;
using std::vector;
vector<wstring> kana2roma(multimap<wstring,wstring>, wstring);
void RenderMap(FTFont*, multimap<wstring,wstring>, wstring);
void RenderVector(FTFont*, vector<wstring>);
void convertMultiByteToWideChar(const char* , std::wstring& );
void RenderText(FTFont*, wstring);
