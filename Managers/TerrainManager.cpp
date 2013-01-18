#include "Ogre.h"

#include "../managers/TerrainManager.h"


myTerrainManager::myTerrainManager()
{
}

myTerrainManager::~myTerrainManager(void)
{
}

void myTerrainManager::init(Ogre::SceneManager* scenemgr)
{
	mSceneMgr = scenemgr;	// Assign pointer to scene manager
}


/*	TODO
	When I compiled the project for the first time after moving the code directories around, 
	this function was defined twice, below. I have no idea how this wasn't causing an obvious 
	issue previously and the commented function below looks obsolete, as a light is established
	elsewhere and the terrain file name is hard coded 

void myTerrainManager::loadTerrain(Ogre::String terrainFileName)
{	
	// This code establishes a test light in the scene
	Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
    lightdir.normalise();
    Ogre::Light* light = mSceneMgr->createLight("tstLight");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(lightdir);
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
	
	// Load the outdoor terrain
	terrainFileName = "terrain";			// Set terrain.dat as terrain to load
	loadTerrain(terrainFileName);			// Load the terrain from an existing file
	
	// Load other objects from a .scene file
	loadLevel();							

	mSceneMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox", 10000, false);	// Set skybox ("name" defined in material script)
}
*/


// Loads terrain from file into the terrain manager
void myTerrainManager::loadTerrain(Ogre::String filename)
{
	mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();											// Create global terrain options
	mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f);	// Create terrain manager
	mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);														// Set origin to zero

	// Check to see if the terrain resource exists
	if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
    	// Define terrain inserts the file into a slot on the overall terrain grid
		// 0,0 represents the location of the slot relative to the center slot on the grid
		mTerrainGroup->defineTerrain(0, 0);			
		
	else 	Ogre::LogManager::getSingletonPtr()->logMessage("!!!!!!!!!!!!!!!!!! Error loading terrain file: " + filename);
	
	// Loads terrains that have been DEFINED but not loaded
	mTerrainGroup->loadAllTerrains(true);
}


void myTerrainManager::loadLevel(void)
{
	Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL,"********* parsing scene file, log level set to normal");
	Ogre::LogManager::getSingleton().setLogDetail(Ogre::LL_NORMAL);

	// Use dotSceneLoader to parse a scene exported from Blender using the .scene format
	dotSceneLoader.parseDotScene("Scene.xml","General", mSceneMgr, mSceneMgr->getRootSceneNode());

	// Access and translate the Cube from the .scene information using its name
	Ogre::SceneNode* test = mSceneMgr->getSceneNode("Cube");
	test->scale(12,12,12);
	test->translate(0,450,0);
}