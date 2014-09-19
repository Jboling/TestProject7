#pragma once
#include "main.hpp"
#include "CEventManager.hpp"
#include "CGLManager.hpp"
#include "CShader.hpp"

class CGLManager;

class CModel {
protected:
	std::string modelName;
	CShader *shader;
	GLuint vbo;
	GLuint vao;
	GLuint ebo;
	GLenum drawMode;
	int indexSize;

public:

	CModel();
	~CModel();

	bool loadModel(std::string modelName);
	bool loadModelFromJson(std::string jsonFile);

	bool setShader(CShader *shader);
	bool setVertexData(GLfloat *vertices, int count);
	bool setIndexData(GLuint *indices, int count);
	bool setAttribute(char *attrib, int count, int stride, int offset);
	void setDrawMode(GLenum drawMode) { this->drawMode = drawMode; }
	void setModelName(std::string modelName) { this->modelName = modelName; }

	void drawElements(GLenum drawMode, int count, int offset);
	void drawElements(GLenum drawMode);
	void drawElements();

	CShader *getShader() { return shader; }
	GLuint getVBO() { return vbo; }
	GLuint getVAO() { return vao; }
	std::string getModelName() { return modelName; }
};