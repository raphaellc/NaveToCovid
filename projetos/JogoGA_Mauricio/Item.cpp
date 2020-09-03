#include "Item.h"

Item::Item()
{
}


Item::~Item()
{
}

void Item::itemInicializar()
{
	gRecursos.carregarSpriteSheet("powerUpShip", "assets/sprite/powerSpeedShip.png", 1, 1);
	gRecursos.carregarSpriteSheet("powerUpShoot", "assets/sprite/powerSpeedShoot.png", 1, 1);
}

void Item::setPosition(int p_x, int p_y)
{
	x = p_x;
	y = p_y;
}

void Item::setSpriteSheet(string p_spriteSheet)
{
	sprite.setSpriteSheet(p_spriteSheet);
}

void Item::startNewItem(int p_posX, int p_posY, int p_powerUp)
{
	sprite.setEscala(0.5f, 0.5f);
	powerUpType = p_powerUp;
	powerUpActive();
	setPosition(p_posX, p_posY);	
}

void Item::setPowerUp(int p_type)
{
	powerUpType = p_type;
}

int Item::getPowerUp()
{
	return powerUpType;
}

void Item::setSpeed(float p_speed)
{
	speed = p_speed;
}

float Item::getSpeed()
{
	return speed;
}

Sprite Item::getSprite()
{
	return sprite;
}

int Item::getPosX()
{
	return x;
}

int Item::getPosY()
{
	return y;
}

void Item::draw()
{
	sprite.desenhar(x, y);
}

void Item::powerUpActive()
{
	if (powerUpType == 0)
	{
		setSpriteSheet("powerUpShip");
		speed = 2.0f;
	}
	else if (powerUpType == 1)
	{
		setSpriteSheet("powerUpShoot");
		speed = 7.0f;
	}
}
