#pragma once
#include "libUnicornio.h"
#include "Tiro.h"
#include "GameObject.h"

class Player : public Tiro, public GameObject
{
public:
	Player();
	~Player();
	
	void playerInicializar();
	
	void setPosition(int p_x, int p_y);
	void setSpeed(float p_speed);
	float getSpeed();
	void setSpriteSheet(string p_spriteSheet);

	void update() override;
	void draw() override;
		
	float getRot();
	void setIsShoot(bool p_status);
	bool getIsShoot();

	void setAudioEffect(string p_name);

	void setIsPowerUp(bool p_status);
	int getPowerUpTime();

private:
	Som effectShoot;
	float speedIntro = 1.0f;
	bool isShoot;
	bool isPowerUp;
	int counterPowerUp;
	
	void move();
	void shoot();
	
};
