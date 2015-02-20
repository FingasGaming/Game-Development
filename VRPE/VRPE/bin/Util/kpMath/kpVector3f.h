#pragma once
#ifndef KPVECTOR3F_H
#define KPVECTOR3F_H

#include <iostream>
#include <cmath>

#ifndef API_EXPORTS
#define JFE_API __declspec(dllexport) 
#else
#define JFE_API __declspec(dllimport)
#endif

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif
//from angle to radian
#define RAD M_PI / 180
#define kpToRadians(x) (float)(((x) * M_PI / 180.0f))
#define kpToDegrees(x) (float)(((x) * 180.0f / M_PI))


namespace JackFruitEngine
{
	class JFE_API kpVector3f
	{
	public:
		float x,y,z;
		kpVector3f();
		kpVector3f(float a,float b);
		kpVector3f(float a,float b,float c);
		float Max();
		float dotProduct(const kpVector3f& vec2);
		kpVector3f crossProduct(const kpVector3f& vec2);
		float length();
		void normalize();
		kpVector3f scalar(float scale = 1);
		kpVector3f lerp(const kpVector3f& vec2, float factor)
		{
			kpVector3f tmp(x,y,z);
			kpVector3f result;
			result.x = vec2.x - tmp.x;
			result.y = vec2.y - tmp.y;
			result.z = vec2.z - tmp.z;
			return (result) * factor + tmp;
		}
		void change(float a,float b,float c);
		void change(kpVector3f vec2);
		void changeX(float a);
		void changeY(float a);
		void changeZ(float a);
		
		kpVector3f operator+(const kpVector3f& vec2);
		kpVector3f operator-(const kpVector3f& vec2);
		kpVector3f operator*(const kpVector3f& vec2);
		kpVector3f operator*(float num);
		kpVector3f operator/(float num);
		
		kpVector3f& operator+=(const kpVector3f& vec2);
		kpVector3f& operator-=(const kpVector3f& vec2);
		kpVector3f& operator*=(float num);
		kpVector3f& operator/=(float num);	
		
		bool operator==(const kpVector3f vec2);
		bool operator==(const int i);
		bool operator=(const int i);
		bool operator!=(const kpVector3f vec2);
		
		//friend std::ostream& operator<<(std::ostream& out,const kpVector3f& vec);
	};
}
#endif
