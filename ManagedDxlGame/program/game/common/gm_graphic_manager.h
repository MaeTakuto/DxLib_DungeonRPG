#pragma once
#include <string>
#include <unordered_map>


//
class GraphicManager {
public:
	static GraphicManager* GetInstance();					// �C���X�^���X��Ԃ��B
	static void Destroy();									// �C���X�^���X�̍폜�B

	int loadGraph(const std::string& gpc_hdl_path);			// �摜�̃��[�h�A�摜�̃A�h���X��n���B
	void deleteGraph(const std::string& gpc_hdl_path);		// �摜�̍폜
 
private:
	GraphicManager();
	~GraphicManager();

	std::unordered_map< std::string, int > gpc_hdl_container_;	// �摜�f�[�^�̊i�[

};