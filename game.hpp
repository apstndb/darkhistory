#include <GL/glfw.h>
#include <boost/shared_ptr.hpp>
#include <boost/random.hpp>
#include <boost/function.hpp>
#include <FTGL/FTFont.h>
#include <queue>
#include "input.hpp"
void GLFWCALL keyinput( int, int );
void GLFWCALL charinput( int, int );
void GLFWCALL titleinput( int, int );
enum mode {
	MODE_LOGO,
	MODE_TITLE,
	MODE_GAME,
	MODE_RESULT
};
class game {
	static std::queue<int> event;
	static mode current;
	public:
	static Input input;
	static boost::function<long (long)> random;
	static boost::shared_ptr<FTFont> font;
	static boost::shared_ptr<FTFont> extrdfont;
	static bool event_is_empty();
	static void set_mode(mode next);
	static mode get_mode();
	static void push_event(int);
	static int pop_event();
	static void init();
};
