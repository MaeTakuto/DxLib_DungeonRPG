#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../scene/gm_scene_play.h"
#include "menu_ui_commander.h"


// �R���X�g���N�^
MenuUICommander::MenuUICommander() {

}

// �f�X�g���N�^
MenuUICommander::~MenuUICommander() {

	delete main_menu_ui_;
	main_menu_ui_ = nullptr;

	delete message_ui_;
	message_ui_ = nullptr;
}

// �A�b�v�f�[�g
void MenuUICommander::update(float delta_time) {

	sequence_.update(delta_time);
}

// �`��
void MenuUICommander::draw() {

	if (main_menu_ui_) main_menu_ui_->draw();
	if (message_ui_) message_ui_->draw();
}

// �ҋ@���
bool MenuUICommander::seqIdle(const float delta_time) {

	if ( tnl::Input::IsKeyDownTrigger( eKeys::KB_ESCAPE ) ) {
		sequence_.change(&MenuUICommander::seqSelMainMenu);
		main_menu_ui_ = new MainMenuUI(menu_ui_pos_);
		ScenePlay* scene_play = static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());
		scene_play->setSelectUIFlg(true);
	}

	return true;
}

// ���C�����j���[�I�����
bool MenuUICommander::seqSelMainMenu(const float delta_time) {

	if (main_menu_ui_) {
		main_menu_ui_->update(delta_time);

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			ScenePlay* scene_play = static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());

			switch (main_menu_ui_->getSelectCmd())
			{
				// �Q�[���I���̑I����ʈړ�
			case MainMenuCmd::MC_GAMEOVER:
				sequence_.change(&MenuUICommander::seqSelGameOverMenu);
				break;
				// �E�B���h�E�����
			case MainMenuCmd::MC_CANCEL:
				sequence_.change(&MenuUICommander::seqIdle);
				delete main_menu_ui_;
				main_menu_ui_ = nullptr;

				scene_play->setSelectUIFlg(false);
				break;
			}
		}
	}

	return true;
}

// �Q�[���I���̑I�����
bool MenuUICommander::seqSelGameOverMenu(const float delta_time) {
	if (sequence_.isStart()) {
		message_ui_ = new MessageUI(mess_ui_pos_, mess_str_);
	}

	if (message_ui_) {
		message_ui_->update(delta_time);

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			ScenePlay* scene_play = static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());

			switch (message_ui_->getTwoChoiseUI()->getSelectCmd())
			{
			// �Q�[�����I��
			case TwoChoiseCmd::TCC_YES:
				sequence_.change(&MenuUICommander::seqIdle);
				delete main_menu_ui_;
				main_menu_ui_ = nullptr;
				delete message_ui_;
				message_ui_ = nullptr;
				scene_play->setSelectUIFlg(false);
				break;
			case TwoChoiseCmd::TCC_NO:
				sequence_.change(&MenuUICommander::seqSelMainMenu);
				delete message_ui_;
				message_ui_ = nullptr;
				break;
			}
		}
	}

	return true;
}