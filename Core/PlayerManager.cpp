#include "../core/PlayerManager.h"

PlayerManager::PlayerManager()
{

}

PlayerManager::~PlayerManager(void)
{
}

void PlayerManager::createPlayer(float hps, float heights, float speeds)
{
	hp=hps;
	height=heights;
	speed=speeds;
}

void PlayerManager::init()
{
	createPlayer(0,30,1);
}

