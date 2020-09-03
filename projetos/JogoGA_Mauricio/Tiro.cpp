#include "Tiro.h"



Tiro::Tiro()
{
	speedIntro = 4.0f;
	isPowerUp = false;
	counterPowerUp = 0;
}


Tiro::~Tiro()
{
}

void Tiro::setPosition(int p_x, int p_y)
{
	x = p_x;
	y = p_y;
}

void Tiro::setSpeed(float p_speed)
{
	speed = p_speed;
}

float Tiro::getSpeed()
{
	return speed;
}

float Tiro::getSpeedIntro()
{
	return speedIntro;
}

void Tiro::setSpriteSheet(string p_spriteSheet)
{
	sprite.setSpriteSheet(p_spriteSheet);
}

void Tiro::moveShot()
{
	y -= speed;
}

void Tiro::draw()
{
	sprite.desenhar(x, y);
}

Sprite Tiro::getSprite()
{
	return sprite;
}

int Tiro::getPosX()
{
	return x;
}

int Tiro::getPosY()
{
	return y;
}

void Tiro::setIsPowerUp(bool p_status)
{
	isPowerUp = p_status;
}

int Tiro::getPowerUpTime()
{
	return counterPowerUp;
}
