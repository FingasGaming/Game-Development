#version 120
attribute vec3 vertex;
attribute vec3 normal;
attribute vec3 tangent;
attribute vec3 baseColor;
attribute vec2 UV;

varying vec3 outNormal;
varying vec3 outVertex;
varying vec2 outUV;
varying vec2 outTexCoord;
varying vec3 outColor;
varying vec3 position;
varying float outRough;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
	gl_Position = modelViewProjectionMatrix * vec4(vertex,1.0);
	position = vec3(modelViewMatrix * vec4(vertex,1.0));
	outNormal = normalMatrix*normal;
	outUV=UV;
	outColor = baseColor;
	outTexCoord = gl_MultiTexCoord0.xy;
}