#pragma once
#ifndef KP_CAMERA_H
#define KP_CAMERA_H

#include "kpcomponent.h"
#include "..\kpMath\kpTransform.h"

namespace JackFruitEngine
{
	class JFE_API kpCamera : public kpComponent
	{
	public:
		kpCamera(void);
		kpCamera(float fov, float aspect, float zNear, float zFar);
		~kpCamera(void);
		kpMatrix4f* GetViewProjection() const;
		kpMatrix4f* GetViewProjection(kpGameObject* obj) const;
		void setAsMain();
	protected:
	private:
		kpMatrix4f* m_projection;
	};
}
#endif