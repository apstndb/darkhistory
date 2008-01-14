#include "darkhistory.hpp"
#ifdef WIN32
#include <windows.h>
int WINAPI WinMain( HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nCmdShow
		)
{
	return mymain();
}
#else
int main(int argc, char** argv)
{
	return mymain();
}
#endif
