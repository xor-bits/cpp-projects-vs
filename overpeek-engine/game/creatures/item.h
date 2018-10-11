#pragma once

#include "../logic/game.h"
#include "creature.h"

class Item : public Creature {
private:
	int m_untilnexttarget;
	int m_wait;
	float m_curtarget_x;
	float m_curtarget_y;

public:
	Item(float x, float y);

	void submitToRenderer(graphics::Renderer *renderer, float renderOffsetX, float renderOffsetY);
	void update();
};