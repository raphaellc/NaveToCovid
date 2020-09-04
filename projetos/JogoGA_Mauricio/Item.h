#pragma once
#include "libUnicornio.h"
#include "ItemBase.h"

class Item : public ItemBase
{
public:
	Item();
	~Item();

	void itemInicializar();
	void setPosition(int p_x, int p_y);
	void setSpriteSheet(string p_spriteSheet);
	void startNewItem(int p_posX, int p_posY, int p_powerUp);

	void setPowerUp(int p_type) override;
	int getPowerUp() override;
	void setSpeed(float p_speed) override;
	float getSpeed() override;

	Sprite getSprite();
	int getPosX();
	int getPosY();
	void draw();

	virtual void powerUpActive() override;

protected:
	Sprite sprite;
	float x, y;
};

