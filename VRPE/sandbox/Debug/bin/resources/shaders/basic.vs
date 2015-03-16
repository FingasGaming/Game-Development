#version 120

uniform mat4 camMatrix;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;

	//gl_Position = camMatrix*gl_Vertex;
}