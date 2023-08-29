#pragma once
#include "../base/gm_chara_symbol_base.h"



// プレイヤーシンボルクラス
class PlayerSymbol : public CharacterSymbol {
public:
	PlayerSymbol();						// コンストラクタ
	~PlayerSymbol();					// デストラクタ

	void update(float delta_time) override;		// プレイヤーのアップデート
	void draw() override;						// プレイヤーの描画

	inline void setNextPos(tnl::Vector3 next_pos) { next_pos_ = next_pos; }			// プレイヤーの次の位置をセット。
	inline tnl::Vector3 getPos() override { return pos_; }							// プレイヤーの現在の位置を返す。
	inline tnl::Vector3 getNextPos() override { return next_pos_; }					// プレイヤーの次の位置を返す。

private:
	tnl::Sequence<PlayerSymbol> sequence_ 
		= tnl::Sequence<PlayerSymbol>(this, &PlayerSymbol::seqIdle);				// プレイヤーの行動状態

	bool seqIdle(const float delta_time);		// 待機状態
	bool seqMove(const float delta_time);		// 移動状態

};
