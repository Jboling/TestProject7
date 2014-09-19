#include "CModel.hpp"

CModel::CModel() {
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenVertexArrays(1, &vao);
	shader = NULL;

	drawMode = GL_TRIANGLES;
	indexSize = 0;
}

CModel::~CModel() {
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
}

bool CModel::loadModel(std::string modelName) {
	std::string jsonFile = "assets\\models\\";

	jsonFile.append(modelName);
	jsonFile.append(".json");

	return loadModelFromJson(jsonFile);
}

bool CModel::loadModelFromJson(std::string jsonFile) {
	std::ifstream fs(jsonFile, std::ifstream::binary);
	Json::Reader reader;
	Json::Value root;

	if (fs.is_open()) {
		bool parseSuccess = reader.parse(fs, root, false);
		if (parseSuccess) {
			if (root["type"].asString().compare("model") == 0) {
				modelName = root["name"].asString();

				std::string shaderName = root["shader"].asString();
				CShader *shader = CGLManager::instance()->getShader(shaderName);
				if (!shader) {
					fs.close();
					return false;
				}
				setShader(shader);

				Json::Value verticesNode = root["vertices"];
				int arraySize = verticesNode.size();
				GLfloat *vertices = (GLfloat *)malloc(arraySize * sizeof(GLfloat));
				int element = 0;
				Json::Value::iterator verticesIt = verticesNode.begin();
				for (; verticesIt != verticesNode.end(); ++verticesIt) {
					vertices[element++] = (*verticesIt).asFloat();
				}
				setVertexData(vertices, arraySize);
				free(vertices);

				Json::Value indicesNode = root["indices"];
				arraySize = indicesNode.size();
				GLuint *indices = (GLuint *)malloc(arraySize * sizeof(GLuint));
				element = 0;
				Json::Value::iterator indicesIt = indicesNode.begin();
				for (; indicesIt != indicesNode.end(); ++indicesIt) {
					indices[element++] = (*indicesIt).asUInt();
				}
				setIndexData(indices, arraySize);
				free(indices);

				Json::Value attributeparametersNode = root["attributeparameters"];
				int drawMode = attributeparametersNode["drawmode"].asUInt();
				int stride = attributeparametersNode["stride"].asUInt();
				Json::Value attributesNode = attributeparametersNode["attributes"];
				Json::Value::iterator attributesIt = attributesNode.begin();
				for (; attributesIt != attributesNode.end(); ++attributesIt) {
					std::string name = (*attributesIt)["name"].asString();
					int count = (*attributesIt)["count"].asUInt();
					int offset = (*attributesIt)["offset"].asUInt();
					setAttribute((char *)name.c_str(), count, stride, offset);
				}
				setDrawMode(drawMode);

				fs.close();
				return true;
			}
		}
		fs.close();
	}

	return false;
}

bool CModel::setVertexData(GLfloat *vertices, int count) {
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	shader->useProgram(true);

	glBufferData(GL_ARRAY_BUFFER, count*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	return true;
}

bool CModel::setIndexData(GLuint *indices, int count) {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	shader->useProgram(true);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLfloat), indices, GL_STATIC_DRAW);
	indexSize = count;

	return true;
}

bool CModel::setShader(CShader *shader) {
	if (shader) {
		this->shader = shader;
		return true;
	}
	return false;
}

bool CModel::setAttribute(char *attrib, int count, int stride, int offset) {
	if (shader) {
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		shader->useProgram(true);

		GLuint attribLocation = glGetAttribLocation(shader->getProgram(), attrib);
		glVertexAttribPointer(attribLocation, count, GL_FLOAT, GL_FALSE, stride*sizeof(GLfloat), (GLvoid *)(offset*sizeof(GLfloat)));
		glEnableVertexAttribArray(attribLocation);
		return true;
	}
	return false;
}

void CModel::drawElements(GLenum drawMode, int count, int offset) {
	if (shader && indexSize>0) {
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		shader->useProgram(true);

		this->drawMode = drawMode;

		glDrawElements(drawMode, count, GL_UNSIGNED_INT, (const GLvoid *)(offset*sizeof(GLuint)));
	}
}

void CModel::drawElements(GLenum drawMode) {
	drawElements(drawMode, indexSize, 0);
}

void CModel::drawElements() {
	drawElements(drawMode, indexSize, 0);
}