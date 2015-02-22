#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "kpBase\kpScript.h"
#include "kpSystem\kpStructure.h"

namespace JackFruitEngine
{
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
		static void setRun(int win);
		static int execute(lua_State* s, int mode = 0);
		static void setScript(const char* s);
	private:
		//variables		
		static int runState;
		static kpEngine* engine;
		static kpScript* src;
		static SDL_Event _event;
		static SDL_Window *window;
		//functions
		kpEngine(void);
	};
}
#endif
