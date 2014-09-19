#include <stdlib.h>
#include "CShader.hpp"

void printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("[INFO] %s\n", infoLog);
		free(infoLog);
	}
}

void printProgramInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("[INFO] %s\n", infoLog);
		free(infoLog);
	}
}

CShader::CShader() {
	vs = 0;
	fs = 0;
	program = 0;
}

CShader::~CShader() {
	deleteShader();
}

bool CShader::loadShader(string shaderName) {
	string fragmentShader = "assets\\shaders\\";
	string vertexShader = "assets\\shaders\\";

	vertexShader.append(shaderName);
	vertexShader.append(".vert.glsl");
	fragmentShader.append(shaderName);
	fragmentShader.append(".frag.glsl");

	loadVertexSource((char *)vertexShader.c_str());
	loadFragmentSource((char *)fragmentShader.c_str());
	buildShader();

	if (program) {
		return true;
	}

	return false;
}

void CShader::loadVertexSource(char *vertexSource) {
	string source(vertexSource);
	vertexList.push_back(source);
}

void CShader::loadFragmentSource(char *fragmentSource) {
	string source(fragmentSource);
	fragmentList.push_back(source);
}

GLuint CShader::buildShader() {
	fstream inFile;
	string shaderSource;
	string temp;
	char **buffer = (char **)malloc(1 * sizeof(char **));

	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);

	list<string>::iterator it = vertexList.begin();
	shaderSource.clear();
	for (; it != vertexList.end(); ++it) {
		inFile.open(it->c_str());
		if (inFile.is_open()) {
			while (!inFile.eof()) {
				getline(inFile, temp);
				shaderSource.append(temp);
				shaderSource.append("\n");
			}
		}
		inFile.close();
	}
	buffer[0] = (char *)shaderSource.c_str();
	glShaderSource(vs, 1, (const GLchar **)buffer, NULL);

	shaderSource.clear();
	for (it = fragmentList.begin(); it != fragmentList.end(); ++it) {
		inFile.open(it->c_str());
		if (inFile.is_open()) {
			while (!inFile.eof()) {
				getline(inFile, temp);
				shaderSource.append(temp);
				shaderSource.append("\n");
			}
		}
		inFile.close();
	}
	buffer[0] = (char *)shaderSource.c_str();
	glShaderSource(fs, 1, (const GLchar **)buffer, NULL);
	shaderSource.clear();

	glCompileShader(vs);
	printShaderInfoLog(vs);
	glCompileShader(fs);
	printShaderInfoLog(fs);

	program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	printProgramInfoLog(program);
	return program;
}

void CShader::useProgram(bool use) {
	if (use == true) {
		glUseProgram(program);
	}
	else {
		glUseProgram(0);
	}
}

GLuint CShader::getUniformLocation(char *uniform) {
	useProgram(true);
	return glGetUniformLocation(program, uniform);
}

GLuint CShader::getAttibLocation(char *attrib) {
	useProgram(true);
	return glGetAttribLocation(program, attrib);
}

void CShader::setUniform1f(char *uniform, float x)  {
	GLuint uniformLocation = getUniformLocation(uniform);
	glUniform1f(uniformLocation, x);
}

void CShader::setUniform2f(char *uniform, float x, float y) {
	GLuint uniformLocation = getUniformLocation(uniform);
	glUniform2f(uniformLocation, x, y);
}

void CShader::setUniform3f(char *uniform, float x, float y, float z) {
	GLuint uniformLocation = getUniformLocation(uniform);
	glUniform3f(uniformLocation, x, y, z);
}

void CShader::setUniform4f(char *uniform, float x, float y, float z, float w) {
	GLuint uniformLocation = getUniformLocation(uniform);
	glUniform4f(uniformLocation, x, y, z, w);
}

void CShader::deleteShader() {
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteProgram(program);
	program = 0;
}