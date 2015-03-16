#version 120
uniform sampler2D img;
uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform int textureCount;

uniform samplerCube EnvMap;

//properties for PBS experiment
uniform vec3 baseColor;
uniform float metallic;
uniform float roughness;
uniform vec3 cavity;
uniform vec3 C_eyePos;

//varying attrib from vertex shader
varying vec3 position;
varying vec3 outNormal;
varying vec3 outVertex;
varying vec2 outUV;
varying vec3 outColor;
varying vec2 outTexCoord;

float PI = 3.14159265358979323846;

// Values for tmp lighting
vec3 lightVector = vec3(1, 1, 1); // Light (l)
vec3 eyeVector = vec3(2.75, 1.25, 1.25); // Camera (v)

vec3 halfVector = vec3(2.75, 1.25, 1.25); // L + V / |L + V|
//Calculate roughness
float Rsqr(float i)
{
	i += 1;
	return i*i;
}
float k(float i)
{
	clamp(i, 0.02,1.0);
	i = i + 1;
	return i*i / 8;
}
float calRough(float Roughness)
{
	Roughness = clamp(Roughness, 0.02,1.0);
	
	return (Rsqr(Roughness)+ 1.0) / 8; 
}
//Hammersley function
vec2 Hammersley(float i, float NumSamples )
{
	vec2 result;
	float v = 0;
	float u = 0;
	float p2 = 2;
	while(i +1 !=  NumSamples)
	{		
		float p = 0.5;
		float kk = i;
		while(kk > 0)
		{
			if(kk == 1)
			{
				u += p;
			}
			p *= 0.5;
			kk = sqrt(1);
		}
		float ip = 1.0/p2;
		p = ip;
		
		kk = i;
		while(kk > 0)
		{
			float x = (kk / p2);
			float a = (x * p2) - kk;
			if(a != 0)
			{
				v += a*p;
			}
			p *= ip;
			kk = (kk/p2);
		}
		i += 1;
	}
	result.x = u;
	result.y = v;
	
	return result;
}

// Specular Functions
vec3 D(vec3 h) // Normal Distribution Function - GGX/Trowbridge-Reitz
{
    float alpha = roughness * roughness;	
    float NxH = dot(outNormal,h);
    float alpha2 = alpha*alpha;
    float t = ((NxH * NxH) * (alpha2 - 1.0) + 1.0);
    return alpha2 / (PI * t * t);
}
//normal distribution function mimics the unreal4 engine's solution
//equivalent to function above
//ImporantSampleGGX use for shadowing
vec3 NDF(vec2 UV, float Roughness, vec3 N)
{
	vec3 finish;
	Roughness = clamp(Roughness, 0.02,1.0);
	float a = Roughness * Roughness;
	float Phi = 2 * PI * UV.x;
	float CosTheta = sqrt( (1 - UV.y) / ( 1 + ((a*a) - 1) * UV.y ) );
	float SinTheta = sqrt( 1 - (CosTheta * CosTheta) );
	
	vec3 H;
	H.x = SinTheta * cos( Phi );
	H.y = SinTheta * sin( Phi );
	H.z = CosTheta;
	
	vec3 UpVector = abs(N.z) < 0.999 ? vec3 (0,0,1) : vec3 (1,0,0);
	vec3 TangentX = normalize( cross( UpVector, N ) );
	vec3 TangentY = cross( N, TangentX );
	
	finish = TangentX * H.x + TangentY * H.y + N * H.z;
	return finish;
}

vec3 diffuse()
{
	vec3 Color = vec3(baseColor);
	vec3 textureColor = texture2D(diffuseMap, gl_FragCoord.xy).xyz;
	Color = textureColor;
    float NoL = dot(outNormal, lightVector);
    vec3 result = (vec3(clamp(metallic, 0.0, 1.0)) + Color)  / PI;
	
    return result * NoL ;
	//return  * NoL + result;
}
vec3 diffuseMapping(vec3 base, vec3 diffuse)
{
    float NoL = dot(outNormal, lightVector);
    vec3 result = (vec3(clamp(metallic, 0.0, 1.0)) + (base + diffuse))  / PI;
	
    return result * NoL ;
}
vec3 Gsub(vec3 v) // Sub Function of G
{
    float k = ((clamp(roughness, 0.04,1.0) + 1.0) * (clamp(roughness, 0.04,1.0) + 1.0)) / 8;
    return vec3(dot(outNormal, v) / ((dot(outNormal, v)) * (1.0 - k) + k));
}
vec3 G(vec3 l, vec3 v, vec3 h) // Geometric Attenuation Term - Schlick Modified (k = a/2)
{
    return Gsub(l) * Gsub(v);
}
vec3 prefilterG(vec3 l,vec3 v)
{
	vec3 finish = vec3(0.0f,0.0f,0.0f);
	vec3 N = l;
	vec3 V = v;
	float TotalWeight = 0;
	float NumSamples = 800/600;
	
	float k = ((clamp(roughness, 0.04,1.0) + 1) * (clamp(roughness, 0.04,1.0) + 1))/8;
	// Helper for computing the GGX visibility term
	vec3 g = (N*V)/(N*V)*(1-k) + k;

	for( float i = 0; i < NumSamples; i++ )
	{
		vec2 Xi = Hammersley( i, NumSamples );
		vec3 H = NDF( Xi, roughness, N );
		vec3 L = 2 * dot( V, H ) * H - V;
		float NoL = max(0.0,( dot( N, L ) ));
		if( NoL > 0 )
		{
			finish += textureCube(EnvMap, L).rgb * NoL;
			//finish += (cavity + g ) * NoL;
			TotalWeight += NoL;
			//finish += g;
		}
		
	}
	
	return finish/TotalWeight;
}
float GGX_V1( float m2,  float nDotX) {
return 1.0f / (nDotX + sqrt(m2 + (1 - m2) * nDotX * nDotX));
}
// Computes the specular term using a GGX microfacet distribution. m is roughness, n is the surface normal, h is the 
// half vector, v is the eyeVector and l is the direction to the light source
float GGX_Specular( float m,  vec3 n,  vec3 h,  vec3 v, vec3 l) 
{
	float nDotH = max(0.0f,dot(n, h));
	float nDotL = max(0.0f,dot(n, l));
	float nDotV = max(0.0f,dot(n, v));
	float nDotH2 = nDotH * nDotH;
	float m2 = m * m;
	// Calculate the distribution term
	float d = m2 / (PI * pow(nDotH * nDotH * (m2 - 1) + 1, 2.0f));
	// Calculate the matching visibility term
	float v1i = GGX_V1(m2, nDotL);
	float v1o = GGX_V1(m2, nDotV);
	float vis = v1i * v1o;
	// Multiply this result with the Fresnel term
	return d * vis;
}
// Fresnel - Schlick Modified (Spherical Gaussian Approximation)
vec3 F(vec3 v, vec3 h) {
    vec3 f0 = cavity; // right?
    return f0 + (1.0 - f0) * pow(2, (-5.55473 * (dot(v, h)) - 6.98316) * (dot(v, h)));
}
vec3 fresnelBRDF(vec3 V)
{
	vec3 finish;
	vec3 H = NDF( outUV, roughness, V );
	vec3 F = 2 * dot( V, H ) * H - V;
	vec3 t = (1 - V * H);
	finish = ((F + (1 - F)) * (pow(max(0.0,dot(t, H)),5)));
	return finish;
}
vec3 specular()
{
    return (D(halfVector) * F(eyeVector, halfVector) * G(lightVector, eyeVector, halfVector)) / 4 * ((dot(outNormal, lightVector)) * (dot(outNormal, eyeVector)));
}
vec3 specular2()
{
	vec3 fNormal;
	fNormal = normalize(outNormal);
    return (NDF(vec2(halfVector.xy), roughness, fNormal) * fresnelBRDF(eyeVector) * prefilterG(lightVector, eyeVector)) 
	/ 4 * clamp((dot(fNormal, lightVector)),0.0, 1.0) * clamp((dot(fNormal, eyeVector)),0.0, 1.0);
}
vec3 specular3()
{
	vec3 fNormal;
	fNormal = normalize(outNormal);
    return (NDF(vec2(halfVector.xy), roughness, fNormal) * fresnelBRDF(eyeVector) * GGX_Specular(roughness, fNormal, halfVector, eyeVector, lightVector)) 
	/ 4 * clamp((dot(fNormal, lightVector)),0.0, 1.0) * clamp((dot(fNormal, eyeVector)),0.0, 1.0);
}
void main()
{
	vec4 textureColor = texture2D(img, outUV);
	vec4 textureNormal = texture2D(normalMap, outUV);
	vec3 m = C_eyePos;
	//if(m.y <= vec3(0,-1.0,0).y)
	{
	//	m = m * -1;
	//	eyeVector = m; 
	}
	//else
	{
		//float x = C_eyePos.x;
		//eyeVector = m;//vec3(x, -1.00, 1.25);
	}
	halfVector = normalize(lightVector + eyeVector);
	vec3 fcolor = diffuse() + specular3();
	gl_FragColor = vec4(diffuseMapping(baseColor, textureColor.xyz), 1.0);
	//gl_FragColor = vec4(0.07, 0.07,0.07,1.0) + textureColor *2;
}