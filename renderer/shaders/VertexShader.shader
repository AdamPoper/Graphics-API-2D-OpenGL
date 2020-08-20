#version 330 core

layout(location = 0) in vec4  pos;
layout(location = 1) in vec4  color;
layout(location = 2) in vec2  texcoord;
layout(location = 3) in float texSlot;
layout(location = 4) in float hasTex;

out vec4 v_colors;
uniform mat4 u_MVP;
out vec2 v_TexCoord;
out float v_texSlot;
out float v_hasTex;

void main()
{
	gl_Position = u_MVP * pos;
	v_colors = color;
	v_TexCoord = texcoord;
	v_texSlot = texSlot;
	v_hasTex = hasTex;
}