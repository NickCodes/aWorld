#include "Ogre.h"

#include "../managers/OutsideManager.h"


OutsideManager::OutsideManager()
{
}

OutsideManager::~OutsideManager()
{
}

void OutsideManager::init(Ogre::SceneManager* scenemgr)
{
	mSceneMgr = scenemgr;								// Assign pointer to scene manager
}


void OutsideManager::loadTerrain(Ogre::String terrainFileName)
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
	terrainFileName = "terrain";			
	
	// Set terrain.dat as terrain to load
	mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();											// Create global terrain options
	mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f);	// Create terrain manager
	mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);														// Set origin to zero

	// Check to see if the terrain resource exists
	if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), terrainFileName))
    	// Define terrain inserts the file into a slot on the overall terrain grid
		// 0,0 represents the location of the slot relative to the center slot on the grid
		mTerrainGroup->defineTerrain(0, 0);			
		
	else 	Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL, "!!!!!!!!!!!!!!!!!! Error loading terrain file: " + terrainFileName);
	
	// Loads terrains that have been DEFINED but not loaded
	mTerrainGroup->loadAllTerrains(true);
		
	// Load other objects from a .scene file
	loadLevel();							

	mSceneMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox", 10000, false);	// Set skybox ("name" defined in material script)
}



void OutsideManager::loadLevel(void)
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