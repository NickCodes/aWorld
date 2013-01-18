#include "../core/Player.h"

Player::Player()
{

}

Player::~Player(void)
{
}

void Player::createPlayer(float hps, float heights, float speeds)
{
	hp=hps;
	height=heights;
	speed=speeds;
}

void Player::init()
{
	createPlayer(10,30,1);
}

