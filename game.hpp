#include <boost/function.hpp>
#include <queue>
class Input;
struct Score {
	int hit;
	int letter;
	int word;
	Score()
		:hit(0), letter(0), word(0)
	{}
};

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
	static Score score;
	static bool ctrl;
	static bool flag;
	static boost::function<long (long)> random;
	static bool event_is_empty();
	static void set_mode(mode next);
	static mode get_mode();
	static void push_event(int);
	static int pop_event();
	static void init();
};
