#pragma once
#ifndef CORE_ENGINE_H
#define CORE_ENGINE_H

#ifndef API_EXPORTS
#define JFE_API __declspec(dllexport) 
#else
#define JFE_API __declspec(dllimport)
#endif

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "kpKernel.h"


#include "bin\Util\kpBase\kpGameObject.h"
namespace JackFruitEngine
{
	class JFE_API kpCore
	{
	public:
		kpCore(void);
		~kpCore(void);
	};

	class JFE_API kpApplication
	{
	private:
		kpKernel* kernel;
	public:
		kpApplication(void);
		~kpApplication(void);

		//function runs the engine as a application from other cpp projects
		int run(kpWindow* win);
		//function runs the engine as a application from cpp game class
		int run(kpGame* game, int mode);
		//function runs the engine as a application from a lua script file
		int run(const char* fileName);
		int run(const char* fileName, int mode);
	};
}
#endif