#include <string>
#include <GL/glfw.h>
#include "kanaset.hpp"
class Input {

	std::wstring buffer;
	std::wstring kana;
	bool lock_;
	public:
	Input()
	{
	}
	inline void lock() {lock_ = true;}
	inline void unlock() {lock_ = false;}
	inline bool is_lock() {return lock_; }
	inline void backspace()
	{
		if(is_lock()) return;
		if(buffer.size()) buffer.resize(buffer.size()-1);
	}
	inline void clear()
	{
		if(is_lock()) return;
		buffer.clear();
		kana.clear();
	}

	inline void operator()(int c)
	{
		if(is_lock()) return;
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

