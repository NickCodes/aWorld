// Nick Fisher 2012
// OGRE3D application
// AppClass.h

// Include --------------------------------------------------------------------------------------------
#include "OgreBase.h"
#include "../core/InputManager.h"
#include "../managers/guiManager.h"
#include "../util/DotSceneLoader.h"

#ifndef OUTSIDEMANAGER_H
#define OUTSIDEMANAGER_H
#include "../managers/myOutsideManager.h"
#endif

#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H
#include "../core/PlayerManager.h"
#endif

#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include "../core/StateManager.h"
#endif

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include "../core/CameraController.h"
#endif

#ifndef TERRAIN_H
#define TERRAIN_H
#include <Terrain/OgreTerrain.h>				// Ogre's terrain manager
#include <Terrain/OgreTerrainGroup.h>			// Ogre's terrain manager
#endif
	


class app : public Base										// Inherits my base framework
{

public:

	app(void);
	~app(void);
	
	void initManagers(void);								// Set up managers (input, state, etc)
	void kickoff(void);
	void update(void);										// Called from main each frame
	void setState (int);
	int	 getState(void);									// Returns the state from private stateManager

	
private:
	
	bool shutDownFlag;										// Flag to shut down the application
	float moveScale, mouseScale, playerHeight;				// Modify this to increase/decrease movement/look speed
	

	// Managers for various tasks	------------------------------------------------------------------------
	StateManager stateManager;								// Class to control game states
	myGUIManager guiManager;								// Class to handke GUI elements
	CameraController cameraController;						// Class to control camera movement 
	InputHandler inputManager;								// Class to handle keyboard and mouse input
	PlayerManager playerManager;
	myOutsideManager outsideManager;						// Class to handle loading terrain

	Ogre::DotSceneLoader dotSceneLoader;					// Class to manage parsing DOTSCENE files for geometry

	// Terrain	--------------------------------------------------------------------------------------------
	Ogre::TerrainGroup* mTerrainGroup;						// Terrain manager
	Ogre::TerrainGlobalOptions* mTerrainGlobals;			// Terrain manager
    Ogre::Vector3 playerPosition;							// Used to snap camera to terrain
	Ogre::Real terrainHeight;								// Used to snap camera to terrain
	Ogre::String terrainFileName;							// Used to hold filename of terrain to load

	void evaluateKeypress(void);							// This is where I define my key event code (escape sequence, etc)
			
protected:

};
