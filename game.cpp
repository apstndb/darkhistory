#include "game.hpp"
#include <FTGL/FTGLExtrdFont.h>
#define SIZE 1.0
#define DEPTH 0.2
#define FONT "/usr/share/fonts/WinFont/msgothic.ttc"
std::queue<int> game::event;
mode game::current;
boost::shared_ptr<FTFont> game::font;
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
	font = boost::shared_ptr<FTFont>(new FTGLExtrdFont(FONT));
	//font = new FTGLPolygonFont(FONT);
	if(font->Error()) exit(1);                     // can't open font file
	if(!font->FaceSize(SIZE)) exit(1);             // can't set font size
	font->Depth(DEPTH);
	if(!font->CharMap(ft_encoding_unicode)) exit(1);// can't set charmap
	glfwSetTime(0.0);
	glfwSetCharCallback(charinput);
	glfwSetKeyCallback(keyinput);
	switch(current = next) {
		case MODE_LOGO:
			break;
		case MODE_TITLE:
			break;
		case MODE_GAME:
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
			case GLFW_KEY_TAB:
				break;
			case GLFW_KEY_ESC:
				game::push_event(key);
				break;
			case GLFW_KEY_F1:
				//game::push_event(key);
				game::set_mode(MODE_LOGO);
				break;
			case GLFW_KEY_F2:
				//game::push_event(key);
				game::set_mode(MODE_TITLE);
				break;
			case GLFW_KEY_F3:
				//game::push_event(key);
				game::set_mode(MODE_GAME);
				break;
			case GLFW_KEY_BACKSPACE:
				game::push_event(key);
				break;
			default:
				break;
		}
	}
}
void GLFWCALL charinput( int character, int action )
{
	if(action == GLFW_PRESS) 
	{
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
