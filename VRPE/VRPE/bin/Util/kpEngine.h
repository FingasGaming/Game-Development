#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "kpBase\kpScript.h"

namespace JackFruitEngine
{
	class JFE_API kpEngine
	{
		//engine class that initialise core engine sub features
	public:
		~kpEngine(void);
		//Function: destroy engine & contents
	static void destroy();
	//Function: initialise engine
	bool initialise();
	//Function: initialise graphics
	bool initialiseGraphics();
	//Function: initialise physics
	bool initialisePhysics();
	//Function: initialise sound

	//Function: initialise network

	//Function: update engine
	static void update();
	//Function: render game world
	static void draw();
	//Function: retrieve engine
	static kpEngine* getEngine();
	private:
		//variables
		static kpEngine* engine;
		//functions
		kpEngine(void);
	};
}
#endif
