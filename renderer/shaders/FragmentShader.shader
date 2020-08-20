#version 330 core

out vec4 color;
in vec4 v_colors;
uniform sampler2D u_Texture[32];    // 32 possible texture slots
in vec2 v_TexCoord;
in float v_texSlot;
in float v_hasTex;

void main()
{
	int index = int(v_texSlot);	
	if (v_hasTex == 1.0f)
	{
		vec4 texColor = texture(u_Texture[index], v_TexCoord);   // choose to sample from the correct index
		color = texColor;
	}
	else		
		color = v_colors;	
}