#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "ui_window_base.h"



class SelectUIBase : public WindowUIBase {
public:
	virtual ~SelectUIBase() {};

	virtual void update(float delta_time) = 0;
	virtual void draw() = 0;

protected:
	int select_cursor_gpc_hdl_;					// �I���J�[�\���̉摜

	std::string cmd_str_;

	tnl::Vector3* select_cursor_pos_;			// �I���J�[�\���̕\���ʒu
	tnl::Vector3 cmd_pos_;						// �R�}���h�e�L�X�g�̕\���ʒu

};