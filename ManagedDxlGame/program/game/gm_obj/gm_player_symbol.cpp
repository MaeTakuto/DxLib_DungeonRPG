#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../common/gm_animation_manager.h"
#include "gm_player_symbol.h"


// �R���X�g���N�^
PlayerSymbol::PlayerSymbol() {
	// �L�����̉摜�f�[�^�̃��[�h
	chara_anim_hdls_data_ = tnl::LoadCsv("csv/player_gpc_pass.csv");
	
	// std::vector�̏ꍇ 
	chara_anim_hdls_.resize( static_cast<int>( CharaDir::DIR_MAX ) );

	for (int i = 0; i < static_cast<int>(CharaDir::DIR_MAX); ++i) {

		chara_anim_hdls_[i].resize( chara_anim_hdls_data_[1][i].getInt() );

		// �A�j���[�V�����̎擾
		chara_anim_hdls_[i] = AnimationManager::GetInstance()->loadAnimation(
			chara_anim_hdls_data_[0][i].getString(),
			chara_anim_hdls_data_[1][i].getInt(),
			chara_anim_hdls_data_[2][i].getInt(),
			chara_anim_hdls_data_[3][i].getInt(),
			GameManager::GPC_CHIP_WIDTH_SIZE,
			GameManager::GPC_CHIP_HEIGHT_SIZE );
	}
	
	// �ʒu���ȂǏ�����
	pos_ = { 1, 1, 0 };
	next_pos_ = pos_;
	col_flg_ = false;

	dir_ = CharaDir::DIR_DOWN;
	act_ = CharaAct::WAIT;
}

// �f�X�g���N�^
PlayerSymbol::~PlayerSymbol() {
	
}

// �A�b�v�f�[�g
void PlayerSymbol::update(float delta_time) {

	sequence_.update(delta_time);
}

// �`��
void PlayerSymbol::draw() {

	DrawGraph( pos_.x * 32, pos_.y * 32, chara_anim_hdls_[ static_cast<int>( dir_ ) ][ ANIM_IDLE ], true );

	DrawStringEx(10, 10, -1, "pos_x = %.2f, pos_y = %.2f", pos_.x, pos_.y);

}

// �ҋ@���
bool PlayerSymbol::seqIdle(const float delta_time) {

	if (act_ == CharaAct::END) {
		act_ = CharaAct::WAIT;
	}

	// A�L�[�i���ړ��j
	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		next_pos_.x -= 1;
		dir_ = CharaDir::DIR_LEFT;
		sequence_.change(&PlayerSymbol::seqCheckWall);
		return true;
	}

	// D�L�[�i�E�ړ��j
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		next_pos_.x += 1;
		dir_ = CharaDir::DIR_RIGHT;
		sequence_.change(&PlayerSymbol::seqCheckWall);
		return true;
	}

	// W�L�[�i��ړ��j
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		next_pos_.y -= 1;
		dir_ = CharaDir::DIR_UP;
		sequence_.change( &PlayerSymbol::seqCheckWall);
		return true;
	}

	// S�L�[�i���ړ��j
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		next_pos_.y += 1;
		dir_ = CharaDir::DIR_DOWN;
		sequence_.change(&PlayerSymbol::seqCheckWall);
		return true;
	}
	
	return true;
}

// �����蔻��̊m�F
bool PlayerSymbol::seqCheckWall(const float delta_time) {

	if (col_flg_) {
		sequence_.change(&PlayerSymbol::seqIdle);
		next_pos_ = pos_;
		col_flg_ = false;
	}
	else {
		sequence_.change(&PlayerSymbol::seqMove);
		act_ = CharaAct::BEGIN;
	}

	return true;
}

// �ړ����
bool PlayerSymbol::seqMove(const float delta_time) {

	act_ = CharaAct::ACT;

	if ( abs(next_pos_.x - pos_.x) > 0.1f || abs(next_pos_.y - pos_.y) > 0.1f ) {
		//tnl::DebugTrace("pos_ = %.2f\n", pos_.length());
		//tnl::DebugTrace("next_pos_ - pos_ = %.2f\n", next_pos_.length() - pos_.length());
		pos_ += (next_pos_ - pos_) * MOVE_SPEED;
	}
	else {
		pos_ = next_pos_;
		act_ = CharaAct::END;
		sequence_.change(&PlayerSymbol::seqIdle);
	}
	
	return true;
}