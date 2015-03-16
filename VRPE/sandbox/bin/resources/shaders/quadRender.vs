attribute vec3 vertex;
attribute vec2 UV;

varying vec2 outUV;

uniform mat4 kpT_modelMatrix;
uniform mat4 kpT_projectionMatrix;
uniform mat4 kpT_viewMatrix;
uniform mat4 kpT_modelViewMatrix;
uniform mat3 kpT_normalMatrix;

void main()
{
	mat4 kpT_modelViewProjectionMatrix = kpT_projectionMatrix * kpT_modelMatrix;
	gl_Position = kpT_modelViewProjectionMatrix * vec4(vertex,1.0);
	outUV=UV;
}
