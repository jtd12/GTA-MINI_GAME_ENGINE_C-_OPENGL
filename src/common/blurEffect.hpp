#ifndef DEF_BLUR_EFFECT_HPP
#define DEF_BLUR_EFFECT_HPP
#include<GL/gl.h>
#include<GL/glu.h>
#include<C:\library\freeglut\include\GL\freeglut.h>

class blurMotion
{
	public:
		blurMotion();
		~blurMotion();
		void initializeTexture(int width, int height);
		void copySceneToTexture(int width, int height);
		void blurTextureVertical(int passes);
		void blurTextureHorizontal(int passes);
		void update(float speed);
		void blurGlowTexture();
	
	private:
		GLuint sceneTexture;
		float offset;
};

#endif
