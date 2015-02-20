#include "kpScript.h"


JackFruitEngine::kpScript::kpScript(void) : kpComponent(), name("script"), filename("none")
{
}
JackFruitEngine::kpScript::kpScript(const char* file) : kpComponent(), name("script"), filename(file)
{
}

JackFruitEngine::kpScript::~kpScript(void)
{
	if(filename)
		delete[] filename;

	filename = NULL;
}

bool JackFruitEngine::kpScript::load(lua_State* s)
{
	if (luaL_dofile(s,filename)) 
	{
		fprintf(stderr,"cannot load file: %s\n", filename);
		return false;
	}
		
	return true;
}
bool JackFruitEngine::kpScript::call(lua_State* s, int args, int retrns)
{
	if (lua_pcall(s,args,retrns,0)) 
	{
		//fprintf(stderr,"cannot call file: %s\n", filename);
		return false;
	}
	return true;
}
bool JackFruitEngine::kpScript::call(lua_State* s, const char* func, int args, int retrns)
{
	if(load(s))
	{
		lua_getglobal(s, func);
		if(lua_isfunction(s, lua_gettop(s)))
		{
			lua_pcall(s,args,retrns,0);
		}
		return true;
	}
	return false;
}
bool JackFruitEngine::kpScript::loadfile(lua_State* s)
{
	if (luaL_loadfile(s,filename)) 
	{
		fprintf(stderr,"cannot load file: %s\n", filename);
		return false;
	}
	return true;
}
bool JackFruitEngine::kpScript::loadScript(lua_State* s, const char* f)
{
	if (luaL_dofile(s,f)) 
	{
		fprintf(stderr,"cannot load file %s\n", f);
		return false;
	}
	return true;
}
int JackFruitEngine::kpScript::getLuaUniformI(lua_State* s, const char* name )
{
	loadScript(s, filename);
	lua_getglobal(s,name);
	int w = -1;
	if(lua_isnumber(s, lua_gettop(s)))
	{
		w = (int)lua_tonumber(s, lua_gettop(s));
	}		
	lua_pop(s,1); //reset stack
	//std::cout << getErr(s);
	return w;
}
int JackFruitEngine::kpScript::getLuaUniformI(lua_State* s, const char* file, const char* name )
{
	loadScript(s, file);
	lua_getglobal(s,name);
	int w = -1;
	if(lua_isnumber(s, lua_gettop(s)))
	{
		w = (int)lua_tonumber(s, lua_gettop(s));
	}		
	lua_pop(s,1); //reset stack
	return w;
}
float JackFruitEngine::kpScript::getLuaUniformF(lua_State* s, const char* name )
{
	//load(s);
	lua_getglobal(s,name);
	float w = -1;
	if(lua_isnumber(s, lua_gettop(s)))
	{
		w = (float)lua_tonumber(s, lua_gettop(s));
	}			
	lua_pop(s,1); //	reset stack
	//std::cout << getErr(s) << std::endl;
	return w;
}
float JackFruitEngine::kpScript::getLuaUniformF(lua_State* s, const char* file, const char* name )
{
	loadScript(s, file);
	lua_getglobal(s,name);
	float w = -1;
	if(lua_isnumber(s, lua_gettop(s)))
	{
		w = (float)lua_tonumber(s, lua_gettop(s));
	}		
	lua_pop(s,1); //reset stack
	return w;

}
double JackFruitEngine::kpScript::getLuaUniformD(lua_State* s, const char* name )
{
	//load(s);
	lua_getglobal(s,name);
	double w = -1;
	if(lua_isnumber(s, lua_gettop(s)))
	{
		w = (double)lua_tonumber(s, lua_gettop(s));
	}			
	lua_pop(s,1); //reset stack	
	//std::cout << getErr(s);
	return w;
}
double JackFruitEngine::kpScript::getLuaUniformD(lua_State* s, const char* file, const char* name )
{
	loadScript(s, file);
	lua_getglobal(s,name);
	double w = -1;
	if(lua_isnumber(s, lua_gettop(s)))
	{
		w = (double)lua_tonumber(s, lua_gettop(s));
	}		
	lua_pop(s,1); //reset stack
	return w;

}
const char* JackFruitEngine::kpScript::getLuaUniformS(lua_State* s, const char* name )
{
	load(s);
	lua_getglobal(s,name);
	const char* w = "";
	if(lua_isstring(s, lua_gettop(s)))
	{
		w = (const char*)lua_tostring(s, lua_gettop(s));
	}	
	lua_pop(s,1); //reset stack
	//std::cout << getErr(s);
	return w;
}
const char* JackFruitEngine::kpScript::getLuaUniformS(lua_State* s, const char* file, const char* name )
{
	loadScript(s, file);
	lua_getglobal(s,name);   //name
	const char* w = "";
	if(lua_isstring(s, lua_gettop(s)))  //name,
	{
		w = (const char*)lua_tostring(s, lua_gettop(s)); //name, string
	}		
	lua_pop(s,1); //reset stack
	return w;
}
const char* JackFruitEngine::kpScript::getErr(lua_State* s)
{
	const char* err = "--No Error--\n";
	if(lua_isstring(s, -1))
	{
		err = (const char*)lua_tostring(s, -1);
		return err;
	}
	return err;
}
/*void getError(lua_State* s)
{
	std::cout << getErr(s) << "\n";
}*/
