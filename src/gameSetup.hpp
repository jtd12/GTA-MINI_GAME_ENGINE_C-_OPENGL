#ifndef DEF_GAMESETUP_HPP
#define DEF_GAMESETUP_HPP
#include"common/objloader.hpp"
#include"common/skybox.h"
#include"common/gestionVehicules.hpp"
#include"common/decor.h"
#include"common/camera.h"
#include"common/robot.hpp"
#include"common/objloader.hpp"
#include"common/ocean.hpp"
#include"common/blurEffect.hpp"
#include<GL/gl.h>
#include<GL/glu.h>
#include<C:\library\freeglut\include\GL\freeglut.h>

class setup
{
	public:
		
	setup();
	~setup();
	void init();
	void keyboard(unsigned char key, int x, int y);
	void keyboardUP(unsigned char key, int x, int y);
	void timer(int value);
	void mouseMove(int mx,int my);
	void specialKey(int key, int x, int y);
	void mouseState(int button, int state, int x, int y);
	void update();
	void draw(int w,int h);
	void specialKeyUP(int key, int x, int y);
	void drawHud();
	void hud();
	void reshapeTextures(int w,int h);
	
	private:
		
	skybox *sky;
	gestionVehicules* gestion;
	decor * sol;
	camera * cam;
	robot *rb;
	objloader *obj;
	std::vector<decor *> levels;
	std::vector<ocean*> water;
	blurMotion* blur;
	vector3d posBlur;
	textures texture;
	GLuint hudTex;
};

#endif

