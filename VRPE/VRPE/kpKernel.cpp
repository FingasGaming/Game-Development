#include "kpKernel.h"

int kpAPILIBS(lua_State* l);
JackFruitEngine::kpKernel::kpKernel(void)
{
}
JackFruitEngine::kpKernel::~kpKernel(void)
{
	kill();
	SDL_Quit();
}
bool JackFruitEngine::kpKernel::kill()
{
	if(l)
	{
		lua_close(l);
		l = NULL;
		return true;
	}
	return false;
}
int JackFruitEngine::kpKernel::initialise()
{
	returnError = 0;

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		//to create lua state for scripting
		returnError++;
		return returnError;
	}

	l = luaL_newstate();

	if(l == NULL)
	{
		//to create lua state for scripting
		returnError++;
		return returnError;
	}
	luaL_openlibs(l);/**/
	kpAPILIBS(l);

	
	return returnError;
}

int JackFruitEngine::kpKernel::run()
{
	returnError = 0;
	return returnError;
}
int JackFruitEngine::kpKernel::run(const char* luafile)
{
	JackFruitEngine::kpEngine::getEngine()->setScript(luafile);
	return JackFruitEngine::kpEngine::getEngine()->execute(l);
}
int JackFruitEngine::kpKernel::run(const char* luafile, int mode)
{
	JackFruitEngine::kpEngine::getEngine()->setScript(luafile);
	return JackFruitEngine::kpEngine::getEngine()->execute(l,mode);
}

