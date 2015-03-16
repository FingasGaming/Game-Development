#include "kpEngine.h"

JackFruitEngine::kpEngine* JackFruitEngine::kpEngine::engine = nullptr;
JackFruitEngine::kpWindow* JackFruitEngine::kpEngine::window = NULL;
JackFruitEngine::kpTimer* JackFruitEngine::kpEngine::timer = NULL;
JackFruitEngine::kpGame* JackFruitEngine::kpEngine::game = NULL;
JackFruitEngine::kpScript* JackFruitEngine::kpEngine::src = NULL;
JackFruitEngine::kpRenderEngine* JackFruitEngine::kpEngine::renEng = NULL;
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
	return window->getWindow();
}
int JackFruitEngine::kpEngine::getRun()
{ return runState;}
void JackFruitEngine::kpEngine::init(lua_State* s)	
{		
	src->load(s);
}
void JackFruitEngine::kpEngine::setMainWindow(SDL_Window* win)
{		
	window->setWindow(win);
}
void JackFruitEngine::kpEngine::setIMainWindow(kpWindow* win)
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
	if(mode == JackFruitEngine::LUA_DEFAULT)
	{
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
				if(_event.type == SDL_WINDOWEVENT_RESIZED)
				{
					int w = _event.window.data1;
					int h = _event.window.data2; 
					window->resize(w, h);
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
	else if(mode == JackFruitEngine::LUA_CUSTUM)
	{
		src->load(s);
	}
	else if (mode == JackFruitEngine::CPP_WINDOWED)
	{
		while(runState == 0 || runState != 2)
		{
			while(SDL_PollEvent(&_event))
			{
				if(_event.type == SDL_QUIT)
				{
					runState = 2;
				}
				if(_event.type == SDL_WINDOWEVENT_RESIZED)
				{
					int w = _event.window.data1;
					int h = _event.window.data2; 
					window->resize(w, h);
				}
				if(game)
				{
					game->onEvent(_event);
				}
			}
			//onUpdate function: use to update engine from script
			update();
			//onRender function: use to do all drawing to the screen from script
			window->RTT();
			if(game)
			{
				getRenderer()->onRender(game, (float)getTimer()->ticks());
			}
			window->RTS();
		}
		if(game)
		{
			game->onDestroy();
		}
	}
	return error;
}
int JackFruitEngine::kpEngine::execute(lua_State* s, kpGame* game, int mode)
{
	int error = 0;
	if(mode == JackFruitEngine::CPP_DEFAULT)
	{
		if(!game->init(s))
			return error++;

		while(runState == 0 || runState != 2)
		{
			while(SDL_PollEvent(&_event))
			{
				if(_event.type == SDL_QUIT)
				{
					runState = 2;
				}				
				if(_event.type == SDL_WINDOWEVENT_RESIZED)
				{
					int w = _event.window.data1;
					int h = _event.window.data2; 
					window->resize(w, h);
				}
				game->onEvent(_event);
			}
			update();
			game->render(getRenderer());
		}
		game->onDestroy();
	}
	else if(mode == JackFruitEngine::CPP_CUSTUM)
	{
	}
	
	return error;
}
void JackFruitEngine::kpEngine::update()
{
	if(!getTimer()->started())
	{
		getTimer()->start();
	}
	if(game)
	{
		int prv = getTimer()->ticks();
		float dt = (getTimer()->ticks() - prv)/1000;
		window->update(dt);
		game->update(dt);
	}
}
JackFruitEngine::kpTimer* JackFruitEngine::kpEngine::getTimer()
{
	if(!timer)
	{
		timer = new kpTimer();
	}
	return timer;
}
JackFruitEngine::kpRenderEngine* JackFruitEngine::kpEngine::getRenderer()
{
	if(!renEng)
	{
		renEng = new kpRenderEngine(window);
	}
	return renEng;
}
JackFruitEngine::kpGame* JackFruitEngine::kpEngine::getGame()
{
	return game;
}
void JackFruitEngine::kpEngine::setGame(kpGame* games)
{
	game = games;
}
void JackFruitEngine::kpEngine::setRenderEngine(kpRenderEngine* _renEng)
{
	renEng = _renEng;
}