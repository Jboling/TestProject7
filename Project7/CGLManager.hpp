#pragma once
#include "main.hpp"
#include "CEventManager.hpp"
#include "CModel.hpp"
#include "CShader.hpp"

class CModel;

class CGLManager {
private:
	std::map<std::string, CModel *> models;
	std::map<std::string, CShader *> shaders;

	CGLManager();

public:

	~CGLManager();

	bool addModel(std::string modelName);
	bool addShader(std::string shaderName);

	bool modelExist(std::string modelName);
	bool shaderExist(std::string shaderName);

	CModel *getModel(std::string modelName);
	CShader *getShader(std::string shaderName);

	static CGLManager *instance();
};