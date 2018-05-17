#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

core::Transform::Transform()
{
	for (auto i = 0; i < 4; ++i)
		for (auto j = 0; j < 4; ++j)
			transform[i][j] = 0;

	transform[0][0] = 1.0f;
	transform[1][1] = 1.0f;
	transform[2][2] = 1.0f;
	transform[3][3] = 1.0f;
}
