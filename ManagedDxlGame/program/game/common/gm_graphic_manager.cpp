#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_graphic_manager.h"



GraphicManager::GraphicManager() {

}


GraphicManager::~GraphicManager() {
	
	for (auto it = gpc_hdl_container_.begin(); it != gpc_hdl_container_.end(); ++it) {
		DeleteGraph(it->second);
	}
	gpc_hdl_container_.clear();
}

// �C���X�^���X��Ԃ�
GraphicManager* GraphicManager::GetInstance() {

	static GraphicManager* instance = nullptr;
	if (!instance) {
		instance = new GraphicManager();
	}
	return instance;
}

// �C���X�^���X���폜
void GraphicManager::Destroy() {
	delete GetInstance();
}

// �摜���[�h
int GraphicManager::loadGraph(const std::string& gpc_hdl_path) {

	auto it = gpc_hdl_container_.find(gpc_hdl_path);
	if (it != gpc_hdl_container_.end()) return gpc_hdl_container_[gpc_hdl_path];
	int gpc_hdl = LoadGraph(gpc_hdl_path.c_str());
	gpc_hdl_container_.insert(std::make_pair(gpc_hdl_path, gpc_hdl));
	return gpc_hdl;
}

// �摜�̍폜
void GraphicManager::deleteGraph(const std::string& gpc_hdl_path) {

	DeleteGraph(gpc_hdl_container_[gpc_hdl_path]);
	gpc_hdl_container_.erase(gpc_hdl_path);
}