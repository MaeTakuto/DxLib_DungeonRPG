#pragma once
#include "../common/gm_scene_base.h"
#include "../gm_obj/gm_player_symbol.h"
#include "../gm_obj/gm_enemy_symbol.h"


class ScenePlay : public SceneBase {
public:
	ScenePlay();
	~ScenePlay();

	const int MAP_WALL_NUM = 1;							// 壁の数値

	// ======================================
	//      キャラとマップ壁の当たり判定 
	// ======================================
	inline int checkHitMapWall(tnl::Vector3& pos) {
		int y = (int)pos.y;
		int x = (int)pos.x;

		return map_data_[y][x];
	}

	inline bool checkHitChara() {


		return true;
	}

	void update(float delta_time) override;
	void draw() override;

private:
	PlayerSymbol* player_symbol_ = nullptr;				// プレイヤーシンボル
	EnemySymbol* enemy_symbol_[3] = { nullptr };				// エネミーシンボル

	std::string gpc_map_chip_hdls_pass_;				// 画像パス
	int map_chip_width_;								// マップチップの幅
	int map_chip_height_;								// マップチップの高さ
	int map_chip_all_size_;								// マップチップの総フレーム数
	int map_chip_x_size_;								// マップチップの横フレーム数
	int map_chip_y_size_;								// マップチップの縦フレーム数
	int* gpc_map_chip_hdls_;							// 画像データ格納

	std::string map_data_csv_pass_;						// マップCSVデータのパス
	std::vector< std::vector< int > > map_data_;		// マップデータ

};
