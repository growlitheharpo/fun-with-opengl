#include "Model.h"

#include <glm/detail/type_vec3.hpp>
#include "rendering/data/VertexFormat.h"
#include "core/utils/NarrowCast.h"

void Model::initialize(const std::vector<rendering::VertexFormat>& vertices)
{
	using namespace rendering;

	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	vbos_.resize(1);
	glGenBuffers(1, &vbos_[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos_[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(Attr_POSITION);
	glVertexAttribPointer(Attr_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), nullptr);
	glEnableVertexAttribArray(Attr_COLOR);
	glVertexAttribPointer(Attr_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(float) * 3));
	
	glBindVertexArray(0);

	vertexCount_ = vertices.size();
}

void Model::release()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(narrow_cast<GLsizei>(vbos_.size()), vbos_.data());
}

void Model::activate() const
{
	glBindVertexArray(vao_);
}

Model Model::create_debug_triangle()
{
	using namespace glm;
	using namespace rendering;

	Model result;
	result.initialize(
		{
			VertexFormat(vec3(0.25, -0.25, 0.0), vec4(1, 0, 0, 1)),
			VertexFormat(vec3(-0.25, -0.25, 0.0), vec4(0, 1, 0, 1)),
			VertexFormat(vec3(0.25, 0.25, 0.0), vec4(0, 0, 1, 1))
		}
	);
	return result;
}

Model Model::create_debug_cube()
{
	using namespace glm;
	using namespace rendering;
	std::vector<VertexFormat> vertices;

	//vertices for the front face of the cube
	vertices.emplace_back(vec3(-1.0, -1.0, 1.0), vec4(0.0, 0.0, 1.0, 1.0));
	vertices.emplace_back(vec3(1.0, -1.0, 1.0), vec4(1.0, 0.0, 1.0, 1.0));
	vertices.emplace_back(vec3(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0));
	vertices.emplace_back(vec3(-1.0, 1.0, 1.0), vec4(0.0, 1.0, 1.0, 1.0));
	vertices.emplace_back(vec3(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0));
	vertices.emplace_back(vec3(-1.0, -1.0, 1.0), vec4(0.0, 0.0, 1.0, 1.0));

	//vertices for the right face of the cube
	vertices.emplace_back(vec3(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0));
	vertices.emplace_back(vec3(1.0, 1.0, -1.0), vec4(1.0, 1.0, 0.0, 1.0));
	vertices.emplace_back(vec3(1.0, -1.0, -1.0), vec4(1.0, 0.0, 0.0, 1.0));
	vertices.emplace_back(vec3(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0));
	vertices.emplace_back(vec3(1.0, -1.0, -1.0), vec4(1.0, 0.0, 0.0, 1.0));
	vertices.emplace_back(vec3(1.0, -1.0, 1.0), vec4(1.0, 0.0, 1.0, 1.0));

	//vertices for the back face of the cube
	vertices.emplace_back(vec3(-1.0, -1.0, -1.0), vec4(0.0, 0.0, 0.0, 1.0));
	vertices.emplace_back(vec3(1.0, -1.0, -1.0), vec4(1.0, 0.0, 0.0, 1.0));
	vertices.emplace_back(vec3(1.0, 1.0, -1.0), vec4(1.0, 1.0, 0.0, 1.0));
	vertices.emplace_back(vec3(-1.0, -1.0, -1.0), vec4(0.0, 0.0, 0.0, 1.0));
	vertices.emplace_back(vec3(1.0, 1.0, -1.0), vec4(1.0, 1.0, 0.0, 1.0));
	vertices.emplace_back(vec3(-1.0, 1.0, -1.0), vec4(0.0, 1.0, 0.0, 1.0));
	//vertices for the left face of the cube
	vertices.emplace_back(vec3(-1.0, -1.0, -1.0), vec4(0.0, 0.0, 0.0, 1.0));
	vertices.emplace_back(vec3(-1.0, -1.0, 1.0), vec4(0.0, 0.0, 1.0, 1.0));
	vertices.emplace_back(vec3(-1.0, 1.0, 1.0), vec4(0.0, 1.0, 1.0, 1.0));
	vertices.emplace_back(vec3(-1.0, -1.0, -1.0), vec4(0.0, 0.0, 0.0, 1.0));
	vertices.emplace_back(vec3(-1.0, 1.0, 1.0), vec4(0.0, 1.0, 1.0, 1.0));
	vertices.emplace_back(vec3(-1.0, 1.0, -1.0), vec4(0.0, 1.0, 0.0, 1.0));

	//vertices for the upper face of the cube
	vertices.emplace_back(vec3(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0));
	vertices.emplace_back(vec3(-1.0, 1.0, 1.0), vec4(0.0, 1.0, 1.0, 1.0));
	vertices.emplace_back(vec3(1.0, 1.0, -1.0), vec4(1.0, 1.0, 0.0, 1.0));
	vertices.emplace_back(vec3(-1.0, 1.0, 1.0), vec4(0.0, 1.0, 1.0, 1.0));
	vertices.emplace_back(vec3(1.0, 1.0, -1.0), vec4(1.0, 1.0, 0.0, 1.0));
	vertices.emplace_back(vec3(-1.0, 1.0, -1.0), vec4(0.0, 1.0, 0.0, 1.0));

	//vertices for the bottom face of the cube
	vertices.emplace_back(vec3(-1.0, -1.0, -1.0), vec4(0.0, 0.0, 0.0, 1.0));
	vertices.emplace_back(vec3(1.0, -1.0, -1.0), vec4(1.0, 0.0, 0.0, 1.0));
	vertices.emplace_back(vec3(-1.0, -1.0, 1.0), vec4(0.0, 0.0, 1.0, 1.0));
	vertices.emplace_back(vec3(1.0, -1.0, -1.0), vec4(1.0, 0.0, 0.0, 1.0));
	vertices.emplace_back(vec3(-1.0, -1.0, 1.0), vec4(0.0, 0.0, 1.0, 1.0));
	vertices.emplace_back(vec3(1.0, -1.0, 1.0), vec4(1.0, 0.0, 1.0, 1.0));

	Model result;
	result.initialize(vertices);
	return result;
}
