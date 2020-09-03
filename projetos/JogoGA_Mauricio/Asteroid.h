#pragma once
#include "libUnicornio.h"

class Asteroid
{
public:
	Asteroid();
	Asteroid(float p_speed);
	~Asteroid();

	void setSpriteSheet(string p_sheet);
	void setPosition(float p_x, float p_y);
	void setScale(float p_x, float p_y);
	void setSpeed(float p_speed);

	Sprite getSprite();
	float getPosX();
	float getPosY();

	void update();
	void asteroidStart();
	void draw();

private:
	Sprite sprite;
	float x, y;
	float speed;
};

