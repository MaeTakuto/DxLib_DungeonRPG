#include "message_ui.h"
#include "../common/gm_graphic_manager.h"



// コンストラクタ
MessageUI::MessageUI(tnl::Vector3 pos, std::string& mess_str) {

	std::string window_gpc_hdl_path = "graphics/MessageWindow.png";

	// 画像、文字などセット
	window_gpc_hdl_ = GraphicManager::GetInstance()->loadGraph(window_gpc_hdl_path);
	message_str_ = mess_str;

	// コマンドウィンドウの幅、高さ取得
	GetGraphSize(window_gpc_hdl_, &window_gpc_hdl_width_, &window_gpc_hdl_height_);

	// 表示位置の初期化
	window_pos_ = pos;
	mess_pos_ = { window_pos_.x + STR_WIDTH_SPACE, window_pos_.y + STR_TOP_HEIGHT_SPACE, 0 };
	two_choise_ui_pos_ = { window_pos_.x + window_gpc_hdl_width_ + 20, window_pos_.y, 0 };

	two_choise_ui_ = new TwoChoiseUI(two_choise_ui_pos_);
}

// デストラクタ
MessageUI::~MessageUI() {

	delete two_choise_ui_;
	two_choise_ui_ = nullptr;
}

// アップデート
void MessageUI::update(float delta_time) {

	two_choise_ui_->update(delta_time);
}

// 描画
void MessageUI::draw() {

	DrawGraph(window_pos_.x, window_pos_.y, window_gpc_hdl_, false);

	SetFontSize(STR_FONT_SIZE);
	DrawStringEx(mess_pos_.x, mess_pos_.y, -1, message_str_.c_str());

	two_choise_ui_->draw();
}