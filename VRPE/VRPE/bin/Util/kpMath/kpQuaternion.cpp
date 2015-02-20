#include "kpQuaternion.h"


JackFruitEngine::kpQuaternion::kpQuaternion()
{
	kpQuaternion(0,0,0,1);
}
JackFruitEngine::kpQuaternion::kpQuaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
JackFruitEngine::kpQuaternion::kpQuaternion(kpMatrix4f& matrix)
{
	float  trace = matrix.m[0][0] + matrix.m[1][1] + matrix.m[2][2];
	if(trace > 0)
	{
		float s = 0.5f/sqrtf(trace + 1.0f);
		w = 0.25f / s;
		x = (matrix.m[1][2] - matrix.m[2][1]) * s;
		y = (matrix.m[2][0] - matrix.m[0][2]) * s;
		z = (matrix.m[0][1] - matrix.m[1][0]) * s;
	}
	else if(matrix.m[0][0] > matrix.m[1][1] && matrix.m[0][0] > matrix.m[2][2])
	{
		float s = 2.0f * sqrtf(1.0f + matrix.m[0][0] - matrix.m[1][1] - matrix.m[2][2]);
		w = (matrix.m[1][2] - matrix.m[2][1]) / s;
		x = 0.25f * s;
		y = (matrix.m[1][0] + matrix.m[0][1]) / s;
		z = (matrix.m[2][0] + matrix.m[0][2]) / s;
	}
	else if(matrix.m[1][1] > matrix.m[2][2])
	{
		float s = 2.0f * sqrtf(1.0f + matrix.m[1][1] - matrix.m[0][0] - matrix.m[2][2]);
		w = (matrix.m[2][0] - matrix.m[0][2]) / s;
		x = (matrix.m[1][0] + matrix.m[0][1]) / s;
		y = 0.25f * s;
		z = (matrix.m[2][1] + matrix.m[1][2]) / s;
	}
	else
	{
		float s = 2.0f * sqrtf(1.0f + matrix.m[2][2] - matrix.m[1][1] - matrix.m[0][0]);
		w = (matrix.m[0][1] - matrix.m[1][0]) / s;
		x = (matrix.m[2][0] + matrix.m[0][2]) / s;
		y = (matrix.m[1][2] + matrix.m[2][1]) / s;
		z = 0.25f * s;
	}
	float length = this->length();
	w = w / length;
	x = x / length;
	y = y / length;
	z = z / length;
}
JackFruitEngine::kpQuaternion::~kpQuaternion()
{
}
float JackFruitEngine::kpQuaternion::length()
{
	return (float)sqrt(x*x + y*y+ z*z+ w*w);
}
JackFruitEngine::kpQuaternion JackFruitEngine::kpQuaternion::normalise()
{
	float l = length();
	this->x /= l;
	this->y /= l;
	this->z /= l;
	this->w /= l;

	return *this;
}
JackFruitEngine::kpQuaternion JackFruitEngine::kpQuaternion::conjugate()
{
	kpQuaternion m(-x, -y, -z, w);

	return m;
}
JackFruitEngine::kpQuaternion JackFruitEngine::kpQuaternion::mul(kpQuaternion r)
{
	float w_ = w * r.getW() - x * r.getX() - y * r.getY() - z * r.getZ();
	float x_ = x * r.getW() - w * r.getX() - y * r.getZ() - z * r.getY();
	float y_ = y * r.getW() - w * r.getY() - z * r.getX() - x * r.getZ();
	float z_ = z * r.getW() - w * r.getZ() - x * r.getY() - y * r.getX();
	return kpQuaternion(x_, y_, z_, w_);
}
JackFruitEngine::kpQuaternion JackFruitEngine::kpQuaternion::mul(kpVector3f r)
{
	float w_ = - x * r.x - y * r.y - z * r.z;
	float x_ = w * r.x - y * r.z - z * r.y;
	float y_ = w * r.y - z * r.x - x * r.z;
	float z_ = w * r.z - x * r.y - y * r.x;
	return kpQuaternion(x_, y_, z_, w_);
}
JackFruitEngine::kpQuaternion JackFruitEngine::kpQuaternion::mul(float r)
{
	float w_ = w * r - x * r - y * r - z * r;
	float x_ = x * r - w * r - y * r - z * r;
	float y_ = y * r - w * r - z * r - x * r;
	float z_ = z * r - w * r - x * r - y * r;
	return kpQuaternion(x_, y_, z_, w_);
}
float JackFruitEngine::kpQuaternion::dot(const kpQuaternion& quat)
{
	return (x*quat.getX() + y*quat.getY() + z*quat.getZ() + w*quat.getW());
}
JackFruitEngine::kpQuaternion JackFruitEngine::kpQuaternion::initRotation(kpVector3f axis, float angle)
{
	float sinHA = (float)sin((RAD * angle) / 2);
	float cosHA = (float)cos((RAD * angle) / 2);

	this->x = axis.x * sinHA;
	this->y = axis.y * sinHA;
	this->z = axis.z * sinHA;
	this->w = cosHA;

	return *this;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpQuaternion::toRotationMatrix()
{
	return kpMatrix4f().initRot(getForward(), getUp(), getRight());
}
JackFruitEngine::kpQuaternion JackFruitEngine::kpQuaternion::lerp(const kpQuaternion& r, float factor) const
{
	kpQuaternion tmp(x,y,z,w);
	kpQuaternion result;
	result.x = r.x - tmp.x;
	result.y = r.y - tmp.y;
	result.z = r.z - tmp.z;
	result.w = r.w - tmp.w;
	return (result) * factor + tmp;
}
JackFruitEngine::kpQuaternion JackFruitEngine::kpQuaternion::NLerp(const kpQuaternion& r, float lerpFactor, bool shortestPath) const
{
	kpQuaternion correctedDest;
	kpQuaternion *tmp = new kpQuaternion(x,y,z,w);
		
	if(shortestPath && tmp->dot(r) < 0)
	{
		correctedDest = r;
		correctedDest = correctedDest * -1.0f;
	}
	else
		correctedDest = r;
	
	return kpQuaternion(lerp(correctedDest, lerpFactor).normalise());
}
JackFruitEngine::kpVector3f JackFruitEngine::kpQuaternion::getForward()
{
	return kpVector3f(2.0f *(x*z - w*y), 2.0f *(y*z + w*x), 1.0f - 2.0f *(x*x + y*y));
}
JackFruitEngine::kpVector3f JackFruitEngine::kpQuaternion::getBack()
{
	return kpVector3f(-2.0f *(x*z - w*y), -2.0f *(y*z + w*x), -(1.0f - 2.0f *(x*x + y*y)));
}
JackFruitEngine::kpVector3f JackFruitEngine::kpQuaternion::getUp()
{
	return kpVector3f(2.0f *(x*y + w*z), 1.0f - 2.0f *(x*x + z*z), 2.0f *(y*z - w*x));
}
JackFruitEngine::kpVector3f JackFruitEngine::kpQuaternion::getDown()
{
	return kpVector3f(-2.0f *(x*y + w*z), -(1.0f - 2.0f *(x*x + z*z)), -2.0f *(y*z - w*x));
}
JackFruitEngine::kpVector3f JackFruitEngine::kpQuaternion::getLeft()
{
	return kpVector3f(-(1.0f - 2.0f * (y*y + z*z)), -2.0f * (x*y - w*z), -2.0f * (x*z + w*y));
}
JackFruitEngine::kpVector3f JackFruitEngine::kpQuaternion::getRight()
{
	return kpVector3f(1.0f - 2.0f * (y*y + z*z), 2.0f * (x*y - w*z), 2.0f * (x*z + w*y));
}

float JackFruitEngine::kpQuaternion::getX()const { return x;}
float JackFruitEngine::kpQuaternion::getY()const { return y;}
float JackFruitEngine::kpQuaternion::getZ()const { return z;}
float JackFruitEngine::kpQuaternion::getW()const { return w;}
JackFruitEngine::kpQuaternion JackFruitEngine::kpQuaternion::operator-(const kpQuaternion& r)
{
	float w_ = w - r.getW();
	float x_ = x - r.getX();
	float y_ = y - r.getY();
	float z_ = z - r.getZ();
	return kpQuaternion(x_, y_, z_, w_);
}
JackFruitEngine::kpQuaternion JackFruitEngine::kpQuaternion::operator*(const kpQuaternion& r)
{
	float w_ = w * r.getW() - x * r.getX() - y * r.getY() - z * r.getZ();
	float x_ = x * r.getW() - w * r.getX() - y * r.getZ() - z * r.getY();
	float y_ = y * r.getW() - w * r.getY() - z * r.getX() - x * r.getZ();
	float z_ = z * r.getW() - w * r.getZ() - x * r.getY() - y * r.getX();
	return kpQuaternion(x_, y_, z_, w_);
}
JackFruitEngine::kpQuaternion JackFruitEngine::kpQuaternion::operator+(const kpQuaternion& r)
{
	float w_ = w + r.getW();
	float x_ = x + r.getX();
	float y_ = y + r.getY();
	float z_ = z + r.getZ();
	return kpQuaternion(x_, y_, z_, w_);
}
JackFruitEngine::kpQuaternion JackFruitEngine::kpQuaternion::operator+(const float& r)
{
	float w_ = w + r;
	float x_ = x + r;
	float y_ = y + r;
	float z_ = z + r;
	return kpQuaternion(x_, y_, z_, w_);
}
JackFruitEngine::kpQuaternion JackFruitEngine::kpQuaternion::operator*(const float& r)
{
	float w_ = w * r - x * r - y * r - z * r;
	float x_ = x * r - w * r - y * r - z * r;
	float y_ = y * r - w * r - z * r - x * r;
	float z_ = z * r - w * r - x * r - y * r;
	return kpQuaternion(x_, y_, z_, w_);
}

JackFruitEngine::kpQuaternion& JackFruitEngine::kpQuaternion::operator*=(kpQuaternion& quat)
{
	x *= quat.getX();
	y *= quat.getY();
	z *= quat.getZ();
	w *= quat.getW();
	return *this;
}
