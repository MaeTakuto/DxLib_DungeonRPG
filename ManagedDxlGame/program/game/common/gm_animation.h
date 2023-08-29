#pragma once



class Animation {
public:
	Animation();
	~Animation();

	int* getAnim();

private:
	int* anim_hdls_;
	int width_all_size_;
	int height_all_size_;
	int all_size_;
};