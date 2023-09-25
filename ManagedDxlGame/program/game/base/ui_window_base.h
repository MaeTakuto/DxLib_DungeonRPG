#pragma once
#include "../../dxlib_ext/dxlib_ext.h"


// ���b�Z�[�W�E�B���h�E��\������N���X�̃x�[�X
class WindowUIBase {
public:
	virtual ~WindowUIBase() {};

	virtual void update(float delta_time) = 0;
	virtual void draw() = 0;

protected:
	const int STR_TOP_HEIGHT_SPACE = 30;		// �R�}���h�e�L�X�g�̈�ԏ�̍����̊Ԋu
	const int STR_HEIGHT_SPACE = 40;			// �R�}���h�e�L�X�g�̏㉺�̕����̊Ԋu
	const int STR_WIDTH_SPACE = 50;				// �R�}���h�e�L�X�g�̉��̊Ԋu
	const int STR_FONT_SIZE = 25;				// �R�}���h�e�L�X�g�̃t�H���g�T�C�Y

	int window_gpc_hdl_;						// �R�}���h�E�B���h�E�̉摜
	int window_gpc_hdl_width_;					// �R�}���h�E�B���h�E�̕�
	int window_gpc_hdl_height_;					// �R�}���h�E�B���h�E�̍���

	tnl::Vector3 window_pos_;					// �R�}���h�E�B���h�E�̉摜�ʒu

};