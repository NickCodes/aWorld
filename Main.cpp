#include "OGREbase/AppClass.h"

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include "../core/CameraController.h"
#endif

#if defined(WIN32)
#include "windows.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
int main (int argc, char *argv[]) {
#endif

	app mApp;							// Instance of my application which derives from the base class
	mApp.initBase();					// Setup Ogre
	mApp.initManagers();				// Set up helper classes
	mApp.kickoff();						// Entry point for user interaction / main menu
	
	// Main loop
	//--------------------------------------------------------------------------------------------
	
	while (mApp.getState() != 0)		// State 0 is the shutdown state	
	{
			mApp.render();
			mApp.update();
	}
		
	// Exit from program
	Ogre::LogManager::getSingletonPtr()->logMessage("***** Exiting main loop");
	return 0;
}	



