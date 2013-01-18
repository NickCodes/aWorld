#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

#ifndef TERRAIN_H
#define TERRAIN_H
#include <Terrain/OgreTerrain.h>				// Ogre's terrain manager
#include <Terrain/OgreTerrainGroup.h>			// Ogre's terrain manager
#endif

class CameraController
{

public:
	
	CameraController(void);
	~CameraController(void);


	void createCameraController (Ogre::Camera* , Ogre::SceneManager*, float speed);
	void pitchCam(Ogre::Radian);
	void yawCam(Ogre::Radian);
	void rollCam(Ogre::Radian);
	void transCam(int);
	void setSpeedScale(float);
	void setHeight(Ogre::Real);
	void updateCamera(Ogre::Real, Ogre::Real);

	float moveScale, playerHeight, mouseScale;		// Movement scaling variable and height of camera from terrain
	
	Ogre::SceneNode* cameraNode;					// Top node
	Ogre::SceneNode* cameraYawNode;					// Inherit movement from above
	Ogre::SceneNode* cameraPitchNode;				// Inherit movement from above
	Ogre::SceneNode* cameraRollNode;				// Bottom node with camera attached

private:



protected:

};

