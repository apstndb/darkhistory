#ifndef MYGLLIB_HPP
#define MYGLLIB_HPP
//#include <string>
#include <GL/gl.h>
#include <vector>
enum RenderFlag {
	RENDER_LEFT,
	RENDER_CENTER,
	RENDER_RIGHT
};
std::vector<GLfloat> baselines(const wchar_t* str);
GLfloat advance(const wchar_t* str);
void adjust(const wchar_t* str);
void align(const wchar_t* str, RenderFlag flag);
void Render(const wchar_t*, RenderFlag = RENDER_CENTER);
void RenderPartiallColor(const wchar_t* str, size_t num, RenderFlag = RENDER_CENTER);
#endif // MYGLLIB_HPP
