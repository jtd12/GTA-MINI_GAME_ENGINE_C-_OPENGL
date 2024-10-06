#include"blurEffect.hpp"


blurMotion::blurMotion()
{
//	initializeTexture();
	offset=0.0f;
	
}


blurMotion::~blurMotion()
{
	
}


void blurMotion::initializeTexture(int width, int height) {
    // Generate a texture to store the scene
    glGenTextures(1, &sceneTexture);
    glBindTexture(GL_TEXTURE_2D, sceneTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void blurMotion::copySceneToTexture(int width, int height) {
    // Copy the framebuffer content into the texture
    glBindTexture(GL_TEXTURE_2D, sceneTexture);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, width, height);
}

void blurMotion::blurTextureHorizontal(int passes) {
	glPushMatrix();
	glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glBindTexture(GL_TEXTURE_2D, sceneTexture);
	glColor4f(1.0f, 0.7f, 0.7f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE); 
    for (int i = 0; i < passes; ++i) {
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f + offset+100, 0.0f);glVertex3i(-1,-1,1);
        glTexCoord2f(1.0f + offset+100, 0.0f); glVertex3i(+1,-1,1);
        glTexCoord2f(1.0f + offset+100, 1.0f); glVertex3i(+1,+1,1); 
        glTexCoord2f(0.0f + offset+100, 1.0f); glVertex3i(-1,+1,1);
        glEnd();
  
    }
	glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glPopMatrix();
}

void blurMotion::blurGlowTexture() {
    int blurSize = 5;  // Adjust blur size to control strength
    float blurAmount = 1.0f;

    // Horizontal blur
    for (int i = -blurSize; i <= blurSize; ++i) {
        glPushMatrix();
        glTranslatef((i * blurAmount)+5, 0, 0);
        blurTextureHorizontal(5.0f);
        glPopMatrix();
    }

    // Vertical blur
    for (int j = -blurSize; j <= blurSize; ++j) {
        glPushMatrix();
        glTranslatef(0, j * blurAmount, 0);
        blurTextureVertical(5.0f);
        glPopMatrix();
    }
}

void blurMotion::update(float speed)
{
	 offset += speed;
	 if(offset>80000)
	 {
	 	offset=80000;
	 }
	 
	 if(offset<=0)
	 {
	 	offset=0;
	 }
}


void blurMotion::blurTextureVertical(int passes) {
		glPushMatrix();
		glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glBindTexture(GL_TEXTURE_2D, sceneTexture);
  
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE); 
	glColor4f(1.0f, 0.7f, 0.7f, 1.0f);
    for (int i = 0; i < passes; ++i) {
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f + offset+100); glVertex3i(-1,-1,1);
        glTexCoord2f(1.0f, 0.0f + offset+100); glVertex3i(+1,-1,1);
        glTexCoord2f(1.0f, 1.0f + offset+100);glVertex3i(+1,+1,1); 
        glTexCoord2f(0.0f, 1.0f + offset+100); glVertex3i(-1,+1,1);
        glEnd();
       
    }
	glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
        glPopMatrix();
}


