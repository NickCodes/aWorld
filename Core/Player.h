// Nick Fisher 2011
// OGRE3D demo application
// player.h - Class to handle player constants and functions

#include "Ogre.h"

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include "../core/CameraController.h"
#endif

class Player
{

public:

	Player();
	~Player(void);
	
	float hp, height, speed;										// Player variables
	
	void createPlayer(float, float, float);		// Create player instance, pass it the camera and variables
	void init(void);												// Setup the class

private:

protected:

};
