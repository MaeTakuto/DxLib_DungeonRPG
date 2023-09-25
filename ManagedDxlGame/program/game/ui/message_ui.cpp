#include "message_ui.h"
#include "../common/gm_graphic_manager.h"



// �R���X�g���N�^
MessageUI::MessageUI(tnl::Vector3 pos, std::string& mess_str) {

	std::string window_gpc_hdl_path = "graphics/MessageWindow.png";

	// �摜�A�����ȂǃZ�b�g
	window_gpc_hdl_ = GraphicManager::GetInstance()->loadGraph(window_gpc_hdl_path);
	message_str_ = mess_str;

	// �R�}���h�E�B���h�E�̕��A�����擾
	GetGraphSize(window_gpc_hdl_, &window_gpc_hdl_width_, &window_gpc_hdl_height_);

	// �\���ʒu�̏�����
	window_pos_ = pos;
	mess_pos_ = { window_pos_.x + STR_WIDTH_SPACE, window_pos_.y + STR_TOP_HEIGHT_SPACE, 0 };
	two_choise_ui_pos_ = { window_pos_.x + window_gpc_hdl_width_ + 20, window_pos_.y, 0 };

	two_choise_ui_ = new TwoChoiseUI(two_choise_ui_pos_);
}

// �f�X�g���N�^
MessageUI::~MessageUI() {

	delete two_choise_ui_;
	two_choise_ui_ = nullptr;
}

// �A�b�v�f�[�g
void MessageUI::update(float delta_time) {

	two_choise_ui_->update(delta_time);
}

// �`��
void MessageUI::draw() {

	DrawGraph(window_pos_.x, window_pos_.y, window_gpc_hdl_, false);

	SetFontSize(STR_FONT_SIZE);
	DrawStringEx(mess_pos_.x, mess_pos_.y, -1, message_str_.c_str());

	two_choise_ui_->draw();
}