#ifndef DEF_ROBOT_HPP
#define DEF_ROBOT_HPP
#include<C:\library\freeglut\include\GL\freeglut.h>
#include<vector>
#include<cmath>
#include"vector.h"
#include"blurEffect.hpp"
#include"C:\library\mathsutils\include\collisionplane.h"
#include"C:\library\mathsutils\include\collisionsphere.h"
#include"C:\library\mathsutils\include\collision.h"
#include"car.h"
#include"menu.hpp"

class robot
{
	
	public:
		robot(collisionsphere ccs);
		~robot();
		void drawRobot(vehicule * car);
		void drawArm(float side);
		void drawLeg(float side);
		void updateMovement(int value, bool control,blurMotion* motionBB);
		void update(int value,int a);
		void handleKeyPress(unsigned int key, int x, int y);
		void handleKeyPressUP(unsigned int key, int x, int y);
		void resetMovement(int a);
		void entrerVehicule(vehicule * car);
		bool getExit();
		vector3d getLocation();
		bool collisionAABB( robot& rb,  vehicule& voiture);
		void collisions(robot *rb,vehicule *voiture,std::vector<collisionplane>& collplane);
		void keyboard(unsigned char key, int x, int y);
		void keyboardUP(unsigned char key, int x, int y);
		void handleJump();
		void updateCollision(std::vector<collisionplane>& collplane);
		void updateCollisionMurs(std::vector<collisionplane>& collplane,robot* rb,vehicule* voiture);
		void setLocation(vector3d location);
		void setPosition(vector3d pos);
		vector3d getScale();

		
	private:
		float angle;
		bool up,down,left,right;
		float rotation;
		float walkSpeed;
		bool control;
		bool enter;
		bool exit;
		bool collision;
		bool collision2;
		float delay;
		bool fermeturePorte;
		float robotYPosition;  // Initial position (ground level)
		float robotYVelocity;  // Vertical velocity (0 at rest)
		float gravity;        // Gravity pulling the robot down
		float jumpForce;      // Initial velocity when the robot jumps
		bool isJumping;       // Is the robot currently jumping?
		bool onGround;         // Is the robot on the ground?
		bool space;
		float sprintSpeed;
		bool sprintKey;
		vector3d force;
		vector3d dir;
		collisionsphere cs;
		bool isground;
		vector3d newPos;
		vector3d scale;
		float speed;
		bool collid;
		
	
	

};

#endif
