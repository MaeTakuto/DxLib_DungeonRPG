#pragma once
#include "../base/gm_scene_base.h"
#include "../gm_obj/gm_player_symbol.h"
#include "../gm_obj/gm_enemy_symbol.h"


class ScenePlay : public SceneBase {
public:
	ScenePlay();
	~ScenePlay();

	static constexpr int MAP_GROUND_NUM = 0;						// ���̔ԍ�
	static constexpr int MAP_WALL_NUM = 1;							// �ǂ̔ԍ�
	static constexpr int MAP_PLAYER_NUM = 2;						// �v���C���[�̔ԍ�
	static constexpr int MAP_ENEMY_NUM = 3;							// �G�l�~�[�̔ԍ�

	static const int ENEMY_MAX_NUM = 3;								// �G�l�~�[�̍ő吶����

	void update(float delta_time) override;							// �V�[���v���C�̃A�b�v�f�[�g
	void draw() override;											// �V�[���v���C�`��

	// ======================================
	//      �}�b�v�̔ԍ���Ԃ�
	// ======================================
	inline int getMapNum(const tnl::Vector3& pos) {
		int y = (int)pos.y;
		int x = (int)pos.x;

		return map_data_[y][x];
	}

	// ======================================
	//         �}�b�v��̃f�[�^�̍X�V
	// ======================================
	inline void setMapData(const tnl::Vector3& pos, int num) {
		int y = (int)pos.y;
		int x = (int)pos.x;

		map_data_[y][x] = num;
	}

private:
	PlayerSymbol* player_symbol_ = nullptr;						// �v���C���[�V���{��
	EnemySymbol* enemy_symbol_[ENEMY_MAX_NUM] = { nullptr };	// �G�l�~�[�V���{��

	bool action_flg_ = false;

	std::string gpc_map_chip_hdls_pass_;						// �摜�p�X
	int map_chip_width_;										// �}�b�v�`�b�v�̕�
	int map_chip_height_;										// �}�b�v�`�b�v�̍���
	int map_chip_all_size_;										// �}�b�v�`�b�v�̑��t���[����
	int map_chip_x_size_;										// �}�b�v�`�b�v�̉��t���[����
	int map_chip_y_size_;										// �}�b�v�`�b�v�̏c�t���[����
	int* gpc_map_chip_hdls_;									// �摜�f�[�^�i�[

	std::string map_data_csv_pass_;								// �}�b�vCSV�f�[�^�̃p�X
	std::vector< std::vector< int > > mapchip_data_;			// �}�b�v�`�b�v�̃f�[�^
	std::vector< std::vector< int > > map_data_;				// �}�b�v�f�[�^ ( �G��v���C���[�Ȃǂ̈ʒu���܂� )

};
