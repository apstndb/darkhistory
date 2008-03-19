#include "input.hpp"
#include "kanaset.hpp"
#include <GL/glfw.h>
void Input::operator()(int c)
{
	switch(c) {
		case GLFW_KEY_BACKSPACE:
			backspace();
			break;
		case GLFW_KEY_ESC:
			clear();
			break;
		default:
			*buffer += static_cast<wchar_t>(c);
			break;
	}
}
void Input::regen_kana(KanaSet* set)
{
	*kana=set->to_kana(*buffer);
}
const size_t Input::size() const
{
	return Input::buffer->size();
}
void Input::clear()
{
	buffer->clear();
	kana->clear();
}
void Input::backspace()
{
	if(buffer->size()) buffer->resize(buffer->size()-1);
}
Input::Input()
	: buffer(new std::wstring), kana(new std::wstring)
{
}
Input::~Input()
{
	delete buffer;
	delete kana;
}
