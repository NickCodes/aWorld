#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreFont.h>
#include <OgreFontManager.h>

#include "../util/aWorldConfig.h"			// aWorld configurations loader


// Below is the Ogre base class that applications will inherit
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

class Base 
{
	
friend class app;

public:
	Base(void);
    ~Base(void);
	
	void initBase(void);
	void render(void);

	Ogre::Camera* mCamera;			
	Ogre::Root* mRoot;					
    Ogre::SceneManager* mSceneMgr;
	Ogre::RenderWindow* mWindow;
    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;			

	MyConfig config;		// Class to handle loading config settings from file

	void setUpOgre(void);
	void setUpResources(void);
	void createWindow(void);
	void chooseSceneManager(void);
	void createCamera(void);
	void createViewport(void);

};
