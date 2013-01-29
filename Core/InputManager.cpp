#include "../core/InputManager.h"


InputHandler::InputHandler(void){};
InputHandler::~InputHandler(void){};


void InputHandler::init(myOutsideManager* man, Ogre::RenderWindow* renderWindow, CameraController* camera, StateManager* s) 
{
	cam = camera;
	state = s;
	outsideManager = man;

	size_t hWnd = 0;																								
	renderWindow->getCustomAttribute("WINDOW", &hWnd);														// Get windows handle
	inputManager = OIS::InputManager::createInputSystem(hWnd);												// Create input manager												
	
	keyBoard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));		// Create keyboard, last arg is true for buffered 
	keyBoard->setEventCallback(this);																		// Add keyboard as KeyListener to capture keyboard events
	mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));					// Create mouse, Last arg is true for buffered
	mouse->setEventCallback(this);																			// Add mouse as listener to capture mouse events

	setMouseBounds(renderWindow->getWidth() - 5,renderWindow->getHeight() - 5);								// Set the mouse boundary to the render window size (assumed fullscreen. The subtraction is a buffer for the edge of the screen so the cursor can be seen)

	moved=false; up = false; left=false; down=false; right = false; escape=false; space=false;				// Flags for movement
}




void InputHandler::setMouseBounds(unsigned int x, unsigned int y)
{
	const OIS::MouseState &mouseState = mouse->getMouseState();
    
	mouseState.width  = x;
    mouseState.height = y;
}




void InputHandler::captureKeyboard(void)
{
	keyBoard->capture();			// Called once per frame to capture keybaord input (buffered or unbuffered)
}

void InputHandler::captureMouse(void)
{
	mouse->capture();				// Called once per frame to capture mouse input (buffered or unbuffered)}
}


bool InputHandler::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	if (state->getState() == 1)
		MyGUI::InputManager::getInstance().injectMousePress(e.state.X.abs, e.state.Y.abs, MyGUI::MouseButton::Enum(id));
	
	return true;
}

bool InputHandler::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	    if (state->getState() == 1)
			MyGUI::InputManager::getInstance().injectMouseRelease(e.state.X.abs, e.state.Y.abs, MyGUI::MouseButton::Enum(id));
		return true;
}


bool InputHandler::keyPressed( const OIS::KeyEvent& e )
{

	// If state is registered as 2, or in FPS control 
	if (state->getState() == 2)				
	{
		switch (e.key)
		{
		case OIS::KC_ESCAPE:
			escape=true;
			break;
		case OIS::KC_W:
			up = true;
			break;
		case OIS::KC_A:
			left = true;
			break;
		case OIS::KC_S:
			down = true;
			break;
		case OIS::KC_D:
			right = true;
			break;
		case OIS::KC_SPACE:
			Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL,"***** InputManager caught SPACE on keypress in FPS mode");
			space=true;
			break;
		}
	}

	// If state is registered as 1, or in MENU control 
	if (state->getState() == 1)				
	{
		switch (e.key)
		{
		case OIS::KC_ESCAPE:
			escape=true;
			break;
		case OIS::KC_SPACE:
			space=true;
			break;
		}

		MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(e.key), e.text);
		
	}

	return true;
}

bool InputHandler::keyReleased( const OIS::KeyEvent& e )
{
	
	// If state is registered as 2, or in FPS control 
	if (state->getState() == 2)				
	{
		switch (e.key)
		{
		case OIS::KC_W:
			up = false;
			break;
		case OIS::KC_A:
			left = false;
			break;
		case OIS::KC_S:
			down = false;
			break;
		case OIS::KC_D:
			right = false;
			break;
		case OIS::KC_SPACE:
			space=false;
			break;

		}
	}

	// If state is registered as 1, or in MENU control 
	if (state->getState() == 1)				
	{
		MyGUI::InputManager::getInstance().injectKeyRelease(MyGUI::KeyCode::Enum(e.key));
			
		switch (e.key)
		{		
		case OIS::KC_SPACE:
			space=false;
			break;
		}
	}
	return true;
}


bool InputHandler::mouseMoved(const OIS::MouseEvent &arg)
{

	// If state is registered as in FPS view, inject control to cameraController (cam)
	if (state->getState() == 2)
		cam->updateCamera(mouse->getMouseState().X.rel,mouse->getMouseState().Y.rel);
	
	// If state is registered as in MENU view, inject control to MyGUI::InputManager
	if (state->getState() == 1)
		MyGUI::InputManager::getInstance().injectMouseMove(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs);

	return true;
}


