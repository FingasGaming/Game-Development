#pragma once
#ifndef KPQUATERNION_H
#define KPQUATERNION_H

#include <math.h>
#include "kpMatrix4f.h"

namespace JackFruitEngine
{
	class JFE_API kpQuaternion
	{
	private:
		float x, y, z, w;
	public:
		kpQuaternion();
		kpQuaternion(float x, float y, float z, float w);
		kpQuaternion(kpMatrix4f& matrix);
		~kpQuaternion();
		float length();
		kpQuaternion normalise();
		kpQuaternion conjugate();
		kpQuaternion mul(kpQuaternion r);
		kpQuaternion mul(kpVector3f r);
		kpQuaternion mul(float r);
		float dot(const kpQuaternion& quat);
		kpQuaternion initRotation(kpVector3f axis, float angle);
		kpMatrix4f toRotationMatrix();
		kpQuaternion lerp(const kpQuaternion& r, float factor) const;
		kpQuaternion NLerp(const kpQuaternion& r, float lerpFactor, bool shortestPath) const;
		kpVector3f getForward();
		kpVector3f getBack();
		kpVector3f getUp();
		kpVector3f getDown();
		kpVector3f getLeft();
		kpVector3f getRight();

		float getX()const;
		float getY()const;
		float getZ()const;
		float getW()const;
		kpQuaternion operator-(const kpQuaternion& r);
		kpQuaternion operator*(const kpQuaternion& r);
		kpQuaternion operator+(const kpQuaternion& r);
		kpQuaternion operator+(const float& r);
		kpQuaternion operator*(const float& r);
	
		kpQuaternion& operator*=(kpQuaternion& quat);
	};
}

#endif