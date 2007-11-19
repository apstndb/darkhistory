#include <boost/algorithm/string.hpp>
#include <vector>
#include "game.hpp"
#include "mygllib.hpp"
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
void Render(const boost::shared_ptr<FTFont>& font, const std::wstring& str)
{
	glPushMatrix();
	glTranslatef(-font->Advance(str.c_str())/2, .0f, .0f);
	font->Render(str.c_str());
	glPopMatrix();
}
