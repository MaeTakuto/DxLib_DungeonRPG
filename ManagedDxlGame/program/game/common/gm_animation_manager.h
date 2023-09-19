#pragma once


// �A�j���[�V�����Ǘ��N���X
class AnimationManager {
public:
	static AnimationManager* GetInstance();		// �C���X�^���X��Ԃ�
	static void Destroy();						// �C���X�^���X���폜

	// �A�j���[�V�����̃��[�h
	int* loadAnimation(std::string& anim_hdl_pass, 
		int all_size, int x_size, int y_size, int anim_hdl_width, int anim_hdl_height);

	// �A�j���[�V�����̍폜
	void deleteAnimation(std::string& anim_hdl_pass, int all_size);

private:
	AnimationManager();							
	~AnimationManager();

	// �A�j���[�V�����n���h���̕ۑ���
	std::unordered_map< std::string, int* > 
		anim_hdl_container_;

	// �A�j���[�V�����̍쐬
	int* createAnimation(std::string& anim_hdl_pass,
		int all_size, int x_size, int y_size, int anim_hdl_width, int anim_hdl_height);

};