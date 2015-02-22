#include "kpEngine.h"

JackFruitEngine::kpEngine* JackFruitEngine::kpEngine::engine = nullptr;

JackFruitEngine::kpScript* JackFruitEngine::kpEngine::src = NULL;
SDL_Window* JackFruitEngine::kpEngine::window = NULL;
SDL_Event JackFruitEngine::kpEngine::_event = SDL_Event();
int JackFruitEngine::kpEngine::runState = 0;

JackFruitEngine::kpEngine::kpEngine(void)
{
	//src = new kpScript("bin/scripts/bootscript.lua");
}


JackFruitEngine::kpEngine::~kpEngine(void)
{
}
//Function: retrieve engine
JackFruitEngine::kpEngine* JackFruitEngine::kpEngine::getEngine()
{
	if(!engine)
	{
		engine = new kpEngine();
	}
	return engine;
}
SDL_Window* JackFruitEngine::kpEngine::getMainWindow()
{
	return window;
}
int JackFruitEngine::kpEngine::getRun()
{ return runState;}
void JackFruitEngine::kpEngine::init(lua_State* s)	
{		
	src->load(s);
}
void JackFruitEngine::kpEngine::setMainWindow(SDL_Window* win)
{		
	window = win;
}
void JackFruitEngine::kpEngine::setRun(int win)
{		
	runState = win;
}
void JackFruitEngine::kpEngine::setScript(const char* s)
{
	if(src)
	{
		delete src;
		src = NULL;
		src = new kpScript(s);
	}
	else
	{
		src = new kpScript(s);
	}
}
int JackFruitEngine::kpEngine::execute(lua_State* s, int mode)
{
	int error = 0;
	if(mode == 0){
	//run bootScript actions
	//onStart function:call from script before main loop
	if(!src->call(s, "onInit"))
		error++;

	//std::cout << src->getLuaUniformI(s, "running") << std::endl;
	if(!src->call(s, "onStart"))
		error++;
	//string sError = src->getErr(s);	
	if(error > 0)
	{
		return error++;
	}

	while(runState == 0 || runState != 2)
	{
		while(SDL_PollEvent(&_event))
		{
			if(_event.type == SDL_QUIT)
			{
				runState = 2;
			}
		}
		//onUpdate function: use to update engine from script
		src->call(s, "onEvent");
		//onUpdate function: use to update engine from script
		src->call(s, "onUpdate");
		//onRender function: use to do all drawing to the screen from script
		src->call(s, "onRender");
	}

	src->call(s, "onDestroy");
	}
	else if(mode == 1)
	{
		src->load(s);
	}
	return error;
}