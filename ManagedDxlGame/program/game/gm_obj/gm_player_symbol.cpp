#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../common/gm_animation_manager.h"
#include "gm_player_symbol.h"


// コンストラクタ
PlayerSymbol::PlayerSymbol() {
	// キャラの画像データのロード
	chara_anim_hdls_data_ = tnl::LoadCsv("csv/player_gpc_pass.csv");
	
	// std::vectorの場合 
	chara_anim_hdls_.resize( static_cast<int>( CharaDir::DIR_MAX ) );

	for (int i = 0; i < static_cast<int>(CharaDir::DIR_MAX); ++i) {

		chara_anim_hdls_[i].resize( chara_anim_hdls_data_[1][i].getInt() );

		// アニメーションの取得
		chara_anim_hdls_[i] = AnimationManager::GetInstance()->loadAnimation(
			chara_anim_hdls_data_[0][i].getString(),
			chara_anim_hdls_data_[1][i].getInt(),
			chara_anim_hdls_data_[2][i].getInt(),
			chara_anim_hdls_data_[3][i].getInt(),
			GameManager::GPC_CHIP_SIZE,
			GameManager::GPC_CHIP_SIZE );
	}
	
	// 位置情報など初期化
	pos_ = { 20, 6, 0 };
	next_pos_ = pos_;
	col_flg_ = false;

	dir_ = CharaDir::DIR_DOWN;
	act_ = CharaAct::WAIT;
}

// デストラクタ
PlayerSymbol::~PlayerSymbol() {
	
}

// アップデート
void PlayerSymbol::update(float delta_time) {

	sequence_.update(delta_time);
}

// 描画
void PlayerSymbol::draw(const tnl::Vector3& camera_pos) {

	tnl::Vector3 draw_pos = tnl::Vector3(pos_.x * GameManager::GPC_DRAW_CHIP_SIZE, pos_.y * GameManager::GPC_DRAW_CHIP_SIZE, 0) - camera_pos + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

	DrawExtendGraph(draw_pos.x, draw_pos.y, draw_pos.x + GameManager::GPC_DRAW_CHIP_SIZE, draw_pos.y + GameManager::GPC_DRAW_CHIP_SIZE, chara_anim_hdls_[static_cast<int>(dir_)][ANIM_IDLE], true);
	// DrawRotaGraph( draw_pos.x, draw_pos.y, 2.0f, 0, chara_anim_hdls_[ static_cast<int>( dir_ ) ][ ANIM_IDLE ], true );

	DrawStringEx(10, 10, -1, "pos_x = %.2f, pos_y = %.2f", pos_.x, pos_.y);

}

// 待機状態
bool PlayerSymbol::seqIdle(const float delta_time) {

	if (act_ == CharaAct::END) {
		act_ = CharaAct::WAIT;
	}

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
		act_ = CharaAct::BEGIN;
	}

	return true;
}

// 移動状態
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