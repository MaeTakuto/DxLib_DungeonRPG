#pragma once
#include "../base/gm_scene_base.h"
#include "../gm_obj/gm_player_symbol.h"
#include "../gm_obj/gm_enemy_symbol.h"


class ScenePlay : public SceneBase {
public:
	ScenePlay();
	~ScenePlay();

	static constexpr int MAP_GROUND_NUM = 0;						// 床の番号
	static constexpr int MAP_WALL_NUM = 1;							// 壁の番号
	static constexpr int MAP_PLAYER_NUM = 2;						// プレイヤーの番号
	static constexpr int MAP_ENEMY_NUM = 3;							// エネミーの番号

	static const int ENEMY_MAX_NUM = 3;								// エネミーの最大生成数

	void update(float delta_time) override;							// シーンプレイのアップデート
	void draw() override;											// シーンプレイ描画

	// ======================================
	//      マップの番号を返す
	// ======================================
	inline int getMapNum(const tnl::Vector3& pos) {
		int y = (int)pos.y;
		int x = (int)pos.x;

		return map_data_[y][x];
	}

	// ======================================
	//         マップ上のデータの更新
	// ======================================
	inline void setMapData(const tnl::Vector3& pos, int num) {
		int y = (int)pos.y;
		int x = (int)pos.x;

		map_data_[y][x] = num;
	}

private:
	PlayerSymbol* player_symbol_ = nullptr;						// プレイヤーシンボル
	EnemySymbol* enemy_symbol_[ENEMY_MAX_NUM] = { nullptr };	// エネミーシンボル

	bool action_flg_ = false;

	std::string gpc_map_chip_hdls_pass_;						// 画像パス
	int map_chip_width_;										// マップチップの幅
	int map_chip_height_;										// マップチップの高さ
	int map_chip_all_size_;										// マップチップの総フレーム数
	int map_chip_x_size_;										// マップチップの横フレーム数
	int map_chip_y_size_;										// マップチップの縦フレーム数
	int* gpc_map_chip_hdls_;									// 画像データ格納

	std::string map_data_csv_pass_;								// マップCSVデータのパス
	std::vector< std::vector< int > > mapchip_data_;			// マップチップのデータ
	std::vector< std::vector< int > > map_data_;				// マップデータ ( 敵やプレイヤーなどの位置を含む )

};
