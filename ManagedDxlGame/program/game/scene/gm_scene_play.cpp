#include <vector>
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_scene_play.h"


// コンストラクタ
ScenePlay::ScenePlay() {
	player_symbol_ = new PlayerSymbol();
	enemy_symbol_[0] = new EnemySymbol(tnl::Vector3{2, 1, 0});
	enemy_symbol_[1] = new EnemySymbol(tnl::Vector3{3, 1, 0});
	enemy_symbol_[2] = new EnemySymbol(tnl::Vector3{4, 1, 0});

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

	mapchip_data_ = tnl::LoadCsv<int>(map_data_csv_pass_);

	// マップデータの初期化
	map_data_.resize(mapchip_data_.size());

	for (int y = 0; y < mapchip_data_.size(); ++y) {
		map_data_[y].resize(mapchip_data_[y].size());

		for (int x = 0; x < mapchip_data_[y].size(); ++x) {
			map_data_[y][x] = mapchip_data_[y][x];
		}
	}

	if (player_symbol_) setMapData(player_symbol_->getPos(), MAP_PLAYER_NUM);

	for (int i = 0; i < ENEMY_MAX_NUM; ++i) {
		if(enemy_symbol_[i])
			setMapData(enemy_symbol_[i]->getPos(), MAP_ENEMY_NUM);
	}

	for (int y = 0; y < map_data_.size(); ++y) {
		for (int x = 0; x < map_data_[y].size(); ++x) {
			tnl::DebugTrace("%d, ", map_data_[y][x]);
		}
		tnl::DebugTrace("\n");
	}
}

// デストラクタ
ScenePlay::~ScenePlay() {

	delete player_symbol_;
	player_symbol_ = nullptr;

	delete[] enemy_symbol_;

	for (int i = 0; i < 3; ++i) {
		enemy_symbol_[i] = nullptr;
	}

	delete[] gpc_map_chip_hdls_;
	gpc_map_chip_hdls_ = nullptr;
}

// シーンプレイのアップデート
void ScenePlay::update(float delta_time) {

	// プレイヤーのアップデート
	if (player_symbol_) {
		player_symbol_->update(delta_time);

		// 当たり判定
		if ( getMapNum(player_symbol_->getNextPos()) == MAP_WALL_NUM ) {
			player_symbol_->setColFlg(true);
		}
		else if ( getMapNum(player_symbol_->getNextPos()) == MAP_ENEMY_NUM ) {
			player_symbol_->setColFlg(true);
		}
		else {
			// マップデータの更新
			setMapData(player_symbol_->getPos(), MAP_GROUND_NUM);
			setMapData(player_symbol_->getNextPos(), MAP_PLAYER_NUM);
		}
	}

	// エネミーのアップデート
	for (int i = 0; i < ENEMY_MAX_NUM; ++i) {
		if (enemy_symbol_[i]) {

			// 行動するかどうか
			if (player_symbol_) {
				if (player_symbol_->getAct() == CharaAct::BEGIN) {
					enemy_symbol_[i]->setAct(CharaAct::BEGIN);
					action_flg_ = true;
				}
			}

			enemy_symbol_[i]->update(delta_time);

			// 行動開始時
			if (enemy_symbol_[i]->getAct() == CharaAct::BEGIN) {

				// 当たり判定
				if (getMapNum(enemy_symbol_[i]->getNextPos()) == MAP_PLAYER_NUM) {
					enemy_symbol_[i]->setColFlg(true);
				}
				else if (getMapNum(enemy_symbol_[i]->getNextPos()) == MAP_ENEMY_NUM) {
					enemy_symbol_[i]->setColFlg(true);
				}

				else if (getMapNum(enemy_symbol_[i]->getNextPos()) == MAP_WALL_NUM) {
					enemy_symbol_[i]->setColFlg(true);
				}
				else {
					// マップデータの更新
					setMapData(enemy_symbol_[i]->getPos(), MAP_GROUND_NUM);
					setMapData(enemy_symbol_[i]->getNextPos(), MAP_ENEMY_NUM);
				}
			}
		}
	}


	/*
	for (int i = 0; i < ENEMY_MAX_NUM; ++i) {
		if (enemy_symbol_[i]) {
			switch (enemy_symbol_[i]->getAct())
			{
			case CharaAct::BEGIN:
				setMapData(enemy_symbol_[i]->getPos(), MAP_GROUND_NUM);
				break;
			case CharaAct::END:
				setMapData(enemy_symbol_[i]->getPos(), MAP_ENEMY_NUM);
			default:
				break;
			}
		}
	}
	*/

	if (enemy_symbol_[2]->getAct() == CharaAct::END) {
		for (int y = 0; y < map_data_.size(); ++y) {
			for (int x = 0; x < map_data_[y].size(); ++x) {
				tnl::DebugTrace("%d, ", map_data_[y][x]);
			}
			tnl::DebugTrace("\n");
		}
	}
}

// シーンプレイの描画
void ScenePlay::draw() {

	// マップの表示
	for (int y = 0; y < mapchip_data_.size(); ++y) {
		for (int x = 0; x < mapchip_data_[y].size(); ++x) {
			DrawGraph(x * map_chip_width_, y * map_chip_height_, gpc_map_chip_hdls_[ mapchip_data_[y][x] ], true);
		}
	}

	if (player_symbol_) player_symbol_->draw();

	for (int i = 0; i < ENEMY_MAX_NUM; ++i) {
		if (enemy_symbol_) enemy_symbol_[i]->draw();
	}
}

