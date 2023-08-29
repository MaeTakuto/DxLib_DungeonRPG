#pragma once
#include "../common/gm_scene_base.h"
#include "../gm_obj/gm_player_symbol.h"
#include "../gm_obj/gm_enemy_symbol.h"


class ScenePlay : public SceneBase {
public:
	ScenePlay();
	~ScenePlay();

	void update(float delta_time) override;
	void draw() override;

private:
	PlayerSymbol* player_symbol_ = nullptr;				// プレイヤーシンボル
	EnemySymbol* enemy_symbol_ = nullptr;				// エネミーシンボル

	std::string gpc_map_chip_hdls_pass_;				// 画像パス
	int map_chip_width_;								// マップチップの幅
	int map_chip_height_;								// マップチップの高さ
	int map_chip_all_size_;								// マップチップの総フレーム数
	int map_chip_x_size_;								// マップチップの横フレーム数
	int map_chip_y_size_;								// マップチップの縦フレーム数
	int* gpc_map_chip_hdls_;							// 画像データ格納

	std::string map_data_csv_pass_;						// マップデータのパス
	std::vector< std::vector< int > > map_data_;		// マップデータ

	// ======================================
	// キャラとマップ壁の当たり判定
	// ======================================
	inline bool checkHitMapWall(tnl::Vector3 a_pos,
		std::vector< std::vector< int > >& map_data) {
		int y = (int)a_pos.y;
		int x = (int)a_pos.x;

		return map_data[y][x] == 1 ? true : false;
	}

};
