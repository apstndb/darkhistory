#include <string>
#include <GL/glc.h>
#include "mygllib.hpp"
void Render(const wchar_t* str, const RenderFlag flag)
{
	glPushMatrix();
	adjust(str);
	align(str, flag);
	glcRenderString(str);
	glPopMatrix();
}
void RenderPartiallColor(const wchar_t* str, const size_t num, const RenderFlag flag)
{
	glPushMatrix();
	adjust(str);
	align(str, flag);
	glColor3f(0.0, 0.0, 1.0);
	glcRenderString(std::wstring(str, str+num).c_str());
	glColor3f(1.0, 0.0, 0.0);
	glcRenderString(std::wstring(str+num).c_str());
	glPopMatrix();
}
std::vector<GLfloat> baselines(const wchar_t* str)
{
	std::vector<GLfloat> v(4);
	glcMeasureString(GL_FALSE, str);
	glcGetStringMetric(GLC_BASELINE, &*v.begin());
	return std::vector<GLfloat>(v);
}
GLfloat advance(const wchar_t* str)
{
	return baselines(str).at(2);
}
void adjust(const wchar_t* str)
{
	GLfloat size = advance(str);
	if(size>17) glScalef(17/size, 17/size, 17/size);
}
void align(const wchar_t* str, RenderFlag flag)
{
	GLfloat size = advance(str);
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
}
