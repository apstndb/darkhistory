#include "mygllib.hpp"
void Render(const std::wstring& str, const RenderFlag flag)
{
	glPushMatrix();
	adjust(str);
	align(str, flag);
	glcRenderString(str.c_str());
	glPopMatrix();
}
void RenderPartiallColor(const std::wstring& str, const size_t num, const RenderFlag flag)
{
	glPushMatrix();
	adjust(str);
	align(str, flag);
	glColor3f(0.0, 0.0, 1.0);
	glcRenderString(str.substr(0,num).c_str());
	glColor3f(1.0, 0.0, 0.0);
	glcRenderString(str.substr(num).c_str());
	glPopMatrix();
}
