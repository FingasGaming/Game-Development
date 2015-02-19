#pragma once
#ifndef ENGINE_SCRIPT_H
#define ENGINE_SCRIPT_H

#include "../../kpLua/lua.hpp"

#include "kpComponent.h"


namespace JackFruitEngine{

	class JFE_API kpScript : kpComponent
	{
	private:
		const char* name, *filename;
	public:
		kpScript(void);
		kpScript(const char* file);
		~kpScript(void);

		bool load(lua_State* s);
		bool call(lua_State* s, int args, int retrns);
		bool call(lua_State* s, const char* func, int args = 0, int retrns = 0);
		bool loadfile(lua_State* s);
		bool loadScript(lua_State* s, const char* f);
		int getLuaUniformI(lua_State* s, const char* name );
		int getLuaUniformI(lua_State* s, const char* file, const char* name );
		float getLuaUniformF(lua_State* s, const char* name );
		float getLuaUniformF(lua_State* s, const char* file, const char* name );
		double getLuaUniformD(lua_State* s, const char* name );
		double getLuaUniformD(lua_State* s, const char* file, const char* name );
		const char* getLuaUniformS(lua_State* s, const char* name );
		const char* getLuaUniformS(lua_State* s, const char* file, const char* name );
		const char* getErr(lua_State* s);
		//void getError(lua_State* s);
	};
}
#endif