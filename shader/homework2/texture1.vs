#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 color;

out vec4 ans;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	ans = color;
}