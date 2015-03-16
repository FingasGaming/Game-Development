#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "kpBase\kpScript.h"
#include "kpSystem\kpStructure.h"
#include "..\Blueprints\kpGame.h"
#include "..\Blueprints\kpWindow.h"
#include "kpSystem\kpTimer.h"
#include "..\Blueprints\kpRenderEngine.h"

namespace JackFruitEngine
{
	enum {
		CPP_DEFAULT = 0,
		CPP_CUSTUM,
		CPP_WINDOWED,
		LUA_DEFAULT,
		LUA_CUSTUM,
		COUNT
	};
	class JFE_API kpEngine
	{
		//engine class that initialise core engine sub features
	public:
		~kpEngine(void);
		//Function: destroy engine & contents
		static void destroy();
		//Function: retrieve engine
		static kpEngine* getEngine();
		//
		static SDL_Window* getMainWindow();
		static int getRun();
		static void init(lua_State* s);
		static void setMainWindow(SDL_Window* win);
		static void setIMainWindow(kpWindow* win);
		static void setRenderEngine(kpRenderEngine* _renEng);
		static void setRun(int win);
		static int execute(lua_State* s, int mode);
		static int execute(lua_State* s, kpGame* game, int mode);
		static void setScript(const char* s);
		static kpRenderEngine* getRenderer();		
		static kpTimer* getTimer();
		static void setGame(kpGame* games);
		static kpGame* getGame();
	private:
		//variables		
		static int runState;
		static kpEngine* engine;
		static kpScript* src;
		static kpGame* game;		
		static kpTimer* timer;
		static kpRenderEngine* renEng;
		static SDL_Event _event;
		static kpWindow *window;
		//functions
		kpEngine(void);
		static void update();
	};
}
#endif
