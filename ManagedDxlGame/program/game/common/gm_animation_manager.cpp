#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_animation_manager.h"


// �R���X�g���N�^
AnimationManager::AnimationManager() {

}

// �f�X�g���N�^
AnimationManager::~AnimationManager() {
	
}

// �C���X�^���X��Ԃ��B
AnimationManager* AnimationManager::GetInstance() {

	static AnimationManager* instance = nullptr;
	if (!instance) {
		instance = new AnimationManager();
	}
	return instance;
}

// �C���X�^���X���폜
void AnimationManager::Destroy() {
	delete GetInstance();
}

// �A�j���[�V�����̃��[�h
int* AnimationManager::loadAnimation(std::string& anim_hdl_pass, 
	int all_size, int x_size, int y_size, int anim_hdl_width, int anim_hdl_height) {

	auto it = anim_hdl_container_.find(anim_hdl_pass);

	// ���łɃA�j���[�V�����̃p�X�����݂����ꍇ
	if (it != anim_hdl_container_.end()) return anim_hdl_container_[anim_hdl_pass];

	auto anim_hdl = createAnimation(anim_hdl_pass, all_size, x_size, y_size, anim_hdl_width, anim_hdl_height);
	anim_hdl_container_.insert(make_pair(anim_hdl_pass, anim_hdl));

	return anim_hdl;
}

// �A�j���[�V�����̍폜
void AnimationManager::deleteAnimation(std::string& anim_hdl_pass, int all_size) {

	auto it = anim_hdl_container_.find(anim_hdl_pass);

	if (it != anim_hdl_container_.end()) {
		for(int i = 0; i < all_size; ++i) 
		DeleteGraph(it->second[i]);
	}
}

// �A�j���[�V�����̃��[�h
int* AnimationManager::createAnimation(std::string& anim_hdl_pass,
	int all_size, int x_size, int y_size, int anim_hdl_width, int anim_hdl_height) {

	int* anim_hdl = new int[all_size];

	LoadDivGraph(
		anim_hdl_pass.c_str(),
		all_size,
		x_size,
		y_size,
		anim_hdl_width,
		anim_hdl_height,
		anim_hdl
		);

	return anim_hdl;
}
