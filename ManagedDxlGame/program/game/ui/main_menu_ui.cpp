#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../common/gm_graphic_manager.h"
#include "main_menu_ui.h"


// �R���X�g���N�^
MainMenuUI::MainMenuUI(const tnl::Vector3& gpc_pos) {

	// �I�𒆂̃R�}���h�̏�����
	select_cmd_ = static_cast<MainMenuCmd>(static_cast<int>(MainMenuCmd::MC_BEGIN) + 1);

	std::string window_gpc_hdl_path = "graphics/SelectWindow.png";
	std::string select_cursor_gpc_hdl_path = "graphics/select_cursor01.png";

	// �摜�̃��[�h
	window_gpc_hdl_ = GraphicManager::GetInstance()->loadGraph(window_gpc_hdl_path);
	select_cursor_gpc_hdl_ = GraphicManager::GetInstance()->loadGraph(select_cursor_gpc_hdl_path);

	// �R�}���h�E�B���h�E�̕��A�����擾
	GetGraphSize(window_gpc_hdl_, &window_gpc_hdl_width_, &window_gpc_hdl_height_);

	// �R�}���h�����̏�����
	cmd_str_[static_cast<int>(MainMenuCmd::MC_GAMEOVER)] = "�Q�[���I��";
	cmd_str_[static_cast<int>(MainMenuCmd::MC_CANCEL)] = "���ǂ�";

	// �\���ʒu�̏�����
	window_pos_ = gpc_pos;
	cmd_pos_ = { window_pos_.x + STR_WIDTH_SPACE, window_pos_.y + STR_TOP_HEIGHT_SPACE, 0 };

	// �I���J�[�\��������
	select_cursor_pos_ = new tnl::Vector3[static_cast<int>(MainMenuCmd::MC_END)];

	for (int i = 0; i < static_cast<int>(MainMenuCmd::MC_END); ++i) {
		select_cursor_pos_[i] = { cmd_pos_.x - 20, cmd_pos_.y + (STR_TOP_HEIGHT_SPACE / 2) + (i * STR_HEIGHT_SPACE), 0 };
	}

}

// �f�X�g���N�^
MainMenuUI::~MainMenuUI() {

	delete[] select_cursor_pos_;
	select_cursor_pos_ = nullptr;
}

// �A�b�v�f�[�g�֐�
void MainMenuUI::update(float delta_time) {

	// �㉺�L�[���������Ƃ�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP, eKeys::KB_W)) {
		if (select_cmd_ == static_cast<MainMenuCmd>(static_cast<int>(MainMenuCmd::MC_BEGIN) + 1)) select_cmd_ = static_cast<MainMenuCmd>(static_cast<int>(MainMenuCmd::MC_END) - 1);
		else select_cmd_ = static_cast<MainMenuCmd>(static_cast<int>(select_cmd_) - 1);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN, eKeys::KB_S)) {
		if (select_cmd_ == static_cast<MainMenuCmd>(static_cast<int>(MainMenuCmd::MC_END) - 1)) select_cmd_ = static_cast<MainMenuCmd>(static_cast<int>(MainMenuCmd::MC_BEGIN) + 1);
		else select_cmd_ = static_cast<MainMenuCmd>(static_cast<int>(select_cmd_) + 1);

	}

}

// �`��֐�
void MainMenuUI::draw() {

	DrawGraph(window_pos_.x, window_pos_.y, window_gpc_hdl_, false);
	DrawRotaGraph(select_cursor_pos_[static_cast<int>(select_cmd_)].x, select_cursor_pos_[static_cast<int>(select_cmd_)].y, 0.85f, 0, select_cursor_gpc_hdl_, false);

	SetFontSize(STR_FONT_SIZE);
	for (int i = 0; i < static_cast<int>(MainMenuCmd::MC_END); ++i) {
		DrawStringEx(cmd_pos_.x, cmd_pos_.y + (STR_HEIGHT_SPACE * i), -1, cmd_str_[i].c_str());
	}
}