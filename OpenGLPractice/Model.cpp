#include "Model.h"
#include "VertexFormat.h"

void Model::initialize(const std::vector<graphics::VertexFormat>& vertices)
{
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	vbos_.resize(1);
	glGenBuffers(1, &vbos_[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos_[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(graphics::VertexFormat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(Attr_POSITION);
	glVertexAttribPointer(Attr_POSITION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Model::release()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(vbos_.size(), vbos_.data());
}

void Model::activate() const
{
	glBindVertexArray(vao_);
}

Model Model::create_debug_triangle()
{
	using namespace glm;
	using namespace graphics;

	Model result;
	result.initialize(
		{
			VertexFormat(vec3(0.25, -0.25, 0.0)),
			VertexFormat(vec3(-0.25, -0.25, 0.0)),
			VertexFormat(vec3(0.25, 0.25, 0.0))
		}
	);
	return result;
}
