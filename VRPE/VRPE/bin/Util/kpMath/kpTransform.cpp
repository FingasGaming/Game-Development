#include "kpTransform.h"


JackFruitEngine::kpTransform::kpTransform()
{
	origin.change( kpVector3f(0.0,0.0,0.0) );
	position.change( kpVector3f(0.0,0.0,0.0) );
	rotation.change( kpVector3f(0.0,0.0,0.0) );
	scale.change( kpVector3f(1.0,1.0,1.0) );
	upVector.change( kpVector3f(0.0,1.0,0.0) );
	parent = nullptr;
	initOld = false;
}

JackFruitEngine::kpTransform::~kpTransform()
{
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpTransform::getParentMatrix() const
{
	if(parent != 0 && parent->hasChanged())
	{
		parentMatrix = parent->getTransformation();
	}
	return parentMatrix;
}
JackFruitEngine::kpTransform::kpTransform(kpVector3f pos)
{
	origin.change( pos );
	position.change( pos );
	rotation.change( kpVector3f(0.0,0.0,0.0) );
	scale.change( kpVector3f(1.0,1.0,1.0) );
	upVector.change( kpVector3f(0.0,1.0,0.0) );
}
JackFruitEngine::kpTransform::kpTransform(kpVector3f pos, kpVector3f rot)
{
	origin.change( pos );
	position.change( pos );
	rotation.change( rot );
	scale.change( kpVector3f(1.0,1.0,1.0) );
	upVector.change( kpVector3f(0.0,1.0,0.0) );
}
JackFruitEngine::kpTransform::kpTransform(kpVector3f pos, kpVector3f rot, kpVector3f &scl)
{
	origin.change( pos );
	position.change( pos );
	rotation.change( rot );
	scale.change( scl );
	upVector.change( kpVector3f(0.0,1.0,0.0) );
}
void JackFruitEngine::kpTransform::Process()
{
	if(initOld)
	{
		oldPos = position;
		oldRot = rotation;
		oldScl = scale;
	}
	else
	{
		oldPos = position + kpVector3f(1,1,1);
		oldRot = rotation * 0.5f;
		oldScl = scale + kpVector3f(1,1,1);
		initOld = true;
	}
}

void JackFruitEngine::kpTransform::setParent(kpTransform * p)
{
	this->parent = p;
}
void JackFruitEngine::kpTransform::setTranslation(kpVector3f pos)
{
	position.change( pos );
}
void JackFruitEngine::kpTransform::setRotation(kpVector3f rot)
{
	rotation.change(rot);
}

void JackFruitEngine::kpTransform::rotate(kpQuaternion& rota)
{
	rot = kpQuaternion((rota * rot).normalise());
}
void JackFruitEngine::kpTransform::setScale(kpVector3f scl)
{
	scale.change(scl);
}
JackFruitEngine::kpQuaternion JackFruitEngine::kpTransform::getLookAtRotation(kpVector3f& point, kpVector3f& up) 
{ 
	kpVector3f d =kpVector3f(point - position);
	d.normalize();
	return kpQuaternion(kpMatrix4f().initRotationFromDirection(d, up)); 
}
void JackFruitEngine::kpTransform::lookAt(kpVector3f& point, kpVector3f& up)
{
	rot = getLookAtRotation(point, up);
}
bool JackFruitEngine::kpTransform::hasChanged()
{
	if(parent != 0 && parent->hasChanged())
	return true;
	
	if(position != oldPos)
		return true;

	if(rotation != oldRot)
		return true;
	
	if(scale != oldScl)
		return true;
		
	return false;
}

JackFruitEngine::kpMatrix4f JackFruitEngine::kpTransform::getTransformation()
{
	kpMatrix4f t = kpMatrix4f().initTranslation(position);
	kpMatrix4f r = kpMatrix4f().initRotation(rotation);
	kpMatrix4f s = kpMatrix4f().initScale(scale);
	return getParentMatrix().mul( t.mul( r.mul(s) ) );
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpTransform::getProjectedTransFormation()
{
	kpMatrix4f t = getTransformation();
	kpMatrix4f r = kpMatrix4f().projection();
	return r.mul(t);
}
JackFruitEngine::kpQuaternion JackFruitEngine::kpTransform::getTransformedRot() const
{
	kpQuaternion parentRot = kpQuaternion(0,0,0,1);
		
	if(parent)
		parentRot = parent->getTransformedRot();
		
	return parentRot * rot;
}
JackFruitEngine::kpQuaternion JackFruitEngine::kpTransform::getRot() const
{
	return rot;
}

JackFruitEngine::kpVector3f JackFruitEngine::kpTransform::getOrigin()
{ return origin;}
JackFruitEngine::kpVector3f JackFruitEngine::kpTransform::getPostion()
{ return position;}
JackFruitEngine::kpVector3f JackFruitEngine::kpTransform::getRotation()
{ return rotation;}
JackFruitEngine::kpVector3f JackFruitEngine::kpTransform::getScale()
{ return scale;}
JackFruitEngine::kpVector3f JackFruitEngine::kpTransform::getUpVector()
{ return upVector;}
JackFruitEngine::kpVector3f JackFruitEngine::kpTransform::getTransformedPos() const 
{ 
	return kpVector3f(getParentMatrix().transform(position)); 
}
