#ifndef DEF_CAR_H
#define DEF_CAR_H
#include"objloader.hpp"
#include"particule.hpp"
#include"blurEffect.hpp"
#include"C:\library\mathsutils\include\collisionplane.h"
#include"C:\library\mathsutils\include\collisionsphere.h"
#include"C:\library\mathsutils\include\collision.h"
#include<C:\library\freeglut\include\GL\freeglut.h>
#include<vector>
#define SPACEBAR 32

	
const float CAR_MASS = 2000.0f;
const float MAX_SPEED = 700;
const float ACCELERATION = 20.0f;
const float MAX_BRAKING_FORCE = 700.0f;
const float STEERING_ANGLE_MAX = 2.5f;
const float SPRING_CONSTANT = 95000.0f; // N/m
const float DAMPING_COEFFICIENT = 200.0f; // N*s/m
const float WHEEL_RADIUS = 0.9f; // m
const float WHEEL_RADIUS2 = 1.5f; // m
const float SUSPENSION_TRAVEL = 0.2f; // m
const float REST_SUSPENSION_HEIGHT = 0.8f; // Resting height of suspension (m)
const float GRAVITY = 9.81f; // Gravity (m/s^2)

class vec
{
public: 
	
	 float distance( vector3d& other,vector3d other2)  {
        float dx = other.x - other2.x;
        float dy = other.y - other2.y;
        float dz = other.z - other2.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
};



class roue
{
public:
		roue(const char * filename);
		~roue();
		void update();
		void draw();
		void setLocation(vector3d vec);
	    vector3d getLocation();
	    void  updateSuspension(float verticalForce, float dt);
	    float suspensionRestLength;
	    float suspensionCurrentLength;
	    float springConstant;
	    float dampingConstant;
	    vector3d position;
	    void setRotation(float rot);
	    
	    
	private:
	
		objloader *obj;
		int roue_;	
		vector3d loc;
		float rotation;
};


class porte_vitre
{
public:
		porte_vitre(const char * filename);
		~porte_vitre();
		void update();
		void draw();
		
	private:
		objloader *obj;
		int porte_vitre_;	
};

class tb
{
public:
		tb(const char * filename);
		~tb();
		void update();
		void draw();
		
	private:
		objloader *obj;
		int tb_;	
};

class porte
{
	public:
		porte(const char * filename);
		~porte();
		void update();
		void draw();
		void setRotPorte(float r);
		void setRotPorteEgal(float r);
		float getRotPorte();
		
	private:
		objloader *obj;
		porte_vitre *p1_vitre;
		porte_vitre *p2_vitre;
		int porte_;
		float rotPorte;


		
};

class vitres
{
	public:
		vitres();
		~vitres();
		void update();
		void draw();
		
	private:
		int vitres_;
		objloader *obj;
		
};

class volant
{
	public:
		volant();
		~volant();
		void update();
		void draw();
		
	private:
		int volant_;
		objloader *obj;
		
};

class boundingboxCar
{
	public:
		boundingboxCar(vector3d loc);
		~boundingboxCar();
		void drawCollision();
		vector3d getLocation();
		void setLocation(vector3d loc);
		void setParent(vector3d parent,float rotationY,int offset);
	private:
	
		vector3d pos;
		float rot;
};


class vehicule
{
	public:
		vehicule(collisionsphere ccs,vector3d s,const char * filename,bool visible);
		~vehicule();
		void ouvrirPorte1();
		void ouvrirPorte2();
		void fermerPorte1();
		void fermerPorte2();
		void update(bool exit,blurMotion* motionBB);
		void draw();
		bool collisionAABB( vehicule& v1, vehicule& v2);
		void collisions(std::vector<vehicule*> cc);
		void elementCars();
		void elementOtherCars();
		void drawWheel(float suspensionLength,roue* wheel);
		void drawCarBody(float rollAngle);
		void updatePhysics(float dt,std::vector<collisionplane>& collplane,std::vector<collisionplane>& collplane2);
		void handleKeyPress(unsigned int key, int x, int y);
		void handleKeyPressUP(unsigned int key, int x, int y);
		void keyboard(unsigned char key, int x, int y);
		void keyboardUP(unsigned char key, int x, int y);
		vector3d getLocation();
		float getRotation();
		void updateCamera(vector3d carPosition);
		void mouseMotion(int x, int y);
		void updateCollision(std::vector<collisionplane>& collplane);
		void updateCollisionMurs(std::vector<collisionplane>& collplane);
		void setLocation(vector3d location);
		void setLocationInc(vector3d loc);
		void setPosition(vector3d pos);
		bool getControl();
		void setControl(bool c);
 		bool instance;
 		bool isCloseTo( vector3d other,float threshold);
		vector3d getScale();
		float getSpeed();
		bool getAvancer();
		bool getReculer();
		void isModePlein(bool s);
		void isModeLines(bool s); 
		bool getIsVisible();
		std::vector<boundingboxCar*> bb;
		
	private:

	int car;
	std::vector<porte *> door;
	std::vector<roue *> wheel;
		std::vector<particules> part;
	objloader *obj;
	vitres *v;
	tb *tab;
	volant * vv;
	float carSpeed ;     // Speed of the car movement
	float carRotation;    // Rotation angle of the car around the Y axis
	float carTurnSpeed;   // Speed of the car turning
	float gravity;
	float groundLevel;
	float deltaTime; // Assuming 60 FPS
	bool up,down,left,right,space;
	bool braking;


	vector3d position;
  	float vx, vz;        // Velocity
    float direction;     // Direction (angle in radians)
    float steeringAngle; // Steering angle (radians)
    float speed;         // Current speed
    float suspensionHeight[4]={REST_SUSPENSION_HEIGHT+0.4f, REST_SUSPENSION_HEIGHT+0.1, REST_SUSPENSION_HEIGHT+0.1f, REST_SUSPENSION_HEIGHT}; // Height of the suspension
    float suspensionVelocity[4]={0.0f, 0.0f, 0.0f, 0.0f}; // Velocity of the suspension for each wheel
    float wheelDistance; // Distance from the car body to the wheel
    float rollAngle; // Car body roll angle
    float pitchAngle; // Car body pitch angle
    float acceleration; 
    float brakingForce;
    float rot;
    vector3d force;
	vector3d dir;
	collisionsphere cs;
	bool isground;
	bool modeAvancer;
	bool modeReculer;
	vector3d scale;
	bool control;
	vec vecteur;
	bool isVisible;
	float regularSpeed;
	bool modePlein;
	bool modeLines;


	



};



#endif
