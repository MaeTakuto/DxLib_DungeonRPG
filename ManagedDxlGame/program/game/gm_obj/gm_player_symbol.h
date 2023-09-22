#pragma once
#include "../base/gm_chara_symbol_base.h"
#include "gm_camera.h"



// �v���C���[�V���{���N���X
class PlayerSymbol : public CharacterSymbol {
public:
	PlayerSymbol();						// �R���X�g���N�^
	~PlayerSymbol();					// �f�X�g���N�^

	void update(float delta_time) override;		// �v���C���[�̃A�b�v�f�[�g
	void draw(const tnl::Vector3& camera_pos) override;						// �v���C���[�̕`��

	inline void setNextPos(tnl::Vector3& next_pos) { next_pos_ = next_pos; }		// �v���C���[�̎��̈ʒu���Z�b�g�B
	inline tnl::Vector3& getPos() override { return pos_; }							// �v���C���[�̌��݂̈ʒu��Ԃ��B
	inline tnl::Vector3& getNextPos() override { return next_pos_; }				// �v���C���[�̎��̈ʒu��Ԃ��B
	inline CharaAct getAct() override { return act_; }						// �v���C���[���s����������Ԃ��B
	inline void setColFlg(bool col_flg) override { col_flg_ = col_flg; }			// �����蔻��̃t���O���Z�b�g

private:
	tnl::Sequence<PlayerSymbol> sequence_ 
		= tnl::Sequence<PlayerSymbol>(this, &PlayerSymbol::seqIdle);				// �v���C���[�̍s�����

	bool seqIdle(const float delta_time);		// �ҋ@���
	bool seqCheckWall(const float delta_time);	// �����蔻��̊m�F
	bool seqMove(const float delta_time);		// �ړ����

};
