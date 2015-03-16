#include "camera.h"

void JackFruitEngine::camera::lockCamera()
{
	if(camPitch>90)
		camPitch=90;
	if(camPitch<-90)
		camPitch=-90;
	if(camYaw<0.0)
		camYaw+=360.0;
	if(camYaw>360.0)
		camYaw-=360;
}

void JackFruitEngine::camera::moveCamera(float dir)
{
	float rad = (camYaw+dir) * M_PI/180.0;
	loc.x-=sin(rad)*movevel;
	loc.z-=cos(rad)*movevel;
}

void JackFruitEngine::camera::moveCameraUp(float dir)
{
	float rad=(camPitch+dir)*M_PI/180.0;
	loc.y+=sin(rad)*movevel;	
}

JackFruitEngine::camera::camera()
{
	camPitch=0;
	camYaw=0;
	movevel=0.2f;
	mousevel=0.2f;
	mi=ismoved=false;
}
JackFruitEngine::camera::camera(kpVector3f l)
{
	loc.change(l);
	camPitch=0;
	camYaw=0;
	movevel=0.2f;
	mousevel=0.2f;
	mi=ismoved=false;
}

JackFruitEngine::camera::camera(kpVector3f l,float yaw,float pitch)
{
	loc.change(l);
	camPitch=pitch;
	camYaw=yaw;
	movevel=0.2f;
	mousevel=0.2f;
	mi=ismoved=false;
}

JackFruitEngine::camera::camera(kpVector3f l,float yaw,float pitch,float mv,float mov)
{
	loc.change(l);
	camPitch=pitch;
	camYaw=yaw;
	movevel=mv;
	mousevel=mov;
	mi=false;
}

void JackFruitEngine::camera::Control(SDL_Window* parent, kpMatrices& pipeline)
{
	if(mi)
	{
		int MidX=320;
		int MidY=240;
		SDL_ShowCursor(SDL_DISABLE);
		int tmpx,tmpy;
		SDL_GetMouseState(&tmpx,&tmpy);
		camYaw+=mousevel*(MidX-tmpx);
		camPitch+=mousevel*(MidY-tmpy);
		lockCamera();
		SDL_WarpMouseInWindow(parent, MidX,MidY);
		const Uint8* state = SDL_GetKeyboardState(NULL);
		ismoved=false;
		if(state[SDLK_w])
		{
			ismoved=true;
			if(camPitch!=90 && camPitch!=-90)
				moveCamera(0.0);
			moveCameraUp(0.0);
		}else if(state[SDLK_s])
		{
			ismoved=true;
			if(camPitch!=90 && camPitch!=-90)
				moveCamera(180.0);
			moveCameraUp(180.0);
		}		
		if(state[SDLK_a])
		{
			ismoved=true;
			moveCamera(90.0);
		}
		else if(state[SDLK_d])
		{
			ismoved=true;
			moveCamera(270);	
		}
	}
	pipeline.matrixMode(VIEW_MATRIX);
	pipeline.rotateX(camPitch);
	pipeline.rotateY(camYaw);
	pipeline.matrixMode(MODEL_MATRIX);
}

void JackFruitEngine::camera::UpdateCamera(kpMatrices& pipeline)
{
	pipeline.matrixMode(VIEW_MATRIX);
	pipeline.translate(loc.x,loc.y,loc.z);
	pipeline.matrixMode(MODEL_MATRIX);
}

//change the spherical coordinate system to cartesian
JackFruitEngine::kpVector3f JackFruitEngine::camera::getVector()
{
	//Google->spherical to cartesian
 	return (kpVector3f(-cos(camPitch*M_PI/180.0)*sin(camYaw*M_PI/180.0),sin(camPitch*M_PI/180.0),-cos(camPitch*M_PI/180.0)*cos(camYaw*M_PI/180.0)));
}
JackFruitEngine::kpVector3f JackFruitEngine::camera::getLocation()
{
	return loc;
}

float JackFruitEngine::camera::getPitch()
{
	return camPitch;
}

float JackFruitEngine::camera::getYaw()
{
	return camYaw;
}
float JackFruitEngine::camera::getMovevel()
{
	return movevel;
}
float JackFruitEngine::camera::getMousevel()
{
	return mousevel;
}

bool JackFruitEngine::camera::isMouseIn()
{
	return mi;
}
		
void JackFruitEngine::camera::setLocation(kpVector3f vec)
{
	loc.change(vec);
}

void JackFruitEngine::camera::lookAt(float pitch,float yaw)
{
	camPitch=pitch;
	camYaw=yaw;
}

void JackFruitEngine::camera::mouseIn(bool b)
{
	mi=b;
}

void JackFruitEngine::camera::setSpeed(float mv,float mov)
{
	movevel=mv;
	mousevel=mov;
}

bool JackFruitEngine::camera::isMoved()
{
	return ismoved;
}
