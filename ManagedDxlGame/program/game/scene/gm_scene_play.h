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
	PlayerSymbol* player_symbol_ = nullptr;				// �v���C���[�V���{��
	EnemySymbol* enemy_symbol_ = nullptr;				// �G�l�~�[�V���{��

	std::string gpc_map_chip_hdls_pass_;				// �摜�p�X
	int map_chip_width_;								// �}�b�v�`�b�v�̕�
	int map_chip_height_;								// �}�b�v�`�b�v�̍���
	int map_chip_all_size_;								// �}�b�v�`�b�v�̑��t���[����
	int map_chip_x_size_;								// �}�b�v�`�b�v�̉��t���[����
	int map_chip_y_size_;								// �}�b�v�`�b�v�̏c�t���[����
	int* gpc_map_chip_hdls_;							// �摜�f�[�^�i�[

	std::string map_data_csv_pass_;						// �}�b�v�f�[�^�̃p�X
	std::vector< std::vector< int > > map_data_;		// �}�b�v�f�[�^

	// ======================================
	// �L�����ƃ}�b�v�ǂ̓����蔻��
	// ======================================
	inline bool checkHitMapWall(tnl::Vector3 a_pos,
		std::vector< std::vector< int > >& map_data) {
		int y = (int)a_pos.y;
		int x = (int)a_pos.x;

		return map_data[y][x] == 1 ? true : false;
	}

};
