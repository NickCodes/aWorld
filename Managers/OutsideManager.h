#ifndef DOTSCENELOADER_H
#define DOTSCENELOADER_H
#include "../util/DotSceneLoader.h"
#endif

#ifndef TERRAIN_H
#define TERRAIN_H
#include <Terrain/OgreTerrain.h>				// Ogre's terrain manager
#include <Terrain/OgreTerrainGroup.h>			// Ogre's terrain manager
#endif
	

class OutsideManager
{

public:

	OutsideManager();
	~OutsideManager(void);
	
	void init(Ogre::SceneManager*);										
	void loadTerrain(Ogre::String);									
	void loadLevel(void);	

private:

	Ogre::SceneManager* mSceneMgr;							// Pointer to scene manager
	
	Ogre::DotSceneLoader dotSceneLoader;					// Class to manage parsing DOTSCENE files for geometry

	Ogre::TerrainGroup* mTerrainGroup;						// Terrain manager
	Ogre::TerrainGlobalOptions* mTerrainGlobals;			// Terrain manager
    Ogre::Vector3 playerPosition;							// Used to snap camera to terrain
	Ogre::Real terrainHeight;								// Used to snap camera to terrain
	Ogre::String terrainFileName;							// Used to hold filename of terrain to load

protected:

};
