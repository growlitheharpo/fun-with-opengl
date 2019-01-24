#pragma once

#include "core/utils/MemoryUtils.h"

enum AttributeIndex
{
	Attr_POSITION = 0,
	Attr_COLOR = 1,
};

#include "glm/glm.hpp"

namespace rendering
{
	struct VertexFormat
	{
		// todo: texcoords, normals, materialid, etc.
		glm::vec3 position;
		glm::vec4 color;

		explicit VertexFormat(const glm::vec3& pos) : position(pos), color(0.0f, 0.0f, 0.0f, 0.0f) { }
		VertexFormat(const glm::vec3& pos, const glm::vec4& col) : position(pos), color(col) { }

		USE_DEFAULT_COPY_SEMANTICS(VertexFormat);
		USE_DEFAULT_MOVE_SEMANTICS(VertexFormat);
	};
}
