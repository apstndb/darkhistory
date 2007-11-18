#include <GL/glfw.h>
#include <boost/shared_ptr.hpp>
#include <FTGL/FTFont.h>
#include <queue>
void GLFWCALL keyinput( int, int );
void GLFWCALL charinput( int, int );
enum mode {
	MODE_LOGO,
	MODE_TITLE,
	MODE_GAME
};
class game {
	static std::queue<int> event;
	static mode current;
	public:
	static boost::shared_ptr<FTFont> font;
	static bool event_is_empty();
	static void set_mode(mode next);
	static mode get_mode();
	static void push_event(int);
	static int pop_event();
};
