#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../scene/gm_scene_play.h"
#include "gm_enemy_symbol.h"


// �R���X�g���N�^
EnemySymbol::EnemySymbol() {
	// �L�����̉摜���[�h
	chara_anim_hdls_data_ = tnl::LoadCsv("csv/enemy_gpc_pass.csv");

	// �_�u���|�C���^�̏ꍇ
	p_gpc_chara_anim_hdls_ = new int* [ static_cast<int>( CharaDir::DIR_MAX ) ];

	for (int i = 0; i < static_cast<int>( CharaDir::DIR_MAX ); ++i) {
		p_gpc_chara_anim_hdls_[i] = new int[3];
	}

	for (int i = 0; i < static_cast<int>( CharaDir::DIR_MAX ); ++i) {
		LoadDivGraph(
			chara_anim_hdls_data_[0][i].getString().c_str(),
			chara_anim_hdls_data_[1][i].getInt(),
			chara_anim_hdls_data_[2][i].getInt(),
			chara_anim_hdls_data_[3][i].getInt(),
			GameManager::GPC_CHIP_WIDTH_SIZE,
			GameManager::GPC_CHIP_HEIGHT_SIZE,
			p_gpc_chara_anim_hdls_[i]
		);
	}

	pos_ = { 2, 1, 0 };
	next_pos_ = pos_;

	dir_ = CharaDir::DIR_DOWN;
}

// �f�X�g���N�^
EnemySymbol::~EnemySymbol() {

	for (int i = 0; i < static_cast<int>( CharaDir:: DIR_MAX ); ++i) {
		delete[] p_gpc_chara_anim_hdls_[i];
	}
	delete[] p_gpc_chara_anim_hdls_;
}

// �A�b�v�f�[�g
void EnemySymbol::update(float delta_time) {

	sequence_.update(delta_time);
}

// �`��
void EnemySymbol::draw() {

	DrawGraph(pos_.x * 32, pos_.y * 32, p_gpc_chara_anim_hdls_[ static_cast<int>( dir_ ) ][ANIM_IDLE], true);
}

// �ҋ@���
bool EnemySymbol::seqIdle(const float delta_time) {

	if (action_flg_) {
		// �ړ���̃|�W�V�����Z�b�g
		switch (dir_) {
		case CharaDir::DIR_DOWN:
			next_pos_.y += 1;
			break;
		case CharaDir::DIR_UP:
			next_pos_.y -= 1;
			break;
		case CharaDir::DIR_LEFT:
			next_pos_.x -= 1;
			break;
		case CharaDir::DIR_RIGHT:
			next_pos_.x += 1;
			break;
		}

		sequence_.change(&EnemySymbol::seqAction);
		action_flg_ = false;
	}

	return true;
}

/*
// �����蔻����m�F���
bool EnemySymbol::seqCheckWall(const float delta_time) {

	next_pos_.y += 1;
	sequence_.change(&EnemySymbol::seqMove);

	return true;
}
*/

// �ړ����
bool EnemySymbol::seqAction(const float delta_time) {

	// �������Ă��邩�ǂ���
	if (col_flg_) {
		dirChange();
		col_flg_ = false;
		next_pos_ = pos_;
	}
	else {
		move();
	}

	return true;
}

/*
// �����]�����
bool EnemySymbol::seqDirChange(const float delta_time) {

	return true;
}
*/

// �ړ�
void EnemySymbol::move() {

	if (abs(next_pos_.x - pos_.x) > 0.1f || abs(next_pos_.y - pos_.y) > 0.1f) {
		tnl::DebugTrace("pos_ = %.2f\n", pos_.length());
		tnl::DebugTrace("next_pos_ - pos_ = %.2f\n", next_pos_.length() - pos_.length());
		pos_ += (next_pos_ - pos_) * MOVE_SPEED;
	}
	else {
		pos_ = next_pos_;
		sequence_.change(&EnemySymbol::seqIdle);
	}
}

// �����]������
void EnemySymbol::dirChange() {

	tnl::Vector3 d_pos[ static_cast<int>( CharaDir::DIR_MAX ) ];

	d_pos[0] = { 0, -1, 0 };
	d_pos[1] = { 0, 1, 0 };
	d_pos[2] = { -1, 0, 0 };
	d_pos[3] = { 1, 0, 0 };

	ScenePlay* scene_play = static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());
	std::vector<CharaDir> dir;

	// ��������
	for (int i = 0; i < static_cast<int>(CharaDir::DIR_MAX); ++i) {
		if (scene_play->checkHitMapWall(pos_ + d_pos[i]) == 0) {
			dir.emplace_back(static_cast<CharaDir>(i));
		}
	} 

	int r = GetRand(static_cast<int>(dir.size() - 1));
	tnl::DebugTrace("r = %d\n", r);

	dir_ = dir[r];

	sequence_.change(&EnemySymbol::seqIdle);

}