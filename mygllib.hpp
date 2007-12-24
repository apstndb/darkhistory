#ifndef MYGLLIB_HPP
#define MYGLLIB_HPP
#include <string>
#include <vector>
#include <GL/glc.h>
enum RenderFlag {
	RENDER_LEFT,
	RENDER_CENTER,
	RENDER_RIGHT
};
template<typename T>
std::vector<GLfloat> baselines(const std::basic_string<T>& str)
{
	std::vector<GLfloat> v(4);
	glcMeasureString(GL_FALSE, str.c_str());
	glcGetStringMetric(GLC_BASELINE, &*v.begin());
	return std::vector<GLfloat>(v);
}
template<typename T>
GLfloat advance(const std::basic_string<T>& str)
{
	return baselines(str).at(2);
}
template<typename T>
void adjust(const std::basic_string<T>& str)
{
	GLfloat size = advance(str);
	if(size>17) glScalef(17/size, 17/size, 17/size);
}
template<typename T>
void align(const std::basic_string<T>& str, RenderFlag flag)
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
void Render(const std::wstring&, RenderFlag = RENDER_CENTER);
void RenderPartiallColor(const std::wstring& str, size_t num, RenderFlag = RENDER_CENTER);
#endif // MYGLLIB_HPP
