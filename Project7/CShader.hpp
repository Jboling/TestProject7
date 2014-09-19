#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <GL/glew.h>
using namespace std;

class CShader {
private:
	list<string> vertexList;
	list<string> fragmentList;
	GLuint vs, fs;
	GLuint program;
public:
	CShader();
	~CShader();

	bool loadShader(string shaderName);

	void loadVertexSource(char *vertexSource);
	void loadFragmentSource(char *fragmentSource);
	GLuint buildShader();
	void useProgram(bool use);

	GLuint getUniformLocation(char *uniform);
	GLuint getAttibLocation(char *attrib);
	void setUniform1f(char *uniform, float x);
	void setUniform2f(char *uniform, float x, float y);
	void setUniform3f(char *uniform, float x, float y, float z);
	void setUniform4f(char *uniform, float x, float y, float z, float w);

	void deleteShader();

	GLuint getProgram() { return program; }
};