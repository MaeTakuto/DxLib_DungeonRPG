#pragma once


class SceneBase;

class GameManager {
public:
	static constexpr int TITLE_FONT_SIZE = 80;								// タイトルのフォントサイズ
	static constexpr int NORMAL_FONT_SIZE = 30;								// ノーマルのフォントサイズ

	static constexpr int GPC_CHIP_SIZE = 32;								// 画像横のチップサイズ
	static constexpr int GPC_DRAW_CHIP_SIZE = GPC_CHIP_SIZE * 2;							// 表示するチップサイズ


	static GameManager* GetInstance(SceneBase* start_scene = nullptr);		// ゲームマネージャーのアドレスを返す
	inline static void Destroy() { delete GetInstance(); }					// アドレスの削除

	void update(float delta_time);											// ゲームマネージャーの更新
	void changeScene(SceneBase* next_scene);								// シーンの切り替えを行う
	inline SceneBase* getSceneInstance() { return now_scene_; }				// シーンのインスタンスを返す。
	
private:
	GameManager(SceneBase* start_scene);									// コンストラクタ

	SceneBase* now_scene_ = nullptr;										// 現在のシーン
	SceneBase* next_scene_ = nullptr;										// 次のシーン

	tnl::Sequence<GameManager> sequense_
		= tnl::Sequence<GameManager>(this, &GameManager::seqRun);			// ゲームマネージャーの状態

	bool seqRun(const float delta_time);									// 何もしない
	bool seqChangeScene(const float delta_time);							// シーンの更新

};