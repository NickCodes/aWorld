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

void myGUIManager::dbug(Ogre::String addition)
{
	
	MyGUI::EditBox* dbWindow = MyGUI::Gui::getInstance().findWidget<MyGUI::EditBox>("wordWrap");
	Ogre::String temp = dbWindow->getCaption();
	temp = temp + "\n" + addition;
	dbWindow->setCaption(temp);
	
}


void myGUIManager::mainMenu()
{	
	if (MyGUI::LayoutManager::getInstance().isExist("newMain.layout")) 
	{
		// Load layout from file
		layout = MyGUI::LayoutManager::getInstance().loadLayout("newMain.layout");
	}	else 
		{
			layout = MyGUI::LayoutManager::getInstance().loadLayout("newMain.layout");

			// Assign the exit function to an existing element in the .layout
			MyGUI::Widget* exitBtn = MyGUI::Gui::getInstance().findWidgetT("exitButton");
			exitBtn->eventMouseButtonClick += MyGUI::newDelegate(this, &myGUIManager::exitFromMenu);

			MyGUI::Widget* optionsBtn = MyGUI::Gui::getInstance().findWidgetT("optionsButton");
			optionsBtn->eventMouseButtonClick += MyGUI::newDelegate(this, &myGUIManager::showOptions);

			MyGUI::Widget* loadMapBtn = MyGUI::Gui::getInstance().findWidgetT("loadMapButton");
			loadMapBtn->eventMouseButtonClick += MyGUI::newDelegate(this, &myGUIManager::showLoadMap);

			MyGUI::Widget* goBtn = MyGUI::Gui::getInstance().findWidgetT("goButton");
			goBtn->eventMouseButtonClick += MyGUI::newDelegate(this, &myGUIManager::go);
		}
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
	dbug("loadMap Clicked");
}

void myGUIManager::go(MyGUI::Widget* _sender)
{
	MyGUI::LayoutManager::getInstancePtr()->unloadLayout(layout);

	outsideManager->loadTerrain("go");
	stateManager->setState(2);
	outsideManager->snap();
}
