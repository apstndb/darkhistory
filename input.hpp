#include <string>
#include <GL/glfw.h>
#include "kanaset.hpp"
class input {
	std::wstring buffer;
	std::wstring kana;
	public:
	input()
	{
	}
	inline void backspace()
	{
		if(buffer.size()) buffer.resize(buffer.size()-1);
	}
	inline void clear()
	{
		buffer.clear();
	}

	inline void operator()(int c)
	{
		switch(c) {
			case GLFW_KEY_BACKSPACE:
				backspace();
				break;
			case GLFW_KEY_ESC:
				clear();
				break;
			default:
				buffer += static_cast<wchar_t>(c);
				break;
		}
	}
	inline void regen_kana(KanaSet* set)
	{
		kana=set->to_kana(buffer);
	}
	inline const std::wstring& get_kana() const
	{
		return kana;
	};

};

