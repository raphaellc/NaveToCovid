#pragma once
#include "libUnicornio.h"
class GameObject
{
public:
	GameObject();
	~GameObject();

	Sprite getSprite();
	float getPosX();
	float getPosY();
	float getRot();

	virtual void setSpriteSheet(string p_sheet);
	virtual void setPosition(float p_x, float p_y);
	virtual void setScale(float p_x, float p_y);
	virtual void setSpeed(float p_speed);
	
	virtual void update();
	virtual void draw();

protected:
	Sprite sprite;
	float x, y;
	float speed;
};

