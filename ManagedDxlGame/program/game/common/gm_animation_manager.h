#pragma once


// アニメーション管理クラス（ Flyweightパターン )
class AnimationManager {
public:
	static AnimationManager* GetInstance();		// インスタンスを返す
	static void Destroy();						// インスタンスを削除

	// アニメーションのロード
	int* loadAnimation(std::string& anim_hdl_pass, 
		int all_size, int x_size, int y_size, int anim_hdl_width, int anim_hdl_height);
	
	int* createAnimation(std::string& anim_hdl_pass,
		int all_size, int x_size, int y_size, int anim_hdl_width, int anim_hdl_height);

	void deleteAnimation(std::string& anim_hdl_pass);					// アニメーションの削除

private:
	AnimationManager();							
	~AnimationManager();

	std::unordered_map< std::string, int* > 
		anim_hdl_container_;						// アニメーションハンドルの保存先

};