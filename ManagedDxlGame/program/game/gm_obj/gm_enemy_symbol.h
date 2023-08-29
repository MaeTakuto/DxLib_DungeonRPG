#pragma once
#include "../base/gm_chara_symbol_base.h"



// �G�l�~�[�V���{���N���X
class EnemySymbol : public CharacterSymbol {
public:
	EnemySymbol();
	~EnemySymbol();

	void update(float delta_time) override;
	void draw() override;

	inline tnl::Vector3 getPos() override { return pos_; }							// �G�l�~�[�̌��݂̈ʒu��Ԃ��B
	inline tnl::Vector3 getNextPos() override { return next_pos_; }					// �G�l�~�[�̎��̈ʒu��Ԃ��B


private:
	// �G�l�~�[�̍s��
	tnl::Sequence<EnemySymbol> sequence_ 
		= tnl::Sequence<EnemySymbol>(this, &EnemySymbol::seqIdle);

	bool seqIdle(const float delta_time);		// �ҋ@���
	bool seqMove(const float delta_time);		// �ړ����
	bool seqDirChange(const float delta_time);	// �����]��

};
