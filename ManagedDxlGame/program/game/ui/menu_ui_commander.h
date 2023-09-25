#pragma once
#include "main_menu_ui.h"
#include "message_ui.h"


// セレクトメニューを表示
class MenuUICommander {
public:
	MenuUICommander();
	~MenuUICommander();

	void update(float delta_time);
	void draw();

private:
	MainMenuUI* main_menu_ui_ = nullptr;				// メインメニューを表示
	MessageUI* message_ui_ = nullptr;					// メッセージウィンドウを表示

	std::string mess_str_ = "ゲームを終了しますか？";

	tnl::Vector3 menu_ui_pos_ = { 50, 50, 0 };
	tnl::Vector3 mess_ui_pos_ = { 50, 450, 0 };

	tnl::Sequence<MenuUICommander> sequence_ =
		tnl::Sequence<MenuUICommander>(this, &MenuUICommander::seqIdle);

	bool seqIdle(const float delta_time);
	bool seqSelMainMenu(const float delta_time);
	bool seqSelGameOverMenu(const float delta_time);

	//void deleteUI

};