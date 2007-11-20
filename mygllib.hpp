#ifndef MYGLLIB_HPP
#define MYGLLIB_HPP
#include <string>
#include <FTGL/FTFont.h>
#include <boost/shared_ptr.hpp>
enum render_flag {
	RENDER_LEFT,
	RENDER_CENTER,
	RENDER_RIGHT
};
void RenderText(FTFont*, const std::wstring&);
void Render(const boost::shared_ptr<FTFont>& , const std::wstring&, render_flag = RENDER_CENTER);
void RenderPartiallColor(const boost::shared_ptr<FTFont>& font, const std::wstring& str, size_t num, render_flag = RENDER_CENTER);
#endif // MYGLLIB_HPP
