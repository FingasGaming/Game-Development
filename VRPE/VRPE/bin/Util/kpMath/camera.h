#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>
#include "matrices.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "kpVector3f.h"

namespace JackFruitEngine
{

	class JFE_API camera
	{
		kpVector3f loc;
		float camPitch,camYaw;
		float movevel;
		float mousevel;
		bool mi,ismoved;
		void lockCamera();
		void moveCamera(float dir);
		void moveCameraUp(float dir);
		public:
			camera();
			camera(kpVector3f loc);
			camera(kpVector3f loc,float yaw,float pitch);
			camera(kpVector3f loc,float yaw,float pitch,float mv,float mov);
			void Control(SDL_Window* parent, kpMatrices& pipeline);
			void UpdateCamera(kpMatrices& pipeline);
			kpVector3f getVector();
			kpVector3f getLocation();
			float getPitch();
			float getYaw();
			float getMovevel();
			float getMousevel();
			bool isMouseIn();
		
			void setLocation(kpVector3f vec);
			void lookAt(float pitch,float yaw);
			void mouseIn(bool b);
			void setSpeed(float mv,float mov);
		
			bool isMoved();
	};
}
#endif
