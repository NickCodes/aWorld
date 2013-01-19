#include "../managers/guiManager.h"	

#ifndef MYGUI_H
#define MYGUI_H
#include "MyGUI.h"
#endif

#ifndef OGRE_H
#define OGRE_H
#include "Ogre.h"
#endif

#ifndef OUTSIDEMANAGER_H
#define OUTSIDEMANAGER_H
#include "../managers/myOutsideManager.h"
#endif


myGUIManager::myGUIManager(void)
{
}

myGUIManager::~myGUIManager(void)
{
	delete mGUI;	// Cleanup the guiManager class
}

void myGUIManager::init(myOutsideManager* t, StateManager* s, Ogre::RenderWindow* rWin, Ogre::SceneManager* mSceneMgr, Ogre::Camera* mCamera)
{
	// Assign the pointers to the various managers
	stateManager = s;
	outsideManager = t;
	renderWindow = rWin;
	sceneManager = mSceneMgr;

	// Instantiate the MyGUI class
	MyGUI::OgrePlatform* mPlatform = new MyGUI::OgrePlatform();
	mPlatform->initialise(renderWindow, mSceneMgr);					
	mGUI = new MyGUI::Gui();
	mGUI->initialise();
}

void myGUIManager::mainMenu()
{	
	/*
	// Create menu bar
	MyGUI::MenuBar* myMainMenu = mGUI->createWidget<MyGUI::MenuBar>("MenuBar", 0, 0, 1000, 25, MyGUI::Align::Top, "Main");
	
	// First menu item on menu bar
	MyGUI::MenuItem* sceneMenuItem = myMainMenu->addItem("Scene", MyGUI::MenuItemType::Popup);
	sceneMenuItem->setFontName("default");
	
	// Create popup item for the first menu item
	MyGUI::PopupMenu * sceneMenuPopUp = sceneMenuItem->createItemChildT<MyGUI::PopupMenu>();		
	// Add menu items to the popup menu
	MyGUI::MenuItem* sceneMenuLoadScene = sceneMenuPopUp->addItem("Load Scene",MyGUI::MenuItemType::Separator);
		sceneMenuLoadScene->setFontName("default");
	MyGUI::MenuItem* sceneMenuLoadTerrain = sceneMenuPopUp->addItem("Load Terrain",MyGUI::MenuItemType::Normal);
		sceneMenuLoadTerrain->setFontName("default");
	MyGUI::MenuItem* sceneMenuProcessTerrain= sceneMenuPopUp->addItem("Process Terrain",MyGUI::MenuItemType::Normal);
		sceneMenuProcessTerrain->setFontName("default");
	MyGUI::MenuItem* sceneMenuSaveTerrain= sceneMenuPopUp->addItem("Save Tererain",MyGUI::MenuItemType::Normal);	
		sceneMenuSaveTerrain->setFontName("default");
	MyGUI::MenuItem* sceneMenuExit= sceneMenuPopUp->addItem("Exit",MyGUI::MenuItemType::Normal);	
		sceneMenuExit->setFontName("default");
	*/

	MyGUI::LayoutManager::getInstance().load("newMain.layout");

}

void myGUIManager::exitFromMenu(void)
{
	stateManager->setState(0);
}
