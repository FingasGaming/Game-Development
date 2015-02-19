#pragma once
#ifndef ENGINE_KERNEL_H
#define ENGINE_KERNEL_H

#include "data\kpLua\lua.hpp"
#include "data\Util\kpBase\kpScript.h"

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
		int run();
		int run(const char* luafile);
	private:
		lua_State* l;
		int returnError;
		kpScript kern;
	};
}
#endif

