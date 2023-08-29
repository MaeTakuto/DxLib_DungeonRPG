#pragma once
#include "../base/gm_chara_symbol_base.h"



// �v���C���[�V���{���N���X
class PlayerSymbol : public CharacterSymbol {
public:
	PlayerSymbol();						// �R���X�g���N�^
	~PlayerSymbol();					// �f�X�g���N�^

	void update(float delta_time) override;		// �v���C���[�̃A�b�v�f�[�g
	void draw() override;						// �v���C���[�̕`��

	inline void setNextPos(tnl::Vector3 next_pos) { next_pos_ = next_pos; }			// �v���C���[�̎��̈ʒu���Z�b�g�B
	inline tnl::Vector3 getPos() override { return pos_; }							// �v���C���[�̌��݂̈ʒu��Ԃ��B
	inline tnl::Vector3 getNextPos() override { return next_pos_; }					// �v���C���[�̎��̈ʒu��Ԃ��B

private:
	tnl::Sequence<PlayerSymbol> sequence_ 
		= tnl::Sequence<PlayerSymbol>(this, &PlayerSymbol::seqIdle);				// �v���C���[�̍s�����

	bool seqIdle(const float delta_time);		// �ҋ@���
	bool seqMove(const float delta_time);		// �ړ����

};
