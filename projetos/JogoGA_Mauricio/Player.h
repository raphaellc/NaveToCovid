#pragma once
#include "libUnicornio.h"
#include "Tiro.h"

class Player : public Tiro
{
public:
	Player();
	~Player();
	
	void playerInicializar();
	void setPosition(int p_x, int p_y);
	void setSpeed(float p_speed);
	float getSpeed();
	void setSpriteSheet(string p_spriteSheet);

	void update();

	Sprite getSprite();
	int getPosX();
	int getPosY();
	float getRot();
	void setIsShoot(bool p_status);
	bool getIsShoot();

	void setAudioEffect(string p_name);

	void setIsPowerUp(bool p_status);
	int getPowerUpTime();

protected:
	Som effectShoot;
	Sprite sprite;
	float x, y;
	float speed;
	float speedIntro = 1.0f;
	bool isShoot;
	bool isPowerUp;
	int counterPowerUp;

	void move();
	void shoot();
	void draw();
};