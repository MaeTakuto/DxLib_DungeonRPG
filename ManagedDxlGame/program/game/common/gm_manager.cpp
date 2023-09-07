#include "../../dxlib_ext/dxlib_ext.h"
#include "../gm_main.h"
#include "gm_manager.h"
#include "gm_scene_base.h"


// コンストラクタ
GameManager::GameManager(SceneBase* start_scene) {
	now_scene_ = start_scene;
}

// ゲームマネージャーのアドレスを返す
GameManager* GameManager::GetInstance(SceneBase* start_scene) {

	static GameManager* instance = nullptr;

	if (!instance) {
		instance = new GameManager(start_scene);
	}
	return instance;
}

// アップデート
void GameManager::update(float delta_time) {

	if (now_scene_) now_scene_->update(delta_time);
	if (now_scene_) now_scene_->draw();

	sequense_.update(delta_time);
}

// シーンの切り替えをセット
void GameManager::changeScene( SceneBase* next_scene ) {
	next_scene_ = next_scene;
	sequense_.change(&GameManager::seqChangeScene);
}

// 何もしない
bool GameManager::seqRun(const float delta_time) {
	return true;
}

// シーンを切り替える
bool GameManager::seqChangeScene(const float delta_time) {
	delete now_scene_;
	now_scene_ = nullptr;
	now_scene_ = next_scene_;
	sequense_.change(&GameManager::seqRun);
	return true;
}