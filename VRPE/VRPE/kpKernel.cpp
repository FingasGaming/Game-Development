#include "kpKernel.h"

int kpAPILIBS(lua_State* l);
JackFruitEngine::kpKernel::kpKernel(void)
{
	l = NULL;
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
		returnError++;
		return returnError;
	}
	

	
	//lua init
	//to create lua state for scripting
	l = luaL_newstate();

	if(l == NULL)
	{
		returnError++;
		return returnError;
	}
	luaL_openlibs(l);/**/
	kpAPILIBS(l);

	return returnError;
}

int JackFruitEngine::kpKernel::run(kpWindow* win)
{
	returnError = 0;
	win->init(l);
	JackFruitEngine::kpEngine::getEngine()->setIMainWindow(win);
	return JackFruitEngine::kpEngine::getEngine()->execute(l, CPP_WINDOWED);
}
int JackFruitEngine::kpKernel::run(const char* luafile)
{
	JackFruitEngine::kpEngine::getEngine()->setScript(luafile);
	return JackFruitEngine::kpEngine::getEngine()->execute(l, 0);
}
int JackFruitEngine::kpKernel::run(const char* luafile, int mode)
{
	JackFruitEngine::kpEngine::getEngine()->setScript(luafile);
	return JackFruitEngine::kpEngine::getEngine()->execute(l, mode);
}
int JackFruitEngine::kpKernel::run(kpGame* game, int mode)
{
	return JackFruitEngine::kpEngine::getEngine()->execute(l, game, mode);
}