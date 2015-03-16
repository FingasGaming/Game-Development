#include "kpRenderEngine.h"

//JackFruitEngine::kpCamera* JackFruitEngine::kpRenderEngine::mainCamera = NULL;
JackFruitEngine::kpRenderEngine::kpRenderEngine(kpWindow* win) : window(win)
{
	mainCamera = new kpCamera(50, win->getWidth()/win->getHeight(), 1, 1000);
	//mainCamera->GetViewProjection().initPerspective(
}


JackFruitEngine::kpRenderEngine::~kpRenderEngine(void)
{
	delete mainCamera;
}

void JackFruitEngine::kpRenderEngine::onRender(kpGame* game,float dt)
{
	window->begin();	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	kpMatrix4f mat;
	mat.identity();
	mat.initPerspective(50, window->getWidth()/window->getHeight(), 1, 1000);
	mat.transform(kpVector3f(0,0,1));
	window->uber->setUniform("CamMatrix", mat);
	//float time = dt/1000;

		//glRotatef(45, 0, 0.002*time, 0.004*time);
		//glTranslatef(0, 0.001*time, 0.00);
		glBegin( GL_QUADS );
			glVertex2f( -0.5f, -0.5f );
			glVertex2f( 0.5f, -0.5f );
			glVertex2f( 0.5f, 0.5f );
			glVertex2f( -0.5f, 0.5f );
		glEnd();

	game->render(this);

	regulateFPS(60, dt);
	window->flip();
}
