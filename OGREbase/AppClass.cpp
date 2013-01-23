// Nick Fisher 2011
// OGRE3D demo application
// AppClass.cpp

#include "AppClass.h"

app::~app(void)
{	
}

app::app(void)
{
	delete Ogre::Root::getSingletonPtr();			// Clean up Ogre
} 


void app::initManagers(void)
{
	config.go();	// Load the config options from file - config.getKeyExists("Player/Name") = t/f
	
	Ogre::LogManager::getSingletonPtr()->logMessage("***** Config loaded. Hello, " + config.getValueAsString("Player/Name"));
	stateManager.init();													
	Ogre::LogManager::getSingletonPtr()->logMessage("***** stateManager initialized");
	// This should be in CamerController::init()
	cameraController.createCameraController(mCamera,mSceneMgr, 0.8);		
	Ogre::LogManager::getSingletonPtr()->logMessage("***** cameraController created");
	guiManager.init(&outsideManager, &stateManager, mWindow, mSceneMgr, mCamera);		
	Ogre::LogManager::getSingletonPtr()->logMessage("***** guiManager initialized");
	inputManager.init(&outsideManager, mWindow, &cameraController, &stateManager);				
	Ogre::LogManager::getSingletonPtr()->logMessage("***** inputManager initialized");
	outsideManager.init(&playerManager, &cameraController, mSceneMgr);
	Ogre::LogManager::getSingletonPtr()->logMessage("***** terrainManager initialized");
	playerManager.init();
	Ogre::LogManager::getSingletonPtr()->logMessage("***** Player Manager initialized");
}



void app::evaluateKeypress(void)
{
	if (inputManager.escape == true)
		setState(0);

	if (inputManager.up == true)
	{
			cameraController.transCam(2);
	}

	if (inputManager.down == true)
	{
			cameraController.transCam(1);
	}

	if (inputManager.left == true)
	{
			cameraController.transCam(3);
	}

	if (inputManager.right == true)
	{
			cameraController.transCam(4);
	}
	
	// When space is pressed, change betweeen state 1 and 2 (menu and fps)
	if (inputManager.space == true)
	{
			if (stateManager.getState() == 1)
				{
					stateManager.setState(2);
					guiManager.dbug("State changed to 2");
					inputManager.space = false;
					Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL,"***** Calling debug update in state 2");
				}
			else if (stateManager.getState() == 2)
				{
					stateManager.setState(1);
					guiManager.dbug("State changed to 1");
					inputManager.space = false;
					Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL,"***** Calling debug update in state 1");
				}
		}
}
		


void app::update(void)
{
	inputManager.captureKeyboard();				// Capture keyboard input
	inputManager.captureMouse();				// Capture Mouse input
	evaluateKeypress();							// Act on the input

	// Quick and dirty snap if in FPS view - remove this later
	if (stateManager.getState() == 2)
		outsideManager.snap();
}


int app::getState(void)
{
	return stateManager.getState();
}

void app::setState(int s)
{
	stateManager.setState(s);
}

// Kickoff is where user interaction begins - ie main menu
void app::kickoff(void)
{
	
	guiManager.mainMenu();	// Draw the main menu bar
}
