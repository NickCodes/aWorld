#ifndef OGRE_H
#define OGRE_H
#include "ogre.h"
#endif

#ifndef MYGUI_H
#define MYGUI_H
#include "MyGUI.h"
#endif

#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include "../core/StateManager.h"
#endif

#ifndef OUTSIDEMANAGER_H
#define OUTSIDEMANAGER_H
#include "../managers/myOutsideManager.h"
#endif

#include "MyGUI_OgrePlatform.h"

class myGUIManager
{

public:

	myGUIManager(void);
	~myGUIManager(void);
	
	void init(myOutsideManager*, StateManager*, Ogre::RenderWindow*, Ogre::SceneManager*, Ogre::Camera*);
	void mainMenu();

	
private:
	// Pointers to various state managers passed to the class on init()
	Ogre::SceneManager* sceneManager;
	StateManager* stateManager;														
	myOutsideManager* outsideManager;
	Ogre::RenderWindow* renderWindow;
	
	// The myGUI class instantiation
	MyGUI::Gui* mGUI;

protected:

};
