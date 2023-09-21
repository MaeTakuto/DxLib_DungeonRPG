#pragma once



class GraphicManager {
public:
	static GraphicManager* GetInstance();
	static void Destroy();

	int loadGraph(const std::string& gpc_hdl_path);
	void deleteGraph(const std::string& gpc_hdl_path);
 
private:
	GraphicManager();
	~GraphicManager();

	std::unordered_map<std::string, int> gpc_hdl_container_;

};