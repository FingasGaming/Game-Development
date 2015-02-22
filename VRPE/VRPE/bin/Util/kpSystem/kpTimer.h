//Timer class for SDL 1.x & 2.0 integration
//created by Sebastian Allen
//Copyright 2013
#pragma once
#ifndef KPTIMER_H
#define KPTIMER_H
#include <SDL.h>

#ifndef API_EXPORTS
#define JFE_API __declspec(dllexport) 
#else
#define JFE_API __declspec(dllimport)
#endif

namespace JackFruitEngine
{

	class JFE_API kpTimer
	{
	public:
		kpTimer();
		//start timer
		void start();
		//stop timer
		void stop();
		//pause timer
		void pause();
		//unpause timer
		void unpause();
		//restart timer and return elapsed ticks
		int restart();
		//get elapsed ticks
		int ticks() const;
		//check if timer started
		bool started() const;
		//check if timer is paused
		bool paused() const;
		//delta
		float delta () const;
	private:
		int startTicks, pausedTicks;
		bool _started, _paused;
	};
}
#endif