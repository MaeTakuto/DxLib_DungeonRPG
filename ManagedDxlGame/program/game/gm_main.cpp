#include <time.h>
#include <string>
#include <vector>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "common/gm_manager.h"
#include "scene/gm_scene_play.h"



//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart(){
	srand(time(0));

	// �C���X�^���X�����A�ŏ��̃V�[�����Z�b�g
	GameManager::GetInstance( new ScenePlay() );

}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	// �Q�[���}�l�[�W���[�̃A�b�v�f�[�g
	GameManager::GetInstance()->update(delta_time);

}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}
