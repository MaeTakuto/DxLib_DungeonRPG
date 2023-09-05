#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "gm_player_symbol.h"


// コンストラクタ
PlayerSymbol::PlayerSymbol() {
	// キャラの画像ロード
	chara_anim_hdls_data_ = tnl::LoadCsv("csv/player_gpc_pass.csv");

	// ダブルポインタの場合
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

	/*
	// std::vectorの場合 
	int temp_gpc_hdls[DIR_MAX][3];
	gpc_chara_anim_hdls_.resize( DIR_MAX );

	for (int i = 0; i < DIR_MAX; ++i) {
		LoadDivGraph(
			gpc_hdls_pass_[i][0].c_str(),
			3,
			3,
			1,
			GameManager::GPC_CHIP_WIDTH_SIZE,
			GameManager::GPC_CHIP_HEIGHT_SIZE,
			temp_gpc_hdls[i]
		);
	}

	for ( int i = 0; i < DIR_MAX; ++i ) {
		gpc_chara_anim_hdls_[i].resize(3);

		for (int k = 0; k < 3; ++k) {
			gpc_chara_anim_hdls_[i][k] = temp_gpc_hdls[i][k];
		}
	}
	*/

	pos_ = { 1, 1, 0 };
	next_pos_ = pos_;
	col_flg_ = false;

	dir_ = CharaDir::DIR_DOWN;
	action_flg_ = false;
}

// デストラクタ
PlayerSymbol::~PlayerSymbol() {
	
	for (int i = 0; i < static_cast<int>( CharaDir::DIR_MAX ); ++i) {
		delete[] p_gpc_chara_anim_hdls_[i];
	}
	delete[] p_gpc_chara_anim_hdls_;
}

// アップデート
void PlayerSymbol::update(float delta_time) {

	sequence_.update(delta_time);
}

// 描画
void PlayerSymbol::draw() {

	DrawGraph( pos_.x * 32, pos_.y * 32, p_gpc_chara_anim_hdls_[ static_cast<int>( dir_ ) ][ ANIM_IDLE ], true );

	DrawStringEx(10, 10, -1, "pos_x = %.2f, pos_y = %.2f", pos_.x, pos_.y);

	// DrawGraph(100, 100, gpc_chara_anim_hdls_[dir_][ANIM_IDLE], true);
}

// 待機状態
bool PlayerSymbol::seqIdle(const float delta_time) {

	// Aキー（左移動）
	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		next_pos_.x -= 1;
		dir_ = CharaDir::DIR_LEFT;
		sequence_.change(&PlayerSymbol::seqCheckWall);
		return true;
	}

	// Dキー（右移動）
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		next_pos_.x += 1;
		dir_ = CharaDir::DIR_RIGHT;
		sequence_.change(&PlayerSymbol::seqCheckWall);
		return true;
	}

	// Wキー（上移動）
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		next_pos_.y -= 1;
		dir_ = CharaDir::DIR_UP;
		sequence_.change( &PlayerSymbol::seqCheckWall);
		return true;
	}

	// Sキー（下移動）
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		next_pos_.y += 1;
		dir_ = CharaDir::DIR_DOWN;
		sequence_.change(&PlayerSymbol::seqCheckWall);
		return true;
	}
	
	return true;
}

// 当たり判定の確認
bool PlayerSymbol::seqCheckWall(const float delta_time) {

	if (col_flg_) {
		sequence_.change(&PlayerSymbol::seqIdle);
		next_pos_ = pos_;
		col_flg_ = false;
	}
	else {
		sequence_.change(&PlayerSymbol::seqMove);
		action_flg_ = true;
	}

	return true;
}

// 移動状態
bool PlayerSymbol::seqMove(const float delta_time) {

	if (sequence_.isStart()) {
		action_flg_ = false;
	}

	if ( abs(next_pos_.x - pos_.x) > 0.1f || abs(next_pos_.y - pos_.y) > 0.1f ) {
		//tnl::DebugTrace("pos_ = %.2f\n", pos_.length());
		//tnl::DebugTrace("next_pos_ - pos_ = %.2f\n", next_pos_.length() - pos_.length());
		pos_ += (next_pos_ - pos_) * MOVE_SPEED;
	}
	else {
		pos_ = next_pos_;
		sequence_.change(&PlayerSymbol::seqIdle);
	}
	
	return true;
}