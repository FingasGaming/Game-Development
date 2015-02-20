#pragma once
#ifndef KPMATRIX4F_H
#define KPMATRIX4F_H

#include "kpVector3f.h"

namespace JackFruitEngine
{
	class JFE_API kpMatrix4f
	{
	private:
		enum matrix4Modes{
		MODEL_MATRIX=0, //local matrix
		VIEW_MATRIX,	//view matrix
		PROJECTION_MATRIX//world matrix
		};
	public:
		float m[4][4];
		kpMatrix4f();
		kpMatrix4f(float matrix[16]);
		~kpMatrix4f();
		kpMatrix4f transpose();
		kpVector3f transform(kpVector3f r);
		kpMatrix4f identity();
		kpMatrix4f initTranslation(float x, float y, float z);
		kpMatrix4f initTranslation(kpVector3f &vec);
		kpMatrix4f initRotation(float x, float y, float z);
		kpMatrix4f initRotation(kpVector3f &vec);
		kpMatrix4f initScale(float x, float y, float z);
		kpMatrix4f initScale(kpVector3f &vec);
		kpMatrix4f projection(float width = 800, float height = 600, float zNear = 0.1, float zFar = 1000, float fov = 70);
		kpMatrix4f View(kpVector3f &forward,kpVector3f &up);
		kpMatrix4f initRot(kpVector3f forward,kpVector3f up,kpVector3f right);
		kpMatrix4f ortho(float left, float right, float bottom, float top, float neara, float fara);
		kpMatrix4f frustum(float left, float right, float bottom, float top, float neara, float fara);
		kpMatrix4f initRotationFromVectors(kpVector3f& n, kpVector3f& v, kpVector3f& u);
		kpMatrix4f initRotationFromDirection(kpVector3f& forward, kpVector3f& up);
		kpMatrix4f mul(kpMatrix4f r);
		kpMatrix4f mulToMatrix(float matrix[16]);
		kpMatrix4f toMatrix4f(float matrix[16]);
		kpMatrix4f initPerspective( float fov, float aspectRatio, float neara, float fara);
		float* getM();
		float get(int x, int y);
		void set(int x, int y, float value);
		bool operator==(kpMatrix4f mat);
		bool operator = (kpMatrix4f mat) const;
	};
}

#endif