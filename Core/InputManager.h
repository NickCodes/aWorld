#include <OIS.h>
#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISInputManager.h>
#include <OgreRenderWindow.h>

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include "../core/CameraController.h"
#endif

#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include "../core/StateManager.h"
#endif

#ifndef MYGUI_H
#define MYGUI_H
#include "MyGUI.h"
#endif

#ifndef OUTSIDEMANAGER_H
#define OUTSIDEMANAGER_H
#include "../managers/myOutsideManager.h"
#endif


class InputHandler : public OIS::KeyListener, public OIS::MouseListener

{
public:
		InputHandler(void);
		~InputHandler(void);

		void init(myOutsideManager*, Ogre::RenderWindow *, CameraController *, StateManager *);			// Init takes the application's render window and camera controller (from my camera controller class); 
		void captureKeyboard(void);																		// Tells OIS to capture keyboard input once per frame
		void captureMouse(void);																		// Tells OIS to capture mouse input once per frame
		void setMouseBounds(unsigned int x, unsigned int y);																			// Sets the bounds of the mouse from upper left IE x=800 y=600
		
		bool up, down, left, right, escape, moved, space;												// Values for acting on basic movement and mouse movement - this needs a better solution TODO
		
private:

		CameraController* cam;																			// To hold the camera controller that is passed
		StateManager* state;																			// to hold the state manager that is passed
		myOutsideManager* outsideManager;
		Ogre::RenderWindow* renderWindow;	

		OIS::Mouse* mouse;																				
	    OIS::Keyboard* keyBoard;																		
		OIS::InputManager* inputManager;
		
		// Overridden virtual key/mouse functions
		bool keyPressed( const OIS::KeyEvent & );														
		bool keyReleased( const OIS::KeyEvent & );									
		bool mouseMoved( const OIS::MouseEvent &e );								
		bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );		
		bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );		
	
};