#include <vector>
#include <map>
#include <string>
#include <FTGL/FTGLPolygonFont.h>
using std::wstring;
using std::multimap;
using std::vector;
void RenderMap(FTFont*, multimap<wstring,wstring>, wstring);
void RenderVector(FTFont*, vector<wstring>);
void RenderText(FTFont*, wstring);
