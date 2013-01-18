#include "Ogre.h"
#include "../managers/myOutsideManager.h"


myOutsideManager::myOutsideManager()
{
}

myOutsideManager::~myOutsideManager()
{
	delete mTerrainGlobals;
	delete mTerrainGroup;
}

void myOutsideManager::init(PlayerManager* pman, CameraController* mcam, Ogre::SceneManager* scenemgr)
{
	// Assign manager pointers to local managers
	cameraController = mcam;
	mSceneMgr = scenemgr;					
	playerManager = pman;
	
	createSun();

	mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();											// Create global terrain options
	mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f);	// Create terrain manager
}


void myOutsideManager::createSun()
{
	// This code establishes a test light in the scene
	Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
    lightdir.normalise();
	Sun = mSceneMgr->createLight("SunLight");
	Sun->setType(Ogre::Light::LT_DIRECTIONAL);
	Sun->setDirection(lightdir);
    Sun->setDiffuseColour(Ogre::ColourValue::White);
    Sun->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
}


void myOutsideManager::loadTerrain(Ogre::String tf)
{	
	mTerrainGroup->setFilenameConvention(tf, "dat");								// Sets the TerrainGroup naming prefix and sufix
	Ogre::String filename = mTerrainGroup->generateFilename(0,0);					// Generates a filename based on the prefix and suffix

	// If the resource exists, define slot (0,0) with the data
	if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
		mTerrainGroup->defineTerrain(0, 0);			
	else 	
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL, "!!!!!!!!!!!!!!!!!! Error loading terrain from file: " + tf);
	
	// Display slot (0,0), and load skybox
	mTerrainGroup->loadTerrain(0,0);
	mSceneMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox", 10000, false);	// Set skybox ("name" defined in material script)
}



void myOutsideManager::loadLevel(void)
{
	Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL,"********* DotSceneLoader is now parsing the scene file for additional objects");
	dotSceneLoader.parseDotScene("Scene.xml","General", mSceneMgr, mSceneMgr->getRootSceneNode());
}



void myOutsideManager::snap(void)
{
	// This function snaps the cameraController sceneNode to the terrainManager height + playerManager height
	
	// Store cameraController node position in currPlayer
	Ogre::Vector3 currPlayer;
	currPlayer.x = cameraController->cameraNode->getPosition().x;
	currPlayer.y = cameraController->cameraNode->getPosition().y;
	currPlayer.z = cameraController->cameraNode->getPosition().z;
	
	// I may not need to cast this to Ogre::Real
	float mHeight = mTerrainGroup->getHeightAtWorldPosition(currPlayer);
	Ogre::Real mapHeight = static_cast<Ogre::Real>(mHeight);

	//Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL,"********* Current location: " + Ogre::StringConverter::toString(currPlayer.x) + " Y: " + Ogre::StringConverter::toString(currPlayer.y) + " Z: " + Ogre::StringConverter::toString(currPlayer.z));
	//Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL,"********* Current terrain height at position: " + Ogre::StringConverter::toString(mapHeight));

	//Snap player to terrain height
	if (currPlayer.y != mapHeight + playerManager->height)
		cameraController->cameraNode->setPosition(currPlayer.x, mapHeight + playerManager->height, currPlayer.z);

	//Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL,"********* Location after snap: " + Ogre::StringConverter::toString(currPlayer.x) + " Y: " + Ogre::StringConverter::toString(currPlayer.y) + " Z: " + Ogre::StringConverter::toString(currPlayer.z));
}


void myOutsideManager::makeNewTerrain(Ogre::String fileName)
{
	Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL,"********* Beginning to process new custom terrain data");
	Ogre::LogManager::getSingleton().setLogDetail(Ogre::LL_BOREME);
		
    mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);
	
	// Configure the terrain defaults
	mTerrainGlobals->setMaxPixelError(8);								// Precision of terrain (vertex number and performance impacting)
    mTerrainGlobals->setCompositeMapDistance(3000);						// How far the renderer will display terrain
	
	// Setting the previously defined directional light data
    mTerrainGlobals->setLightMapDirection(Sun->getDerivedDirection());
    mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
    mTerrainGlobals->setCompositeMapDiffuse(Sun->getDiffuseColour());

	// Configure default import settings for if we use imported image
    Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
    defaultimp.terrainSize = 513;			// Should match terraingroup values
    defaultimp.worldSize = 12000.0f;		// Should match terraingroup values
    defaultimp.inputScale = 600;			// due terrain.png is 8 bpp
    defaultimp.minBatchSize = 33;
    defaultimp.maxBatchSize = 65;
	
	
	// textures
    defaultimp.layerList.resize(3);																	// Number of splatting textures
    defaultimp.layerList[0].worldSize = 100;														// Smaller number causes higher resolution texture
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");			// Diffuse texture with a specular map in the alpha channel 
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");				// Normal map with a height map in the alpha channel
    defaultimp.layerList[1].worldSize = 30;
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
    defaultimp.layerList[2].worldSize = 200;
    defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
    defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
	
	Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL,"********* Loading " + fileName + ".PNG");
	Ogre::Image img;
	img.load(fileName + ".png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	
	mTerrainGroup->defineTerrain(0, 0, &img);
	mTerrainGroup->loadAllTerrains(true);
	initBlendMaps(mTerrainGroup->getTerrain(0,0));
	
	mTerrainGroup->freeTemporaryResources();
}


void myOutsideManager::initBlendMaps(Ogre::Terrain* terrain)
{
	Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
    Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
    Ogre::Real minHeight0 = 70;
    Ogre::Real fadeDist0 = 40;
    Ogre::Real minHeight1 = 70;
    Ogre::Real fadeDist1 = 15;
    float* pBlend0 = blendMap0->getBlendPointer();
    float* pBlend1 = blendMap1->getBlendPointer();
    for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
    {
        for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
        {
            Ogre::Real tx, ty;
 
            blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
            Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
            Ogre::Real val = (height - minHeight0) / fadeDist0;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend0++ = val;
 
            val = (height - minHeight1) / fadeDist1;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend1++ = val;
        }
    }
    blendMap0->dirty();
    blendMap1->dirty();
    blendMap0->update();
    blendMap1->update();
   
}


void myOutsideManager::saveMap(Ogre::String fn)
{
	Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL,"********* Saving Map as: " + fn + ".dat");
	mTerrainGroup->setFilenameConvention(fn, "dat");
	mTerrainGroup->saveAllTerrains(true);
}
