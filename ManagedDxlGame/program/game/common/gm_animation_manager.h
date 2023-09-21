#pragma once


// �A�j���[�V�����Ǘ��N���X
class AnimationManager {
public:
	static AnimationManager* GetInstance();		// �C���X�^���X��Ԃ�
	static void Destroy();						// �C���X�^���X���폜

	// �A�j���[�V�����̃��[�h
	std::vector<int> loadAnimation(const std::string& anim_hdl_path, 
		int all_size, int x_size, int y_size, int anim_hdl_width, int anim_hdl_height);

	// �A�j���[�V�����̍폜
	void deleteAnimation(const std::string& anim_hdl_path, int all_size);

private:
	AnimationManager();							
	~AnimationManager();

	// �A�j���[�V�����n���h���̕ۑ���
	std::unordered_map< std::string, std::vector<int> > 
		anim_hdl_container_;

	// �A�j���[�V�����̍쐬
	std::vector<int> createAnimation(const std::string& anim_hdl_path,
		int all_size, int x_size, int y_size, int anim_hdl_width, int anim_hdl_height);

};