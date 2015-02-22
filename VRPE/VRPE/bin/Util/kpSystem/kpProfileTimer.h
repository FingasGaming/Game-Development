#pragma once
#ifndef KPPROFILE_H
#define KPPROFILE_H

#include "kpTimer.h"
#include <cassert>
#include <string>

#define PROFILE_ENABLE_MESH_DRAW 0
#define PROFILE_ENABLE_SHADING 0
#define PROFILE_ENABLE_VIEWPORT_1X1 0
#define PROFILE_ENABLE_TEXTURE_2X2 0

namespace JackFruitEngine
{
	class JFE_API kpProfileTimer
	{
	public:
		kpProfileTimer(): numInvocation(0), totalTime(0.0), startTime(0.0)
		{}
		void startInvocation(kpTimer* time)
		{
			startTime = time->ticks();
		}
		void stopInvocation(kpTimer* time)
		{
			if (startTime == 0)
			{
				std::cout << "Error" << std::endl;
				assert(startTime != 0);
			}
			numInvocation++;
			totalTime += (time->ticks() - startTime);
			startTime = 0.0;
		}
		double displayAndReset(std::string msg, double div = 0)
		{
			double dividen = div;

			if(dividen == 0)
			{
				dividen = numInvocation;
			}

			double time;
			if(dividen == 0)
			{
				time = 0;
			}
			else
			{
				time = ((1000.0 * totalTime)/((double)dividen));
			}
			std::cout << msg << ": " << time  << " ms"<< std::endl;
			totalTime = 0.0;
			numInvocation = 0;

			return time;
		}
	private:
		int numInvocation;
		double totalTime;
		double startTime;
	protected:
	};
}
#endif