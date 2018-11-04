#include "player.h"
#include "../../engine.h"
#include "../logic/game.h"
#include "../world/tile.h"

Player::Player(float x, float y, Inventory *inv) : Creature(x, y, 0, false, nullptr) {
	inventory = inv;
}

void Player::submitToRenderer(graphics::Renderer *renderer, float renderOffsetX, float renderOffsetY) {
	Creature::submitToRenderer(renderer, renderOffsetX, renderOffsetY);
}

void Player::update() {
	Creature::update();
	if (!Game::debugMode) Creature::collide();
}

void Player::hit() {
	Creature::hit();
}

void Player::place() {
	Tile* tmp;
	switch (heading)
	{
	case 0:
		tmp = Game::getTile(x, y - 1);
		//m_swingDir = 1;
		break;
	case 1:
		tmp = Game::getTile(x + 1, y);
		//m_swingDir = 2;
		break;
	case 2:
		tmp = Game::getTile(x, y + 1);
		//m_swingDir = 3;
		break;
	default:
		tmp = Game::getTile(x - 1, y);
		//m_swingDir = 4;
		break;
	}

	if (tmp) {
		Game::trySetTileObject(tmp, 4);
	}
	audio::AudioManager::play(1);
}