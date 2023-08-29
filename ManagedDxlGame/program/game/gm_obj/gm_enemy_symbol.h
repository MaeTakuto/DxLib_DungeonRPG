#pragma once
#include "../base/gm_chara_symbol_base.h"



// エネミーシンボルクラス
class EnemySymbol : public CharacterSymbol {
public:
	EnemySymbol();
	~EnemySymbol();

	void update(float delta_time) override;
	void draw() override;

	inline tnl::Vector3 getPos() override { return pos_; }							// エネミーの現在の位置を返す。
	inline tnl::Vector3 getNextPos() override { return next_pos_; }					// エネミーの次の位置を返す。


private:
	// エネミーの行動
	tnl::Sequence<EnemySymbol> sequence_ 
		= tnl::Sequence<EnemySymbol>(this, &EnemySymbol::seqIdle);

	bool seqIdle(const float delta_time);		// 待機状態
	bool seqMove(const float delta_time);		// 移動状態
	bool seqDirChange(const float delta_time);	// 方向転換

};
