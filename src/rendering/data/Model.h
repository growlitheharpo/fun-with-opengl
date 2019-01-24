#pragma once
#include <GL/glew.h>
#include <vector> // TODO: Replace with DynamicVector

#include "rendering/data/VertexFormat.h"
#include "core/utils/MemoryUtils.h"

class Model
{
private:
	std::vector<GLuint> vbos_;
	GLuint vao_ = 0;

	size_t vertexCount_ = 0;

public:
	Model() = default;

	DISABLE_COPY_SEMANTICS(Model);
	USE_DEFAULT_MOVE_SEMANTICS(Model);

	~Model() = default;

	void initialize(const std::vector<rendering::VertexFormat>& vertices);
	void release();

	size_t vertexCount() const { return vertexCount_; };
	void activate() const;

	static Model create_debug_triangle();
	static Model create_debug_cube();
};
