#pragma once
#include "../base/gm_chara_symbol_base.h"
#include "gm_camera.h"



// プレイヤーシンボルクラス
class PlayerSymbol : public CharacterSymbol {
public:
	PlayerSymbol();						// コンストラクタ
	~PlayerSymbol();					// デストラクタ

	void update(float delta_time) override;		// プレイヤーのアップデート
	void draw(const tnl::Vector3& camera_pos) override;						// プレイヤーの描画

	inline void setNextPos(tnl::Vector3& next_pos) { next_pos_ = next_pos; }		// プレイヤーの次の位置をセット。
	inline tnl::Vector3& getPos() override { return pos_; }							// プレイヤーの現在の位置を返す。
	inline tnl::Vector3& getNextPos() override { return next_pos_; }				// プレイヤーの次の位置を返す。
	inline CharaAct getAct() override { return act_; }						// プレイヤーが行動したかを返す。
	inline void setColFlg(bool col_flg) override { col_flg_ = col_flg; }			// 当たり判定のフラグをセット

private:
	tnl::Sequence<PlayerSymbol> sequence_ 
		= tnl::Sequence<PlayerSymbol>(this, &PlayerSymbol::seqIdle);				// プレイヤーの行動状態

	bool seqIdle(const float delta_time);		// 待機状態
	bool seqCheckWall(const float delta_time);	// 当たり判定の確認
	bool seqMove(const float delta_time);		// 移動状態

};
