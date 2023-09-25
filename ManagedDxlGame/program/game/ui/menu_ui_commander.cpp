#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../scene/gm_scene_play.h"
#include "menu_ui_commander.h"


// コンストラクタ
MenuUICommander::MenuUICommander() {

}

// デストラクタ
MenuUICommander::~MenuUICommander() {

	delete main_menu_ui_;
	main_menu_ui_ = nullptr;

	delete message_ui_;
	message_ui_ = nullptr;
}

// アップデート
void MenuUICommander::update(float delta_time) {

	sequence_.update(delta_time);
}

// 描画
void MenuUICommander::draw() {

	if (main_menu_ui_) main_menu_ui_->draw();
	if (message_ui_) message_ui_->draw();
}

// 待機画面
bool MenuUICommander::seqIdle(const float delta_time) {

	if ( tnl::Input::IsKeyDownTrigger( eKeys::KB_ESCAPE ) ) {
		sequence_.change(&MenuUICommander::seqSelMainMenu);
		main_menu_ui_ = new MainMenuUI(menu_ui_pos_);
		ScenePlay* scene_play = static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());
		scene_play->setSelectUIFlg(true);
	}

	return true;
}

// メインメニュー選択画面
bool MenuUICommander::seqSelMainMenu(const float delta_time) {

	if (main_menu_ui_) {
		main_menu_ui_->update(delta_time);

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			ScenePlay* scene_play = static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());

			switch (main_menu_ui_->getSelectCmd())
			{
				// ゲーム終了の選択画面移動
			case MainMenuCmd::MC_GAMEOVER:
				sequence_.change(&MenuUICommander::seqSelGameOverMenu);
				break;
				// ウィンドウを閉じる
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

// ゲーム終了の選択画面
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
			// ゲームを終了
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