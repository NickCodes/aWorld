#include "OgreBase.h"
#include <iostream>

Base::Base(void)
{
}

Base::~Base(void)
{
}


// initBase is called to successively call all setup functions 
// :
void Base::initBase(void)
{
	setUpOgre();			// Creates root, loads render system
	setUpResources();		// Sets resource group locations, initializes
	createWindow();			// Creates a window manually
	chooseSceneManager();	// Creates scene manager
	createCamera();			// Creates camera
	createViewport();		// Creates viewport
}


void Base::setUpOgre(void)
{
	
	// Create root, allow CFG to be entered programatically
	mRoot = new Ogre::Root("", "");
	
	// Set the log level detail to low for initialisation, I don't need this debug info as of 4/20/2012 ;)
	// Ogre::LL_LOW or LL_NORMAL or LL_BOREME
	Ogre::LogManager::getSingleton().setLogDetail(Ogre::LL_NORMAL);

	// Load our application custom config
	config.go();
	Ogre::LogManager::getSingletonPtr()->logMessage("***** Config loaded. Hello, " + config.getValueAsString("Player/Name"));
		
	// Get the render system setting and load the appropriate plugin
	Ogre::String rSys = config.getValueAsString("System/renderSystem");
	Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL, "********* Render: " + rSys);

	if (config.getValueAsString("System/renderSystem") == "RenderSystem_Direct3D9_d")
	{
		#if defined(_DEBUG)
			mRoot->loadPlugin("RenderSystem_Direct3D9_d");
			Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL, "********* Loading RenderSystem_Direct3D9_d");
		#else
			mRoot->loadPlugin("RenderSystem_Direct3D9_d");
		#endif
	} else if (config.getValueAsString("System/renderSystem") == "RenderSystem_OpenGL_d")
	{
		#if defined(_DEBUG)
			mRoot->loadPlugin("RenderSystem_OpenGL_d");
			Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL, "********* Loading RenderSystem_OpenGL_d");
		#else
			mRoot->loadPlugin("RenderSystem_OpenGL_d");
		#endif
	} else 
	{
		Ogre::LogMessageLevel::LML_CRITICAL, "********* Render system: " + rSys + " not recognized, defaulting to direct3D";
		
		#if defined(_DEBUG)
			mRoot->loadPlugin("RenderSystem_Direct3D9_d");
			Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL, "********* Loading RenderSystem_Direct3D9_d");
		#else
			mRoot->loadPlugin("RenderSystem_Direct3D9_d");
		#endif
	}
	
	// Iterates through a list of available render systems and initializes them
	const Ogre::RenderSystemList &renderSystem = mRoot->getAvailableRenderers();	
    Ogre::RenderSystemList::const_iterator &r_it = renderSystem.begin();			
	mRoot->setRenderSystem(*r_it);
    mRoot->initialise(false);
}

void Base::setUpResources(void)
{

	Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_NORMAL, "********* Parsing Resources config file");// Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load("resources_d.cfg");

	// Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
			
			Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_NORMAL,"Resource loaded: " + Ogre::String(archName+","+typeName+", "+ secName));
        }
    }

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}



void Base::createWindow(void)
{
	Ogre::NameValuePairList opts;
	
	if ( config.getKeyExists("System/screenWidth"))
	{
		int wid = config.getValueAsInt("System/screenWidth");
		int hei = config.getValueAsInt("System/screenHeight");
		Ogre::String res = Ogre::StringConverter::toString(wid + "x" + hei);
		opts["resolution"] = res;
	} else opts["resolution"] = "800x600";	// Fallback if config is not set

    if ( config.getKeyExists("System/fullScreen"))
	{
		opts["fullscreen"] = config.getValueAsString("System/fullScreen");
	} else opts["fullscreen"] = "false";

	if ( config.getKeyExists("System/fullScreen"))
	{
		opts["vsync"] = config.getValueAsString("System/vSync");
	} else opts["vsync"] = "false";
	
	mWindow = mRoot->createRenderWindow("WINDOW", config.getValueAsInt("System/screenWidth"),config.getValueAsInt("System/screenHeight"), config.getKeyExists("System/fullScreen"), &opts);
}

void Base::chooseSceneManager(void)
{
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}

void Base::createCamera(void)
{
 	mCamera = mSceneMgr->createCamera("PlayerCam");
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);
}

void Base::createViewport(void)
{
	// Create viewport VP and pass it the camera
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth())/ Ogre::Real(vp->getActualHeight()));
}

void Base::render(void)
{
	mRoot->renderOneFrame();
}




