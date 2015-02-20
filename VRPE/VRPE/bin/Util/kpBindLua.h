#pragma once
#ifndef ENGINE_LUABIND_H
#define ENGINE_LUABIND_H


#include "kpSystem\kpLua\lua.hpp"
extern "C"{
#include "lauxlib.h"
}
#include <string>
using namespace std;

namespace JackFruitEngine{

	class kpBindLua 
	{
	lua_State* L;
	public:
		kpBindLua(lua_State* l):L(l){}
		void pushnil()
		{
			lua_pushnil(L);
		}
		void pushnumber (double n)
		{
			lua_pushnumber(L,n);
		}
		void pushinterger (int n)
		{
			lua_pushinteger(L,n);
		}
		void pushboolean (int n)
		{
			lua_pushboolean(L,n);
		}
		void pushunsigned (unsigned int n)
		{
			lua_pushunsigned(L,n);
		}
		void pushstring (const char* s)
		{
			lua_pushstring(L,s); 
		}
		double checknumber (int index)
		{
			return luaL_checknumber(L,index);
		}
		int checkinteger (int index)
		{
			return luaL_checkinteger(L,index);
		}
		/*'lua_Integer' : forcing value to bool 'true' or 'false' (performance warning)
		*/
		bool checkbool (int index)
		{
			bool t = false;
			if(luaL_checkinteger(L,index) >= 1)
			{
				t = true;
			}
			else if(luaL_checkinteger(L,index) <= 0)
			{
				t = false;
			}
			return t;
		}
		unsigned int checkunsigned (int index)
		{
			return luaL_checkunsigned(L,index);
		}
		const char* checkstring (int index)
		{
		return luaL_checkstring(L,index);
		}
		int libsize (const luaL_Reg *l) 
		{
		  int size = 0;
		  for (; l && l->name; l++) size++;
		  return size;
		}
		const char *luaL_findtable (lua_State *L, int idx, const char *fname, int szhint) 
		{
			const char *e;
			if (idx) lua_pushvalue(L, idx);
			do {
			e = strchr(fname, '.');
			if (e == NULL) e = fname + strlen(fname);
			lua_pushlstring(L, fname, e - fname);
			lua_rawget(L, -2);
			if (lua_isnil(L, -1)) {  /* no such field? */
				lua_pop(L, 1);  /* remove this nil */
				lua_createtable(L, 0, (*e == '.' ? 1 : szhint)); /* new table for field */
				lua_pushlstring(L, fname, e - fname);
				lua_pushvalue(L, -2);
				lua_settable(L, -4);  /* set new table into field */
			}
			else if (!lua_istable(L, -1)) {  /* field has a non-table value? */
				lua_pop(L, 2);  /* remove table and value */
				return fname;  /* return problematic part of the name */
			}
			lua_remove(L, -2);  /* remove previous table */
			fname = e + 1;
			} while (*e == '.');
			return NULL;
			}
		void luaL_pushmodule (lua_State *L, const char *modname, int sizehint) 
		{
			luaL_findtable(L, LUA_REGISTRYINDEX, "_LOADED", 1);  /* get _LOADED table */
			lua_getfield(L, -1, modname);  /* get _LOADED[modname] */
			if (!lua_istable(L, -1)) {  /* not found? */
			lua_pop(L, 1);  /* remove previous result */
			/* try global variable (and create one if it does not exist) */
			lua_pushglobaltable(L);
			if (luaL_findtable(L, 0, modname, sizehint) != NULL)
			{
				luaL_error(L, "name conflict for module " LUA_QS, modname);
			}
			lua_pushvalue(L, -1);
			lua_setfield(L, -3, modname);  /* _LOADED[modname] = new table */
			}
				lua_remove(L, -2);  /* remove _LOADED table */
		}
		void luaL_openlib(lua_State *L, const char *libname, const luaL_Reg *l, int nup)
			{
				luaL_checkversion(L);
				if (libname) 
				{
					luaL_pushmodule(L, libname, libsize(l));  /* get/create library table */
					lua_insert(L, -(nup + 1));  /* move library table to below upvalues */
				}
			if (l)
			luaL_setfuncs(L, l, nup);
			else
			lua_pop(L, nup);  /* remove upvalues */

			}
		void init (const char* tname, const char* bname, const luaL_Reg *flist, int (*destroy) (lua_State*)) 
		 {
			lua_newtable(L);                  // create table for type checking
			lua_pushstring(L,"v");
			lua_setfield(L,-2,"__mode");     // set as weak-value table
			lua_pushvalue(L,-1);             // duplicate table
			lua_setmetatable(L,-2);          // set itself as metatable
			//lua_replace(L, LUA_REGISTRYINDEX + 1);  // set table as env table
			luaL_openlib(L,tname,flist,0);     // create libtable
			luaL_newmetatable(L,tname);      // create metatable for objects
			lua_pushvalue(L,-2);
			lua_setfield(L,-2,"__index");    // mt.__index = libtable
			lua_pushcfunction(L,destroy);
			lua_setfield(L,-2,"__gc");       // mt.__gc = destroy
			if (bname) 
			{
			 luaL_getmetatable(L,bname);
			 lua_setfield(L,-2,"_base");	 // mt._base = base mt
			}
			lua_pop(L, 1);					// pop metatable
			if (bname) 
			{
				lua_getfield(L,LUA_REGISTRYINDEX,bname);
				lua_setfield(L,-2,"__index"); // libtable.__index = base libtable
				lua_pushvalue(L,-1);          // duplicate libtable
				lua_setmetatable(L,-2);       // set itself as metatable
			}
		 }
		void pushusertype (void* udata, const char* tname) 
		 {
			lua_pushlightuserdata(L,udata);
			lua_rawget(L,LUA_REGISTRYINDEX);     // get udata in env table
			if (lua_isnil(L,-1)) 
			{
				lua_newtable(L);                 // create table to be the object
				lua_pushlightuserdata(L,udata);  // push address
				lua_setfield(L,-2,"_pointer");   // table._pointer = address
				luaL_getmetatable(L,tname);     // get metatable 
				lua_setmetatable(L,-2);         // set metatable for udata
				lua_pushlightuserdata(L,udata); // push address
				lua_pushvalue(L,-2);            // push udata
				lua_rawset(L,LUA_REGISTRYINDEX); // envtable[address] = udata
			}
		 }
		void *checkusertype (int index, const char* tname) 
		 {
			lua_getfield(L, LUA_REGISTRYINDEX, tname);   /* get metatable of given type */
			lua_getmetatable(L,index);                   /* get associated metatable */
			while (lua_istable(L,-1)) 
			{
				if (lua_rawequal(L,-1,-2)) 
				{
					lua_pop(L,2);		// pop string and mt
					lua_getfield(L,index,"_pointer");  // get address
					void* udata = lua_touserdata(L,-1);
					return udata;
				}
				lua_getfield(L,-1,"_base");          // get mt._base
				lua_replace(L,-2);                   // replace: mt = mt._base
			}
			luaL_argerror(L,index,tname);
			return NULL;
		 }
		void* checkusertype (int index, char* tname) 
		 {
			 lua_getmetatable(L, index);                // get metatable
			 while (lua_istable(L,-1)) 
			 {                // while mt is valid 
				 lua_pushvalue(L,-1);                   // duplicate mt
				 lua_rawget(L, LUA_REGISTRYINDEX);      // get stored type name 
				 const char *tn = lua_tostring(L, -1);
				 if (tn && (strcmp(tn, tname) == 0)) 
				 {    // compare types
					 lua_getfield(L,index,"_pointer");  // get address
					 void* udata = lua_touserdata(L,-1);
					 lua_pop(L,2);                      // pop string and mt
					 return udata;
				 }
				 lua_pop(L,1);                          // pop string 
				 lua_getfield(L,-1,"_base");            // get mt._base
				 lua_replace(L,-2);                     // replace: mt = mt._base
			 }
			 lua_pop(L, 1);                             // pop mt
			 luaL_argerror(L,index,tname);
			 return NULL;
		}
	};
}
#endif