#version 330 core

layout (location = 0) out vec4 color;

in DATA
{
	vec4 position;
	vec2 uv;
	vec4 color;
	vec4 bgColor;
} fs_in;

uniform sampler2D tex;

void main()
{
	vec4 texColor = texture2D(tex, fs_in.uv);

	color = mix(fs_in.bgColor, texColor * fs_in.color, texColor.a);
}