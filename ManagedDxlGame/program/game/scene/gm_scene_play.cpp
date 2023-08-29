#include <vector>
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_scene_play.h"


// コンストラクタ
ScenePlay::ScenePlay() {
	player_symbol_ = new PlayerSymbol();
	enemy_symbol_ = new EnemySymbol();

	// マップチップの画像のロード
	gpc_map_chip_hdls_pass_ = "graphics/mapchip.png";

	map_chip_width_ = 32;
	map_chip_height_ = 32;
	map_chip_x_size_ = 2;
	map_chip_y_size_ = 1;
	map_chip_all_size_ = map_chip_x_size_ * map_chip_y_size_;
	gpc_map_chip_hdls_ = new int[map_chip_all_size_];

	LoadDivGraph( gpc_map_chip_hdls_pass_.c_str(),
		map_chip_all_size_, 
		map_chip_x_size_,
		map_chip_y_size_,
		map_chip_width_,
		map_chip_height_,
		gpc_map_chip_hdls_ );

	// マップデータのロード
	map_data_csv_pass_ = "csv/map_data.csv";

	map_data_ = tnl::LoadCsv<int>(map_data_csv_pass_);
}

// デストラクタ
ScenePlay::~ScenePlay() {

	delete player_symbol_;
	player_symbol_ = nullptr;

	delete enemy_symbol_;
	enemy_symbol_ = nullptr;
}

// シーンプレイのアップデート
void ScenePlay::update(float delta_time) {

	// プレイヤーのアップデート
	if (player_symbol_) {
		player_symbol_->update(delta_time);

		if (checkHitMapWall(player_symbol_->getNextPos(), map_data_)) {
			player_symbol_->setNextPos(player_symbol_->getPos());
		}
	}
}

// シーンプレイの描画
void ScenePlay::draw() {

	for (int y = 0; y < map_data_.size(); ++y) {
		for (int x = 0; x < map_data_[y].size(); ++x) {
			DrawGraph(x * map_chip_width_, y * map_chip_height_, gpc_map_chip_hdls_[ map_data_[y][x] ], true);
		}
	}

	if (player_symbol_) player_symbol_->draw();
	if (enemy_symbol_) enemy_symbol_->draw();
}

