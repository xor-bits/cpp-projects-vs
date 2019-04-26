#pragma once

#include "creature.h"

class Pathfinder;
class Zombie : public Creature {
private:
	float m_untilnexttarget;
	float m_wait;
	float m_hit_cooldown;
	float m_check_player_cooldown;
	float m_curtarget_x;
	float m_curtarget_y;
	bool m_chasing;

	Pathfinder* m_path = nullptr;
	std::vector<glm::vec2>* m_retrace;
	unsigned int m_retrace_checkpoint;
	glm::ivec2 last_target_pos;
	int m_result;
	int m_stuck_timer;

private:
	void followTarget(float divider);

public:
	Zombie(float x, float y);
	~Zombie();

	void ai(float divider);
	void update(int index, float divider);
	void collide(float divider);
};