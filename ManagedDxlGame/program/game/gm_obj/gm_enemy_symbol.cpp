#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "gm_enemy_symbol.h"


// コンストラクタ
EnemySymbol::EnemySymbol() {
	// キャラの画像ロード
	chara_anim_hdls_data_ = tnl::LoadCsv("csv/enemy_gpc_pass.csv");

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

	pos_ = { 2, 1, 0 };
	next_pos_ = pos_;

	dir_ = CharaDir::DIR_DOWN;
}

// デストラクタ
EnemySymbol::~EnemySymbol() {

	for (int i = 0; i < static_cast<int>( CharaDir:: DIR_MAX ); ++i) {
		delete[] p_gpc_chara_anim_hdls_[i];
	}
	delete[] p_gpc_chara_anim_hdls_;
}

// アップデート
void EnemySymbol::update(float delta_time) {

}

// 描画
void EnemySymbol::draw() {

	DrawGraph(pos_.x * 32, pos_.y * 32, p_gpc_chara_anim_hdls_[ static_cast<int>( dir_ ) ][ANIM_IDLE], true);
}

// 待機状態
bool EnemySymbol::seqIdle(const float delta_time) {

	return true;
}