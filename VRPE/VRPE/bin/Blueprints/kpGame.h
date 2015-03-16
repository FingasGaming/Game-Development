#pragma once
#ifndef KPGAME_H
#define KPGAME_H

#include "../Util/kpBase/kpBlueprint.h"
#include "kpSprite.h"

namespace JackFruitEngine
{
	class JFE_API kpGame : public kpBlueprint
	{
	public:
		kpGame(void);
		~kpGame(void);
		virtual bool init(lua_State* l = NULL);
		virtual bool onStart(bool exe = true);
		virtual void onEvent(SDL_Event _event);
		virtual void onDestroy();
		virtual void update(float delta = 1);
		virtual void render(kpRenderEngine* eng);
		virtual void Execute();
		
	};

}
#endif