#pragma once
#ifndef KPTRANSFORM_H
#define KPTRANSFORM_H

#include "matrices.h"

#include "kpQuaternion.h"


namespace JackFruitEngine
{
	class JFE_API kpTransform
	{
	private:
		kpVector3f origin;
		kpVector3f position, oldPos;
		kpVector3f rotation, oldRot;
		kpVector3f scale, oldScl;
		kpVector3f upVector;
		kpQuaternion rot;
		kpTransform *parent;
		bool initOld;
		kpMatrix4f parentMatrix;
		kpMatrix4f getParentMatrix() const;
	public:
		kpTransform();
		~kpTransform();
		kpTransform(kpVector3f pos);
		kpTransform(kpVector3f pos, kpVector3f rot);
		kpTransform(kpVector3f pos, kpVector3f rot, kpVector3f &scl);
		void Process();

		void setParent(kpTransform * p);
		void setTranslation(kpVector3f pos);
		void setRotation(kpVector3f rot);

		void rotate(kpQuaternion& rota);
		void setScale(kpVector3f scl);
		kpQuaternion getLookAtRotation(kpVector3f& point, kpVector3f& up);
		void lookAt(kpVector3f& point, kpVector3f& up);
		bool hasChanged();

		kpMatrix4f getTransformation();
		kpMatrix4f getProjectedTransFormation();
		kpQuaternion getTransformedRot() const;
		kpQuaternion getRot() const;

		kpVector3f getOrigin();
		kpVector3f getPostion();
		kpVector3f getRotation();
		kpVector3f getScale();
		kpVector3f getUpVector();
		kpVector3f getTransformedPos() const ;
	};
}

#endif

