#pragma once
#include <GL/glew.h>
#include <vector>
#include "VertexFormat.h"

class Model
{
private:
	std::vector<GLuint> vbos;
	GLuint vao;

public:
	Model() = default;
	~Model();

	void initialize(const std::vector<graphics::VertexFormat>& vertices);
};

