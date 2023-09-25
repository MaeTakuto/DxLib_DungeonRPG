#pragma once
#include "../base/ui_window_base.h"
#include "two_choise_ui.h"


// メッセージを表示するウィンドウクラス
class MessageUI : public WindowUIBase {
public:
	MessageUI(tnl::Vector3 pos, std::string& mess_str);
	~MessageUI();

	void update(float delta_time) override;
	void draw() override;

	inline TwoChoiseUI* getTwoChoiseUI() { return two_choise_ui_; }

private:
	TwoChoiseUI* two_choise_ui_ = nullptr;

	std::string message_str_;

	tnl::Vector3 two_choise_ui_pos_;
	tnl::Vector3 mess_pos_;

};