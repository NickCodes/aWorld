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

	// Instantiate the MyGUI class - TODO class should be independent of this instantiation
	MyGUI::OgrePlatform* mPlatform = new MyGUI::OgrePlatform();
	mPlatform->initialise(renderWindow, mSceneMgr);
	mGUI = new MyGUI::Gui();
	mGUI->initialise();
}

void myGUIManager::dbug()
{
	//Ogre::LogManager::getSingletonPtr()->logMessage("?*?*?*?*?*?*?*?* Debug called");
	//Ogre::String debugOutput;
	// MyGUI::Widget* dbWindow = MyGUI::Gui::getInstance().findWidgetT("debugText");
	//dbugWindow->setUserString("salad","forks");
}


void myGUIManager::mainMenu()
{	
	// Define the whole screen as a parent widget
	MyGUI::WidgetPtr wholeScreen = mGUI->createWidget<MyGUI::Widget>("PanelSkin",0,0,renderWindow->getWidth(),renderWindow->getHeight(),MyGUI::Align::Default,"Back");
	// Load layout from file
	MyGUI::LayoutManager::getInstance().loadLayout("newMain.layout","",wholeScreen);
	
	// Assign the exit function to an existing element in the .layout
	MyGUI::Widget* exitBtn = MyGUI::Gui::getInstance().findWidgetT("exitButton");
	exitBtn->eventMouseButtonClick += MyGUI::newDelegate(this, &myGUIManager::exitFromMenu);

	MyGUI::Widget* optionsBtn = MyGUI::Gui::getInstance().findWidgetT("optionsButton");
	optionsBtn->eventMouseButtonClick += MyGUI::newDelegate(this, &myGUIManager::showOptions);

	MyGUI::Widget* loadMapBtn = MyGUI::Gui::getInstance().findWidgetT("loadMapButton");
	loadMapBtn->eventMouseButtonClick += MyGUI::newDelegate(this, &myGUIManager::showLoadMap);

	/*
	// Create menu bar manually
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
	*/
}

void myGUIManager::exitFromMenu(MyGUI::Widget* _sender)
{
	stateManager->setState(0);
}

void myGUIManager::showOptions(MyGUI::Widget* _sender)
{
	MyGUI::Widget* optionsMenu = MyGUI::Gui::getInstance().findWidgetT("menuOptions");
	if (optionsMenu->getVisible()) { optionsMenu->setVisible(false); } else optionsMenu->setVisible(true);

}

void myGUIManager::showLoadMap(MyGUI::Widget* _sender)
{
	MyGUI::Widget* loadMenu = MyGUI::Gui::getInstance().findWidgetT("loadMapMenu");
	if (loadMenu->getVisible()) {loadMenu->setVisible(false);} else loadMenu->setVisible(true);
}

