#include "game.hpp"
#include "mylib.hpp"
#include <sys/timeb.h>
#include <iostream>
#include <GL/glc.h>
#ifdef WIN32
#define _WIN32_IE 0x400
#include <shlobj.h>
#endif //WIN32

std::queue<int> game::event;
Score game::score;
Input game::input;
boost::function<long (long)> game::random;
mode game::current;
bool game::ctrl;
bool game::flag=false;
void game::init()
{
#ifdef WIN32
	TCHAR fontdir[_MAX_PATH];
	SHGetSpecialFolderPath(NULL, fontdir, CSIDL_FONTS, FALSE);
	glcAppendCatalog(fontdir);
#endif // WIN32
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
			score = Score();
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
#ifdef MY_DEBUG
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
			case GLFW_KEY_F4:
				game::set_mode(MODE_RESULT);
				return;
				break;
#endif // MY_DEBUG
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
					case MODE_GAME:
						game::push_event(GLFW_KEY_ESC);

						return;
						break;
					default:
						break;
				}
			case GLFW_KEY_SPACE:
				if(game::get_mode()==MODE_GAME) game::flag=true;
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
				glfwGetKey(GLFW_KEY_RCTRL)==GLFW_PRESS) {
			switch(character) {
				case 'h':
				case 'H':
					game::push_event(GLFW_KEY_BACKSPACE);
					return;
				case 'u':
				case 'U':
					game::push_event(GLFW_KEY_ESC);
					return;
				default:
					break;
			}
		}
		game::push_event(character);
		game::score.hit++;
	}
}
