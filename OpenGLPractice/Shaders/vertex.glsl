#version 430 core
 
 layout(location = 0) in vec3 in_position; // LOCATION 0: VertexFormat.h Attr_POSITION

void main(void)
{
	gl_Position = vec4(in_position, 1.0);
}
