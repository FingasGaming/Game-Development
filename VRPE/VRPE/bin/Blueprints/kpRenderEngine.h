#pragma once
#ifndef KPRENDERENGINE_H
#define KPRENDERENGINE_H

#include "kpWindow.h"
#include "kpGame.h"
#include "../Util/kpBase/kpCamera.h"

namespace JackFruitEngine
{
	class JFE_API kpRenderEngine : public kpBlueprint
	{
	private:
		kpWindow* window;
		kpCamera* mainCamera;
	public:
		kpRenderEngine(kpWindow* win);
		~kpRenderEngine(void);
		virtual void onRender(kpGame* game, float dt);
		inline void setCamera(kpCamera* cam){ mainCamera = cam; }
	};
}
#endif
