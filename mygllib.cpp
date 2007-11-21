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
void Render(const boost::shared_ptr<FTFont>& font, const std::wstring& str, render_flag flag)
{
	glPushMatrix();
	GLfloat size = font->Advance(str.c_str());
	if(size>17) glScalef(17/size, 17/size, 17/size);
	switch(flag) {
		case RENDER_LEFT:
			glTranslatef(-size, .0f, .0f);
			break;
		case RENDER_CENTER:
			glTranslatef(-size/2, .0f, .0f);
			break;
		case RENDER_RIGHT:
			break;
	}
	font->Render(str.c_str());
	glPopMatrix();
}
void RenderPartiallColor(const boost::shared_ptr<FTFont>& font, const std::wstring& str, size_t num, render_flag flag)
{
	glPushMatrix();
	GLfloat size = font->Advance(str.c_str());
	if(size>17) glScalef(17/size, 17/size, 17/size);
	switch(flag) {
		case RENDER_LEFT:
			glTranslatef(-size, .0f, .0f);
			break;
		case RENDER_CENTER:
			glTranslatef(-size/2, .0f, .0f);
			break;
		case RENDER_RIGHT:
			break;
	}
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	font->Render(str.substr(0,num).c_str());
	glPopMatrix();
	glTranslatef(font->Advance(str.substr(0,num).c_str()), .0f, .0f);
	glColor3f(1.0, 0.0, 0.0);
	font->Render(str.substr(num).c_str());
	glPopMatrix();
}
