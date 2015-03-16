#pragma once
#ifndef ENGINE_KERNEL_H
#define ENGINE_KERNEL_H

#include "bin\Util\kpEngine.h"
#include "bin\Util\kpSystem\kpStructure.h"

namespace JackFruitEngine
{
	class kpKernel
	{
		//class that initialise core features and engine init
	public:
		kpKernel(void);
		~kpKernel(void);
		bool kill();
		int initialise();
		int run(kpWindow* win);
		int run(const char* luafile);		
		int run(const char* luafile, int mode);
		int run(kpGame* game, int mode);
	private:
		lua_State* l;
		int returnError;
		kpScript kern;
	};
}
#endif

