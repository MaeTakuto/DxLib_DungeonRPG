#pragma once
#include "../common/gm_manager.h"


// ÉJÉÅÉâÉNÉâÉX
class Camera {
public:
	Camera(const tnl::Vector3 target_pos);
	~Camera();

	void update(const tnl::Vector3 target_pos);

	inline tnl::Vector3 getPos() { return pos_; }

private:
	const float MAX_UP_POS = 8 * GameManager::GPC_DRAW_CHIP_SIZE;
	const float MAX_DOWN_POS = 22 * GameManager::GPC_DRAW_CHIP_SIZE;
	const float MAX_LEFT_POS = 12 * GameManager::GPC_DRAW_CHIP_SIZE;
	const float MAX_RIGHT_POS = 30 * GameManager::GPC_DRAW_CHIP_SIZE;

	tnl::Vector3 pos_;

};