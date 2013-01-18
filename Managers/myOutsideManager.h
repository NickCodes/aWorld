#ifndef DOTSCENELOADER_H
#define DOTSCENELOADER_H
#include "../util/DotSceneLoader.h"
#endif

#ifndef TERRAIN_H
#define TERRAIN_H
#include <Terrain/OgreTerrain.h>				// Ogre's terrain manager
#include <Terrain/OgreTerrainGroup.h>			// Ogre's terrain manager
#endif

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include "../core/CameraController.h"
#endif

#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H
#include "../core/PlayerManager.h"
#endif


class myOutsideManager
{

public:

	myOutsideManager();
	~myOutsideManager(void);
	
	void init(PlayerManager*, CameraController*, Ogre::SceneManager*);										
	void loadTerrain(Ogre::String);									
	void loadLevel(void);	
	void snap(void);
	void makeNewTerrain(Ogre::String);
	void saveMap(Ogre::String);
	
private:
		
	Ogre::SceneManager* mSceneMgr;									// Pointer to scene manager
	CameraController* cameraController;
	PlayerManager* playerManager; 

	Ogre::DotSceneLoader dotSceneLoader;							// Class to manage parsing DOTSCENE files for geometry
	Ogre::TerrainGroup* mTerrainGroup;								// Terrain manager
	Ogre::TerrainGlobalOptions* mTerrainGlobals;					// Terrain manager
    Ogre::Vector3 playerPosition;									// Used to snap camera to terrain
	Ogre::Real terrainHeight;										// Used to snap camera to terrain
	Ogre::String loadFileName;										// Used to hold filename of terrain to load

	Ogre::Light* Sun;												// Pointer to a light used for directional lightmapping in outdoors scenes, aka the sun

	bool saveFlag;
	
	void initBlendMaps(Ogre::Terrain* terrain);
	void createSun();

protected:

};
