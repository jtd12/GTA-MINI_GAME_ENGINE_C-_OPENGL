#include"gameSetup.hpp"
#include<GL/gl.h>
#include<GL/glu.h>
#include"C:\library\freeglut\include\GL\freeglut.h"
#define LARGEUR 960
#define HAUTEUR 540

int windowWidth = 960, windowHeight = 540;
float fov = 45.0f;  // Initial field of view
void timer(int value);
void display();
void init();
void mouseMove(int mx,int my);
void changeSize(int w, int h);
void keyboard(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void specialKeyUP(int key, int x, int y);
void mouseState(int button, int state, int x, int y);
void keyboardUP(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

int windowsName;
setup* game;

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(LARGEUR,HAUTEUR);
	glutInitWindowPosition(100,100); 
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH | GLUT_STENCIL);
	windowsName=glutCreateWindow("GTA STYLE Game Engine OpenGL 2.0");
	init();
	createMenu();
	glutDisplayFunc(display);
	glutMouseFunc(mouseState);
	glutMotionFunc(mouseMove);
	glutMouseWheelFunc(mouse);
	glutReshapeFunc(changeSize);
	glutSpecialFunc(specialKey);
	glutSpecialUpFunc(specialKeyUP);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUP);
	glutTimerFunc(16, timer, 0);
	glutMainLoop();
	delete game;
	return 0;
}

void timer(int value)
{
	game->timer(value);
	glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void changeSize(int w, int h) {
	windowWidth=w;
	windowHeight=h;

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix


	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(200,0,200,0);
	gluPerspective(fov,(float)w/(float)h,1.0,150000.0);
	glMatrixMode(GL_MODELVIEW);

          
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	float col[]={1.0,1.0,1.0,1.0};
	glLightfv(GL_LIGHT0,GL_DIFFUSE,col);
	game->reshapeTextures( w, h);

}

void init()
{
	glClearColor(0.9,0.9,0.9,0.9);

	
	game=new setup();

	

}


void mouse(int button, int dir, int x, int y)
{
   // Wheel reports as button 3(scroll up) and button 4(scroll down)
 if(dir>0)
 {
 	  fov -= 2.0f;  // Zoom in (scroll up)
        if (fov < 10.0f) {
            fov = 10.0f;  // Clamp the FOV to prevent extreme zoom
        }
 }
 else
 {
 	  fov += 2.0f;  // Zoom out (scroll down)
        if (fov > 90.0f) {
            fov = 90.0f;  // Clamp the FOV to prevent extreme zoom out
        }
 }
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, (float)windowWidth / (float)windowHeight, 0.1f, 50000.0f);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();  // Request a redraw

}

void mouseMove(int mx,int my)
{
	game->mouseMove(mx,my);
}
void keyboard(unsigned char key, int x, int y)
{
	game->keyboard(key,x,y);
}

void keyboardUP(unsigned char key, int x, int y)
{
	game->keyboardUP(key,x,y);
}


void mouseState(int button, int state, int x, int y)
{
	game->mouseState( button,  state,  x,  y);
}
void specialKey(int key, int x, int y)
{
	game->specialKey(key,x,y);
}
void specialKeyUP(int key, int x, int y)
{
		game->specialKeyUP(key,x,y);
}
void display()
{
	game->update();
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();
	float pos[]={-1.0,80.0,1.0,1.1};
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	//gluLookAt(0,15,20,0,0,0,0,1,0);
	game->draw(windowWidth,windowHeight);
	
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}


