#ifndef DEF_DECOR_H
#define DEF_DECOR_H
#include"vector.h"
#include<vector>
#include"collisionplane.h"
#include<GL/gl.h>
#include<GL/glu.h>

class decor
{
	public:
		decor(const char* c,unsigned int map , std::vector<collisionplane>& cplane, std::vector<vector3d>& sp);
		~decor();
		void update();
		void draw();
		std::vector<collisionplane>& getCollisionPlanes();
		std::string& getName();
  		void change(const char* c,unsigned int map , std::vector<collisionplane>& cplane, std::vector<vector3d>& sp);
 		std::vector<vector3d>& getSpawnPoints();
		void isModePlein(bool s);
		void isModeLines(bool s);  
		
	private:
		int mesh;
		std::vector<collisionplane> cp;
		std::vector<vector3d> spawnpoints;
		std::string name;
		bool modePlein;
		bool modeLines;
	
};
#endif
