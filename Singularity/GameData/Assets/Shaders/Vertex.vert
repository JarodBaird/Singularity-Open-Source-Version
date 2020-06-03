#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 color;
layout (location = 3) in vec4 bgColor;

out DATA
{
	vec4 position;
	vec2 uv;
	vec4 color;
	vec4 bgColor;
} vs_out;

void main()
{
	gl_Position = position;
	vs_out.position = position;
	vs_out.uv = uv;
	vs_out.color = color;
	vs_out.bgColor = bgColor;
}