#pragma once
#include "../../dxlib_ext/dxlib_ext.h"


// �L�����̕���
enum class CharaDir {
	DIR_DOWN,		// ��
	DIR_LEFT,		// ��
	DIR_RIGHT,		// �E
	DIR_UP,			// ��
	DIR_MAX			// �ő�l
};

const int ANIM_IDLE = 1;	// �ҋ@���


// �L�����N�^�[�V���{���̊��N���X
class CharacterSymbol {
public:
	virtual ~CharacterSymbol() {};

	virtual void update(float delta_time) = 0;
	virtual void draw() = 0;

	virtual tnl::Vector3 getPos() = 0;			// �L�����̌��݂̈ʒu��Ԃ��B
	virtual tnl::Vector3 getNextPos() = 0;		// �L�����̎��̈ʒu��Ԃ��B

protected:
	const float MOVE_SPEED = 0.25f;		// �ړ����x

	tnl::Vector3 pos_;					// �ʒu���
	tnl::Vector3 next_pos_;				// �ړ���̈ʒu

	std::vector< std::vector < int > >
		gpc_chara_anim_hdls_;			// �L�����̉摜

	int** p_gpc_chara_anim_hdls_;		// �L�����̉摜

	std::vector< std::vector< tnl::CsvCell > > 
		chara_anim_hdls_data_;			// �L�����N�^�[�̃A�j���[�V�����f�[�^

	CharaDir dir_;						// �L�����̕���

};