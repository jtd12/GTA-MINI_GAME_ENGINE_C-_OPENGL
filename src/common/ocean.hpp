#ifndef DEF_OCEAN_HPP
#define DEF_OCEAN_HPP
#define TAILLE 256
#include <gl/gl.h>
#include<gl/glu.h>
#include<C:\library\freeglut\include\GL\freeglut.h>
#include<vector>
#include<cmath>
#include"vector.h"
#include"texture.hpp"

class ocean
{
	public:
		ocean();
		~ocean();
		void GenerateInitGrid();
		void update(float time);
		void animateHeightMap(float time);
		void updateOceanVertices(float deltaTime);
		void draw();
		void loadTexture(const char* filename);
		void isModePlein(bool s);
		void isModeLines(bool s); 
		
	private:
		float speed;
		float vertices[TAILLE][TAILLE][3]; // Store x, y, z coordinates of each vertex
// FFT generated height map
		double heightMap[TAILLE][TAILLE]; // FFT will populate this with wave heights
		float textureCoords[TAILLE][TAILLE][2];  // Texture coordinates for each vertex
		GLuint texture;
		textures* tex;
		bool modePlein;
		bool modeLines;
};

#endif
