#include"decor.h"

decor::decor(const char* c,unsigned int map , std::vector<collisionplane>& cplane, std::vector<vector3d>& sp)
{
	cp=cplane;
	spawnpoints=sp;
	name=c;
	mesh=map;
	
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
	glCallList(mesh);
	glPopMatrix();
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

