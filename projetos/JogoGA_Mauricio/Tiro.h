#pragma once
#include "libUnicornio.h"

class Tiro
{
public:
	Tiro();
	~Tiro();

	void setPosition(int p_x, int p_y);
	void setSpeed(float p_speed);
	float getSpeed();
	float getSpeedIntro();
	void setSpriteSheet(string p_spriteSheet);

	void moveShot();
	void draw();
	Sprite getSprite();
	int getPosX();
	int getPosY();	

	void setIsPowerUp(bool p_status);
	int getPowerUpTime();

private:
	Sprite sprite;
	float x, y;
	float speedIntro;
	float speed;

protected:
	bool isPowerUp;
	int counterPowerUp;
};

