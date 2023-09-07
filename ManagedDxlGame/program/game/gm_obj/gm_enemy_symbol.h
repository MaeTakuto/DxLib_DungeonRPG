#pragma once
#include "../base/gm_chara_symbol_base.h"



// �G�l�~�[�V���{���N���X
class EnemySymbol : public CharacterSymbol {
public:
	EnemySymbol(tnl::Vector3 pos);
	~EnemySymbol();

	void update(float delta_time) override;
	void draw() override;

	inline tnl::Vector3& getPos() override { return pos_; }							// �G�l�~�[�̌��݂̈ʒu��Ԃ��B
	inline tnl::Vector3& getNextPos() override { return next_pos_; }					// �G�l�~�[�̎��̈ʒu��Ԃ��B
	inline bool getActionFlg() override { return action_flg_; }						// �G�l�~�[���s�����Ă��邩��Ԃ��B
	inline void setActionFlg(bool action_flg) { action_flg_ = action_flg; }			// �G�l�~�[�̍s���t���O������B
	inline void setColFlg(bool col_flg) override { col_flg_ = col_flg; }			// �����蔻��t���O�̃Z�b�g

private:
	// �G�l�~�[�̍s��
	tnl::Sequence<EnemySymbol> sequence_ 
		= tnl::Sequence<EnemySymbol>(this, &EnemySymbol::seqIdle);

	bool seqIdle(const float delta_time);		// �ҋ@���
	// bool seqCheckWall(const float delta_time);	// �����蔻��̊m�F
	bool seqAction(const float delta_time);		// �ړ����
	// bool seqDirChange(const float delta_time);	// �����]��

	void move();								// �ړ�����
	void dirChange();							// �����]������

};
