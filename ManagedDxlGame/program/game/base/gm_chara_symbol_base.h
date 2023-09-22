#pragma once
#include "../../dxlib_ext/dxlib_ext.h"


// �L�����̕���
enum class CharaDir {
	DIR_UP,			// ��
	DIR_DOWN,		// ��
	DIR_LEFT,		// ��
	DIR_RIGHT,		// �E
	DIR_MAX			// �ő�l
};

// �L�����̍s�����
enum class CharaAct {
	WAIT,
	BEGIN,
	ACT,
	END
};

const int ANIM_IDLE = 1;	// �ҋ@���


// �L�����N�^�[�V���{���̊��N���X
class CharacterSymbol {
public:
	virtual ~CharacterSymbol() {};

	virtual void update(float delta_time) = 0;
	virtual void draw(const tnl::Vector3& camera_pos) = 0;

	virtual tnl::Vector3& getPos() = 0;			// �L�����̌��݂̈ʒu��Ԃ��B
	virtual tnl::Vector3& getNextPos() = 0;		// �L�����̎��̈ʒu��Ԃ��B
	virtual CharaAct getAct() = 0;			// �L�������s�����Ă��邩��Ԃ��B
	virtual void setColFlg(bool col_flg) = 0;	// �L�����ɓ����蔻��Z�b�g

protected:
	const float MOVE_SPEED = 0.25f;		// �ړ����x
	const float WALK_TIME = 0.25f;
	const float RUN_TIME = 0.05f;

	tnl::Vector3 pos_;					// �ʒu���
	tnl::Vector3 next_pos_;				// �ړ���̈ʒu

	std::vector< std::vector < int > >
		chara_anim_hdls_;				// �L�����̃A�j���[�V����

	int anim_frame_;					// �A�j���[�V�����t���[��
	float anim_time_count_;				// �A�j���[�V�����̎���

	bool col_flg_;						// �Փ˔���

	std::vector< std::vector< tnl::CsvCell > > 
		chara_anim_hdls_data_;			// �L�����N�^�[�̃A�j���[�V�����f�[�^

	CharaDir dir_;						// �L�����̕���
	CharaAct act_;						// �L�����̍s�����

};