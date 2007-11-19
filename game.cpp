#include "game.hpp"
#include "mylib.hpp"
#include <sys/timeb.h>
#include <iostream>
#include <FTGL/FTGLPolygonFont.h>
#include <FTGL/FTGLExtrdFont.h>
#include <boost/filesystem.hpp>
#define SIZE 1.0
#define DEPTH 0.2
#ifdef WIN32
#define _WIN32_IE 0x400
#include <shlobj.h>
#endif //WIN32
//#define FONT "/usr/share/fonts/WinFont/msgothic.ttc"
#define FONT "/usr/share/fonts/WinFont/msgothic.ttc"
#define FONTDIR "/usr/share/fonts/WinFont"
#define FONTNAME "msgothic.ttc"

//#define FONT "msgothic.ttc"
std::queue<int> game::event;
Input game::input;
boost::function<long (long)> game::random;
mode game::current;
boost::shared_ptr<FTFont> game::font;
boost::shared_ptr<FTFont> game::extrdfont;
void game::init()
{
	using namespace boost;
	using namespace boost::filesystem;
	std::string fontdir;
#ifdef WIN32
	TCHAR szPath[_MAX_PATH];
	SHGetSpecialFolderPath(NULL, szPath, CSIDL_FONTS, FALSE);
	fontdir = szPath;
	//std::cout << szPath<< std::endl;
	//convertWideCharToMultiByte((const wchar_t*)szPath, fontdir);
	//std::cout << fontdir << std::endl;
#else
	fontdir = FONTDIR;
#endif // WIN32
	path fontpath(fontdir);
	fontpath /= FONTNAME;
	std::cout << fontpath.string() << std::endl;
	if(!exists(fontpath)) {
		std::cout << "File " << fontpath.string() << " is not found." << std::endl;
		exit(1);
	}
	font = shared_ptr<FTFont>(new FTGLPolygonFont(fontpath.string().c_str()));
	extrdfont = shared_ptr<FTFont>(new FTGLExtrdFont(fontpath.string().c_str()));
	if(extrdfont->Error()) exit(1);                     // can't open font file
	if(!extrdfont->FaceSize(SIZE)) exit(1);             // can't set font size
	extrdfont->Depth(DEPTH);
	if(!extrdfont->CharMap(ft_encoding_unicode)) exit(1);// can't set charmap
	if(font->Error()) exit(1);                     // can't open font file
	if(!font->FaceSize(SIZE)) exit(1);             // can't set font size
	if(!font->CharMap(ft_encoding_unicode)) exit(1);// can't set charmap

}
bool game::event_is_empty()
{
	return event.empty();
}
void game::push_event(int i)
{
	event.push(i);
}
int game::pop_event()
{
	int i = event.front();
	event.pop();
	return i;
}
mode game::get_mode()
{
	return current;
}
void game::set_mode(mode next)
{
	using namespace boost;
	static mt19937 mt;
	timeb t;
	ftime(&t);
	mt.seed(t.millitm + t.time << (sizeof(t.millitm)*8));
	random = random_number_generator<mt19937>(mt);
	input.clear();
	glfwSetTime(0.0);
	glfwSetCharCallback(NULL);
	glfwSetKeyCallback(keyinput);
	switch(current = next) {
		case MODE_LOGO:
			break;
		case MODE_TITLE:
			//glfwSetCharCallback(charinput);
			glfwSetCharCallback(titleinput);
			break;
		case MODE_GAME:
			glfwSetCharCallback(charinput);
			break;
		default:
			break;
	}
}
void GLFWCALL keyinput( int key, int action )
{
	if(action == GLFW_PRESS)
	{
		switch(key) {
			case GLFW_KEY_F1:
				game::set_mode(MODE_LOGO);
				return;
				break;
			case GLFW_KEY_F2:
				game::set_mode(MODE_TITLE);
				return;
				break;
			case GLFW_KEY_F3:
				game::set_mode(MODE_GAME);
				return;
				break;
			case GLFW_KEY_ESC:
			case GLFW_KEY_BACKSPACE:
				if(game::get_mode()==MODE_GAME) {
					game::push_event(key);
				}
				return;
				break;
			case GLFW_KEY_ENTER:
				switch(game::get_mode()) {
					case MODE_LOGO:
						game::set_mode(MODE_TITLE);
						return;
						break;
					case MODE_TITLE:
						game::set_mode(MODE_GAME);
						return;
						break;
					case MODE_RESULT:
						game::set_mode(MODE_TITLE);
						return;
						break;
					default:
						break;
				}
			default:
				break;

		}
	}
}
void GLFWCALL titleinput( int character, int action )
{
			game::set_mode(MODE_GAME);
			return;
}
void GLFWCALL charinput( int character, int action )
{
	if(action == GLFW_PRESS) 
	{
		if(game::get_mode()==MODE_TITLE) {
			game::set_mode(MODE_GAME);
			return;
		}
		if(glfwGetKey(GLFW_KEY_LCTRL)==GLFW_PRESS ||
				glfwGetKey(GLFW_KEY_RCTRL)==GLFW_PRESS){
			switch(character) {
				case 'h':
					game::push_event(GLFW_KEY_BACKSPACE);
					return;
				case 'u':
					game::push_event(GLFW_KEY_ESC);
					return;
			}
		}
		game::push_event(character);
	}
}
