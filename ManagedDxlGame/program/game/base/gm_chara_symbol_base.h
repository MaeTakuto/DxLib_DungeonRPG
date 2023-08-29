#pragma once
#include "../../dxlib_ext/dxlib_ext.h"


// キャラの方向
enum class CharaDir {
	DIR_DOWN,		// 下
	DIR_LEFT,		// 左
	DIR_RIGHT,		// 右
	DIR_UP,			// 上
	DIR_MAX			// 最大値
};

const int ANIM_IDLE = 1;	// 待機状態


// キャラクターシンボルの基底クラス
class CharacterSymbol {
public:
	virtual ~CharacterSymbol() {};

	virtual void update(float delta_time) = 0;
	virtual void draw() = 0;

	virtual tnl::Vector3 getPos() = 0;			// キャラの現在の位置を返す。
	virtual tnl::Vector3 getNextPos() = 0;		// キャラの次の位置を返す。

protected:
	const float MOVE_SPEED = 0.25f;		// 移動速度

	tnl::Vector3 pos_;					// 位置情報
	tnl::Vector3 next_pos_;				// 移動先の位置

	std::vector< std::vector < int > >
		gpc_chara_anim_hdls_;			// キャラの画像

	int** p_gpc_chara_anim_hdls_;		// キャラの画像

	std::vector< std::vector< tnl::CsvCell > > 
		chara_anim_hdls_data_;			// キャラクターのアニメーションデータ

	CharaDir dir_;						// キャラの方向

};