#include "CGLManager.hpp"

CGLManager::CGLManager() {
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		std::clog << "[SEVERE] Error on GLEW initialization." << std::endl;
		std::clog << "\t" << glewGetErrorString(glewError) << std::endl;
	}
	else {
		std::clog << "[INFO] Glew successfully initialized." << std::endl;
	}

	std::clog << "[INFO] GL manager instance created." << std::endl;
}

bool CGLManager::addModel(std::string modelName) {
	if (modelExist(modelName)) {
		return true;
	}
	CModel *model = new CModel();
	bool createSuccess = model->loadModel(modelName);
	if (createSuccess) {
		models[modelName] = model;
	}
	return createSuccess;
}

bool CGLManager::addShader(std::string shaderName) {
	if (shaderExist(shaderName)) {
		return true;
	}
	CShader *shader = new CShader();
	bool createSuccess = shader->loadShader(shaderName);
	if (createSuccess) {
		shaders[shaderName] = shader;
	}
	return createSuccess;
}

bool CGLManager::modelExist(std::string modelName) {
	if (models.count(modelName)) {
		return true;
	}
	return false;
}

bool CGLManager::shaderExist(std::string shaderName) {
	if (shaders.count(shaderName)) {
		return true;
	}
	return false;
}

CModel *CGLManager::getModel(std::string modelName) {
	if (modelExist(modelName)) {
		return models[modelName];
	}
	else {
		bool createSuccess = addModel(modelName);
		if (createSuccess) {
			return models[modelName];
		}
	}
	return NULL;
}

CShader *CGLManager::getShader(std::string shaderName) {
	if (shaderExist(shaderName)) {
		return shaders[shaderName];
	}
	else {
		bool createSuccess = addShader(shaderName);
		if (createSuccess) {
			return shaders[shaderName];
		}
	}
	return NULL;
}

CGLManager *CGLManager::instance() {
	static CGLManager *inst = 0;
	if (!inst) {
		inst = new CGLManager();
	}
	return inst;
}