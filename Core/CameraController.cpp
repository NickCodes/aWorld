#include "../core/CameraController.h"

CameraController::CameraController(void){}

CameraController::~CameraController(void){}


void CameraController::createCameraController (Ogre::Camera* c, Ogre::SceneManager* s, float speed)
{
	cameraNode = s->getRootSceneNode()->createChildSceneNode();
	cameraYawNode = cameraNode->createChildSceneNode();
 	cameraPitchNode = cameraYawNode->createChildSceneNode();
 	cameraRollNode = cameraPitchNode->createChildSceneNode();
	cameraRollNode->attachObject(c);

	setSpeedScale(speed);
}

void CameraController::pitchCam (Ogre::Radian rot)
{
	cameraPitchNode->pitch(rot);
}

void CameraController::yawCam (Ogre::Radian rot)
{
	cameraYawNode->yaw(rot);
}

void CameraController::rollCam (Ogre::Radian rot)
{
	cameraRollNode->roll(rot);
}



void CameraController::transCam(int direction)
{
	// Direction 1,2,3,4 represents translating left, right, forwards and backwards	
	switch (direction)
	{
	case 1:
	cameraNode->translate(cameraYawNode->getOrientation() * cameraPitchNode->getOrientation() * Ogre::Vector3(0,0,moveScale));
	break;
	case 2:
	cameraNode->translate(cameraYawNode->getOrientation() * cameraPitchNode->getOrientation() * Ogre::Vector3(0,0,-moveScale));
	break;
	case 3:
	cameraNode->translate(cameraYawNode->getOrientation() * cameraPitchNode->getOrientation() * Ogre::Vector3(-moveScale,0,0));
	break;
	case 4:
	cameraNode->translate(cameraYawNode->getOrientation() * cameraPitchNode->getOrientation() * Ogre::Vector3(moveScale,0,0));
	break;
	}
}



void CameraController::setSpeedScale(float scale)
{
	moveScale = scale;			// Set the scale of movement
}


void CameraController::setHeight(Ogre::Real h)
{
	playerHeight = h;			// Sets the height of the camera
}



// Code adapted from: http://www.ogre3d.org/tikiwiki/Creating+a+simple+first-person+camera+system
// ---------------------------------------------------------------------------------------------------------

void CameraController::updateCamera(Ogre::Real X, Ogre::Real Y)
{
	Ogre::Real pitchAngle;		
	Ogre::Real pitchAngleSign;
	
	pitchCam(Ogre::Radian(-(Y) * .002));																		// Pitch according to the relative movement of the mouse Y
	cameraYawNode->yaw(Ogre::Radian(-(X) * .002));																// Yaw according to the relative movement of the mouse X
	
	pitchAngle = (2 * Ogre::Degree(Ogre::Math::ACos(cameraPitchNode->getOrientation().w)).valueDegrees());		// Angle of rotation around the X-axis
 	pitchAngleSign = cameraPitchNode->getOrientation().x;														// Just to determine sign, value not important
	
	// Limit the pitch between -90 degress and +90 degrees (Up/down)
	
	if (pitchAngle > 90.0f)
	{
		if (pitchAngleSign > 0)
			cameraPitchNode->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f), Ogre::Math::Sqrt(0.5f), 0, 0));	// Set orientation to 90 degrees on X-axis.
		else if (pitchAngleSign < 0)
			cameraPitchNode->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f), -Ogre::Math::Sqrt(0.5f), 0, 0));	// Sets orientation to -90 degrees on X-axis.
	}

}


