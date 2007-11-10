#include <stdlib.h>    // For malloc() etc.
#include <stdio.h>    // For printf(), fopen() etc.
#include <math.h>    // For sin(), cos() etc.
#include <GL/glfw.h>   // For GLFW, OpenGL and GLU
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include "mylib.h"

using namespace std;
using namespace boost;

class word {
	wstring str;
	wstring input;
	public:
	word(const wchar_t*& ws)
		:str(ws)
	{
	}
	word(const wstring& ws)
		:str(ws)
	{
	}
	word()
	{
	}
	inline void backspace()
	{
		if(input.size()) input.resize(input.size()-1);
	}
	inline void add(wchar_t c)
	{
		input += c;
	}
	inline void print()
	{
		wcout << str << endl;
	}
	void printkana(KanaSet& set)
	{
		wcout << set.to_kana(input) << endl;
		return;
		wstring temp = input;
		//wcout << input << endl;
		wcout << temp << endl;
		for(unsigned int i = 1; i <= temp.size();i++)
		{
			wcout << wformat(L"%1% %2%") % i % temp.substr(0,i) << endl;
			KanaSet::kanaset_yomi_index& index = set.kanaset.get<by_yomi>();
			KanaSet::kanaset_yomi_index::iterator hoge = index.find(temp.substr(0,i));
			if(hoge != index.end()) {
				wcout << hoge->kana << endl;
				temp = temp.substr(i);
				i=1;
			}
			//wcout << (index.find(input.substr(0,i)))->kana << endl ;
	//		KanaSet::kanaset_yomi_index::iterator iter = index.if_find(str.substr(0,i));
//			wcout << iter->yomi << endl;
		}
	}
	inline void printinput()
	{
		wcout << input << endl;
	}

};
queue<wchar_t> global_queue;
bool flag = false;
double date = 0.0;
enum mode {
	MODE_TITLE,
	MODE_LOGO,
	MODE_GAME
};
//========================================================================
// Textures
//========================================================================

enum tex_enum { TEX_TITLE, TEX_MENU, TEX_WINNER1, TEX_WINNER2, TEX_FIELD };
//#define NUM_TEXTURES 6
#define NUM_TEXTURES 1

// Texture names
const char * tex_name[ NUM_TEXTURES ] = {
	//    "pong3d_title.tga",
	"sofmelogo.tga",
	//    "pong3d_menu.tga",
	//    "pong3d_instr.tga",
	//    "pong3d_winner1.tga",
	//    "pong3d_winner2.tga",
	//    "pong3d_field.tga"
};

// OpenGL texture object IDs
GLuint tex_id[ NUM_TEXTURES ];


void LoadTextures( void );

void GLFWCALL charinput( int character, int action )
{
	if(action == GLFW_PRESS) 
	{
		global_queue.push((wchar_t)character);
		//  settime();
	}
}

//----------------------------------------------------------------------
// Draw() - Main OpenGL drawing function that is called each frame
//----------------------------------------------------------------------

void Draw( KanaSet& set )
{

	int    width, height;  // Window dimensions
	double t;      // Time (in seconds)
	static word tanuki(wstring(L"ほげほげほげら"));
	while(!global_queue.empty()) { 
		tanuki.add(global_queue.front());
		global_queue.pop();
		//tanuki.printinput();
		tanuki.printkana(set);
	}

	//glEnable( GL_TEXTURE_2D );
	if(!flag &&glfwGetKey(GLFW_KEY_BACKSPACE)==GLFW_PRESS) { 
		flag = true;
		tanuki.backspace();

		tanuki.printkana(set);
		//  settime();
	}
	if(glfwGetKey(GLFW_KEY_BACKSPACE)==GLFW_RELEASE) {flag=false;}

	// Get current time
	t = glfwGetTime();

	// Get window size
	glfwGetWindowSize( &width, &height );

	// Make sure that height is non-zero to avoid division by zero
	height = height < 1 ? 1 : height;

	// Set viewport
	glViewport( 0, 0, width, height );

	// Clear color and depht buffers
	// glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClearColor( 1.0f, 1.0f, 1.0f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Set up projection matrix
	glMatrixMode( GL_PROJECTION );   // Select projection matrix
	glLoadIdentity();      // Start with an identity matrix
	gluPerspective(       // Set perspective view
			65.0,        // Field of view = 65 degrees
			(double)width/(double)height, // Window aspect (assumes square pixels)
			1.0,        // Near Z clipping plane
			100.0        // Far Z clippling plane
		      );

	// Set up modelview matrix
	glMatrixMode( GL_MODELVIEW );   // Select modelview matrix
	glLoadIdentity();      // Start with an identity matrix
	gluLookAt(        // Set camera position and orientation
			0.0, 0.0, 10.0,      // Camera position (x,y,z)
			0.0, 0.0, 0.0,      // View point (x,y,z)
			0.0, 1.0, 0.0      // Up-vector (x,y,z)
		 );

	// Here is where actual OpenGL rendering calls would begin...
	if(t < 6.0) glTranslated(.0,fabs(sin(6.28*t))/(t*t),-5/(t*t*t*t));

	glScalef(1.5f,1.5f,1.5f);
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, tex_id[ TEX_TITLE ] );
	glBegin(GL_QUADS);
	glTexCoord2f( 0.0f, 1.0f );
	glVertex2d(-8.0,1.0);
	glTexCoord2f( 1.0f, 1.0f );
	glVertex2d(8.0,1.0);
	glTexCoord2f( 1.0f, 0.0f );
	glVertex2d(8.0,-1.0);
	glTexCoord2f( 0.0f, 0.0f );
	glVertex2d(-8.0,-1.0);
	glEnd();
	glDisable( GL_TEXTURE_2D );


}


//----------------------------------------------------------------------
// main() - Program entry point
//----------------------------------------------------------------------

int main( int argc, char **argv )
{
	int    ok;      // Flag telling if the window was opened
	int    running;     // Flag telling if the program is running
	KanaSet set;
	setlocale(LC_ALL, "");
	initset("roma2hira.dat", set);
	
	
	{
		
		using namespace boost;
		/*
		{
			KanaSet::kanaset_fifo_index& index = set.kanaset.get<by_fifo>();
			BOOST_FOREACH( const KanaYomi& s, index )
				wcout << wformat(L"%1% %2%") % s.kana % s.yomi << endl;
		}
		{
			KanaSet::kanaset_kana_index& index = set.kanaset.get<by_kana>();
			BOOST_FOREACH( const KanaYomi& s, index )
				wcout << wformat(L"%1% %2%") % s.kana % s.yomi << endl;
		}
		{
			KanaSet::kanaset_yomi_index& index = set.kanaset.get<by_yomi>();
			BOOST_FOREACH( const KanaYomi& s, index )
				wcout << wformat(L"%1% %2%") % s.kana % s.yomi << endl;
		}
		*/
	}
	

	// Initialize GLFW
	glfwInit();

	// Open window
	ok = glfwOpenWindow(
			640, 480,     // Width and height of window
			8, 8, 8,     // Number of red, green, and blue bits for color buffer
			8,       // Number of bits for alpha buffer
			24,       // Number of bits for depth buffer (Z-buffer)
			0,       // Number of bits for stencil buffer
			GLFW_WINDOW     // We want a desktop window (could be GLFW_FULLSCREEN)
			);

	// If we could not open a window, exit now
	if( !ok )
	{
		glfwTerminate();
		return 0;
	}

	// Set window title
	glfwSetWindowTitle("My OpenGL program");

	glfwSetCharCallback(charinput);

	// Enable sticky keys
	glfwEnable(GLFW_STICKY_KEYS);

	LoadTextures();
	// Main rendering loop
	do
	{
		// Call our rendering function
		Draw(set);

		// Swap front and back buffers (we use a double buffered display)
		glfwSwapBuffers();

		// Check if the escape key was pressed, or if the window was closed
		running = !glfwGetKey( GLFW_KEY_ESC ) &&
			glfwGetWindowParam( GLFW_OPENED );
	}
	while( running );

	// Terminate GLFW
	glfwTerminate();

	// Exit program
	return 0;
}

void LoadTextures( void )
{
	int  i;

	// Generate texture objects
	glGenTextures( NUM_TEXTURES, tex_id );

	// Load textures
	for( i = 0; i < NUM_TEXTURES; i ++ )
	{
		// Select texture object
		glBindTexture( GL_TEXTURE_2D, tex_id[ i ] );

		// Set texture parameters
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		// Upload texture from file to texture memory
		glfwLoadTexture2D( tex_name[ i ], 0 );
	}
}

