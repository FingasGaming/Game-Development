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
		int run();
		//function runs the engine as a application from cpp game class
		//int run(kpGame game);
		//function runs the engine as a application from a lua script file
		int run(const char* fileName);
	};
}
#endif