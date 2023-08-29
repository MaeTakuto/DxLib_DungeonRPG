#pragma once


class SceneBase {
public:
	virtual ~SceneBase() {};

	virtual void update(float delta_time) = 0;
	virtual void draw() = 0;
};