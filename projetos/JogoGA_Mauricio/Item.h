#pragma once
#include "ItemBase.h"

class Item : public ItemBase
{
public:
	Item();
	~Item();

	void itemInicializar();
	void startNewItem(int p_posX, int p_posY, int p_powerUp);

	void setPowerUp(int p_type) override;
	int getPowerUp() override;
	void setSpeed(float p_speed) override;
	float getSpeed() override;
		
	void powerUpActive() override;
};

