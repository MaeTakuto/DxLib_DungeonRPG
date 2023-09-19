#pragma once
#include "../base/gm_chara_symbol_base.h"



// エネミーシンボルクラス
class EnemySymbol : public CharacterSymbol {
public:
	EnemySymbol(tnl::Vector3 pos);
	~EnemySymbol();

	void update(float delta_time) override;
	void draw() override;

	inline tnl::Vector3& getPos() override { return pos_; }							// エネミーの現在の位置を返す。
	inline tnl::Vector3& getNextPos() override { return next_pos_; }				// エネミーの次の位置を返す。
	inline CharaAct getAct() override { return act_; }								// エネミーが行動状態を返す。
	inline void setAct(CharaAct act) { act_ = act; }							// エネミーの行動フラグを入れる。
	inline void setColFlg(bool col_flg) override { col_flg_ = col_flg; }			// 当たり判定フラグのセット

private:
	// エネミーの行動
	tnl::Sequence<EnemySymbol> sequence_ 
		= tnl::Sequence<EnemySymbol>(this, &EnemySymbol::seqIdle);

	bool seqIdle(const float delta_time);		// 待機状態
	// bool seqCheckWall(const float delta_time);	// 当たり判定の確認
	bool seqAction(const float delta_time);		// 移動状態
	// bool seqDirChange(const float delta_time);	// 方向転換

	void move();								// 移動処理
	void dirChange();							// 方向転換処理

};
