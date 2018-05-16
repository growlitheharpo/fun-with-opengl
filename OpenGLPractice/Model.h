#pragma once
#include <GL/glew.h>
#include <vector>
#include "VertexFormat.h"

class Model
{
private:
	std::vector<GLuint> vbos_;
	GLuint vao_ = 0;

public:
	Model() = default;
	Model(const Model&) = default;
	Model(Model&&) noexcept = default;
	~Model() = default;

	Model& operator = (const Model& other) = default;
	Model& operator = (Model&& other) = default;

	void initialize(const std::vector<graphics::VertexFormat>& vertices);
	void release();

	void activate() const;

	static Model create_debug_triangle();
};
