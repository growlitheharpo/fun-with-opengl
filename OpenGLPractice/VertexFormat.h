#pragma once

enum AttributeIndex
{
	Attr_POSITION = 0,
};

#include "glm/vec3.hpp"

namespace graphics
{
	struct VertexFormat
	{
		// todo: texcoords, normals, materialid, etc.
		glm::vec3 position;

		explicit VertexFormat(const glm::vec3& pos) : position(pos) { }
	};
}
