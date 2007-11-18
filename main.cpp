//#include <stdlib.h>    // For malloc() etc.
//#include <stdio.h>    // For printf(), fopen() etc.
#include <cmath>    // For sin(), cos() etc.
#include <GL/glfw.h>   // For GLFW, OpenGL and GLU
//#include <iostream>
//#include <vector>
//#include <string>
//#include <queue>
//#include <boost/foreach.hpp>
//#include <boost/format.hpp>
//#include <boost/assign.hpp>
#include <FTGL/FTGLExtrdFont.h>
//#include <FTGL/FTGLPolygonFont.h>
#include "mylib.h"
#include "mygllib.h"
#include "input.hpp"
#include "kanaset.hpp"
#include "game.hpp"

//#define SIZE 1.0
//#define DEPTH 0.2
//#define FONT "/usr/share/fonts/WinFont/msgothic.ttc"
using namespace std;
using namespace boost;

void setUpLighting()
{
	// Set up lighting.
	float light1_ambient[4]  = { 1.0, 1.0, 1.0, 1.0 };
	float light1_diffuse[4]  = { 1.0, 0.9, 0.9, 1.0 };
	float light1_specular[4] = { 1.0, 0.7, 0.7, 1.0 };
	float light1_position[4] = { -1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT,  light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glEnable(GL_LIGHT1);

	float light2_ambient[4]  = { 0.2, 0.2, 0.2, 1.0 };
	float light2_diffuse[4]  = { 0.9, 0.9, 0.9, 1.0 };
	float light2_specular[4] = { 0.7, 0.7, 0.7, 1.0 };
	float light2_position[4] = { 1.0, -1.0, -1.0, 0.0 };
	glLightfv(GL_LIGHT2, GL_AMBIENT,  light2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE,  light2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	// glEnable(GL_LIGHT2);

	float front_emission[4] = { 0.3, 0.2, 0.1, 0.0 };
	float front_ambient[4]  = { 0.2, 0.2, 0.2, 0.0 };
	float front_diffuse[4]  = { 0.95, 0.95, 0.8, 0.0 };
	float front_specular[4] = { 0.6, 0.6, 0.6, 0.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, front_emission);
	glMaterialfv(GL_FRONT, GL_AMBIENT, front_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, front_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, front_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 16.0);
	glColor4fv(front_diffuse);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
}

//========================================================================
// Textures
//========================================================================

enum tex_enum { TEX_TITLE, TEX_MENU, TEX_WINNER1, TEX_WINNER2, TEX_FIELD };
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


//----------------------------------------------------------------------
// Draw() - Main OpenGL drawing function that is called each frame
//----------------------------------------------------------------------

//void Draw( KanaSet* set ,FTFont* font)
void Draw( KanaSet* set)
{

	int    width, height;  // Window dimensions
	double t;      // Time (in seconds)
	static input tanuki;
	while(!game::event_is_empty()) { 
		tanuki(game::pop_event());
		tanuki.regen_kana(set);

		//wcout << tanuki.get_kana() << endl;
	}


	// Get current time
	t = glfwGetTime();

	// Get window size
	glfwGetWindowSize( &width, &height );

	// Make sure that height is non-zero to avoid division by zero
	height = height < 1 ? 1 : height;

	// Set viewport
	glViewport( 0, 0, width, height );

	// Clear color and depht buffers
	switch(game::get_mode()) {
		case MODE_LOGO:
			glClearColor( 1.0f, 1.0f, 1.0f, 0.0f );
			break;
		case MODE_TITLE:
			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			break;
		case MODE_GAME:
			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			break;
		default:
			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			break;
	}
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
	switch(game::get_mode()) {
		case MODE_LOGO:
			glDisable(GL_LIGHTING);
			glDisable(GL_COLOR_MATERIAL);
			glDisable(GL_LIGHT1);
			if(t < 6.0) glTranslated(.0,fabs(sin(6.28*t))/(t*t),-3/(t*t*t*t));

			glScalef(1.5f,1.5f,1.5f);
			glColor4f(1.0, 1.0, 1.0, 0.0);
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
			break;
		case MODE_TITLE:
			setUpLighting();
			//game::font->FaceSize(1.0);
			glRotatef(t*360 ,0.0, 1.0, 0.0);
			glTranslatef(-game::font->Advance(L"タイピング黒歴史")/2, .0f, .0f);
			//RenderText(game::font, L"タイピング黒歴史" );
			//RenderText(game::font, L"タイピング黒歴史" );
			//RenderText(game::font, L"タイピング黒歴史" );
			game::font->Render(L"タイピング黒歴史");
			//font->FaceSize(SIZE);
			break;

		case MODE_GAME:
			setUpLighting();
			//glTranslatef(-8.0f, 5.0f, 0.0f);
			glTranslatef(-game::font->Advance(tanuki.get_kana().c_str())/2, .0f, -5.0f);
			game::font->Render(tanuki.get_kana().c_str());
			//RenderText(game::font, tanuki.get_kana() );
			break;
		default:
			break;
	}


}


//----------------------------------------------------------------------
// main() - Program entry point
//----------------------------------------------------------------------

int main( int argc, char **argv )
{
	//vector<string> tex_name_v = assign::list_of("sofmelogo.tga");
	int    ok;      // Flag telling if the window was opened
	int    running;     // Flag telling if the program is running
//	FTFont *font;
//	font = new FTGLExtrdFont(FONT);
//	//font = new FTGLPolygonFont(FONT);
//	if (font->Error()) exit(1);			// can't open font file
//	if (!font->FaceSize(SIZE)) exit(1);		// can't set font size
//	font->Depth(DEPTH);
//	if (!font->CharMap(ft_encoding_unicode)) exit(1);// can't set charmap 
	setlocale(LC_ALL, "");
	KanaSet set("roma2hira.dat");


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

	//glfwSetCharCallback(charinput);
	game::set_mode(MODE_LOGO);

	// Enable sticky keys
	//glfwEnable(GLFW_STICKY_KEYS);
	glfwDisable(GLFW_KEY_REPEAT);

	//	glEnable(GL_CULL_FACE);

	LoadTextures();
	// Main rendering loop
	do
	{
		// Call our rendering function
		Draw(&set);

		// Swap front and back buffers (we use a double buffered display)
		glfwSwapBuffers();

		// Check if the escape key was pressed, or if the window was closed
		running = glfwGetWindowParam( GLFW_OPENED );
		//running = !glfwGetKey( GLFW_KEY_ESC ) &&
		//	glfwGetWindowParam( GLFW_OPENED );
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

