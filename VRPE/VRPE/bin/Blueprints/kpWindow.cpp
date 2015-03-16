#include "kpWindow.h"
#include "..\Util\kpEngine.h"


JackFruitEngine::kpWindow::kpWindow() : JackFruitEngine::kpBlueprint(), mode(false), uber(NULL)
{
}


JackFruitEngine::kpWindow::~kpWindow()
{
	if(uber)
	{
		delete uber;
	}
}

bool JackFruitEngine::kpWindow::init(lua_State* l)
{
	window = loadWindowSettings("bin/config/settings.ini");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	context = SDL_GL_CreateContext(window);
	JackFruitEngine::kpEngine::setGame(new kpGame());
	return true;
}
bool JackFruitEngine::kpWindow::myWindowSettings(const char* path)
{
	INIReader* read = new INIReader(path);

	string title = "";
	title = read->Get("MAIN WINDOW", "title", "noTitle").c_str();
	width = read->GetInteger("MAIN WINDOW", "width", 300);
	height = read->GetInteger("MAIN WINDOW", "height", 200);
	mode = read->GetBoolean("MAIN WINDOW", "3dMode", false);
	fr = read->GetInteger("MAIN WINDOW", "refreshRate", 30);

	delete read;

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	glViewport(0, 0, width, height);
	pipeline.perspective(50, width/height, 1, 1000);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, width/height, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);


	_title = title.c_str();

	if(window)
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
		context = SDL_GL_CreateContext(window);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
		
		glClearColor(0.3, 0.3, 1, 1);
		//init glew
		GLenum glewInitResult;
		glewExperimental = GL_TRUE;
		glewInitResult = glewInit();

		if(GLEW_OK != glewInitResult)
		{
		//returnError += glewInitResult;
			return false;
		}
		
		#include <iostream>
		const unsigned char* t = glGetString(GL_VERSION);
		std::cout << "OpenGL Version: " << t <<"\n";

		

		return true;
	}
	return false;
}
void JackFruitEngine::kpWindow::setupWindowInfo(SDL_Window* win)
{
	if(win)
	{
		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		context = SDL_GL_CreateContext(win);
	}
}
bool JackFruitEngine::kpWindow::onStart(bool exe)
{
	return true;
}
void JackFruitEngine::kpWindow::onDestroy()
{
	if(context)
	{
		SDL_GL_DeleteContext(context);
	}
	if(renderer)
	{
		SDL_DestroyRenderer(renderer);
	}
	if(window)
	{
		SDL_DestroyWindow(window);
	}
}
void JackFruitEngine::kpWindow::update(float delta)
{
	if(uber)
	{
		pipeline.updateMatrices(uber->getProgramId());
	}
}
SDL_Window* JackFruitEngine::kpWindow::getWindow()
{
	return window;
}
void JackFruitEngine::kpWindow::setWindow(SDL_Window* win)
{
	window = win;
}
void JackFruitEngine::kpWindow::begin()
{
	if(mode == false)
	{
		SDL_RenderClear(renderer);
	}
	else
	{		
		//to be removed
		if(uber)
		{
			uber->setUniform("baseColor",kpVector3f(1, 1, 0));
			uber->useShader();
		}
	}
}
void JackFruitEngine::kpWindow::flip()
{
	if(mode == false){
		SDL_RenderPresent(renderer);
	}
	else{
		if(uber)
			uber->delShader();
		SDL_GL_SwapWindow(window);
	}
}
SDL_Renderer* JackFruitEngine::kpWindow::getRenderer(){return renderer;}
SDL_GLContext JackFruitEngine::kpWindow::getContext(){return context;}
void JackFruitEngine::kpWindow::resize(float w, float h)
{
	if(window)
	{
		if(mode)
		{
			SDL_GL_DeleteContext(context);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			width = w;
			height = h;
			window = SDL_CreateWindow(_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
			context = SDL_GL_CreateContext(window);
			glViewport(0, 0,w,h);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(50, width/height, 1, 1000);
			glMatrixMode(GL_MODELVIEW);
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			SDL_GL_DeleteContext(context);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			width = w;
			height = h;
			window = SDL_CreateWindow(_title, 100, 100, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
		}
	}
}
void JackFruitEngine::kpWindow::RTT()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//render to texture
	pipeline.matrixMode(MODEL_MATRIX);
	pipeline.loadIdentity();
	uber->useShader();
}
void JackFruitEngine::kpWindow::RTS()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pipeline.matrixMode(VIEW_MATRIX);
	pipeline.loadIdentity();
	//Render to screen

	uber->useShader();
}