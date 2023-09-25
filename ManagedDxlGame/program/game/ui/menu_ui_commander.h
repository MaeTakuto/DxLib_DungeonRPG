#pragma once
#include "main_menu_ui.h"
#include "message_ui.h"


// �Z���N�g���j���[��\��
class MenuUICommander {
public:
	MenuUICommander();
	~MenuUICommander();

	void update(float delta_time);
	void draw();

private:
	MainMenuUI* main_menu_ui_ = nullptr;				// ���C�����j���[��\��
	MessageUI* message_ui_ = nullptr;					// ���b�Z�[�W�E�B���h�E��\��

	std::string mess_str_ = "�Q�[�����I�����܂����H";

	tnl::Vector3 menu_ui_pos_ = { 50, 50, 0 };
	tnl::Vector3 mess_ui_pos_ = { 50, 450, 0 };

	tnl::Sequence<MenuUICommander> sequence_ =
		tnl::Sequence<MenuUICommander>(this, &MenuUICommander::seqIdle);

	bool seqIdle(const float delta_time);
	bool seqSelMainMenu(const float delta_time);
	bool seqSelGameOverMenu(const float delta_time);

	//void deleteUI

};