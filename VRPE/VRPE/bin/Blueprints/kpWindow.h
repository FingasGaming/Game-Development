#pragma once
#ifndef KPWINDOW_H
#define KPWINDOW_H

#include "../Util/kpBase/kpShader.h"
#include "../Util/kpBase/kpBlueprint.h"


#include "kpGame.h"

namespace JackFruitEngine
{
	class JFE_API kpWindow : public kpBlueprint
	{
	private:
		int fr;
		bool mode;
		const char* _title;
	protected:
		int width, height;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_GLContext context;
		void setupWindowInfo(SDL_Window* win);
		bool myWindowSettings(const char* path);
	public:
		kpMatrices pipeline;
		kpShader* uber;
		kpWindow();
		~kpWindow();
		virtual bool init(lua_State* l = NULL);
		virtual bool onStart(bool exe = true);
		virtual void onDestroy();
		virtual void update(float delta = 1);
		SDL_Window* getWindow();
		void setWindow(SDL_Window* win);
		void begin();
		void flip();
		SDL_Renderer* getRenderer();
		SDL_GLContext getContext();
		float getWidth(){return (float)width;}
		float getHeight(){return (float)height;}
		void resize(float w, float h);
		void RTT();
		void RTS();
	};

}
#endif