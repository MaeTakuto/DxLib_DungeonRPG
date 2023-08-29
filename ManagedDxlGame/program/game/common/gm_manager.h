#pragma once


class SceneBase;

class GameManager {
public:
	static constexpr int TITLE_FONT_SIZE = 80;								// �^�C�g���̃t�H���g�T�C�Y
	static constexpr int NORMAL_FONT_SIZE = 30;								// �m�[�}���̃t�H���g�T�C�Y

	static constexpr int GPC_CHIP_WIDTH_SIZE = 32;							// �摜���̃`�b�v�T�C�Y
	static constexpr int GPC_CHIP_HEIGHT_SIZE = 32;							// �摜�c�̃`�b�v�T�C�Y


	static GameManager* GetInstance(SceneBase* start_scene = nullptr);		// �Q�[���}�l�[�W���[�̃A�h���X��Ԃ�
	inline static void Destroy() { delete GetInstance(); }					// �A�h���X�̍폜

	void update(float delta_time);											// �Q�[���}�l�[�W���[�̍X�V
	void changeScene(SceneBase* next_scene);								// �V�[���̐؂�ւ����s��
	
private:
	GameManager(SceneBase* start_scene);									// �R���X�g���N�^

	SceneBase* now_scene_ = nullptr;										// ���݂̃V�[��
	SceneBase* next_scene_ = nullptr;										// ���̃V�[��

	tnl::Sequence<GameManager> sequense_
		= tnl::Sequence<GameManager>(this, &GameManager::seqRun);			// �Q�[���}�l�[�W���[�̏��

	bool seqRun(const float delta_time);									// �������Ȃ�
	bool seqChangeScene(const float delta_time);							// �V�[���̍X�V

};