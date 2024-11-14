#include"decor.h"

decor::decor(const char* c,unsigned int map , std::vector<collisionplane>& cplane, std::vector<vector3d>& sp)
{
	cp=cplane;
	spawnpoints=sp;
	name=c;
	mesh=map;
	modePlein=true;
	modeLines=false;
	
}
decor::~decor()
{

}
void decor::update()
{

} 
void decor::draw()
{
	glPushMatrix();	
	if(modeLines)
	  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if(modePlein)
	  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(mesh);
	glPopMatrix();
}

void decor::isModePlein(bool s)
{
	 modePlein=s;
}
void decor::isModeLines(bool s)
{
	 modeLines=s;
}

std::vector<collisionplane>& decor::getCollisionPlanes()
	{
		return cp;
	}
	std::string& decor::getName()
	{
		return name;
	}
	void decor::change(const char* c,unsigned int map , std::vector<collisionplane>& cplane, std::vector<vector3d>& sp)
	{
	mesh=map;
	cp=cplane;
	spawnpoints=sp;
	name=c;
	}
	std::vector<vector3d>& decor::getSpawnPoints()
	{
		return spawnpoints;
	}

