#include "Model.h"
#include "VertexFormat.h"

Model::~Model()
{
	
	glDeleteBuffers(vbos.size(), vbos.data());
}

void Model::initialize(const std::vector<graphics::VertexFormat>& vertices)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vbos.resize(1);
	glGenBuffers(1, &vbos[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(graphics::VertexFormat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(Attr_POSITION);
	glVertexAttribPointer(Attr_POSITION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}
