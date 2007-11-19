#ifndef MYGLLIB_HPP
#define MYGLLIB_HPP
#include <string>
#include <FTGL/FTFont.h>
#include <boost/shared_ptr.hpp>
void RenderText(FTFont*, const std::wstring&);
void Render(const boost::shared_ptr<FTFont>& , const std::wstring&);
#endif // MYGLLIB_HPP
