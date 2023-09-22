#pragma once
#include "../../dxlib_ext/dxlib_ext.h"


// キャラの方向
enum class CharaDir {
	DIR_UP,			// 上
	DIR_DOWN,		// 下
	DIR_LEFT,		// 左
	DIR_RIGHT,		// 右
	DIR_MAX			// 最大値
};

// キャラの行動状態
enum class CharaAct {
	WAIT,
	BEGIN,
	ACT,
	END
};

const int ANIM_IDLE = 1;	// 待機状態


// キャラクターシンボルの基底クラス
class CharacterSymbol {
public:
	virtual ~CharacterSymbol() {};

	virtual void update(float delta_time) = 0;
	virtual void draw(const tnl::Vector3& camera_pos) = 0;

	virtual tnl::Vector3& getPos() = 0;			// キャラの現在の位置を返す。
	virtual tnl::Vector3& getNextPos() = 0;		// キャラの次の位置を返す。
	virtual CharaAct getAct() = 0;			// キャラが行動しているかを返す。
	virtual void setColFlg(bool col_flg) = 0;	// キャラに当たり判定セット

protected:
	const float MOVE_SPEED = 0.25f;		// 移動速度
	const float WALK_TIME = 0.25f;
	const float RUN_TIME = 0.05f;

	tnl::Vector3 pos_;					// 位置情報
	tnl::Vector3 next_pos_;				// 移動先の位置

	std::vector< std::vector < int > >
		chara_anim_hdls_;				// キャラのアニメーション

	int anim_frame_;					// アニメーションフレーム
	float anim_time_count_;				// アニメーションの時間

	bool col_flg_;						// 衝突判定

	std::vector< std::vector< tnl::CsvCell > > 
		chara_anim_hdls_data_;			// キャラクターのアニメーションデータ

	CharaDir dir_;						// キャラの方向
	CharaAct act_;						// キャラの行動状態

};