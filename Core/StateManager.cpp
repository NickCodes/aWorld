#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include "../core/StateManager.h"
#endif

#ifndef OGRE_H
#define OGRE_H
#include "ogre.h"
#endif



void StateManager::init(void)
{
	state = 1;					// Set default state 1 (menu state)
}

int StateManager::getState(void)
{
	return state;
}


void StateManager::setState(int s)
{
	state = s;
}

