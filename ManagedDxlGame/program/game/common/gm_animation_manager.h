#pragma once


// アニメーション管理クラス
class AnimationManager {
public:
	static AnimationManager* GetInstance();		// インスタンスを返す
	static void Destroy();						// インスタンスを削除

	// アニメーションのロード
	int* loadAnimation(std::string& anim_hdl_pass, 
		int all_size, int x_size, int y_size, int anim_hdl_width, int anim_hdl_height);

	// アニメーションの削除
	void deleteAnimation(std::string& anim_hdl_pass, int all_size);

private:
	AnimationManager();							
	~AnimationManager();

	// アニメーションハンドルの保存先
	std::unordered_map< std::string, int* > 
		anim_hdl_container_;

	// アニメーションの作成
	int* createAnimation(std::string& anim_hdl_pass,
		int all_size, int x_size, int y_size, int anim_hdl_width, int anim_hdl_height);

};