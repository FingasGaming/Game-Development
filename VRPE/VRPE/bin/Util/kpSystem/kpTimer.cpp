#include "kpTimer.h"

JackFruitEngine::kpTimer::kpTimer()
	: startTicks(0), pausedTicks(0), _started(false), _paused(false)
{
	//prv = 0;
}
void JackFruitEngine::kpTimer::start()
{
	_started = true;
	_paused = false;
	startTicks = SDL_GetTicks();
}
void JackFruitEngine::kpTimer::stop()
{
	_started = false;
	_paused = false;
}
void JackFruitEngine::kpTimer::pause()
{
	if(_started && !_paused)
	{
		_paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}
void JackFruitEngine::kpTimer::unpause()
{
	if(_paused)
	{
		_paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}
int JackFruitEngine::kpTimer::restart()
{
	int elapsedTicks = ticks();
	start();
	return elapsedTicks;
}
int JackFruitEngine::kpTimer::ticks() const
{
	if(_started)
	{
		if(_paused)
		{
			return pausedTicks;
		}
		else
		{
			return SDL_GetTicks() - startTicks;
		}
	}
	return 0;
}
bool JackFruitEngine::kpTimer::started() const
{
	return _started;
}
bool JackFruitEngine::kpTimer::paused() const
{
	return _paused;
}
