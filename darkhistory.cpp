#include <clocale>
#include <cmath>    // For sin(), cos() etc.
#include <GL/glfw.h>   // For GLFW, OpenGL and GLU
#include <GL/glc.h>   // For GLFW, OpenGL and GLU
#include <boost/format.hpp>
#include "mylib.hpp"
#include "mygllib.hpp"
#include "kanaset.hpp"
#include "game.hpp"
#include "input.hpp"
#include "darkhistory.hpp"

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

enum tex_enum { TEX_TITLE };
#define NUM_TEXTURES 1

// Texture names

const char* tex_name[ NUM_TEXTURES ] = { "sofmelogo.tga" };

// OpenGL texture object IDs
GLuint tex_id[ NUM_TEXTURES ];


void LoadTextures( void );


//----------------------------------------------------------------------
// Draw() - Main OpenGL drawing function that is called each frame
//----------------------------------------------------------------------

void Draw( KanaSet* set, KanaSet* hatena)
{

	int    width, height;  // Window dimensions
	double t;      // Time (in seconds)


	// Get current time
	t = glfwGetTime();


	// Get window size
	glfwGetWindowSize( &width, &height );

	// Make sure that height is non-zero to avoid division by zero
	height = height < 1 ? 1 : height;

	// Set viewport
	glViewport( 0, 0, width, height );

	// Clear color and depht buffers
	switch (game::get_mode()) {
		case MODE_LOGO:
			glClearColor( 1.0f, 1.0f, 1.0f, 0.0f );
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
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT1);
	glColor3f(1.0, 1.0, 1.0);

	// Here is where actual OpenGL rendering calls would begin...
	switch (game::get_mode()) {
		case MODE_LOGO:
			if (t < 5.0) {
				glTranslated(.0,fabs(sin(6.28*t))/(t*t),-3/(t*t*t*t));
			} else if (t > 6.0) {
				game::set_mode(MODE_TITLE);
				return;
			}

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

			break;
		case MODE_TITLE:
			setUpLighting();
			glPushMatrix();
			if (t < 4.0) {
				glTranslatef(.0, .0, -1/(t*t*t*t));
				glRotatef(180/(t*t*t*t*t) ,0.0, 0.0, 1.0);
			}
			glScalef(1.5, 1.5, 1.5);
			Render(L"タイピング黒歴史");
			glPopMatrix();
			if (t > 2.0) {
				glPushMatrix();
				glTranslatef(.0, -3.0, .0);
				glRotatef(30*sin(t) ,0.0, 1.0, 0.0);
				Render(L"hit any key");
				glPopMatrix();
			}
			break;

		case MODE_GAME:
			static KanaYomi current_word;
			while (!game::event_is_empty()) {
				game::input(game::pop_event());
				game::input.regen_kana(set);

			}
			if (60 < t) {
				game::score.letter+=matchLength(current_word.yomi.c_str(), game::input.get_kana().c_str());
				game::set_mode(MODE_RESULT);
				game::flag = true;
			}
			if (current_word.yomi == game::input.get_kana()) {
				game::score.word++;
				game::score.letter+=current_word.yomi.size();
				game::flag = true;
			}
			if (game::flag) {
				game::input.clear();
				current_word = hatena->kanaset[ game::random(hatena->kanaset.size()) ];
				game::flag = false;
			}
			glPushMatrix();
			glTranslatef(.0,-5.0,.0);
			Render(L"BackSpace: 一文字削除、Enter: クリア、Space: スキップ");
			glPopMatrix();
			glPushMatrix();
			glTranslatef(5.0, 5.0, .0);
			Render(str(wformat(L"%1$ .2f")%(60-t)).c_str());
			glPopMatrix();
			glPushMatrix();
			glTranslatef( .0f, 2.5, .0);
			Render(current_word.kana.c_str());
			glTranslatef( .0, -2.5, .0);
			Render(current_word.yomi.c_str());
			glTranslatef( .0, -2.5, .0);
			RenderPartiallColor(game::input.get_kana().c_str(),
					matchLength(current_word.yomi.c_str(), game::input.get_kana().c_str()));
			glPopMatrix();
			break;
		case MODE_RESULT:
			glPushMatrix();
			glTranslatef(.0,-5.0,.0);
			Render(L"Enter: タイトル画面に戻る");
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0, 3, 0);
			Render(str(wformat(L"入力した単語数 %1%") % game::score.word).c_str());
			glTranslatef(0, -3, 0);
			Render(str(wformat(L"正しく入力されたかな数 %1%") % game::score.letter).c_str());
			glTranslatef(0, -3, 0);
			Render(str(wformat(L"入力速度 %1% かな/秒") % (game::score.letter / 60.0)).c_str());
			glPopMatrix();
			break;
		default:
			break;
	}


}


//----------------------------------------------------------------------
// main() - Program entry point
//----------------------------------------------------------------------

int mymain()
{
	int    ok;      // Flag telling if the window was opened
	int    running;     // Flag telling if the program is running
	setlocale(LC_ALL, "");
	KanaSet set("roma2hira.txt");
	KanaSet hatena("word.txt");
	FILE *fp = fopen("fullscreen", "r");
	bool fs = fp!=NULL;
	if (fs) fclose(fp);
	// Initialize GLFW
	glfwInit();
	// Open window
	ok = glfwOpenWindow(
			fs?1024:640, fs?768:480,     // Width and height of window
			8, 8, 8,     // Number of red, green, and blue bits for color buffer
			8,       // Number of bits for alpha buffer
			24,       // Number of bits for depth buffer (Z-buffer)
			0,       // Number of bits for stencil buffer
			//			GLFW_WINDOW     // We want a desktop window (could be GLFW_FULLSCREEN)
			fs?GLFW_FULLSCREEN:GLFW_WINDOW
			);

	// If we could not open a window, exit now
	if ( !ok )
	{
		glfwTerminate();
		return 0;
	}

	// Set window title
	glfwSetWindowTitle("The Dark History");

	game::set_mode(MODE_LOGO);

	// Enable sticky keys
	glfwDisable(GLFW_KEY_REPEAT);

	LoadTextures();
	GLint ctx = glcGenContext();
	glcContext(ctx);
#ifdef WIN32
	glcStringType(GLC_UCS2);
#else
	glcStringType(GLC_UCS4);
#endif //!WIN32
	glcRenderStyle(GLC_TRIANGLE);
	game::init();
	// Main rendering loop
	do
	{
		// Call our rendering function
		Draw(&set, &hatena);

		// Swap front and back buffers (we use a double buffered display)
		glfwSwapBuffers();

		// Check if the escape key was pressed, or if the window was closed
		running = !glfwGetKey( GLFW_KEY_ESC ) &&
			glfwGetWindowParam( GLFW_OPENED );
	}
	while ( running );

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
	for ( i = 0; i < NUM_TEXTURES; i ++ )
	{
		// Select texture object
		glBindTexture( GL_TEXTURE_2D, tex_id[ i ] );

		// Set texture parameters
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		// Upload texture from file to texture memory
		glfwLoadTexture2D( tex_name[i], 0 );
	}
}

