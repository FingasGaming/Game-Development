#include "kpCore.h"


JackFruitEngine::kpCore::kpCore(void)
{
}


JackFruitEngine::kpCore::~kpCore(void)
{
}

JackFruitEngine::kpApplication::kpApplication(void)
{
	kernel = new kpKernel();
}


JackFruitEngine::kpApplication::~kpApplication(void)
{
	if(kernel != NULL)
	{
		kernel->kill();
		kernel = NULL;
	}
}

int JackFruitEngine::kpApplication::run()
{
	int error = kernel->initialise();
	if(error == 0)
	{
		error = kernel->run();
	}
	return error;
}
int JackFruitEngine::kpApplication::run(const char* fileName)
{
	int error = kernel->initialise();
	if(error == 0)
	{
		error = kernel->run(fileName, 0);
	}
	return error;
}
int JackFruitEngine::kpApplication::run(const char* fileName, int mode)
{
	int error = kernel->initialise();
	if(error == 0)
	{
		error = kernel->run(fileName, mode);
	}
	return error;
}